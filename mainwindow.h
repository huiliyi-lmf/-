#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"vote.h"
#include"Find_password.h"
#include"Create_Peo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_login_clicked();

    void on_btn_create_clicked();

    void on_btn_forget_clicked();

    void on_checkBox_clicked(bool checked);



    void on_btn_quit_clicked();
    void show_again();


private:
    Ui::MainWindow *ui;
    vote vote_rel;
    Find_password find_pwd;
    Create_Peo create_peo;

};
int Get_Login_Info(Ui::MainWindow *ui,QString &userid,QString &password);
#endif // MAINWINDOW_H
