#include "musicplaybackmodel.h"
#include "musiclistcontroller.h"
MusicPlaybackModel *MusicPlaybackModel::instance = nullptr;
MusicPlaybackModel::MusicPlaybackModel(QObject *parent)
    : BasePlaybackModel(parent)
    ,m_currentSongTitle("")
    ,m_currentAlbumName("")
    ,m_currentArtistName("")
    ,m_currentFilePath(MusicListController::m_ListModel.listSongs().isEmpty()? "" : MusicListController::m_ListModel.listSongs().first().toMap().value("filePath").toString())
{}

MusicPlaybackModel *MusicPlaybackModel::getInstance()
{
    if(instance == nullptr)
        instance = new MusicPlaybackModel();
    return instance;
}

QString MusicPlaybackModel::currentSongTitle() const {
    return m_currentSongTitle;
}

void MusicPlaybackModel::setCurrentSongTitle(const QString &title) {
    if (m_currentSongTitle != title) {
        m_currentSongTitle = title;
        emit currentSongTitleChanged();
    }
}

void MusicPlaybackModel::setCurrentMusicLength(QString currentMusicLength)
{
    if (m_currentMusicLength == currentMusicLength)
        return;

    m_currentMusicLength = currentMusicLength;
    emit currentMusicLengthChanged(m_currentMusicLength);
}

QString MusicPlaybackModel::currentAlbumName() const {
    return m_currentAlbumName;
}

void MusicPlaybackModel::setCurrentAlbumName(const QString &album) {
    if (m_currentAlbumName != album) {
        m_currentAlbumName = album;
        emit currentAlbumNameChanged();
    }
}

QString MusicPlaybackModel::currentArtistName() const {
    return m_currentArtistName;
}

void MusicPlaybackModel::setCurrentArtistName(const QString &artist) {
    if (m_currentArtistName != artist) {
        m_currentArtistName = artist;
        emit currentArtistNameChanged();
    }
}

QUrl MusicPlaybackModel::coverArt() const {
    return m_coverArt;
}

void MusicPlaybackModel::setCoverArt(const QUrl &url) {
    if (m_coverArt != url) {
        m_coverArt = url;
        emit coverArtChanged();
    }
}

QString MusicPlaybackModel::currentFilePath() const
{
    return m_currentFilePath;
}

QString MusicPlaybackModel::currentMusicLength() const
{
    return m_currentMusicLength;
}

void MusicPlaybackModel::setCurrentFilePath(QString currentFilePath)
{
    if (m_currentFilePath == currentFilePath)
        return;

    m_currentFilePath = currentFilePath;
    for (int i = 0; i < MusicListController::m_ListModel.listSongs().size(); ++i) {
        QVariantMap song = MusicListController::m_ListModel.listSongs()[i].toMap();
        if (song.value("filePath").toString() == currentFilePath) {
            m_currentMediaIndex = i;
            break;
        }
    }
    qDebug() << __FUNCTION__ << m_currentFilePath << m_currentMediaIndex;
    emit currentMediaIndex();
    emit currentFilePathChanged();
}
