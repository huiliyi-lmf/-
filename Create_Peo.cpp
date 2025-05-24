#include "Create_Peo.h"
#include "ui_create_peo.h"
#include"io_baseB.h"
#include<QMessageBox>
#include"check.h"
#include"qurry.h"

Create_Peo::Create_Peo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Create_Peo)
{
    ui->setupUi(this);
}

Create_Peo::~Create_Peo()
{
    delete ui;
}



void Create_Peo::on_btn_creat_clicked()
{
    QString id,name,email,password,confirmpassword;
        int level = GetNewUserInfo(ui,id,name,email,password,confirmpassword);//原来之前把Email没用引用
        if(!level)
        {
            return;
        }
        qDebug()<<email;
        if(!CombineCheckInput(id,password,confirmpassword))
        {
            QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入不合法，用户名，密码，只能输入A~Z,a~z,0~9。"),QMessageBox::Yes);
            return;
        }
        if(!isValidName(name))
        {
            QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入不合法，姓名只能是字母或者汉字形式"),QMessageBox::Yes);
            return;
        }
        if(!Check_EmailBox_Input(email))
        {
            qDebug()<<email;
            QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入不合法，邮箱只能是qq邮箱格式"),QMessageBox::Yes);
            return;
        }
        if(password != confirmpassword)
        {
            QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您并没有确认您的密码，请重试。"),QMessageBox::Yes);
            return;
        }
        QVector<Vote> voters = ReadVote();
        QHash<QString, QVector<Vote> > votes_table = hashTable_Vote(voters);
        QVector<Vote> vote_now = queryVotesById(votes_table,id);
        if(!vote_now.empty())
        {
            QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该用户已经被注册，请更换您的用户名。"),QMessageBox::Yes);
            return;
        }
        int votes = 0;
        int state_vote = 0;
        Vote voter_new = Vote(id,name,votes,state_vote,password,email);
        AddVote(voter_new);
        ui->id->clear();
        ui->password->clear();
        ui->confirmpassword->clear();
        ui->name->clear();
        ui->email->clear();
        QMessageBox::warning(NULL,QObject::tr("恭喜"),QObject::tr("注册成功！"),QMessageBox::Yes);

}
int GetNewUserInfo(Ui::Create_Peo*ui,QString &id,QString& name,QString& email,QString &password,QString &confirmpassword)
{
    if(ui->id->text().isEmpty()){
        ui->id->setFocus();
        return 0;
    }
    if(ui->name->text().isEmpty()){
        ui->name->setFocus();
        return 0;
    }
    if(ui->email->text().isEmpty()){
        ui->email->setFocus();
        return 0;
    }
    if(ui->password->text().isEmpty()){
        ui->password->setFocus();
        return 0;
    }
    if(ui->confirmpassword->text().isEmpty()){
        ui->confirmpassword->setFocus();
        return 0;
    }
    id = ui->id->text().toUtf8().data();
    name = ui->name->text().toUtf8().data();
    email = ui->email->text().toUtf8().data();
    password = ui->password->text().toUtf8().data();
    qDebug()<<email<<"jj";
    confirmpassword = ui->confirmpassword->text().toUtf8().data();

    return 1;
}
int CombineCheckInput(QString id,QString password,QString confirmpassword)
{
    int tag = Check_A_To_Z_Input(id) && Check_A_To_Z_Input(password) && Check_A_To_Z_Input(confirmpassword);
    return tag;
}

void Create_Peo::on_btn_back_clicked()
{
    emit Show_login_Widget();
    this->close();
}

void Create_Peo::on_btn_quit_clicked()
{
    qApp->quit();

}
