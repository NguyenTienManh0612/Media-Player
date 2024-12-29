#include "baseplaybackmodel.h"
#include "musiclistcontroller.h"
BasePlaybackModel::BasePlaybackModel(QObject *parent)
    : QObject(parent), m_duration(0), m_position(0), m_currentMediaIndex(-1), m_mediaPlayerState(QMediaPlayer::StoppedState)
      //m_currentMediaName(MusicListController::getListModel().listSong().isEmpty()?"":MusicListController::getListModel().listSong().first()),
{

}

int BasePlaybackModel::duration() const
{
    return m_duration;
}

int BasePlaybackModel::position() const
{
    return m_position;
}

int BasePlaybackModel::currentMediaIndex() const
{
    return m_currentMediaIndex;
}

QMediaPlayer::State BasePlaybackModel::mediaPlayerState() const
{
    return m_mediaPlayerState;
}

void BasePlaybackModel::setDuration(int duration)
{
    if (m_duration == duration)
        return;

    m_duration = duration;
    emit durationChanged(duration);
}

void BasePlaybackModel::setPosition(int position)
{
    if (m_position == position)
        return;

    m_position = position;
    emit positionChanged();
}

void BasePlaybackModel::setCurrentMediaIndex(int currentMediaIdx)
{
    if (m_currentMediaIndex == currentMediaIdx)
        return;

    m_currentMediaIndex = currentMediaIdx;
    emit currentMediaIndexChanged();
}

void BasePlaybackModel::setMediaPlayerState(QMediaPlayer::State newMediaPlayerState)
{
    if (m_mediaPlayerState == newMediaPlayerState)
        return;

    m_mediaPlayerState = newMediaPlayerState;
    if (duration() != 0) {
        emit durationChanged(duration());
    }
    emit mediaPlayerStateChanged();
}

int BasePlaybackModel::volume() const
{
    return m_volume;
}

void BasePlaybackModel::setVolume(int volume)
{
    if (m_volume == volume)
        return;

    m_volume = volume;
    emit volumeChanged(m_volume);
}
