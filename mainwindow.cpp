#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"vote.h"
#include"check.h"
#include"class_base.h"
#include"io_baseB.h"
#include<QMessageBox>
#include"qurry.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->password->setEchoMode(QLineEdit::Password);
    connect(&vote_rel,SIGNAL(Show_login_Widget()),this,SLOT(show_again()));
    setWindowTitle("投票系统登录界面");
    connect(&create_peo,SIGNAL(Show_login_Widget()),this,SLOT(show_again()));
    connect(&find_pwd,SIGNAL(Show_login_Widget()),this,SLOT(show_again()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_login_clicked()
{
    QString id,password;
    int result = Get_Login_Info(ui,id,password);//判断是不是有效信息
    if(result == 0)
    {
        return;
    }
    QVector<Vote> voters = ReadVote();
    QHash<QString, QVector<Vote> > votes_table = hashTable_Vote(voters);
    QVector<Vote> vote_peo = queryVotesById(votes_table,id);
    if(vote_peo.empty())
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该用户不存在。"),QMessageBox::Yes);
        ui->id->clear();
        ui->password->clear();
        return;
    }
    if(vote_peo[0].password != password)
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的密码错误，请重新输入"),QMessageBox::Yes);
        ui->password->clear();
        return;
    }
    Set_Id(id);//为投票界面传入账号

    vote_rel.show();
    vote_rel.UpdateVotes();
    this->hide();
}

void MainWindow::on_btn_create_clicked()
{
    create_peo.show();
    this->hide();

}

void MainWindow::on_btn_forget_clicked()
{
    find_pwd.show();
    this->hide();

}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->password->setEchoMode(QLineEdit::Normal);

    }
    else
    {
        ui->password->setEchoMode(QLineEdit::Password);
    }

}
int Get_Login_Info(Ui::MainWindow *ui,QString &userid,QString &password)
{
    if(ui->id->text().isEmpty())
    {
        ui->id->setFocus();
        return 0;
    }
    if(ui->password->text().isEmpty())//bool值
    {
        ui->password->setFocus();
        return 0;
    }
    userid = ui->id->text().toUtf8().data();
    password = ui->password->text().toUtf8().data();
    if(Check_Password_Right(userid)==0 || Check_Password_Right(password)==0)
    {
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入不合法，用户名，密码，只能输入A~Z,a~z,0~9。"),QMessageBox::Yes);
        return 0;
    }
    return 1;
}



void MainWindow::on_btn_quit_clicked()
{
    qApp->quit();
}
void MainWindow::show_again()
{
    ui->id->clear();
    ui->password->clear();
    this->show();
}
