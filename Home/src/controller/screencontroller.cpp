#include "screencontroller.h"
#include "appdefines.h"
#include "loghelper.h"

ScreenController* ScreenController::m_instance = nullptr;

ScreenController::ScreenController(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
    , m_engine(nullptr)
{
    LOG_INFO << "Screen Controller is initialized";
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
        context->setContextProperty("SCREEN_CTRL", this); //this m_instance
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
        // show home menu screen
        pushScreen(AppEnums::SCREEN_ID_HOME_MENU);
    }
}

void ScreenController::pushScreen(int screenId)
{ // home screenId = 0; setting srId = 1
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
        // reload screen on qml
        m_model.setCurrentScreen(screenName);
        if((m_engine != nullptr) && (m_engine->rootObjects().count() > 0))
        {
            QMetaObject::invokeMethod(m_engine->rootObjects().at(0), "reloadScreen");
        }
    }
}
