#include "chatpanel.h"
#include "ui_chatpanel.h"
#include<time.h>
#include<cstdio>
#include<cstdlib>
ChatPanel::ChatPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatPanel)
{
    ui->setupUi(this);




}
void ChatPanel::updatePicture(){

    QGraphicsScene* scene = new QGraphicsScene(this);
    QGraphicsPixmapItem* item;
    //qDebug()<<index;
    QFile picfile("./tmp/pic"+QString::number(index)+".jpeg");
    qDebug()<<picfile.exists();
    if(picfile.exists()){

        item = new QGraphicsPixmapItem(QPixmap("./tmp/pic"+QString::number(index)+".jpeg"));
        qDebug()<<"./tmp/pic"+QString::number(index)+".jpeg";
        scene->addItem(item);
        ui->chatCView->setScene(scene);
        index++;
        picfile.remove();
    }

}
void ChatPanel::showAndSend(){



}
void ChatPanel::updateChat(){
    QByteArray friendQB=this->friendID.toLocal8Bit();
    QByteArray myQB=this->myID.toLocal8Bit();
    refreshChat->stop();
    char *frichar=friendQB.data();
    char res[MAXLINE+1];
    getmsgCommand(frichar,res,1024);
    QString *qs;
    qDebug()<<qs;
    qs = new QString(res);
    if(qs->compare("NULL",Qt::CaseSensitive)!=0){
        ui->chatText->append(*qs);
    }
    delete qs;
    refreshChat->start(1500);
}
void ChatPanel::set_parameters(QString name,QString my){

    ui->friendEdit->setText(name);
    this->friendID = name;
    this->myID = my;
    refreshpeerPic = new QTimer(this);
    refreshChat = new QTimer(this);
    sendrefresh = new QTimer(this);
    index = 0;
    connect(refreshpeerPic, SIGNAL(timeout()), this, SLOT(updatePicture()));
    connect(refreshChat, SIGNAL(timeout()), this, SLOT(updateChat()));
    connect(sendrefresh, SIGNAL(timeout()), this, SLOT(showAndSend()));
    /* build client and set file descriptor*/

    /**/
    refreshpeerPic->start(10);
    refreshChat->start(1500);
}
ChatPanel::~ChatPanel()
{
    delete ui;
}

void ChatPanel::on_sendMsgBtn_clicked()
{
    QByteArray friendQB=this->friendID.toLocal8Bit();
    QByteArray msgQB=this->ui->msgText->toPlainText().toLocal8Bit();
    char *frichar=friendQB.data();
    char *msgchar=msgQB.data();
    msgCommand(frichar,msgchar);

    ui->chatText->append(this->myID+": "+this->ui->msgText->toPlainText());
    ui->msgText->clear();
}

void ChatPanel::on_ChatPanel_finished(int result)
{
    //this->rstop();
    this->refreshChat->stop();
    this->refreshpeerPic->stop();
    char *friendQB = this->friendID.toLocal8Bit().data();
    if(this->onCamera){
        qDebug()<<"LEAVE";
        lrCommand(friendQB);
        exitCamera();

    }
}
QString ChatPanel::getName(){
    return this->friendID;
}
