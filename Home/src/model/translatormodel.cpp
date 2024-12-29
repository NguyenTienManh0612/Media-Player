#include "translatormodel.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
TranslatorModel *TranslatorModel::instance = nullptr;
TranslatorModel::TranslatorModel(QObject *parent)
    : QObject{parent}
    , m_currentLanguage("English")
{
    loadLanguageFromFile();
    // default language when start running app
    if(m_currentLanguage == "English"){
        m_translator.load(":/localization/AppLanguage_en.qm");
    }else{
        m_translator.load(":/localization/AppLanguage_vi.qm");
    }
    qApp->installTranslator(&m_translator);
    emit languageChanged();
}

void TranslatorModel::setTranslation(QString language)
{
    m_translator.load(":/localization/" + language + ".qm");
    qApp->installTranslator(&m_translator);
    emit languageChanged();
}

QString TranslatorModel::currentLanguage() const
{
    return m_currentLanguage;
}

TranslatorModel *TranslatorModel::getInstance()
{
    if(instance == nullptr)
        instance = new TranslatorModel();
    return instance;
}

void TranslatorModel::setCurrentLanguage(QString currentLanguage)
{
    if (m_currentLanguage == currentLanguage)
        return;

    m_currentLanguage = currentLanguage;
    saveLanguageToFile();
    emit languageChanged();
}
void TranslatorModel::saveLanguageToFile()
{
    QFile file("language.json");
    if (file.open(QIODevice::WriteOnly)) {
        QJsonObject json;
        json["language"] = m_currentLanguage;
        QJsonDocument doc(json);
        file.write(doc.toJson());
        file.close();
    } else {
        qWarning("Couldn't open file to save language.");
    }
}

void TranslatorModel::loadLanguageFromFile()
{
    QFile file("language.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc(QJsonDocument::fromJson(data));
        if (!doc.isNull()) {
            QJsonObject json = doc.object();
            if (json.contains("language") && json["language"].isString()) {
                m_currentLanguage = json["language"].toString();
            }
        }
    } else {
        qWarning("Couldn't open file to load language.");
    }
}
