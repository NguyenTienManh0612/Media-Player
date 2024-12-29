#include "musicplayercontroller.h"
#include "musicplaybackmodel.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QImage>
MusicPlayerController *MusicPlayerController::m_instance = nullptr;
MusicPlayerController::MusicPlayerController(QObject *parent) : BasePlayerController(parent)
{
    //m_playbackModel = new MusicPlaybackModel(this);
    connect(&m_player, &QMediaPlayer::mediaStatusChanged,
            this, &MusicPlayerController::onMetaDataChanged);
    connect(&m_player, &QMediaPlayer::stateChanged,
            this, &MusicPlayerController::handelPlaybackStateChanged);
    //m_player.setPlaylist(&m_playlist);
    connect(&m_player, &QMediaPlayer::durationChanged, this, [](int duration) {
        MusicPlaybackModel::getInstance()->setDuration(duration);
    });

    connect(&m_player, &QMediaPlayer::positionChanged, this, [](int position) {
        MusicPlaybackModel::getInstance()->setPosition(position);
    });

    connect(&m_playlist, &QMediaPlaylist::currentIndexChanged, this, [](int idx) {
        MusicPlaybackModel::getInstance()->setCurrentMediaIndex(idx);
    });

    connect(&m_player, &QMediaPlayer::stateChanged, this, [](QMediaPlayer::State state) {
        MusicPlaybackModel::getInstance()->setMediaPlayerState(state);
    });

    connect(&m_player, &QMediaPlayer::volumeChanged, this, [](int volume) {
        MusicPlaybackModel::getInstance()->setVolume(volume);
    });
}

MusicPlayerController *MusicPlayerController::getInstance()
{
    if (m_instance == nullptr) {
        m_instance = new MusicPlayerController();
    }
    return m_instance;
}

void MusicPlayerController::initialize(QQmlContext *context)
{
    if (!m_initialized)
    {
        m_initialized = true;
        context->setContextProperty("MPLAYER_CTRL", this);
        context->setContextProperty("MPLAYBACK_MODEL", MusicPlaybackModel::getInstance());

        // connect with signal from home app
        QDBusConnection::sessionBus().connect("",
                                              "/vn/com/fsoft/home/appInterface",
                                              "vn.com.fsoft.home.appInterface",
                                              "requestChangeVolume",
                                              this, SLOT(onReceivedRequestChangeVolume(int)));

        // connect with signal from home app
        QDBusConnection::sessionBus().connect("",
                                              "/vn/com/fsoft/home/appInterface",
                                              "vn.com.fsoft.home.appInterface",
                                              "requestDisplayMusic",
                                              this, SLOT(onRequestDisplayMusicPlayer()));
    }
    loadMusicPlaylist();
    loadStateFromFile();
}
void MusicPlayerController::onReceivedRequestChangeVolume(int msg) {
    qDebug() << "Current volume: " << msg;
    m_player.setVolume(msg * 10);
}
void MusicPlayerController::handelPlaybackStateChanged(QMediaPlayer::State state)
{
       MusicPlaybackModel::getInstance()->setMediaPlayerState(state);
       saveStateToFile();
       qDebug() << __FUNCTION__ << "Current file path: " << MusicPlaybackModel::getInstance()->currentFilePath();
       qDebug() << __FUNCTION__<< "Current index: " << MusicPlaybackModel::getInstance()->currentMediaIndex();
}

