#ifndef BASESHAPE_H
#define BASESHAPE_H

// Qt
#include <QObject>
#include <QGeoCoordinate>

class BaseShape : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int type READ type NOTIFY typeChanged)
    Q_PROPERTY(bool selected READ selected WRITE select NOTIFY selectedChanged)
    Q_PROPERTY(QList<QGeoCoordinate> boundingRect READ boundingRect NOTIFY boundingRectChanged)

    Q_ENUMS(Type)

public:
    enum Type {CIRCLE=Qt::UserRole+1, RECTANGLE, TRIANGLE};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    BaseShape(QObject *pParent=nullptr);

    //! Constructor
    BaseShape(const Type &eType, QObject *pParent=nullptr);

    //! Destructor
    virtual ~BaseShape();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return type
    int type() const;

    //! Return selected state
    bool selected() const;

    //! Select
    void select(bool bSelected);

    //! Set position
    Q_INVOKABLE virtual void setPosition(const QGeoCoordinate &position);

private:
    //! Bounding rect
    virtual QList<QGeoCoordinate> boundingRect() const;

private:
    //! Type
    Type m_eType=CIRCLE;

    //! Selected?
    bool m_bSelected = false;

signals:
    //! Type changed
    void typeChanged();

    //! Selected changed
    void selectedChanged();

    //! Bounding rect changed
    void boundingRectChanged();
};

class RectShape : public BaseShape
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate topLeft READ topLeft WRITE setTopLeft NOTIFY topLeftChanged)
    Q_PROPERTY(QGeoCoordinate bottomRight READ bottomRight WRITE setBottomRight NOTIFY bottomRightChanged)

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    RectShape(QObject *pParent=nullptr);

    //! Constructor
    RectShape(const QGeoCoordinate &topLeft, const QGeoCoordinate &bottomRight, QObject *pParent=nullptr);

    //! Destructor
    virtual ~RectShape();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return top left
    const QGeoCoordinate &topLeft() const;

    //! Set top left
    void setTopLeft(const QGeoCoordinate &topLeft);

    //! Return bottom right
    const QGeoCoordinate &bottomRight() const;

    //! Set bottom right
    void setBottomRight(const QGeoCoordinate &topLeft);

private:
    //! Bounding rect
    virtual QList<QGeoCoordinate> boundingRect() const;

private:
    //! Top left
    QGeoCoordinate m_topLeft;

    //! Bottom right
    QGeoCoordinate m_bottomRight;

signals:
    //! Top left changed
    void topLeftChanged();

    //! Bottom right changed
    void bottomRightChanged();
};

class CircleShape : public BaseShape
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate center READ center WRITE setCenter NOTIFY centerChanged)
    Q_PROPERTY(double radius READ radius WRITE setRadius NOTIFY radiusChanged)

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    CircleShape(QObject *pParent=nullptr);

    //! Constructor
    CircleShape(const QGeoCoordinate &center, double dRadius, QObject *pParent=nullptr);

    //! Destructor
    virtual ~CircleShape();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return center
    const QGeoCoordinate &center() const;

    //! Set center
    void setCenter(const QGeoCoordinate &center);

    //! Return radius
    double radius() const;

    //! Set radius
    void setRadius(double dRadius);

    //! Set position
    Q_INVOKABLE virtual void setPosition(const QGeoCoordinate &position);

private:
    //! Bounding rect
    virtual QList<QGeoCoordinate> boundingRect() const;

private:
    //! Center
    QGeoCoordinate m_center;

    //! Radius (meters)
    double m_dRadius = 0;

signals:
    //! Center changed
    void centerChanged();

    //! Radius changed
    void radiusChanged();
};

class TriangleShape : public BaseShape
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate point1 READ point1 WRITE setPoint1 NOTIFY point1Changed)
    Q_PROPERTY(QGeoCoordinate point2 READ point2 WRITE setPoint2 NOTIFY point2Changed)
    Q_PROPERTY(QGeoCoordinate point3 READ point3 WRITE setPoint3 NOTIFY point3Changed)

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    TriangleShape(QObject *pParent=nullptr);

    //! Constructor
    TriangleShape(const QGeoCoordinate &point1, const QGeoCoordinate &point2, const QGeoCoordinate &point3, QObject *pParent=nullptr);

    //! Destructor
    virtual ~TriangleShape();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return point1
    const QGeoCoordinate &point1() const;

    //! Set point1
    void setPoint1(const QGeoCoordinate &point);

    //! Return point2
    const QGeoCoordinate &point2() const;

    //! Set point2
    void setPoint2(const QGeoCoordinate &point);

    //! Return point3
    const QGeoCoordinate &point3() const;

    //! Set point3
    void setPoint3(const QGeoCoordinate &point);

private:
    //! Bounding rect
    virtual QList<QGeoCoordinate> boundingRect() const;

private:
    //! Point1
    QGeoCoordinate m_point1;

    //! Point2
    QGeoCoordinate m_point2;

    //! Point3
    QGeoCoordinate m_point3;

signals:
    //! Point1 changed
    void point1Changed();

    //! Point2 changed
    void point2Changed();

    //! Point3 changed
    void point3Changed();
};

#endif // BASESHAPE_H
