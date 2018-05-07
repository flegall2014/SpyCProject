#ifndef WAYPOINTMODEL_H
#define WAYPOINTMODEL_H

// Qt
#include <QAbstractListModel>
#include <QVector>
#include <QGeoCoordinate>
#include <QGeoPath>

// Application
#include <waypoint.h>

class WayPointModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QGeoPath path READ path NOTIFY pathChanged)
    Q_PROPERTY(int pointCount READ pointCount NOTIFY pathChanged)

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Define roles
    enum Roles {WayPointIndex=Qt::UserRole+1, WayPointCoordinate, WayPointLatitude, WayPointLongitude, WayPointType};

    //! Constructor
    WayPointModel(QObject *pParent=nullptr);

    //! Destructor
    ~WayPointModel();

    //-------------------------------------------------------------------------------------------------
    // QAbstractListModel interface
    //-------------------------------------------------------------------------------------------------

    //! Return row count
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;

    //! Return data
    virtual QVariant data(const QModelIndex &index, int role) const;

    //! Set point position
    void setPointPosition(int iIndex, const QGeoCoordinate &geoCoord);

    //! Return role names
    virtual QHash<int, QByteArray> roleNames() const;

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return path
    const QGeoPath &path() const;

    //! Return point count
    int pointCount() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Add coordinate
    void addCoordinate(const QGeoCoordinate &coordinate);

    //! Remove coordinate at index
    void removeCoordinateAtIndex(int iCoordIndex);

    //! Clear mission plan
    void clear();

private:
    //! Geo points
    QGeoPath m_geoPath;

    //! Way points
    QVector<Model::WayPoint> m_vWayPoints;

signals:
    //! Path changed
    void pathChanged();
};

#endif // WAYPOINTMODEL_H
