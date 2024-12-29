#ifndef TRANSLATORMODEL_H
#define TRANSLATORMODEL_H

#include <QObject>
#include <QTranslator>
#include <QGuiApplication>
#include <QDebug>

extern int g_volume;
extern QString g_language;

#define STRING_ID(Name, Value) \
    public: \
    Q_PROPERTY(QString Name READ Name NOTIFY languageChanged) \
    static QString Name() { \
    return (Value); \
    }
class TranslatorModel : public QObject
{
    Q_OBJECT
    STRING_ID(STR_APP_TITLE, tr("STR_APP_TITLE"))
    STRING_ID(STR_TITLE, tr("STR_TITLE"))
    STRING_ID(STR_UNKNOWN, tr("STR_UNKNOWN"))
    STRING_ID(STR_ARTIST, tr("STR_ARTIST"))
    STRING_ID(STR_LANGUAGE, tr("STR_LANGUAGE"))
    STRING_ID(STR_VOLUME, tr("STR_VOLUME"))
    STRING_ID(STR_ENGLISH, tr("STR_ENGLISH"))
    STRING_ID(STR_VIETNAMESE, tr("STR_VIETNAMESE"))
    STRING_ID(STR_SETTINGS, tr("STR_SETTINGS"))
    STRING_ID(STR_MUSIC_TITLE, tr("STR_MUSIC_TITLE"))
    STRING_ID(STR_VIDEO_TITLE, tr("STR_VIDEO_TITLE"))

    Q_PROPERTY(QString currentLanguage READ currentLanguage WRITE setCurrentLanguage NOTIFY languageChanged)
public:
    explicit TranslatorModel(QObject *parent = nullptr); 
    QString currentLanguage() const;
    static TranslatorModel *getInstance();
    Q_INVOKABLE void setTranslation(QString language);
    void loadLanguageFromFile();
    void saveLanguageToFile();
signals:
    void languageChanged();

public slots:
    void setCurrentLanguage(QString currentLanguage);

private:
    QTranslator m_translator;
    QString m_currentLanguage;
    static TranslatorModel *instance;
};

#endif // TRANSLATORMODEL_H
