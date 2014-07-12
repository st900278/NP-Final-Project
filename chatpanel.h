#ifndef CHATPANEL_H
#define CHATPANEL_H

#include <QDialog>
#include <QTimer>
#include <QPixmap>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QFile>
#include "client.h"
namespace Ui {
class ChatPanel;
}

class ChatPanel : public QDialog
{
    Q_OBJECT

public:
    explicit ChatPanel(QWidget *parent = 0);
    ~ChatPanel();
    void set_parameters(QString name, QString my);
    void add_message(QString name);
    QString getName();
    bool onCamera;
private slots:
    void updatePicture();
    void on_sendMsgBtn_clicked();
    void updateChat();
    void showAndSend();
    void on_ChatPanel_finished(int result);

private:
    Ui::ChatPanel *ui;
    QTimer *refreshpeerPic;
    QTimer *refreshChat;
    QTimer *sendrefresh;
    int index;
    int streamfd;
    QString friendID;
    QString myID;

};

#endif // CHATPANEL_H
