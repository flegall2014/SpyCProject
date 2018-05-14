#ifndef HELPER_H
#define HELPER_H

// Qt
#include <QDir>

class Helper
{
public:
    //! Return application dir
    static QDir applicationDir();

    //! Return i18n dir
    static QDir i18nDir();
};

#endif // HELPER_H
