// Application
#include "Messenger.h"
#define DATA_SIZE 4
#define SERVER_PORT "ServerPort"

static inline QByteArray IntToArray(qint32 source);
static inline qint32 ArrayToInt(QByteArray source);

//-------------------------------------------------------------------------------------------------

Messenger::Messenger(QObject *pParent) : QObject(pParent)
{
    // Read settings
    m_iServerPort = Utils::readSetting(SERVER_PORT).toInt();

    // Socket
    m_pSocket = new QTcpSocket(this);

    // Buffer
    m_pBuffer = new QByteArray();

    // Listen to incoming data
    connect(m_pSocket, SIGNAL(readyRead()), SLOT(onReadyRead()));
}

//-------------------------------------------------------------------------------------------------

Messenger::~Messenger()
{
    delete m_pBuffer;
    m_pBuffer = NULL;
}

//-------------------------------------------------------------------------------------------------

void Messenger::setServerIP(const QString &sServerIP)
{
    // Set IP
    m_sServerIP = sServerIP;

    // Connect to host
    connectToHost(m_sServerIP, m_iServerPort);
}

//-------------------------------------------------------------------------------------------------

bool Messenger::connectToHost(const QString &sHost, quint16 iPort)
{
    m_pSocket->connectToHost(sHost, iPort);
    //return m_pSocket->waitForConnected();
    return true;
}

//-------------------------------------------------------------------------------------------------

bool Messenger::writeData(const QByteArray &baData)
{
    // Make sure socket is connected
    if (m_pSocket->state() == QAbstractSocket::ConnectedState)
    {
        // Write size of data
        m_pSocket->write(IntToArray(baData.size()));

        // Write data
        m_pSocket->write(baData);

        return m_pSocket->waitForBytesWritten();
    }
    return false;
}

//-------------------------------------------------------------------------------------------------

void Messenger::onReadyRead()
{
    qDebug() << "READY READ";

    QTcpSocket *pSocket = static_cast<QTcpSocket *>(sender());

    if (pSocket != NULL) {
        while (pSocket->bytesAvailable() > 0)
        {
            m_pBuffer->append(pSocket->readAll());

            // While can process data, process it
            while ((m_iExpectedDataSize == 0 && m_pBuffer->size() >= DATA_SIZE) || (m_iExpectedDataSize > 0 && m_pBuffer->size() >= m_iExpectedDataSize))
            {
                // If size of data has received completely, then store it on our global variable
                if (m_iExpectedDataSize == 0 && m_pBuffer->size() >= DATA_SIZE)
                {
                    m_iExpectedDataSize = ArrayToInt(m_pBuffer->mid(0, DATA_SIZE));
                    m_pBuffer->remove(0, DATA_SIZE);
                }
                // If data has received completely, then emit our SIGNAL with the data
                if (m_iExpectedDataSize > 0 && m_pBuffer->size() >= m_iExpectedDataSize)
                {
                    QByteArray baData = m_pBuffer->mid(0, m_iExpectedDataSize);
                    m_pBuffer->remove(0, m_iExpectedDataSize);
                    m_iExpectedDataSize = 0;
                    emit dataReady(baData);
                    m_pBuffer->clear();
                }
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------

void Messenger::sendPing()
{
    // Define request
    CXMLNode xRequest;
    xRequest.attributes()[PROPNAME_ACTION] = ACTNAME_PING;

    // Post
    QString sRequest = xRequest.toJsonString();
    writeData(sRequest.simplified().toUtf8());
}

//-------------------------------------------------------------------------------------------------

void Messenger::addShape(const QString &sSerializedShape)
{
    // Define action
    CXMLNode xRequest;
    xRequest.attributes()[PROPNAME_ACTION] = ACTNAME_ADD_SHAPE;

    // Define data
    CXMLNode xData = CXMLNode::parseJSON(sSerializedShape);
    xData.setTag(PROPNAME_DATA);
    xRequest << xData;

    // Post
    QString sRequest = xRequest.toJsonString();
    qDebug() << "SENDING " << sRequest;
    writeData(sRequest.simplified().toUtf8());
}

//-------------------------------------------------------------------------------------------------

void Messenger::removeShape(const QString &sShapeUID)
{
    // Define action
    CXMLNode xRequest;
    xRequest.attributes()[PROPNAME_ACTION] = ACTNAME_REMOVE_SHAPE;

    // Define data
    CXMLNode xData;
    xData.setTag(PROPNAME_DATA);
    xData.attributes()[PROPNAME_SHAPEUID] = sShapeUID;
    xRequest << xData;

    // Post
    QString sRequest = xRequest.toJsonString();
    qDebug() << "SENDING " << sRequest;
    writeData(sRequest.simplified().toUtf8());
}

//-------------------------------------------------------------------------------------------------

void Messenger::setShapeRect(const QString &sShapeUID, const QRect &rNewRect)
{
    // Define action
    CXMLNode xRequest;
    xRequest.attributes()[PROPNAME_ACTION] = ACTNAME_SET_SHAPE_RECT;

    // Define data
    CXMLNode xData;
    xData.setTag(PROPNAME_DATA);
    xData.attributes()[PROPNAME_SHAPEUID] = sShapeUID;

    QStringList lPoints;
    lPoints << QString::number(rNewRect.left()) << QString::number(rNewRect.top())
        << QString::number(rNewRect.right()) << QString::number(rNewRect.bottom());
    xData.attributes()[PROPNAME_SHAPEPOINTS] = lPoints.join(",");

    // Update request
    xRequest << xData;

    // Post
    QString sRequest = xRequest.toJsonString();
    qDebug() << "SENDING " << sRequest;
    writeData(sRequest.simplified().toUtf8());
}

//-------------------------------------------------------------------------------------------------

void Messenger::undoAll(const QStringList &lTargetShapeUIDs)
{
    // Define action
    CXMLNode xRequest;
    xRequest.attributes()[PROPNAME_ACTION] = ACTNAME_UNDO_ALL;

    // Define data
    CXMLNode xData;
    xData.setTag(PROPNAME_DATA);
    xData.attributes()[PROPNAME_SHAPEUID] = lTargetShapeUIDs.join(",");

    // Update request
    xRequest << xData;

    // Post
    QString sRequest = xRequest.toJsonString();
    qDebug() << "SENDING " << sRequest;
    writeData(sRequest.simplified().toUtf8());
}

//-------------------------------------------------------------------------------------------------

qint32 ArrayToInt(QByteArray source)
{
    qint32 itemp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> itemp;
    return itemp;
}

//-------------------------------------------------------------------------------------------------

QByteArray IntToArray(qint32 source)
{
    // Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
