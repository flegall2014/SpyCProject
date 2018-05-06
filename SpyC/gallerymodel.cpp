// Qt
#include <QImage>
#include <QDir>
#include <QDebug>

// Application
#include "gallerymodel.h"

//-------------------------------------------------------------------------------------------------

GalleryModel::GalleryModel(QObject *pParent) : QAbstractListModel(pParent)
{

}

//-------------------------------------------------------------------------------------------------

GalleryModel::GalleryModel(const QString &sSnapShotDir, QObject *pParent) : QAbstractListModel(pParent),
    m_sSnapShotDir(sSnapShotDir)
{

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

QVariant GalleryModel::data(const QModelIndex &index, int iRole) const
{
    if (!index.isValid())
        return QVariant();
    if ((index.row() < 0) || (index.row() > (rowCount()-1)))
        return QVariant();
    SnapShot snapShot = m_vSnaps[index.row()];
    QFileInfo fi(snapShot.filePath);

    if (iRole == FileNameRole)
        return fi.baseName();
    if (iRole == FilePathRole)
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
    qDebug() << "ADDING: " << sSnapShotPath;
    QImage img(sSnapShotPath);
    if (!img.isNull())
    {
        qDebug() << "ADDING: " << sSnapShotPath;
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_vSnaps << SnapShot(sSnapShotPath);
        endInsertRows();
    }
}

//-------------------------------------------------------------------------------------------------

QString GalleryModel::getNextSnapShotName(const QString &sDroneUID)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    int iYear = currentDateTime.date().year();
    int iMonth = currentDateTime.date().month();
    int iDay = currentDateTime.date().day();
    int iHour = currentDateTime.time().hour();
    int iMin = currentDateTime.time().minute();
    int iSec = currentDateTime.time().second();
    QString sUniqueName = QString("%1_%2_%3_%4_%5_%6_%7.jpg").arg(sDroneUID).arg(iYear).arg(iMonth).arg(iDay).arg(iHour).arg(iMin).arg(iSec);
    sUniqueName.replace(" ", "_");
    return QDir(m_sSnapShotDir).absoluteFilePath(sUniqueName);
}
//-------------------------------------------------------------------------------------------------

void GalleryModel::initialize()
{
    beginResetModel();
    m_vSnaps.clear();
    QStringList lImages = QDir(m_sSnapShotDir).entryList(QStringList() << "*", QDir::Files);
    foreach (QString sImagePath, lImages)
    {
        QString sFullImagePath = QDir(m_sSnapShotDir).absoluteFilePath(sImagePath);
        QImage img(sFullImagePath);
        if (!img.isNull())
            m_vSnaps << SnapShot(sFullImagePath);
    }
    endResetModel();
}
