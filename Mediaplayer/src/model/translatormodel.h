#ifndef TRANSLATORMODEL_H
#define TRANSLATORMODEL_H

#include <QObject>
#include <QTranslator>
#include <QGuiApplication>
#include <QDebug>
#include <QDBusConnection>

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
    STRING_ID(STR_LIST_EMPTY, tr("STR_LIST_EMPTY"))
    STRING_ID(STR_TITLE, tr("STR_TITLE"))
    STRING_ID(STR_UNKNOWN, tr("STR_UNKNOWN"))
    STRING_ID(STR_ALBUM, tr("STR_ALBUM"))
    STRING_ID(STR_ARTIST, tr("STR_ARTIST"))

public:
    explicit TranslatorModel(QObject *parent = nullptr);
    Q_INVOKABLE void setTranslation(QString language);

signals:
    void languageChanged();

private:
    QTranslator m_translator;
};

#endif // TRANSLATORMODEL_H
