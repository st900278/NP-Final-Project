#include "loginwindow.h"
#include "ui_loginwindow.h"

QFile sourceFile;   // class member.
QAudioOutput* audio; // class member.

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    //connect to server
    beginclient();

}

LoginWindow::~LoginWindow()
{
    delete ui;
}
void LoginWindow::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
        case QAudio::IdleState:
            // Finished playing (no more data)
            audio->stop();
            sourceFile.close();
            delete audio;
            break;

        case QAudio::StoppedState:
            // Stopped for other reasons
            if (audio->error() != QAudio::NoError) {
                // Error handling
            }
            break;

        default:
            // ... other cases as appropriate
            break;
    }
}

void LoginWindow::on_LoginBtn_clicked()
{

       /*sourceFile.setFileName("/home/henry/NP_fQt5/audio0.raw");
       sourceFile.open(QIODevice::ReadOnly);

       QAudioFormat format;
       // Set up the format, eg.
       format.setSampleRate(16000);
       format.setChannelCount(2);
       format.setSampleSize(8);
       format.setCodec("audio/pcm");
       format.setByteOrder(QAudioFormat::BigEndian);
       format.setSampleType(QAudioFormat::UnSignedInt);

       QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
       if (!info.isFormatSupported(format)) {
           qWarning() << "Raw audio format not supported by backend, cannot play audio.";
           return;
       }

       audio = new QAudioOutput(format, this);
       connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
       audio->start(&sourceFile);*/


    //transfer Qstring to byteArray to char array
    /*mw = new MainWindow(this);
    this->close();
    mw->fetch_friendlist();
    mw->show();*/
    QByteArray usrbyte=ui->IDEdit->text().toLocal8Bit ();
    QByteArray pwdbyte=ui->pwdEdit->text().toLocal8Bit ();
    char *userchar=usrbyte.data();
    char *pwdchar=pwdbyte.data();

    //excute login command
    switch(loginCommand(userchar,pwdchar)){
        case 0:
            qDebug()<<"0";
            mw = new MainWindow(this);
            this->close();
            mw->set_parameter(ui->IDEdit->text());
            mw->fetch_friendlist(0);
            mw->show();
            break;
        case -2: //Login faill
            ui->status_Label->setText("Fail");
            break;
        case -1://disconnected
            break;
    }

}

void LoginWindow::on_LoginBtn_2_clicked()
{
    QByteArray usrbyte=ui->IDEdit->text().toLocal8Bit ();
    QByteArray pwdbyte=ui->IDEdit->text().toLocal8Bit ();
    char *userchar=usrbyte.data();
    char *pwdchar=pwdbyte.data();
    switch(createCommand(userchar,pwdchar)){
        case 0:
            ui->status_Label->setText("Create Account Success");
            break;
        case -2: //Create faill
            ui->status_Label->setText("Create Account Fail");
            break;
        case -1://disconnected
            break;
    }
    //int r = QMessageBox::warning(this,"Infromation","",QMessageBox)
}
