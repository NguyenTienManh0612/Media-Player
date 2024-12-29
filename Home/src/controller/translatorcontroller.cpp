#include "translatorcontroller.h"
#include "loghelper.h"

TranslatorController* TranslatorController::m_instance = nullptr;
TranslatorController::TranslatorController(QObject *parent)
    : QObject{parent}
    , m_initialized(false)
{

}

TranslatorController *TranslatorController::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new TranslatorController();
    }

    return m_instance;
}

void TranslatorController::initialize(QQmlContext *context)
{
//    LOG_INFO << m_initialized;

    if(!m_initialized)
    {
        m_initialized = true;
        context->setContextProperty("TRANSLATE_CTRL", this);
        context->setContextProperty("TRANSLATE_MODEL", TranslatorModel::getInstance());

        // first setup language for app media for first run
        requestChangeLanguage();
    }

}

void TranslatorController::requestChangeLanguage()
{
    // 1. create a dbus signal
    QDBusMessage msg = QDBusMessage::createSignal(
                "/home/appInterface",       // object path
                "home.appInterface",        // service interface
                "requestChangeLanguage"     // signal name
                );

    // 2. append input arguments
    msg << TranslatorModel::getInstance()->currentLanguage();

    // 3. broadcast signal (using session)
    QDBusConnection::sessionBus().send(msg);
    // save current lang before close app

}
