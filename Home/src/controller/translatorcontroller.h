#ifndef TRANSLATORCONTROLLER_H
#define TRANSLATORCONTROLLER_H

#include <QObject>
#include <translatormodel.h>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QDBusConnection>
#include <QDBusMessage>

class TranslatorController : public QObject
{
    Q_OBJECT
private:
    explicit TranslatorController(QObject *parent = nullptr);

public:
    // singleton pattern
    static TranslatorController *getInstance();
    // initialize controller
    void initialize(QQmlContext *context);

    // request change language for 2 app
    Q_INVOKABLE void requestChangeLanguage();

private:
    static TranslatorController *m_instance;
    bool m_initialized;
    //TranslatorModel m_model;

};

#endif // TRANSLATORCONTROLLER_H
