#ifndef TRANSLATORCONTROLLER_H
#define TRANSLATORCONTROLLER_H

#include <QObject>
#include <translatormodel.h>
#include <QQmlContext>
#include <QQmlApplicationEngine>

/*
 bat app media truoc de co the apply duoc language
*/

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

public slots:
    void onReceivedRequestChangeLanguage(QString msg);
private:
    static TranslatorController *m_instance;
    bool m_initialized;
    TranslatorModel m_model;

};

#endif // TRANSLATORCONTROLLER_H
