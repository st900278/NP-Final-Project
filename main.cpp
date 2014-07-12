#include "loginwindow.h"
#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    //TCPsocket mTest;
    //mTest.Test();
    QDir q;
    q.mkdir("tmp");
    w.show();

    return a.exec();
}

