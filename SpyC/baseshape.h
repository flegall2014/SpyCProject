#ifndef BASESHAPE_H
#define BASESHAPE_H

// Qt
#include <QObject>
#include <QGeoCoordinate>
#include <QVector>
#include <QGeoPath>
#define DEFAULT_RADIUS 500

class BaseShape : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoPath path READ path NOTIFY pathChanged)
    Q_PROPERTY(QGeoCoordinate center READ center NOTIFY pathChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int type READ type NOTIFY typeChanged)
    Q_ENUMS(Type)

public:
    //! Type
    enum Type {RECTANGLE=Qt::UserRole+1, TRIANGLE, CIRCLE};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Destructor
    virtual ~BaseShape();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Rotate
    Q_INVOKABLE virtual void rotate(double dAngle);

    //! Move to
    Q_INVOKABLE void moveTo(const QGeoCoordinate &pos);

    //! Rescale
    Q_INVOKABLE virtual void rescale(int iIncrement);

    //! Set latitude at index
    Q_INVOKABLE void setLatitudeAtIndex(int iIndex, double dLatitude);

    //! Set longitude at index
    Q_INVOKABLE void setLongitudeAtIndex(int iIndex, double dLongitude);

    //! Set altitude at index
    Q_INVOKABLE void setAltitudeAtIndex(int iIndex, double dAltitude);

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return path
    const QGeoPath &path() const;

protected:
    //! Constructor
    BaseShape(QObject *pParent=nullptr);

    //! Compute center
    QGeoCoordinate computeCenter() const;

protected:
    //! Points
    QGeoPath m_path;

    //! Center
    QGeoCoordinate m_center;

    //! Type
    Type m_eType = RECTANGLE;

private:
    //! Return count
    int count() const;

    //! Return type
    int type() const;

    //! Return center
    const QGeoCoordinate &center() const;

signals:
    //! Path changed
    void pathChanged();

    //! Count changed
    void countChanged();

    //! Selected changed
    void selectedChanged();

    //! Type changed
    void typeChanged();
};

Q_DECLARE_METATYPE(BaseShape::Type)

class RectangleShape : public BaseShape
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    RectangleShape(QObject *pParent=nullptr);

    //! Constructor
    RectangleShape(const QGeoCoordinate &topLeft, const QGeoCoordinate &bottomRight, QObject *pParent=nullptr);

    //! Destructor
    virtual ~RectangleShape();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return top left
    QGeoCoordinate topLeft() const;

    //! Return bottom right
    QGeoCoordinate bottomRight() const;
};

class CircleShape : public BaseShape
{
    Q_OBJECT
    Q_PROPERTY(double radius READ radius NOTIFY pathChanged)

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

    //! Return radius
    double radius() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Rotate
    Q_INVOKABLE virtual void rotate(double dAngle);

    //! Rescale
    Q_INVOKABLE virtual void rescale(int iIncrement);

private:
    //! Circle radius
    double m_dRadius = 0;
};

class TriangleShape : public BaseShape
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    TriangleShape(QObject *pParent=nullptr);

    //! Constructor
    TriangleShape(const QGeoCoordinate &point1, const QGeoCoordinate &point2, const QGeoCoordinate &pojnt3, QObject *pParent=nullptr);

    //! Destructor
    virtual ~TriangleShape();
};

#endif // BASESHAPE_H
