#include "baseplayercontroller.h"
#include "musiclistcontroller.h"
#include "videolistcontroller.h"
#include "loghelper.h"
//auto musicPlaybackModel = MusicPlaybackModel::getInstance();
BasePlayerController::BasePlayerController(QObject *parent)
    : QObject(parent), m_initialized(false)
{
}
BasePlayerController::~BasePlayerController()
{
    //delete m_playbackMModel;
}

void BasePlayerController::mplaypause()
{ 
    if(MusicPlaybackModel::getInstance()->currentFilePath() == "")
    {
        LOG_INFO << "List empty";
        return;
    }

    if(MusicPlaybackModel::getInstance()->mediaPlayerState() == QMediaPlayer::StoppedState)
    {
        m_player.setMedia(QUrl::fromLocalFile(MusicPlaybackModel::getInstance()->currentFilePath()));
        m_player.play();
    } else if(MusicPlaybackModel::getInstance()->mediaPlayerState() == QMediaPlayer::PlayingState){
        m_player.pause();
    }else if (MusicPlaybackModel::getInstance()->mediaPlayerState() == QMediaPlayer::PausedState)
    {
        m_player.play();
    }
    //qDebug() <<  m_playlist.currentMedia().request().url() << "<-- Current Media";
    qDebug() << m_player.currentMedia().request().url() << "<-- Current Media";
    qDebug() << m_player.position()/1000 << "<-- Current position";
}

void BasePlayerController::mnext()
{
    if(MusicPlaybackModel::getInstance()->currentFilePath() == "")
    {
        LOG_INFO << "List empty";
        return;
    }

    if(MusicListController::m_ListModel.listSongs().count() - 1 == MusicPlaybackModel::getInstance()->currentMediaIndex()){
        //current index in last -> set current name is first
        MusicPlaybackModel::getInstance()->setCurrentFilePath(MusicListController::m_ListModel.listSongs().first().toMap().value("filePath").toString());
    }else {
        //set current name in next index
        qDebug() << "Current index: " << MusicPlaybackModel::getInstance()->currentMediaIndex();
        MusicPlaybackModel::getInstance()->setCurrentFilePath(MusicListController::m_ListModel.listSongs()
                                            .at(MusicPlaybackModel::getInstance()->currentMediaIndex() + 1).toMap().value("filePath").toString());
    }
    //stop current media and request play next media
    MusicPlaybackModel::getInstance()->setMediaPlayerState(QMediaPlayer::StoppedState);
    mplaypause();
//    int nextIndex = (m_playlist.currentIndex() + 1) % m_playlist.mediaCount();
//    m_playlist.setCurrentIndex(nextIndex);
//    play(m_playlist.currentMedia().request().url().toLocalFile());
    qDebug() <<  m_player.currentMedia().request().url() << "<-- Current Media";
}

void BasePlayerController::mprevious()
{
    if(MusicPlaybackModel::getInstance()->currentFilePath() == ""){
        LOG_INFO << "List empty";
        return;
    }


    if(MusicPlaybackModel::getInstance()->currentMediaIndex() == 0){
        // current index in first -> set current name is last
        MusicPlaybackModel::getInstance()->setCurrentFilePath(MusicListController::m_ListModel.listSongs().last().toMap().value("filePath").toString());
    }else{
        //set current name in previous index
        qDebug() << "Current index: " << MusicPlaybackModel::getInstance()->currentMediaIndex();
        MusicPlaybackModel::getInstance()->setCurrentFilePath(MusicListController::m_ListModel.listSongs()
                                            .at(MusicPlaybackModel::getInstance()->currentMediaIndex() - 1).toMap().value("filePath").toString());
    }
    //stop vurrent media and request play next media
    MusicPlaybackModel::getInstance()->setMediaPlayerState(QMediaPlayer::StoppedState);
    mplaypause();
//    int previousIndex = (m_playlist.currentIndex() - 1 + m_playlist.mediaCount()) % m_playlist.mediaCount();
//    m_playlist.setCurrentIndex(previousIndex);
//    play(m_playlist.currentMedia().request().url().toLocalFile());
}

void BasePlayerController::setMediaPosition(const int position)
{
    return m_player.setPosition(position);
}

void BasePlayerController::loadMusicPlaylist()
{
    auto musicListController = MusicListController::getInstance();
    QStringList filePaths = musicListController->getMusicFilePaths();
    //qDebug() << __FUNCTION__ << filePaths;
//    for (const QString &filePath : filePaths) {
//        m_playlist.addMedia(QUrl::fromLocalFile(filePath));
//    }
    //QVariant song = musicListController->m_ListModel.listSongs();
    if(MusicListController::m_ListModel.listSongs().isEmpty()) {
        return;
    }
    else {
        QVariantMap firstSong = musicListController->m_ListModel.listSongs().first().toMap();
        //QString firstSong = musicListController->m_ListModel.listSongs().first().toMap().value("filePath").toString();
        MusicPlaybackModel::getInstance()->setCurrentFilePath(musicListController->m_ListModel.listSongs().first().toMap().value("filePath").toString());
        MusicPlaybackModel::getInstance()->setCurrentAlbumName(firstSong["album"].toString());
        MusicPlaybackModel::getInstance()->setCurrentSongTitle(firstSong["title"].toString());
        MusicPlaybackModel::getInstance()->setCurrentArtistName(firstSong["artist"].toString());
        QString coverArt = firstSong["coverArt"].toString();
        if (coverArt.isEmpty()) {
            // Path to default cover art
            coverArt = "qrc:/images/default-coverArt.png";
        }
        MusicPlaybackModel::getInstance()->setCoverArt(QUrl(coverArt));
        MusicPlaybackModel::getInstance()->setCurrentMusicLength(firstSong["time"].toString());
    }
    //m_playlist.setCurrentIndex(0);
    //m_player.setPlaylist(&m_playlist);
    //qDebug() << __FUNCTION__ << m_playlist.isEmpty();
}


