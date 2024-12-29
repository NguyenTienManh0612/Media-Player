#ifndef DBUSCONTROLLER_H
#define DBUSCONTROLLER_H

#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
extern int g_volume;

class DbusController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool modeDisplay READ modeDisplay WRITE setModeDisplay NOTIFY modeDisplayChanged)
    Q_PROPERTY(int currentVolume READ currentVolume WRITE setCurrentVolume NOTIFY currentVolumeChanged)

    // property receiver from media app
    Q_PROPERTY(QString currentTitle READ currentTitle WRITE setCurrentTitle NOTIFY metaDataChanged)
    Q_PROPERTY(QString currentArtist READ currentArtist WRITE setCurrentArtist NOTIFY metaDataChanged)
    //Q_PROPERTY(bool isCurrentCoverArtNull READ isCurrentCoverArtNull WRITE setIsCurrentCoverArtNull NOTIFY metaDataChanged)
    Q_PROPERTY(QString currentCoverArt READ currentCoverArt WRITE setCurrentCoverArt NOTIFY metaDataChanged)
    Q_PROPERTY(QString currentVideoName READ currentVideoName WRITE setCurrentVideoName NOTIFY currentVideoNameChanged)
private:
    explicit DbusController(QObject *parent = nullptr);
public:
    ~DbusController();
    static DbusController *getInstance();
    // initialize controller
    void initialize(QQmlContext *context);
    void initializeScreen(QQmlApplicationEngine *engine);

    Q_INVOKABLE void requestDisplayMusicPlayer();
    Q_INVOKABLE void requestDisplayVideoPlayer();
    Q_INVOKABLE void requestChangeVolume();

    bool modeDisplay() const;
    int currentVolume() const;

    // meta data for music player
    QString currentTitle() const;
    QString currentArtist() const;
    //bool isCurrentCoverArtNull() const;
    QString currentCoverArt() const;
    QString currentVideoName() const;
    void loadStateFromFile();
    void saveStateToFile();
public slots:
    void onReceivedBackToHome();
    void setModeDisplay(bool newModeDisplay);
    void setCurrentVolume(int newCurrentVolume);

    // set meta data for music player
    void setCurrentTitle(const QString &newCurrentTitle);
    void setCurrentArtist(const QString &newCurrentArtist);
    //void setIsCurrentCoverArtNull(bool newIsCurrentCoverArtNull);
    void setCurrentCoverArt(const QString &newCurrentPathCoverArt);

    void onReceivedSendMetaData(QString title, QString artist, QString pathCoverArt);//, QString videoName);
    void onReceivedMetaDataVideo(QString videoName);
    void setCurrentVideoName(const QString &newCurrentVideoName);

signals:
    void modeDisplayChanged();
    void currentVolumeChanged();
    void metaDataChanged();
    void currentVideoNameChanged();

private:
    QQmlApplicationEngine *m_engine;
    bool m_initialized;
    static DbusController *m_instance;
    bool m_modeDisplay;
    int m_currentVolume;
    QString m_currentTitle;
    QString m_currentArtist;
    //bool m_isCurrentCoverArtNull;
    QString m_currentCoverArt;
    QString m_currentVideoName;
};

#endif // DBUSCONTROLLER_H
