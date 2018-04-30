#ifndef DRONEBASE_H
#define DRONEBASE_H

// Qt
#include <QObject>
#include <QGeoCoordinate>

// Application
class WayPointModel;

class DroneBase : public QObject
{
    Q_OBJECT

    // UID & video URL
    Q_PROPERTY(QString uid READ uid NOTIFY uidChanged)
    Q_PROPERTY(QString videoUrl READ videoUrl NOTIFY uidChanged)

    // Initial position, current position and heading
    Q_PROPERTY(QGeoCoordinate initialPosition READ initialPosition NOTIFY initialPositionChanged)
    Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(double heading READ heading WRITE setHeading NOTIFY headingChanged)

    // State, edit mode and global status
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString stateText READ stateText NOTIFY stateChanged)
    Q_PROPERTY(int editMode READ editMode WRITE setEditMode NOTIFY editModeChanged)
    Q_PROPERTY(int globalStatus READ globalStatus NOTIFY globalStatusChanged)

    // Battery and GPS level/status
    Q_PROPERTY(int batteryLevel READ batteryLevel WRITE setBatteryLevel NOTIFY batteryLevelChanged)
    Q_PROPERTY(int gpsStrength READ gpsStrength WRITE setGPSStrength NOTIFY gpsStrengthChanged)
    Q_PROPERTY(int batteryStatus READ batteryStatus NOTIFY batteryStatusChanged)
    Q_PROPERTY(int gpsStatus READ gpsStatus NOTIFY gpsStatusChanged)

    // Mission plan model and safety model
    Q_PROPERTY(WayPointModel *missionPlanModel READ missionPlanModel NOTIFY missionPlanModelChanged)
    Q_PROPERTY(WayPointModel *safetyModel READ safetyModel NOTIFY safetyModelChanged)

    Q_ENUMS(Status)
    Q_ENUMS(State)
    Q_ENUMS(EditMode)

public:
    //! Define a status
    enum Status {NOMINAL=Qt::UserRole+1, WARNING, CRITICAL};

    //! Define a drone state
    enum State {IDLE=Qt::UserRole+1, FLYING};

    //! Define a drone mode
    enum EditMode {NONE=Qt::UserRole+1, MISSION_PLAN_EDIT, SAFETY_EDIT, CARTO_EDIT, PAYLOAD_EDIT};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    explicit DroneBase(QObject *pParent=nullptr);

    //! Constructor
    DroneBase(const QString &sDroneUID, const QString &sVideoUrl, const QGeoCoordinate &initialPosition, QObject *pParent=nullptr);

    //! Destructor
    virtual ~DroneBase();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return drone uid
    const QString &uid() const;

    //! Return video url
    const QString &videoUrl() const;

    //! Return battery level
    int batteryLevel() const;

    //! Set battery level
    void setBatteryLevel(int iBatteryLevel);

    //! Return GPS strength
    int gpsStrength() const;

    //! Set GPS strength
    void setGPSStrength(int iStrength);

    //! Return initial position
    const QGeoCoordinate &initialPosition() const;

    //! Return position
    const QGeoCoordinate &position() const;

    //! Set position
    void setPosition(const QGeoCoordinate &pos);

    //! Return heading
    double heading() const;

    //! Set heading
    void setHeading(double dHeading);

    //! Return battery status
    int batteryStatus() const;

    //! Return GPS status
    int gpsStatus() const;

    //! Return global status
    int globalStatus() const;

    //! Return state
    int state() const;

    //! Return state text
    QString stateText() const;

    //! Set state
    void setState(int iState);

    //! Return edit mode
    int editMode() const;

    //! Set edit mode
    void setEditMode(int iMode);

    //! Return mission plan model
    WayPointModel *missionPlanModel() const;

    //! Return safety model
    WayPointModel *safetyModel() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Clear mission plan
    Q_INVOKABLE void clearMissionPlan();

    //! Clear safety
    Q_INVOKABLE void clearSafety();

    //! Add coordinate to mission plan
    Q_INVOKABLE void addCoordinateToMissionPlan(const QGeoCoordinate &geoCoordinate);

    //! Add coordinate to safety
    Q_INVOKABLE void addCoordinateToSafety(const QGeoCoordinate &geoCoordinate);

    //! Set mission plan point position
    Q_INVOKABLE void setMissionPlanPointPosition(int iPointIndex, const QGeoCoordinate &geoCoord);

    //! Set safety point position
    Q_INVOKABLE void setSafetyPointPosition(int iPointIndex, const QGeoCoordinate &geoCoord);

    //! Remove coordinate from safety at index
    Q_INVOKABLE void removeCoordinateFromSafetyPlanAtIndex(int iPointIndex);

    //! Remove coordinate from mission plan at index
    Q_INVOKABLE void removeCoordinateFromMissionPlanAtIndex(int iPointIndex);

private:
    //! UID
    QString m_sDroneUID = "";

    //! Video URL
    QString m_sVideoUrl = "";

    //! Battery level
    int m_iBatteryLevel = 0;

    //! GPS strength
    int m_iGPSStrength = 0;

    //! Original position
    QGeoCoordinate m_initialPosition;

    //! Position
    QGeoCoordinate m_position;

    //! Heading
    double m_dHeading = 0;

    //! Mission plan model
    WayPointModel *m_pMissionPlanModel = nullptr;

    //! Safety model
    WayPointModel *m_pSafetyModel = nullptr;

    //! State
    State m_eState = IDLE;

    //! Mode
    EditMode m_eEditMode = PAYLOAD_EDIT;

signals:
    //! UID changed
    void uidChanged();

    //! Video url changed
    void videoUrlChanged();

    //! Global status changed
    void globalStatusChanged();

    //! Mode changed
    void stateChanged();

    //! Battery level changed
    void batteryLevelChanged();

    //! GPS strength changed
    void gpsStrengthChanged();

    //! Battery status changed
    void batteryStatusChanged();

    //! GPS status changed
    void gpsStatusChanged();

    //! Position changed
    void positionChanged();

    //! Initial position changed
    void initialPositionChanged();

    //! Heading changed
    void headingChanged();

    //! Position status changed
    void positionStatusChanged();

    //! Mission plan model changed
    void missionPlanModelChanged();

    //! Safety model changed
    void safetyModelChanged();

    //! Edit mode changed
    void editModeChanged();
};

Q_DECLARE_METATYPE(DroneBase::State)

#endif // DRONEBASE_H
