#include "videoplayercontroller.h"
#include "videoplaybackmodel.h"
#include "loghelper.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
VideoPlayerController *VideoPlayerController::m_instance = nullptr;
VideoPlayerController::VideoPlayerController(QObject *parent) : BasePlayerController(parent), m_isFullScreenVideo(false)
{
    connect(&m_Vplayer, &QMediaPlayer::mediaStatusChanged,
            this, &VideoPlayerController::onMetaDataChanged);
    connect(&m_Vplayer, &QMediaPlayer::stateChanged,
            this, &VideoPlayerController::handelPlaybackStateChanged);
    connect(&m_Vplayer, &QMediaPlayer::durationChanged, this, [](int duration) {
        VideoPlaybackModel::getInstance()->setDuration(duration);
    });

    connect(&m_Vplayer, &QMediaPlayer::positionChanged, this, [](int position) {
        VideoPlaybackModel::getInstance()->setPosition(position);
    });

    connect(&m_Vplaylist, &QMediaPlaylist::currentIndexChanged, this, [](int idx) {
        VideoPlaybackModel::getInstance()->setCurrentVideoIndex(idx);
    });

    connect(&m_Vplayer, &QMediaPlayer::stateChanged, this, [](QMediaPlayer::State state) {
        VideoPlaybackModel::getInstance()->setVideoPlayerState(state);
    });

    connect(&m_Vplayer, &QMediaPlayer::volumeChanged, this, [](int volume) {
        VideoPlaybackModel::getInstance()->setVolume(volume);
    });
}

VideoPlayerController::~VideoPlayerController()
{
    m_videoSurface = nullptr;
    //m_playbackModel = nullptr;
}

VideoPlayerController *VideoPlayerController::getInstance()
{
    if (m_instance == nullptr) {
        m_instance = new VideoPlayerController();
    }
    return m_instance;
}

void VideoPlayerController::initialize(QQmlContext *context)
{
    if (!m_initialized)
    {
        m_initialized = true;
        context->setContextProperty("VPLAYER_CTRL", this);
        context->setContextProperty("VPLAYBACK_MODEL", VideoPlaybackModel::getInstance());

        // connect with signal from home app
        QDBusConnection::sessionBus().connect("",
                                              "/vn/com/fsoft/home/appInterface",
                                              "vn.com.fsoft.home.appInterface",
                                              "requestChangeVolume",
                                              this, SLOT(onReceivedRequestChangeVolume(int)));
        //handel if state Player change

    //        QObject::connect(&m_player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
    //                         this, SLOT(onMediaStatuschanged(QMediaPlayer::MediaStatus)));

        // connect with signal from home app
        QDBusConnection::sessionBus().connect("",
                                              "/vn/com/fsoft/home/appInterface",
                                              "vn.com.fsoft.home.appInterface",
                                              "requestDisplayVideo",
                                              this, SLOT(onRequestDisplayVideoPlayer()));
    }
    loadVideoPlaylist();
    loadStateFromFile();
}

void VideoPlayerController::vplaypause()
{
    if(VideoPlaybackModel::getInstance()->currentFilePath() == "")
    {
        LOG_INFO << "List empty";
        return;
    }

    if(VideoPlaybackModel::getInstance()->videoPlayerState() == QMediaPlayer::StoppedState)
    {
        m_Vplayer.setMedia(QUrl::fromLocalFile(VideoPlaybackModel::getInstance()->currentFilePath()));
        m_Vplayer.play();
    } else if(VideoPlaybackModel::getInstance()->videoPlayerState() == QMediaPlayer::PlayingState){
        m_Vplayer.pause();
    }else if (VideoPlaybackModel::getInstance()->videoPlayerState() == QMediaPlayer::PausedState)
    {
        m_Vplayer.play();
    }
    //qDebug() <<  m_playlist.currentMedia().request().url() << "<-- Current Media";
    qDebug() << m_Vplayer.currentMedia().request().url() << "<-- Current Media";
    qDebug() << m_Vplayer.position()/1000 << "<-- Current position";
}