void MusicPlayerController::onMetaDataChanged(QMediaPlayer::MediaStatus status)
{
    qDebug() << "STATUS" << status;
    if (status == QMediaPlayer::LoadedMedia || status == QMediaPlayer::BufferedMedia) {
        //QString currentMediaPath = m_playlist.currentMedia().request().url().toLocalFile();
        //QVariantMap metaData = MusicListController::getInstance()->metaDataContainer(currentMediaPath.toStdString().c_str());
        QVariantMap metaData = MusicListController::getInstance()->getMetaDataCurrSong(MusicPlaybackModel::getInstance()->currentFilePath());
        MusicPlaybackModel::getInstance()->setCurrentSongTitle(metaData["title"].toString());
        MusicPlaybackModel::getInstance()->setCurrentAlbumName(metaData["album"].toString());
        MusicPlaybackModel::getInstance()->setCurrentArtistName(metaData["artist"].toString());
        MusicPlaybackModel::getInstance()->setCurrentFilePath(metaData["filePath"].toString());
        MusicPlaybackModel::getInstance()->setCurrentMusicLength(metaData["time"].toString());

        // Handle cover art
        QString coverArt = metaData["coverArt"].toString();
        if (coverArt.isEmpty()) {
            // Path to default cover art
            coverArt = "qrc:/images/default-coverArt.png";
        }
        MusicPlaybackModel::getInstance()->setCoverArt(QUrl(coverArt));
        qDebug() << __FUNCTION__ << metaData;
    }
//    if (status == QMediaPlayer::EndOfMedia)
//    {
//        mnext();
//    }
}

void MusicPlayerController::onRequestDisplayMusicPlayer()
{
    qDebug() << __FUNCTION__ << "test pause video";
    //stop current media if playing video
        VideoPlaybackModel::getInstance()->setVideoPlayerState(QMediaPlayer::StoppedState);
        //m_Vplayer.stop();
}

void MusicPlayerController::requestSendMetaData()
{
    // 1. create a dbus signal
        QDBusMessage msg = QDBusMessage::createSignal(
                    "/vn/com/fsoft/media/mediaInterface",
                    "vn.com.fsoft.media.mediaInterface",
                    "requestSendMetaData"      // signal name
                    );
        // 2. append input arguments
        msg << MusicPlaybackModel::getInstance()->currentSongTitle() << MusicPlaybackModel::getInstance()->currentArtistName()
            << MusicPlaybackModel::getInstance()->coverArt().toString();// << m_playbackModel->videoName();

        // 3. broadcast signal (using session)
        QDBusConnection::sessionBus().send(msg);
}
void MusicPlayerController::saveStateToFile() {
    QJsonObject state;
    state["currentFilePath"] = MusicPlaybackModel::getInstance()->currentFilePath();
    state["currentSongTitle"] = MusicPlaybackModel::getInstance()->currentSongTitle();
    state["currentAlbumName"] = MusicPlaybackModel::getInstance()->currentAlbumName();
    state["currentArtistName"] = MusicPlaybackModel::getInstance()->currentArtistName();
    state["currentMusicLength"] = MusicPlaybackModel::getInstance()->currentMusicLength();
    state["coverArt"] = MusicPlaybackModel::getInstance()->coverArt().toString();
    state["position"] = MusicPlaybackModel::getInstance()->position();
    state["volume"] = MusicPlaybackModel::getInstance()->volume();

    QJsonDocument doc(state);
    QString filePath = "MusicPlayerState.json";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
        qDebug() << "State saved to" << filePath;
    } else {
        qWarning() << "Couldn't open file to save state.";
    }
}

void MusicPlayerController::loadStateFromFile() {
    QString filePath = "MusicPlayerState.json";
    QFile file(filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc(QJsonDocument::fromJson(data));
        QJsonObject state = doc.object();

        MusicPlaybackModel::getInstance()->setCurrentFilePath(state["currentFilePath"].toString());
        MusicPlaybackModel::getInstance()->setCurrentSongTitle(state["currentSongTitle"].toString());
        MusicPlaybackModel::getInstance()->setCurrentAlbumName(state["currentAlbumName"].toString());
        MusicPlaybackModel::getInstance()->setCurrentArtistName(state["currentArtistName"].toString());
        MusicPlaybackModel::getInstance()->setCurrentMusicLength(state["currentMusicLength"].toString());
        MusicPlaybackModel::getInstance()->setCoverArt(QUrl(state["coverArt"].toString()));
        MusicPlaybackModel::getInstance()->setPosition(state["position"].toInt());
        MusicPlaybackModel::getInstance()->setVolume(state["volume"].toInt());
        qDebug() << "State loaded from" << filePath;
    } else {
        qWarning() << "Couldn't open file to load state.";
    }
}
