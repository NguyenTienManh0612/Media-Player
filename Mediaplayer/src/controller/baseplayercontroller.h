#ifndef BASEPLAYERCONTROLLER_H
#define BASEPLAYERCONTROLLER_H

#include <QObject>
#include <QQmlContext>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDBusConnection>
#include <QDBusMessage>
#include "baseplaybackmodel.h"
#include "musiclistmodel.h"
#include "videolistmodel.h"
#include "musicplaybackmodel.h"
#include "videoplaybackmodel.h"

class BasePlayerController : public QObject
{
    Q_OBJECT
public:
    explicit BasePlayerController(QObject *parent = nullptr);
    ~BasePlayerController();
    void initialize(QQmlContext *context);
    // initialize controller
    Q_INVOKABLE void mplaypause();
    //Q_INVOKABLE void play(const QString &filepath);
    //Q_INVOKABLE void pause();
    //Q_INVOKABLE void stop();
    Q_INVOKABLE void mnext();
    Q_INVOKABLE void mprevious();
//    Q_INVOKABLE void vplaypause();
//    Q_INVOKABLE void vnext();
//    Q_INVOKABLE void vprevious();
    //Q_INVOKABLE bool playListIsEmpty() const;
    Q_INVOKABLE void setMediaPosition(const int position);
    void loadMusicPlaylist();
    //void loadVideoPlaylist();
    bool initialized() const;
    void setInitialized(bool initialized);

public slots:
    //void onReceivedRequestChangeVolume(int);
    //void onRequestedPlayVideo();
    //void handelPlaybackStateChanged(QMediaPlayer::State status);
    //void onMetaDataChanged(QMediaPlayer::MediaStatus status);
    //void onRequestedPlayMusic();

protected:
    bool m_initialized;
    QMediaPlayer m_player;
    QMediaPlayer m_Vplayer;
    QMediaPlaylist m_playlist;
    QMediaPlaylist m_Vplaylist;
    //MusicPlaybackModel* m_playbackMModel;
    //MusicPlaybackModel * m_playbackModel;
    MusicListModel m_model;
    VideoListModel m_vmodel;
};

#endif // MUSICPLAYERCONTROLLER_H
