#include "dbuscontroller.h"
#include "loghelper.h"
DbusController *DbusController::m_instance = nullptr;
DbusController::DbusController(QObject *parent)
    : QObject(parent), m_engine(nullptr), m_initialized(false), m_modeDisplay(true), m_currentVolume(g_volume), m_currentTitle(""),
    m_currentArtist(""), m_currentCoverArt(""), m_currentVideoName("")
{
    LOG_INFO;
    // dbus to request back to home from media app
    QDBusConnection::sessionBus().connect("",
                                          "/vn/com/fsoft/media/mediaInterface",
                                          "vn.com.fsoft.media.mediaInterface",
                                          "requestBackToHome",
                                          this, SLOT(onReceivedBackToHome()));
    requestChangeVolume();

    // connect with requestSendMetaData signal form music app
    QDBusConnection::sessionBus().connect("",
                                          "/vn/com/fsoft/media/mediaInterface",
                                          "vn.com.fsoft.media.mediaInterface",
                                          "requestSendMetaData",
                                          this, SLOT(onReceivedSendMetaData(QString, QString, QString)));
    // video app
    QDBusConnection::sessionBus().connect("",
                                          "/vn/com/fsoft/media/mediaInterface",
                                          "vn.com.fsoft.media.mediaInterface",
                                          "requestSendMetaDataVideo",
                                          this, SLOT(onReceivedMetaDataVideo(QString)));
}

DbusController::~DbusController()
{
    m_engine = nullptr;
}

DbusController *DbusController::getInstance()
{
    if(m_instance == nullptr)
        m_instance = new DbusController();
    return m_instance;
}

void DbusController::initialize(QQmlContext *context)
{
    LOG_INFO << m_initialized;
    if(!m_initialized)
    {
        m_initialized = true;
        context->setContextProperty("DBUS_CTRL", this);
    }
    loadStateFromFile();
}

void DbusController::requestDisplayMusicPlayer()
{
    // 1. create a dbus signal
    QDBusMessage requestDMP = QDBusMessage::createSignal(
                "/vn/com/fsoft/home/appInterface",       // object path
                "vn.com.fsoft.home.appInterface",        // service interface
                "requestDisplayMusicPlayer"       // signal name
                );
    // 2. broadcast signal (using session)
    QDBusConnection::sessionBus().send(requestDMP);
}

void DbusController::requestDisplayVideoPlayer()
{
    // 1. create a dbus signal
    QDBusMessage requestDVP = QDBusMessage::createSignal(
                "/vn/com/fsoft/home/appInterface",       // object path
                "vn.com.fsoft.home.appInterface",        // service interface
                "requestDisplayVideoPlayer"       // signal name
                );
    // 2. broadcast signal (using session)
    QDBusConnection::sessionBus().send(requestDVP);
}

void DbusController::requestChangeVolume()
{
    // 1. create a dbus signal
    QDBusMessage requestVolume = QDBusMessage::createSignal(
                "/vn/com/fsoft/home/appInterface",       // object path
                "vn.com.fsoft.home.appInterface",        // service interface
                "requestChangeVolume"       // signal name
                );
    requestVolume << m_currentVolume;
    // 2. broadcast signal (using session)
    QDBusConnection::sessionBus().send(requestVolume);
}

bool DbusController::modeDisplay() const
{
    return m_modeDisplay;
}

int DbusController::currentVolume() const
{
    return m_currentVolume;
}

QString DbusController::currentTitle() const
{
    return m_currentTitle;
}

QString DbusController::currentArtist() const
{
    return m_currentArtist;
}

//bool DbusController::isCurrentCoverArtNull() const
//{
//    return m_isCurrentCoverArtNull;
//}

QString DbusController::currentCoverArt() const
{
    return m_currentCoverArt;
}

QString DbusController::currentVideoName() const
{
    return m_currentVideoName;
}

void DbusController::onReceivedBackToHome()
{
    setModeDisplay(true);
}

void DbusController::setModeDisplay(bool newModeDisplay)
{
    if(m_modeDisplay == newModeDisplay)
        return;
    m_modeDisplay = newModeDisplay;
    emit modeDisplayChanged();
}

void DbusController::setCurrentVolume(int newCurrentVolume)
{
    if (m_currentVolume == newCurrentVolume)
        return;

    m_currentVolume = newCurrentVolume;
    g_volume = m_currentVolume;
    emit currentVolumeChanged();
    saveStateToFile();
}

void DbusController::setCurrentTitle(const QString &newCurrentTitle)
{
    if (m_currentTitle == newCurrentTitle)
        return;

    m_currentTitle = newCurrentTitle;
    emit metaDataChanged();
}

void DbusController::setCurrentArtist(const QString &newCurrentArtist)
{
    if (m_currentArtist == newCurrentArtist)
        return;

    m_currentArtist = newCurrentArtist;
    emit metaDataChanged();
}

//void DbusController::setIsCurrentCoverArtNull(bool newIsCurrentCoverArtNull)
//{
//    if (m_isCurrentCoverArtNull == newIsCurrentCoverArtNull)
//        return;

//    m_isCurrentCoverArtNull = newIsCurrentCoverArtNull;
//    emit metaDataChanged();
//}

void DbusController::setCurrentCoverArt(const QString &newCurrentPathCoverArt)
{
    if (m_currentCoverArt == newCurrentPathCoverArt)
        return;

    m_currentCoverArt = newCurrentPathCoverArt;
    emit metaDataChanged();
}

void DbusController::onReceivedSendMetaData(QString title, QString artist, QString pathCoverArt)
{
    qDebug() << __FUNCTION__ << "Receiver meta data form media app";
    qDebug() << "Title: " << title;
    qDebug() << "Artist: " << artist;
    qDebug() << "path cover art: " << pathCoverArt;
    setCurrentTitle(title);
    setCurrentArtist(artist);
    setCurrentCoverArt(pathCoverArt);

    saveStateToFile();
}

void DbusController::onReceivedMetaDataVideo(QString videoName)
{
    qDebug() << __FUNCTION__ << "Receiver meta data form media app";
    qDebug() << "Video name: " << videoName;
    setCurrentVideoName(videoName);
    saveStateToFile();
}

void DbusController::setCurrentVideoName(const QString &newCurrentVideoName)
{
    if (m_currentVideoName == newCurrentVideoName)
        return;

    m_currentVideoName = newCurrentVideoName;
    emit currentVideoNameChanged();
}

void DbusController::saveStateToFile() {
    QJsonObject state;
    state["volume"] = m_currentVolume;
    state["title"] = m_currentTitle;
    state["artist"] = m_currentArtist;
    state["coverArt"] = m_currentCoverArt;
    state["videoName"] = m_currentVideoName;

    QJsonDocument doc(state);
    QString filePath = "HomeSaveMediaState.json";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
        qDebug() << "State saved to" << filePath;
    } else {
        qWarning() << "Couldn't open file to save state.";
    }
}

void DbusController::loadStateFromFile() {
    QString filePath = "HomeSaveMediaState.json";
    QFile file(filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc(QJsonDocument::fromJson(data));
        QJsonObject state = doc.object();

        m_currentVolume = state["volume"].toInt();
        m_currentTitle = state["title"].toString();
        m_currentArtist = state["artist"].toString();
        m_currentCoverArt = state["coverArt"].toString();
        m_currentVideoName = state["videoName"].toString();

        emit currentVolumeChanged();
        emit metaDataChanged();
        emit currentVideoNameChanged();

        qDebug() << "State loaded from" << filePath;
    } else {
        qWarning() << "Couldn't open file to load state.";
    }
}
