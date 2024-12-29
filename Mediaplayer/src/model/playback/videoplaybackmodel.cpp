#include "videoplaybackmodel.h"
#include "videolistcontroller.h"
VideoPlaybackModel *VideoPlaybackModel::instance = nullptr;
VideoPlaybackModel::VideoPlaybackModel(QObject *parent)
    : BasePlaybackModel(parent)
    , m_currentFilePath(VideoListController::m_ListVModel.listVideos().isEmpty()? "" : VideoListController::m_ListVModel.listVideos().first().toMap().value("filePath").toString())
    , m_currentVideoName("")
    , m_currentVideoIndex(-1)
    , m_videoPlayerState(QMediaPlayer::StoppedState)
{}

VideoPlaybackModel *VideoPlaybackModel::getInstance()
{
    if(instance == nullptr)
        instance = new VideoPlaybackModel();
    return instance;
}

QString VideoPlaybackModel::currentFilePath() const
{
    return m_currentFilePath;
}

void VideoPlaybackModel::setCurrentFilePath(QString currentFilePath)
{
    if (m_currentFilePath == currentFilePath)
        return;
    m_currentFilePath = currentFilePath;
    for (int i = 0; i < VideoListController::m_ListVModel.listVideos().size(); ++i) {
        QVariantMap video = VideoListController::m_ListVModel.listVideos()[i].toMap();
        if (video.value("filePath").toString() == currentFilePath) {
            m_currentVideoIndex = i;
            break;
        }
    }
    qDebug() << __FUNCTION__ << m_currentFilePath << m_currentVideoIndex;

    emit currentVideoIndex();
    emit currentFilePathChanged();
}

QString VideoPlaybackModel::currentVideoName() const
{
    return m_currentVideoName;
}

void VideoPlaybackModel::setCurrentVideoName(QString currentVideoName)
{
    m_currentVideoName = currentVideoName;
}

int VideoPlaybackModel::currentVideoIndex() const
{
    return m_currentVideoIndex;
}

QMediaPlayer::State VideoPlaybackModel::videoPlayerState() const
{
    return m_videoPlayerState;
}

void VideoPlaybackModel::setCurrentVideoIndex(int currentVideoIndex)
{
    if (m_currentVideoIndex == currentVideoIndex)
        return;

    m_currentVideoIndex = currentVideoIndex;
    emit currentVideoIndexChanged();
}

void VideoPlaybackModel::setVideoPlayerState(QMediaPlayer::State videoPlayerState)
{
    if (m_videoPlayerState == videoPlayerState)
        return;

    m_videoPlayerState = videoPlayerState;
    if (duration() != 0) {
        emit durationChanged(duration());
    }
    emit videoPlayerStateChanged();
}
