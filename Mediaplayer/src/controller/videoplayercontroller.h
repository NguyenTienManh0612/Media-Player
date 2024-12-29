#ifndef VIDEOPLAYERCONTROLLER_H
#define VIDEOPLAYERCONTROLLER_H

#include "baseplayercontroller.h"
#include "videoplaybackmodel.h"
#include "videolistcontroller.h"
#include <QObject>
#include <QAbstractVideoSurface>
#include <QDBusConnection>
#include <QDBusMessage>

class VideoPlayerController : public BasePlayerController
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface* videoSurface READ videoSurface WRITE setVideoSurface NOTIFY videoSurfaceChanged)
    Q_PROPERTY(bool isFullScreenVideo READ isFullScreenVideo WRITE setIsFullScreenVideo NOTIFY isFullScreenVideoChanged)
public:
    ~VideoPlayerController();
    static VideoPlayerController* getInstance();
    void initialize(QQmlContext *context);
    Q_INVOKABLE void vplaypause();
    Q_INVOKABLE void vnext();
    Q_INVOKABLE void vprevious();
    Q_INVOKABLE void requestSendMetaData();
    QAbstractVideoSurface* videoSurface() const;
    void setVideoSurface(QAbstractVideoSurface* videoSurface);   
    bool isFullScreenVideo() const;
    void loadVideoPlaylist();
    void saveStateToFile();
    void loadStateFromFile();
public slots:
    void onMetaDataChanged(QMediaPlayer::MediaStatus status);
    void onReceivedRequestChangeVolume(int msg);
    void onRequestDisplayVideoPlayer();
    void handelPlaybackStateChanged(QMediaPlayer::State state);
    void setIsFullScreenVideo(bool newIsFullScreen);

signals:
    void videoSurfaceChanged();   
    void isFullScreenVideoChanged();

private:
    explicit VideoPlayerController(QObject *parent = nullptr);
    static VideoPlayerController *m_instance;
    //VideoPlaybackModel *m_playbackModel;
    QAbstractVideoSurface* m_videoSurface;
    bool m_isFullScreenVideo;
};

#endif // VIDEOPLAYERCONTROLLER_H
