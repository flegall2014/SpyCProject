#ifndef SNAPSHOTMODEL_H
#define SNAPSHOTMODEL_H

// Qt
#include <QFileSystemModel>
#include <QSortFilterProxyModel>
class SnapShotModel;

class SnapShotModelFilter : public QSortFilterProxyModel
{
public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    SnapShotModelFilter(QObject *pParent=nullptr);

    //! Constructor
    SnapShotModelFilter(const QString &sDroneSnapShotDir, QObject *pParent=nullptr);

    //! Destructor
    ~SnapShotModelFilter();

    //! Accept row?
    virtual bool filterAcceptsRow(int iSrcRow, const QModelIndex &source_parent=QModelIndex()) const;

private:
    //! Src model
    SnapShotModel *m_pSrcModel = nullptr;
};

class SnapShotModel : public QFileSystemModel
{
public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    SnapShotModel(QObject *pParent=nullptr);

    //! Constructor
    SnapShotModel(const QString &sDroneSnapDir, QObject *pParent=nullptr);

    //! Destructor
    ~SnapShotModel();

    //! Data
    virtual QVariant data(const QModelIndex &index, int role) const;

    //! Role names
    virtual QHash<int, QByteArray> roleNames() const;
};

#endif // SNAPSHOTMODEL_H
