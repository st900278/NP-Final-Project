#include "tcpsocket.h"

TCPsocket::TCPsocket(QObject *parent) :
    QObject(parent)
{
}
void TCPsocket::Test()
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

    qDebug() << "Connecting,..";

    socket->connectToHost("www.yahoo.com.tw", 80);

    if(!socket->waitForDisconnected(23000))
    {
        qDebug() << "Error: " << socket->errorString();
    }

}

void TCPsocket::connected()
{
    qDebug() << "Connected!";

    socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");

}

void TCPsocket::disconnected()
{
    qDebug() << "Disconnected!";
}

void TCPsocket::bytesWritten(qint64 bytes)
{
    qDebug() << "We wrote: " << bytes;
}

void TCPsocket::readyRead()
{
    qDebug() << "Reading...";
    qDebug() << socket->readLine();
}
