// Qt
#include <QImage>

// Application
#include "snapshotmodel.h"

//-------------------------------------------------------------------------------------------------


SnapShotModelFilter::SnapShotModelFilter(QObject *pParent) : QSortFilterProxyModel(pParent)
{
    m_pSrcModel = new SnapShotModel(pParent);
    setSourceModel(m_pSrcModel);
}

//-------------------------------------------------------------------------------------------------

SnapShotModelFilter::SnapShotModelFilter(const QString &sDroneSnapDir, QObject *pParent) : QSortFilterProxyModel(pParent)
{
    m_pSrcModel = new SnapShotModel(sDroneSnapDir, pParent);
    setSourceModel(m_pSrcModel);
}

//-------------------------------------------------------------------------------------------------

SnapShotModelFilter::~SnapShotModelFilter()
{

}

//-------------------------------------------------------------------------------------------------

bool SnapShotModelFilter::filterAcceptsRow(int iSrcRow, const QModelIndex &srcParent) const
{
    SnapShotModel *pSrcModel = dynamic_cast<SnapShotModel *>(sourceModel());
    if (pSrcModel != nullptr)
    {
        QString sFilePath = pSrcModel->data(pSrcModel->index(iSrcRow, 0, srcParent), QFileSystemModel::FilePathRole).toString();
        QImage img(sFilePath);
        return !img.isNull();
    }
    return false;
}

//-------------------------------------------------------------------------------------------------

SnapShotModel::SnapShotModel(QObject *pParent) : QFileSystemModel(pParent)
{
    setFilter(QDir::Files|QDir::NoDotAndDotDot);
}

//-------------------------------------------------------------------------------------------------

SnapShotModel::SnapShotModel(const QString &sDroneSnapDir, QObject *pParent) : QFileSystemModel(pParent)
{
    setRootPath(sDroneSnapDir);
    setFilter(QDir::Files|QDir::NoDotAndDotDot);
}

//-------------------------------------------------------------------------------------------------

SnapShotModel::~SnapShotModel()
{

}

//-------------------------------------------------------------------------------------------------

QHash<int, QByteArray> SnapShotModel::roleNames() const
{
    QHash<int, QByteArray> hRoleNames;
    hRoleNames[FileNameRole] = "fileName";
    hRoleNames[FilePathRole] = "filePath";
    return hRoleNames;
}

//-------------------------------------------------------------------------------------------------

QVariant SnapShotModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
        return QVariant();
    if ((index.row() < 0) || (index.row() > (rowCount()-1)))
        return QVariant();

    if (role == FileNameRole)
        return QFileSystemModel::data(index, FileNameRole);
    if (role == FilePathRole)
        return QFileSystemModel::data(index, FilePathRole);

    return QVariant();
}
