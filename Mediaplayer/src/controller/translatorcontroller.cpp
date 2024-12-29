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
        context->setContextProperty("TRANSLATE_MODEL", &m_model);

        // connect with requestChangeLanguage signal from home app
        QDBusConnection::sessionBus().connect("",
                                              "/home/appInterface",
                                              "home.appInterface",
                                              "requestChangeLanguage",
                                              this, SLOT(onReceivedRequestChangeLanguage(QString)));
    }
}

void TranslatorController::onReceivedRequestChangeLanguage(QString msg)
{
    if(msg == "English"){
        m_model.setTranslation("AppLanguage_en");
    }else {
        m_model.setTranslation("AppLanguage_vi");
    }
}
