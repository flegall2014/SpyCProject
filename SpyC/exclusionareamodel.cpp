// Application
#include "exclusionareamodel.h"
#include "baseshape.h"

//-------------------------------------------------------------------------------------------------

ExclusionAreaModel::ExclusionAreaModel(QObject *pParent) : QAbstractListModel(pParent)
{

}

//-------------------------------------------------------------------------------------------------

ExclusionAreaModel::~ExclusionAreaModel()
{

}

//-------------------------------------------------------------------------------------------------

QVariant ExclusionAreaModel::data(const QModelIndex &index, int iRole) const
{
    if (!index.isValid())
        return QVariant();
    if ((index.row() < 0) || (index.row() > rowCount()-1))
        return QVariant();
    if (iRole == ShapeRole)
        return QVariant::fromValue(m_vShapes[index.row()]);
    return QVariant();
}

//-------------------------------------------------------------------------------------------------

int ExclusionAreaModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_vShapes.size();
}

//-------------------------------------------------------------------------------------------------

QHash<int, QByteArray> ExclusionAreaModel::roleNames() const
{
    QHash<int, QByteArray> hRoleNames;
    hRoleNames[ShapeRole] = "shape";
    return hRoleNames;
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addShape(BaseShape *pShape)
{
    if (pShape != nullptr)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_vShapes << pShape;
        endInsertRows();
    }
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addRect(const QGeoCoordinate &topLeft, const QGeoCoordinate &bottomRight)
{
    RectShape *pShape = new RectShape(topLeft, bottomRight, this);
    addShape(pShape);
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addCircle(const QGeoCoordinate &center, double dRadius)
{
    CircleShape *pShape = new CircleShape(center, dRadius);
    addShape(pShape);
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addTriangle(const QGeoCoordinate &point1, const QGeoCoordinate &point2, const QGeoCoordinate &point3)
{
    TriangleShape *pShape = new TriangleShape(point1, point2, point3);
    addShape(pShape);
}


