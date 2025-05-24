#ifndef FIND_PASSWORD_H
#define FIND_PASSWORD_H

#include <QWidget>

namespace Ui {
class Find_password;
}

class Find_password : public QWidget
{
    Q_OBJECT

public:
    explicit Find_password(QWidget *parent = nullptr);
    ~Find_password();

private slots:
    void on_btn_back_clicked();

    void on_btn_quit_clicked();

    void on_btn_findpwd_clicked();

private:
    Ui::Find_password *ui;
signals:
    void Show_login_Widget();
};

#endif // FIND_PASSWORD_H
