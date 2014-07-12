#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
class TCPsocket : public QObject
{
    Q_OBJECT
public:
    explicit TCPsocket(QObject *parent = 0);

    void Test();

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *socket;

};

#endif // TCPSOCKET_H
