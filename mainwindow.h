#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QListWidgetItem>
#include <QDebug>
#include "client.h"
#include "chatpanel.h"
#include "addfdialog.h"
#include "client.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void set_parameter(QString userID);


public slots:
     int fetch_friendlist(int i);
private slots:


    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_actionExit_triggered();

    void on_LogoutBtn_clicked();

    void on_addFBtn_clicked();

    void set_id(int j);
    void on_actionLogout_triggered();

private:
    Ui::MainWindow *ui;
    QList<ChatPanel*> chatList;
    bool canOpenStream;
};

#endif // MAINWINDOW_H
