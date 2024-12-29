#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QStack>
#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QDBusConnection>
#include <QDBusMessage>
#include "screenmodel.h"

class ScreenController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool modeDisplay READ modeDisplay WRITE setModeDisplay NOTIFY modeDisplayChanged)
private:
    explicit ScreenController(QObject *parent = nullptr);

public:
    ~ScreenController();

    // singleton pattern
    static ScreenController *getInstance();

    // initialize controller
    void initialize(QQmlContext *context);
    void initializeScreen(QQmlApplicationEngine *engine);

    // screen transition
    Q_INVOKABLE void pushScreen(int screenId);
    Q_INVOKABLE void replaceScreen(int screenId);
    Q_INVOKABLE void popScreen();
    Q_INVOKABLE void popToRoot();
    // return count screen in stack screen of media app
    Q_INVOKABLE int countScreenInStack();
    Q_INVOKABLE void requestBackToHome();
    bool modeDisplay() const;

public slots:
    void setModeDisplay(bool modeDisplay);
    void onReceivedRequestDisplayMusic();
    void onReceivedRequestDisplayVideo();
signals:
    void modeDisplayChanged();

private:
    void reloadScreen();

private:
    static ScreenController *m_instance;
    bool m_initialized;

    ScreenModel m_model;
    QStack<int> m_screenStack;
    QQmlApplicationEngine *m_engine;
    bool m_modeDisplay;
};

#endif // SCREENCONTROLLER_H
