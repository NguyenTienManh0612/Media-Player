#ifndef APPENGINE_H
#define APPENGINE_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

class AppEngine : public QObject
{
    Q_OBJECT

private:
    explicit AppEngine(QObject *parent = nullptr);

public:
    ~AppEngine();

    // singleton pattern
    static AppEngine *getInstance();

    // initialize app
    void initialize(QGuiApplication *app);

private:
    void registerQmlObjects();
    void createControllers();
    void initControllers();
    void initScreens();

private:
    static AppEngine* m_instance;
    bool m_initialized;

    QGuiApplication* m_app;
    QQmlApplicationEngine m_engine;
};

#endif // APPENGINE_H
