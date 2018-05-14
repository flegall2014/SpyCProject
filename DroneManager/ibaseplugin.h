#ifndef IBASEWINDOW_H
#define IBASEWINDOW_H

// Qt
#include <QObject>

// Application
#include "drone_manager_global.h"

class DRONEMANAGERSHARED_EXPORT IBasePlugin : public QObject
{
    Q_OBJECT

public:
    //! Constructor
    IBasePlugin(QObject *pParent=nullptr) : QObject(pParent)
    {

    }

    //! Destructor
    virtual ~IBasePlugin()
    {

    }

    //! Return plugin name
    virtual QString name() const = 0;

    //! Return version
    virtual float version() const = 0;
};

QT_BEGIN_NAMESPACE
#define IBasePluginInterface_iid "com.tosa.ibaseplugin"
Q_DECLARE_INTERFACE(IBasePlugin, IBasePluginInterface_iid)
QT_END_NAMESPACE

#endif // IBASEWINDOW_H
