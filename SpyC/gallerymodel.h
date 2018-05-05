#ifndef GALLERYMODEL_H
#define GALLERYMODEL_H

// Qt
#include <QAbstractListModel>
#include <QDateTime>
class GalleryModel;

struct SnapShot
{
    SnapShot() {
    }
    SnapShot(const QString &sFilePath) : filePath(sFilePath)
    {
    }
    QString filePath = "";
};

class GalleryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {FileNameRole=Qt::UserRole+1, FilePathRole};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    GalleryModel(QObject *pParent=nullptr);

    //! Constructor
    GalleryModel(const QString &sDroneSnapDir, QObject *pParent=nullptr);

    //! Destructor
    ~GalleryModel();

    //! Data
    virtual QVariant data(const QModelIndex &index, int role) const;

    //! Role names
    virtual QHash<int, QByteArray> roleNames() const;

    //! Row count
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Add snapshot
    Q_INVOKABLE void addSnapShot(const QString &sDroneSnapDir);

    //! Initialize
    void initialize();

private:
    //! Snaps
    QVector<SnapShot> m_vSnaps;

    //! Drone snap dir
    QString m_sDroneSnapDir = "";
};

#endif // GALLERYMODEL_H
