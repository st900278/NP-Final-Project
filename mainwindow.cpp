#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::fetch_friendlist(int i){

    char result[1024];
    char result2[1024];
    QString *resultobj;
    QString *statusobj;
    getFriendCommand(result,1024);
    resultobj = new QString(result);
    getFriendStatus(result2,1024);
    statusobj = new QString(result2);

    QStringList friendList = resultobj->split(";");
    QStringList statusList = statusobj->split(";");
    bool online=false;

    ui->listWidget->clear();
    foreach (QString str, friendList) {
        if(str.compare("",Qt::CaseSensitive)!=0){
            online=false;
            foreach(QString str2,statusList){
                if(str.compare(str2,Qt::CaseSensitive)==0){

                    ui->listWidget->addItem(new QListWidgetItem(QIcon(":/icon/online-icon.png"),str));
                    online=true;
                }
            }
            if(!online){
                 ui->listWidget->addItem(new QListWidgetItem(QIcon(":/icon/offline-icon.png"),str));
            }

            //ui->listWidget->addItem(new QListWidgetItem(QIcon(":/icon/offline-icon.png"),str));
        }
    }


    /*for(i=0;i<10;i++){

    }*/
    return 0;
}

void MainWindow::set_parameter(QString userID){
    ui->nameLabel->setText(userID);
    canOpenStream = true;

}
void MainWindow::set_id(int j){

}
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug() << item->text();
    bool open;
    ChatPanel *q;
    char *friendQB = item->text().toLocal8Bit().data();
    open = true;

    foreach(ChatPanel *cp,chatList){
        if(cp->getName().compare(item->text())==0){

            if(!cp->isVisible()){
                chatList.removeOne(cp);
                if(cp->onCamera==true){
                    this->canOpenStream = true;
                }
                delete cp;
                open=true;
            }else{
                cp->activateWindow();
                open=false;
            }

            break;
        }
    }
    if(open){

        q = new ChatPanel(this);

        q->set_parameters(item->text(),ui->nameLabel->text());
        if(canOpenStream){
            roomCommand(friendQB);
            qDebug()<<"ROOM OPEN";
            canOpenStream=false;
            q->onCamera = true;
            buildCamera();
        }else{
            q->onCamera =false;
        }
        q->setWindowTitle("Message:"+item->text());
        q->show();

        connect(q,SIGNAL(finished(int)), this, SLOT(set_id(int)));
        chatList<<q;//record the chat;

    }


}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_LogoutBtn_clicked()
{
    if(logoutCommand()==0){
        this->close();
        this->parentWidget()->show();
        delete this;
    }else{

    }
}




void MainWindow::on_addFBtn_clicked()
{
    qDebug()<<"click";
    addfDialog q(this);
    connect(&q,SIGNAL(finished(int)), this, SLOT(fetch_friendlist(int)));
    q.exec();
    q.raise();
    q.activateWindow();
    q.show();


}

void MainWindow::on_actionLogout_triggered()
{
    if(logoutCommand()==0){
        this->close();
        this->parentWidget()->show();
        delete this;
    }else{

    }
}
