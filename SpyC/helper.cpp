// Qt
#include <QCoreApplication>

// Application
#include "helper.h"

//-------------------------------------------------------------------------------------------------

QDir Helper::applicationDir()
{
    return QCoreApplication::applicationDirPath();
}

//-------------------------------------------------------------------------------------------------

QDir Helper::i18nDir()
{
    QDir appDir = applicationDir();
    if (appDir.cdUp())
    {
        if (appDir.cd("SpyC"))
        {
            if (appDir.cd("i18n"))
                return appDir;
        }
    }
    return appDir;
}
