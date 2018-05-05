// Qt
#include <QImage>
#include <QDir>

// Application
#include "gallerymodel.h"

//-------------------------------------------------------------------------------------------------

GalleryModel::GalleryModel(QObject *pParent) : QAbstractListModel(pParent)
{
    initialize();
}

//-------------------------------------------------------------------------------------------------

GalleryModel::GalleryModel(const QString &sDroneSnapDir, QObject *pParent) : QAbstractListModel(pParent),
    m_sDroneSnapDir(sDroneSnapDir)
{
    initialize();
}

//-------------------------------------------------------------------------------------------------

GalleryModel::~GalleryModel()
{

}

//-------------------------------------------------------------------------------------------------

QHash<int, QByteArray> GalleryModel::roleNames() const
{
    QHash<int, QByteArray> hRoleNames;
    hRoleNames[FileNameRole] = "fileName";
    hRoleNames[FilePathRole] = "filePath";
    return hRoleNames;
}

//-------------------------------------------------------------------------------------------------

QVariant GalleryModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
        return QVariant();
    if ((index.row() < 0) || (index.row() > (rowCount()-1)))
        return QVariant();
    SnapShot snapShot = m_vSnaps[index.row()];
    QFileInfo fi(snapShot.filePath);

    if (role == FileNameRole)
        return fi.baseName();
    if (role == FilePathRole)
        return fi.absoluteFilePath();

    return QVariant();
}

//-------------------------------------------------------------------------------------------------

int GalleryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_vSnaps.size();
}

//-------------------------------------------------------------------------------------------------

void GalleryModel::addSnapShot(const QString &sSnapShotPath)
{
    QImage img(sSnapShotPath);
    if (!img.isNull())
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_vSnaps << SnapShot(sSnapShotPath);
        endInsertRows();
    }
}

//-------------------------------------------------------------------------------------------------

void GalleryModel::initialize()
{
    beginResetModel();
    QStringList lImages = QDir(m_sDroneSnapDir).entryList(QStringList() << "*", QDir::Files);
    foreach (QString sImagePath, lImages)
    {
        QImage img(sImagePath);
        if (!img.isNull())
            m_vSnaps << SnapShot(sImagePath);
    }
    endResetModel();
}
