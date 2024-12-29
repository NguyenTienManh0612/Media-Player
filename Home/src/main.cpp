#include <QGuiApplication>
#include "appengine.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

int g_volume = 5;
QString g_language = "English";

//void saveLanguageToFile();
//void loadLanguageFromFile();

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //loadLanguageFromFile();
    AppEngine::getInstance()->initialize(&app);   
    //saveLanguageToFile();
    return app.exec();
}

//void saveLanguageToFile() {
//    QJsonObject lang;
//    lang["language"] = g_language;

//    QJsonDocument doc(lang);
//    QString filePath = "Homelanguage.json";
//    QFile file(filePath);
//    if (file.open(QIODevice::WriteOnly)) {
//        file.write(doc.toJson());
//        file.close();
//        qDebug() << "State saved to" << filePath;
//    } else {
//        qWarning() << "Couldn't open file to save state.";
//    }
//}

//void loadLanguageFromFile() {
//    QString filePath = "Homelanguage.json";
//    QFile file(filePath);
//    if (file.exists() && file.open(QIODevice::ReadOnly)) {
//        QByteArray data = file.readAll();
//        file.close();

//        QJsonDocument doc(QJsonDocument::fromJson(data));
//        QJsonObject lang = doc.object();

//        g_language = lang["language"].toString();

//        qDebug() << "State loaded from" << filePath;
//    } else {
//        qWarning() << "Couldn't open file to load state.";
//    }
//}
