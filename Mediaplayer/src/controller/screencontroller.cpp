#include "screencontroller.h"
#include "appdefines.h"
#include "loghelper.h"

ScreenController* ScreenController::m_instance = nullptr;

ScreenController::ScreenController(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
    , m_engine(nullptr)
{
    LOG_INFO;
    // connect with requestDisplayMedia signal from home app
    QDBusConnection::sessionBus().connect("",
                                          "/vn/com/fsoft/home/appInterface",       // object path
                                          "vn.com.fsoft.home.appInterface",        // service interface
                                          "requestDisplayMusicPlayer",
                                          this, SLOT(onReceivedRequestDisplayMusic()));

    // connect with requestDisplayVideo signal from home app
    QDBusConnection::sessionBus().connect("",
                                          "/vn/com/fsoft/home/appInterface",       // object path
                                          "vn.com.fsoft.home.appInterface",        // service interface
                                          "requestDisplayVideoPlayer",
                                          this, SLOT(onReceivedRequestDisplayVideo()));
}

ScreenController::~ScreenController()
{
    LOG_INFO;
    m_engine = nullptr;
}

ScreenController *ScreenController::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new ScreenController();
    }

    return m_instance;
}

void ScreenController::initialize(QQmlContext *context)
{
    LOG_INFO << m_initialized;
    if(!m_initialized)
    {
        m_initialized = true;
        context->setContextProperty("SCREEN_CTRL", this);
        context->setContextProperty("SCREEN_MODEL", &m_model);
    }
}

void ScreenController::initializeScreen(QQmlApplicationEngine *engine)
{
    LOG_INFO;
    if(m_engine == nullptr)
    {
        m_engine = engine;

        // load main qml
        m_engine->load(QUrl(QStringLiteral(MAIN_QML)));

        // show default screen
        //pushScreen(AppEnums::SCREEN_ID_VIDEO_PLAYER);
    }
}

void ScreenController::pushScreen(int screenId)
{
    LOG_INFO << screenId;
    m_screenStack.push(screenId);
    reloadScreen();
}

void ScreenController::replaceScreen(int screenId)
{
    LOG_INFO << screenId;
    if(!m_screenStack.isEmpty())
    {
        m_screenStack.pop();
    }
    m_screenStack.push(screenId);
    reloadScreen();
}

void ScreenController::popScreen()
{
    LOG_INFO << m_screenStack.count();
    if(m_screenStack.count() > 1)
    {
        m_screenStack.pop();
        reloadScreen();
    }
}

void ScreenController::popToRoot()
{
    LOG_INFO << m_screenStack.count();
    while(m_screenStack.count() > 1)
    {
        m_screenStack.pop();
    }
    reloadScreen();
}

void ScreenController::reloadScreen()
{
    if(!m_screenStack.isEmpty())
    {
        QString screenName = ScreenNameMap.value(m_screenStack.top());
        m_model.setCurrentScreen(screenName);
        // reload screen on qml
        if((m_engine != nullptr) && (m_engine->rootObjects().count() > 0))
        {
            QMetaObject::invokeMethod(m_engine->rootObjects().at(0), "reloadScreen");
        }
    }
}
int ScreenController::countScreenInStack(){
    return m_screenStack.count();
}

bool ScreenController::modeDisplay() const
{
    return m_modeDisplay;
}
void ScreenController::requestBackToHome()
{
    // 1. create a dbus signal
    QDBusMessage msg = QDBusMessage::createSignal(
                "/vn/com/fsoft/media/mediaInterface",
                "vn.com.fsoft.media.mediaInterface",
                "requestBackToHome"      // signal name
                );
    // 2. broadcast signal (using session)
    QDBusConnection::sessionBus().send(msg);
}

void ScreenController::onReceivedRequestDisplayMusic()
{
    qDebug() << "check request music player";
    if(m_screenStack.count() == 0){
        pushScreen(AppEnums::SCREEN_ID_MUSIC_PLAYER);
    }

    if(m_screenStack.top() == AppEnums::SCREEN_ID_VIDEO_PLAYER){
        m_screenStack.clear();
        pushScreen(AppEnums::SCREEN_ID_MUSIC_PLAYER);
    }
    setModeDisplay(true);
}

void ScreenController::onReceivedRequestDisplayVideo()
{
    qDebug() << "check request video player";
    if(m_screenStack.count() == 0){
        pushScreen(AppEnums::SCREEN_ID_VIDEO_PLAYER);
    }

    if(m_screenStack.top() == AppEnums::SCREEN_ID_MUSIC_PLAYER || m_screenStack.top() == AppEnums::SCREEN_ID_MUSIC_LIST){
        m_screenStack.clear();

        pushScreen(AppEnums::SCREEN_ID_VIDEO_PLAYER);
    }
    setModeDisplay(true);
}

void ScreenController::setModeDisplay(bool modeDisplay)
{
    qDebug() << m_modeDisplay;
    if (m_modeDisplay == modeDisplay)
        return;

    m_modeDisplay = modeDisplay;
    emit modeDisplayChanged();
    qDebug() << m_modeDisplay;
}
