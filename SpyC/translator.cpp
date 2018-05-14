// Qt
#include <QGuiApplication>
#include <QDir>
#include <QTranslator>
#include <QDebug>

// Application
#include "translator.h"
#include "helper.h"

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
        // Setup translator
        if (!m_pTranslator->load(Helper::i18nDir().absoluteFilePath("french.qm")))
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