void VideoPlayerController::vnext()
{
    if(VideoPlaybackModel::getInstance()->currentFilePath() == "")
    {
        LOG_INFO << "List empty";
        return;
    }

    if(VideoListController::m_ListVModel.listVideos().count() - 1 == VideoPlaybackModel::getInstance()->currentVideoIndex()){
        //current index in last -> set current name is first
        VideoPlaybackModel::getInstance()->setCurrentFilePath(VideoListController::m_ListVModel.listVideos().first().toMap().value("filePath").toString());
        qDebug() << __FUNCTION__ << VideoListController::m_ListVModel.listVideos().first().toMap().value("filePath").toString();
    }else {
        //set current name in next index
        qDebug() << "Current index: " << VideoPlaybackModel::getInstance()->currentVideoIndex();
        VideoPlaybackModel::getInstance()->setCurrentFilePath(VideoListController::m_ListVModel.listVideos()
                                            .at(VideoPlaybackModel::getInstance()->currentVideoIndex() + 1).toMap().value("filePath").toString());
    }
    //stop current media and request play next media
    VideoPlaybackModel::getInstance()->setVideoPlayerState(QMediaPlayer::StoppedState);
    vplaypause();
//    int nextIndex = (m_playlist.currentIndex() + 1) % m_playlist.mediaCount();
//    m_playlist.setCurrentIndex(nextIndex);
//    play(m_playlist.currentMedia().request().url().toLocalFile());
    qDebug() <<  m_Vplayer.currentMedia().request().url() << "<-- Current Media";
}

void VideoPlayerController::vprevious()
{
    if(VideoPlaybackModel::getInstance()->currentFilePath() == ""){
        LOG_INFO << "List empty";
        return;
    }

    if(VideoPlaybackModel::getInstance()->currentVideoIndex() == 0){
        // current index in first -> set current name is last
        VideoPlaybackModel::getInstance()->setCurrentFilePath(VideoListController::m_ListVModel.listVideos().last().toMap().value("filePath").toString());
    }else{
        //set current name in previous index
        qDebug() << "Current index: " << VideoPlaybackModel::getInstance()->currentVideoIndex();
        VideoPlaybackModel::getInstance()->setCurrentFilePath(VideoListController::m_ListVModel.listVideos()
                                                              .at(VideoPlaybackModel::getInstance()->currentVideoIndex() - 1).toMap().value("filePath").toString());
    }
    //stop vurrent media and request play next media
    VideoPlaybackModel::getInstance()->setVideoPlayerState(QMediaPlayer::StoppedState);
    vplaypause();
}
void VideoPlayerController::onReceivedRequestChangeVolume(int msg) {
    qDebug() << "Current volume: " << msg;
    m_Vplayer.setVolume(msg * 10);
}
void VideoPlayerController::handelPlaybackStateChanged(QMediaPlayer::State state)
{
       VideoPlaybackModel::getInstance()->setVideoPlayerState(state);
       saveStateToFile();
       qDebug() << __FUNCTION__ << "Current file path: " << VideoPlaybackModel::getInstance()->currentFilePath();
       qDebug() << __FUNCTION__<< "Current index: " << VideoPlaybackModel::getInstance()->currentVideoIndex();
}
void VideoPlayerController::loadVideoPlaylist()
{
    auto videoListController = VideoListController::getInstance();
    QStringList filePaths = videoListController->getVideoFilePaths();
    //qDebug() << __FUNCTION__ << filePaths;
    if(VideoListController::m_ListVModel.listVideos().isEmpty()) {
        return;
    }
    else {
        QVariantMap firstVideo = videoListController->m_ListVModel.listVideos().first().toMap();
        VideoPlaybackModel::getInstance()->setCurrentFilePath(videoListController->m_ListVModel.listVideos().first().toMap().value("filePath").toString());
        VideoPlaybackModel::getInstance()->setCurrentVideoName(firstVideo["name"].toString());
        //MusicPlaybackModel::getInstance()->setDuration(firstSong["length"].toInt());
    }
}
void VideoPlayerController::setIsFullScreenVideo(bool newIsFullScreen)
{
    if(m_isFullScreenVideo == newIsFullScreen)
        return;

    m_isFullScreenVideo = newIsFullScreen;
    emit isFullScreenVideoChanged();
}

