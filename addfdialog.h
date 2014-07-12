#ifndef ADDFDIALOG_H
#define ADDFDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "client.h"
#include <QDebug>
namespace Ui {
class addfDialog;
}

class addfDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addfDialog(QWidget *parent = 0);
    ~addfDialog();

private slots:




    void on_okokbtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::addfDialog *ui;
};

#endif // ADDFDIALOG_H
