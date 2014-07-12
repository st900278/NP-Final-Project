#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include "client.h"
#include <QMainWindow>
#include "mainwindow.h"
#include <QtMultimedia/QAudioInput>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia>
#include <QMessageBox>
#include <QFile>
#include <QAudio>
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    MainWindow* mw;
private slots:
    void on_LoginBtn_clicked();
    void handleStateChanged(QAudio::State newState);
    void on_LoginBtn_2_clicked();

private:
    Ui::LoginWindow *ui;
    QFile sourceFile;   // class member.
    QAudioOutput* audio; // class member.
};

#endif // LOGINWINDOW_H