void VideoPlayerController::setVideoSurface(QAbstractVideoSurface *videoSurface)
{
    if (m_videoSurface == videoSurface)
        return;

    m_videoSurface = videoSurface;
    m_Vplayer.setVideoOutput(m_videoSurface);
    emit videoSurfaceChanged();
}

bool VideoPlayerController::isFullScreenVideo() const
{
    return m_isFullScreenVideo;
}

void VideoPlayerController::onMetaDataChanged(QMediaPlayer::MediaStatus status)
{
    qDebug() << "STATUS" << status;
    if (status == QMediaPlayer::LoadedMedia || status == QMediaPlayer::BufferedMedia) {
        //QString currentMediaPath = m_playlist.currentMedia().request().url().toLocalFile();
        QVariantMap metaData = VideoListController::getInstance()->getMetaDataCurrVideo(VideoPlaybackModel::getInstance()->currentFilePath());
        //QVariantMap metaData = VideoListController::getInstance()->getMetaDataCurrVideo(currentMediaPath);
        VideoPlaybackModel::getInstance()->setCurrentFilePath(metaData["filePath"].toString());
        VideoPlaybackModel::getInstance()->setCurrentVideoName(metaData["name"].toString());
        //qDebug() << __FUNCTION__ << metaData;
    }
    saveStateToFile();
}

void VideoPlayerController::onRequestDisplayVideoPlayer()
{
    //stop current media if playing music
    qDebug() << __FUNCTION__ << "Stop music to play video";
    MusicPlaybackModel::getInstance()->setMediaPlayerState(QMediaPlayer::StoppedState);
    m_player.pause();
}

void VideoPlayerController::requestSendMetaData()
{
    // 1. create a dbus signal
        QDBusMessage msg = QDBusMessage::createSignal(
                    "/vn/com/fsoft/media/mediaInterface",
                    "vn.com.fsoft.media.mediaInterface",
                    "requestSendMetaDataVideo"      // signal name
                    );
        // 2. append input arguments
        msg <<  VideoPlaybackModel::getInstance()->currentVideoName();

        // 3. broadcast signal (using session)
        QDBusConnection::sessionBus().send(msg);
}

QAbstractVideoSurface *VideoPlayerController::videoSurface() const
{
    return m_videoSurface;
}

void VideoPlayerController::saveStateToFile() {
    QJsonObject state;
    state["currentFilePath"] = VideoPlaybackModel::getInstance()->currentFilePath();
    state["videoName"] = VideoPlaybackModel::getInstance()->currentVideoName();
    state["position"] = VideoPlaybackModel::getInstance()->position();
    state["volume"] = VideoPlaybackModel::getInstance()->volume();
    QJsonDocument doc(state);
    QString filePath = "VideoPlayerState.json";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
        qDebug() << "State saved to" << filePath;
    } else {
        qWarning() << "Couldn't open file to save state.";
    }
}

void VideoPlayerController::loadStateFromFile() {
    QString filePath = "VideoPlayerState.json";
    QFile file(filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc(QJsonDocument::fromJson(data));
        QJsonObject state = doc.object();

        VideoPlaybackModel::getInstance()->setCurrentFilePath(state["currentFilePath"].toString());
        VideoPlaybackModel::getInstance()->setCurrentVideoName(state["videoName"].toString());
        VideoPlaybackModel::getInstance()->setPosition(state["position"].toInt());
        VideoPlaybackModel::getInstance()->setVolume(state["volume"].toInt());
        qDebug() << "State loaded from" << filePath;
    } else {
        qWarning() << "Couldn't open file to load state.";
    }
}
