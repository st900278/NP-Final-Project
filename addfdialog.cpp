#include "addfdialog.h"
#include "ui_addfdialog.h"

addfDialog::addfDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addfDialog)
{
    ui->setupUi(this);
}

addfDialog::~addfDialog()
{
    delete ui;
}




void addfDialog::on_okokbtn_clicked()
{
    qDebug()<<"click";
    QByteArray fribyte=ui->frinameEdit->text().toLocal8Bit ();
    char *frichar=fribyte.data();
    if(addFriendCommand(frichar)==0){
            this->close();
    }else{
            this->ui->statusLabel->setText("Error Occured! Please contact us");
    }


}

void addfDialog::on_cancelBtn_clicked()
{
    this->close();
}
