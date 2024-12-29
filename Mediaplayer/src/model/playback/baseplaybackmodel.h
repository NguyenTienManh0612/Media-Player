#ifndef BASEPLAYBACKMODEL_H
#define BASEPLAYBACKMODEL_H

#include <QAbstractListModel>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <taglib/fileref.h>

// tim nhung cai property chung giua music va video de cho vao day, vi du: play status, current time, total time
class BasePlaybackModel : public QObject
{
    Q_OBJECT
    // property for displaying the duration of media
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)
    // property for displaying current position
    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)
    // property for getting current index of media
    Q_PROPERTY(int currentMediaIndex READ currentMediaIndex WRITE setCurrentMediaIndex NOTIFY currentMediaIndexChanged)
    // property for getting current state
    Q_PROPERTY(QMediaPlayer::State mediaPlayerState READ mediaPlayerState WRITE setMediaPlayerState NOTIFY mediaPlayerStateChanged)
    // set volumn
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    //Q_PROPERTY(QString currentMediaName READ currentMediaName WRITE setCurrentMediaName NOTIFY currentMediaNameChanged)

//    //for music
//    Q_PROPERTY(QString currentSongTitle READ currentSongTitle WRITE setCurrentSongTitle NOTIFY currentSongTitleChanged)
//    Q_PROPERTY(QString currentAlbumName READ currentAlbumName WRITE setCurrentAlbumName NOTIFY currentAlbumNameChanged)
//    Q_PROPERTY(QString currentArtistName READ currentArtistName WRITE setCurrentArtistName NOTIFY currentArtistNameChanged)
//    Q_PROPERTY(QUrl coverArt READ coverArt WRITE setCoverArt NOTIFY coverArtChanged)
//    Q_PROPERTY(QString currentFilePath READ currentFilePath WRITE setCurrentFilePath NOTIFY currentFilePathChanged)

public:
    BasePlaybackModel(QObject *parent = nullptr);
    int duration() const;
    int position() const;
    int currentMediaIndex() const;
    QMediaPlayer::State mediaPlayerState() const; 

    int volume() const;
    void setVolume(int volume);
public slots:
    void setDuration(int duration);
    void setPosition(int position);

    void setCurrentMediaIndex(int currentMediaIndex);
    void setMediaPlayerState(QMediaPlayer::State newMediaPlayerState);
    //QString currentMediaName() const;
    //void setCurrentMediaName(QString currentMediaName);
//    //for music
//    QString currentSongTitle() const;
//    void setCurrentSongTitle(const QString &title);

//    QString currentAlbumName() const;
//    void setCurrentAlbumName(const QString &album);

//    QString currentArtistName() const;
//    void setCurrentArtistName(const QString &artist);

//    QUrl coverArt() const;
//    void setCoverArt(const QUrl &url);
//    QString currentFilePath() const;
//    void setCurrentFilePath(QString currentFilePath);

signals:
    void durationChanged(int duration);
    void positionChanged();
    void currentMediaIndexChanged();
    void mediaPlayerStateChanged();
    void volumeChanged(int volume);   
    //void currentMediaNameChanged();

//    // for music
//    void currentSongTitleChanged();
//    void currentAlbumNameChanged();
//    void currentArtistNameChanged();
//    void coverArtChanged();
//    void currentFilePathChanged();

protected:
    int m_duration;
    int m_position;
    int m_currentMediaIndex;
    QMediaPlayer::State m_mediaPlayerState;
    int m_volume;
//    //for music
//    QString m_currentSongTitle;
//    QString m_currentAlbumName;
//    QString m_currentArtistName;
//    QUrl m_coverArt;
//    QString m_currentFilePath;
    //QString m_currentMediaName;
};

#endif // BASEPLAYBACKMODEL_H
