#ifndef CHECK_H
#define CHECK_H
#include<QString>
int Check_A_To_Z_Input(QString s);//检查是否含有非法字符
int Check_Password_Right(QString s);//检查输入的字符是否正确
int Check_EmailBox_Input(QString s);//检查邮箱格式是否正确
bool isValidName(const QString& name);//检查名字是否仅含字母或者汉字

#endif // CHECK_H
