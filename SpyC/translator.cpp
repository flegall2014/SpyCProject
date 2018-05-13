// Qt
#include <QGuiApplication>
#include <QDir>
#include <QTranslator>
#include <QDebug>

// Application
#include "translator.h"

//-------------------------------------------------------------------------------------------------

Translator::Translator(QObject *pParent) : QObject(pParent)
{
    m_pTranslator = new QTranslator(this);
}

//-------------------------------------------------------------------------------------------------

Translator::~Translator()
{

}

//-------------------------------------------------------------------------------------------------

QString Translator::getEmptyString()
{
    return QString();
}

//-------------------------------------------------------------------------------------------------

void Translator::selectLanguage(const QString &sLanguage)
{
    // working folder
    if (sLanguage == "FR")
    {
        if (!m_pTranslator->load("D:/projects/SpyCProject/SpyC/i18n/french.qm"))
            qDebug() << "Failed to load: " << sLanguage;
        else
            qDebug() << sLanguage << " successfully loaded";
        qApp->installTranslator(m_pTranslator);
    }
    else
    {
        qDebug() << "Removing translator";
        qApp->removeTranslator(m_pTranslator);
    }

    emit languageChanged();
}
