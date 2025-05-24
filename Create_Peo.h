#ifndef CREATE_PEO_H
#define CREATE_PEO_H

#include <QWidget>

namespace Ui {
class Create_Peo;
}

class Create_Peo : public QWidget
{
    Q_OBJECT

public:
    explicit Create_Peo(QWidget *parent = nullptr);
    ~Create_Peo();

private slots:


    void on_btn_creat_clicked();

    void on_btn_back_clicked();

    void on_btn_quit_clicked();

private:
    Ui::Create_Peo *ui;
signals:
    void Show_login_Widget();
};
int GetNewUserInfo(Ui::Create_Peo*ui,QString &id,QString& name,QString& email,QString &password,QString &confirmpassword);
int CombineCheckInput(QString id,QString password,QString confirmpassword);
#endif // CREATE_PEO_H
