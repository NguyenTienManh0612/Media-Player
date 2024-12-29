#ifndef VIDEOPLAYBACKMODEL_H
#define VIDEOPLAYBACKMODEL_H

#include "baseplaybackmodel.h"

// handle properties for usb video playback screen,ex: file name, full screen status
class VideoPlaybackModel : public BasePlaybackModel
{
    Q_OBJECT
    Q_PROPERTY(QString currentFilePath READ currentFilePath WRITE setCurrentFilePath NOTIFY currentFilePathChanged)
    Q_PROPERTY(QString currentVideoName READ currentVideoName WRITE setCurrentVideoName NOTIFY currentVideoNameChanged)
    //Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)
    //Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(int currentVideoIndex READ currentVideoIndex WRITE setCurrentVideoIndex NOTIFY currentVideoIndexChanged)
    Q_PROPERTY(QMediaPlayer::State videoPlayerState READ videoPlayerState WRITE setVideoPlayerState NOTIFY videoPlayerStateChanged)
    //Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
private:
    static VideoPlaybackModel *instance;
    QString m_currentFilePath;
    QString m_currentVideoName;

    int m_currentVideoIndex;

    QMediaPlayer::State m_videoPlayerState;

public:
    explicit VideoPlaybackModel(QObject *parent = nullptr);
    static VideoPlaybackModel *getInstance();
    QString currentFilePath() const;
    void setCurrentFilePath(QString currentFilePath);
    QString currentVideoName() const;
    void setCurrentVideoName(QString currentVideoName);

    int currentVideoIndex() const;

    QMediaPlayer::State videoPlayerState() const;

public slots:
    void setCurrentVideoIndex(int currentVideoIndex);

    void setVideoPlayerState(QMediaPlayer::State videoPlayerState);

signals:
    void currentFilePathChanged();
    void currentVideoNameChanged();
    void currentVideoIndexChanged();
    void videoPlayerStateChanged();
};

#endif // VIDEOPLAYBACKMODEL_H
