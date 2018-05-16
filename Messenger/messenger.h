#ifndef MESSENGER_H
#define MESSENGER_H

// Qt
#include <QtCore>
#include <QtNetwork>
#include "messenger_global.h"

class MESSENGERSHARED_EXPORT Messenger : public QObject
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    explicit Messenger(QObject *pParent=nullptr);

    //! Destructor
    ~Messenger();

    //-------------------------------------------------------------------------------------------------
    // Set server IP
    //-------------------------------------------------------------------------------------------------

    //! Set server IP
    void setServerIP(const QString &sServerIP);

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Ping
    void sendPing();

    //! Add shape
    void addShape(const QString &sSerializedShape);

    //! Remove shape
    void removeShape(const QString &sShapeUID);

    //! Set shape rect
    void setShapeRect(const QString &sShapeUID, const QRect &rNewRect);

    //! Undo all
    void undoAll(const QStringList &lTargetShapeUIDs);

public slots:
    //-------------------------------------------------------------------------------------------------
    // Slots
    //-------------------------------------------------------------------------------------------------

    //! Connect to host
    bool connectToHost(const QString &sHost, quint16 iPort);

    //! Write data
    bool writeData(const QByteArray &baData);

    //! Ready read
    void onReadyRead();

private:
    //! Server IP
    QString m_sServerIP = "127.0.0.1";

    //! Server port
    qint32 m_iServerPort = 8080;

    //! Own socket
    QTcpSocket *m_pSocket = nullptr;

    //! Buffer
    QByteArray *m_pBuffer = nullptr;

    //! Expected data size
    qint32 m_iExpectedDataSize = 0;

signals:
    //-------------------------------------------------------------------------------------------------
    // Signals
    //-------------------------------------------------------------------------------------------------

    //! Data received
    void dataReady(const QByteArray &ba);
};

#endif // MESSENGER_H
