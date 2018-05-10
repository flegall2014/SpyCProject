#ifndef EXCLUSIONAREAMODEL_H
#define EXCLUSIONAREAMODEL_H

// Qt
#include <QAbstractListModel>
#include <QGeoCoordinate>

// Application
class BaseShape;

class ExclusionAreaModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {ShapeRole=Qt::UserRole+1};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    ExclusionAreaModel(QObject *pParent=nullptr);

    //! Destructor
    ~ExclusionAreaModel();

    //-------------------------------------------------------------------------------------------------
    // QAbstractListModel interface
    //-------------------------------------------------------------------------------------------------

    //! Return data
    virtual QVariant data(const QModelIndex &index, int iRole) const;

    //! Row count
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;

    //! Return role names
    virtual QHash<int, QByteArray> roleNames() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Add rect
    Q_INVOKABLE void addRect(const QGeoCoordinate &topLeft, const QGeoCoordinate &bottomRight);

    //! Add circle
    Q_INVOKABLE void addCircle(const QGeoCoordinate &center, double dRadius);

    //! Add triangle
    Q_INVOKABLE void addTriangle(const QGeoCoordinate &point1, const QGeoCoordinate &point2, const QGeoCoordinate &point3);

private:
    //! Add shape
    void addShape(BaseShape *pShape);

private:
    //! Shapes
    QVector<BaseShape *> m_vShapes;
};

#endif // EXCLUSIONAREAMODEL_H
