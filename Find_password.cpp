#include "Find_password.h"
#include "ui_find_password.h"
#include"send_email.h"
#include"check.h"
#include"io_baseB.h"
#include"qurry.h"

Find_password::Find_password(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Find_password)
{
    ui->setupUi(this);
}

Find_password::~Find_password()
{
    delete ui;
}

void Find_password::on_btn_back_clicked()
{
    emit Show_login_Widget();
    this->close();
}

void Find_password::on_btn_quit_clicked()
{
    qApp->quit();
}

void Find_password::on_btn_findpwd_clicked()
{
    if(ui->id->text().isEmpty())
    {
        ui->id->setFocus();
        return;
    }
    if(ui->email->text().isEmpty())
    {
        ui->email->setFocus();
        return;
    }
    QString Regist_MailBox = ui->email->text().toUtf8().data();
    QString UserId = ui->id->text().toUtf8().data();
    if(!Check_EmailBox_Input(Regist_MailBox))
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入不合法，或者不为支持的邮箱类型。（目前仅支持qq）"),QMessageBox::Yes);
        Regist_MailBox = "";
        return;
    }
    QVector<Vote> voters = ReadVote();
    QHash<QString, QVector<Vote> > votes_table = hashTable_Vote(voters);
    QVector<Vote> user = queryVotesById(votes_table,UserId);
    qDebug()<<user.size();
    if(user.empty())
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该账号不存在"),QMessageBox::Yes);
        return;
    }
    if(user[0].email != Regist_MailBox){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该邮箱与该账号不匹配"),QMessageBox::Yes);
        return;
    }
    QString Password = user[0].password;
    qDebug()<<user[0].password;
    //BasicSmtp *sendmail = new PasswordSmtp();
    PasswordSmtp *sendmail = new PasswordSmtp();
    sendmail->sslSocket = new QSslSocket();;
    sendmail->Password = Password;
    if (sendmail->sslSocket == nullptr)
    {
        qDebug() << "Failed to allocate memory for sslSocket";
        return;
        // 处理内存分配失败的情况
    }
    //sendmail->SetValue(Password);//设置密码
    //sendmail->SetValue(Password);//设置密码
    //sendmail->Password = Password;
    sendmail->ReceiverEmailAddress = Regist_MailBox;
    sendmail->sslSocket->connectToHostEncrypted("smtp.qq.com", 465);

    //sendmail->sslSocket->connectToHost("smtp.qq.com",465);
    sendmail->sslSocket->waitForConnected(3000);
    sendmail->CheckConnectState();
    delete sendmail->sslSocket;
    delete sendmail;
    return;
}
