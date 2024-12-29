#include <QGuiApplication>
#include "appengine.h"
int g_volume;
QString g_language;
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    AppEngine::getInstance()->initialize(&app);
    return app.exec();
}
