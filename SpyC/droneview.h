#ifndef DRONEVIEW_H
#define DRONEVIEW_H

// Qt
#include <QAbstractListModel>

// Application
#include <alert.h>
class DroneBase;

// Application
namespace Model {
class DroneManager;
}

class DroneView : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int droneCount READ droneCount NOTIFY droneCountChanged)

public:
    enum Roles {DroneRole=Qt::UserRole+1};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    DroneView(QObject *pParent=nullptr);

    //! Destructor
    ~DroneView();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Add drone
    void addDrone(DroneBase *pDrone);

    //-------------------------------------------------------------------------------------------------
    // QAbstractItemModel methods
    //-------------------------------------------------------------------------------------------------

    //! Data
    virtual QVariant data(const QModelIndex &index, int iRole) const;

    //! Return row count
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;

    //! Return role names
    virtual QHash<int, QByteArray> roleNames() const;

private:
    //! Return drone count
    int droneCount() const;

private:
    //! Drones
    QVector<DroneBase *> m_vDrones;

public slots:
    //! Update view
    void onUpdateView();

signals:
    //! Drone count changed
    void droneCountChanged();
};

#endif // DRONEVIEW_H
