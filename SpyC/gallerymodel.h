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
    Q_PROPERTY(int currentScreenCapIndex READ currentScreenCapIndex WRITE setCurrentScreenCapIndex NOTIFY currentScreenCapIndexChanged)

public:
    enum Roles {FileNameRole=Qt::UserRole+1, FilePathRole};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    GalleryModel(QObject *pParent=nullptr);

    //! Constructor
    GalleryModel(const QString &sSnapShotDir, QObject *pParent=nullptr);

    //! Destructor
    ~GalleryModel();

    //! Data
    virtual QVariant data(const QModelIndex &index, int iRole) const;

    //! Role names
    virtual QHash<int, QByteArray> roleNames() const;

    //! Row count
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Add snapshot
    Q_INVOKABLE void addSnapShot(const QString &sDroneSnapDir);

    //! Return next snapshot name
    Q_INVOKABLE QString getNextSnapShotName(const QString &sDroneUID);

    //! Initialize
    Q_INVOKABLE void initialize();

    //! Remove current screenCap
    Q_INVOKABLE void removeCurrentScreenCap();

    //! Clear gallery
    Q_INVOKABLE void clear();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return current screenCap index
    int currentScreenCapIndex() const;

    //! Set current screenCap index
    void setCurrentScreenCapIndex(int iIndex);

private:
    //! Snaps
    QVector<SnapShot> m_vSnaps;

    //! Drone snap dir
    QString m_sSnapShotDir = "";

    //! Current screencap index
    int m_iCurrentScreenCapIndex = 0;

signals:
    //! Current screenCap index changed
    void currentScreenCapIndexChanged();
};

#endif // GALLERYMODEL_H
