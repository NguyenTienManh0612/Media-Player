#ifndef MUSICPLAYERCONTROLLER_H
#define MUSICPLAYERCONTROLLER_H

#include "baseplayercontroller.h"
#include "musicplaybackmodel.h"
#include "musiclistcontroller.h"
#include <QObject>
#include <QDBusConnection>
#include <QDBusMessage>
class MusicPlayerController : public BasePlayerController
{
    Q_OBJECT
public:
    static MusicPlayerController *getInstance();
    void initialize(QQmlContext *context);

    Q_INVOKABLE void requestSendMetaData();
    void saveStateToFile();
    void loadStateFromFile();
public slots:
    void onMetaDataChanged(QMediaPlayer::MediaStatus status);
    void onReceivedRequestChangeVolume(int msg);
    void onRequestDisplayMusicPlayer();
    void handelPlaybackStateChanged(QMediaPlayer::State state);
private:
    explicit MusicPlayerController(QObject *parent = nullptr);
    static MusicPlayerController *m_instance;
    MusicPlaybackModel *m_playbackModel;
};

#endif // MUSICPLAYERCONTROLLER_H
