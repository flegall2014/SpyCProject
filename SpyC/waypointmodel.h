#ifndef WAYPOINTMODEL_H
#define WAYPOINTMODEL_H

// Qt
#include <QAbstractListModel>
#include <QVector>
#include <QGeoCoordinate>
#include <QGeoPath>

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
    enum Roles {WayPointRole=Qt::UserRole+1, WayPointLatitude, WayPointLongitude};

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

    //! Clear mission plan
    void clear();

private:
    //! Geo points
    QGeoPath m_geoPath;

signals:
    //! Path changed
    void pathChanged();
};

#endif // WAYPOINTMODEL_H
