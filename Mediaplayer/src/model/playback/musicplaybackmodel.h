#ifndef MUSICPLAYERMODEL_H
#define MUSICPLAYERMODEL_H

#include <QObject>
#include "baseplaybackmodel.h"
// handle properties display on music: current song title, current album name, current artist name, coverart
class MusicPlaybackModel : public BasePlaybackModel
{
    Q_OBJECT
    Q_PROPERTY(QString currentSongTitle READ currentSongTitle WRITE setCurrentSongTitle NOTIFY currentSongTitleChanged)
    Q_PROPERTY(QString currentAlbumName READ currentAlbumName WRITE setCurrentAlbumName NOTIFY currentAlbumNameChanged)
    Q_PROPERTY(QString currentArtistName READ currentArtistName WRITE setCurrentArtistName NOTIFY currentArtistNameChanged)
    Q_PROPERTY(QUrl coverArt READ coverArt WRITE setCoverArt NOTIFY coverArtChanged)
    Q_PROPERTY(QString currentFilePath READ currentFilePath WRITE setCurrentFilePath NOTIFY currentFilePathChanged)
    Q_PROPERTY(QString currentMusicLength READ currentMusicLength WRITE setCurrentMusicLength NOTIFY currentMusicLengthChanged)
    // Property for storing metadata of the current track
    //Q_PROPERTY(QVariantMap currentTrackMetadata READ currentTrackMetadata WRITE setCurrentTrackMetadata NOTIFY currentTrackMetadataChanged)

public:
    MusicPlaybackModel(QObject *parent = nullptr);

    //QVariantMap currentTrackMetadata() const;
    //void setCurrentTrackMetadata(const QVariantMap &metadata);
    static MusicPlaybackModel *getInstance();
    QString currentSongTitle() const;


    QString currentAlbumName() const;


    QString currentArtistName() const;


    QUrl coverArt() const;

    QString currentFilePath() const;

    QString currentMusicLength() const;

public slots:
    void setCurrentFilePath(QString currentFilePath);
    void setCoverArt(const QUrl &url);
    void setCurrentArtistName(const QString &artist);
    void setCurrentAlbumName(const QString &album);
    void setCurrentSongTitle(const QString &title);
    void setCurrentMusicLength(QString currentMusicLength);

signals:
    void currentSongTitleChanged();
    void currentAlbumNameChanged();
    void currentArtistNameChanged();
    void coverArtChanged();
    void currentFilePathChanged();

    void currentMusicLengthChanged(QString currentMusicLength);

private:
    QString m_currentSongTitle;
    QString m_currentAlbumName;
    QString m_currentArtistName;
    QUrl m_coverArt;
    QString m_currentFilePath;
    static MusicPlaybackModel *instance;
    QString m_currentMusicLength;
};

#endif // MUSICPLAYERMODEL_H
