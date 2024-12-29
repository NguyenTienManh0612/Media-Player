#include "translatormodel.h"

TranslatorModel::TranslatorModel(QObject *parent)
    : QObject{parent}
{

}

void TranslatorModel::setTranslation(QString language)
{
    m_translator.load(":/localization/" + language + ".qm");
    qApp->installTranslator(&m_translator);
    emit languageChanged();
}
