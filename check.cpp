#include<iostream>
#include"check.h"
#include<QStringList>
#include<regex>
#include<io_baseB.h>
#include<regex>
#include<QRegularExpression>
int Check_A_To_Z_Input(QString s)//检查是否含有非法字符
{
    int size = s.size();
    int tag = 1;
    for (int i = 0; i < size; i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9')) {
            continue;
        }
        else {
            tag = 0;
            break;
        }
    }
    return tag;
}
int Check_Password_Right(QString s)//检查密码格式对不对
{
    int size = s.size();
    int right = 1;//判断正确性
    for(int i = 0;i < size;i++)
    {
        if((s[i] <='z'&&s[i]>='a')||(s[i]<='Z'&&s[i]>='A')||(s[i]>='0'&&s[i]<='9'))
        {
            continue;
        }
        else
        {
            right = 0;
            break;
        }
    }
    return right;
}
int Check_EmailBox_Input(QString s)//检查邮箱格式对不对
{

    if(s == "")
    {
        return 0;
    }
    int size = s.size();
    if (!(s[0] > '0' && s[0] <= '9'))
    {
        return 0;
    }
    int position = 0;
    for(int i = 1;i < size;i++)
    {
        if (!(s[i] >= '0' && s[i] <= '9'))
        {
            if(s[i] == '@')
            {
                position = i+1;
                break;
            }
            else
            {
                return 0;
            }
        }
    }
    if(!position)
    {
        return 0;
    }
    QStringList SS = s.split("@");
    if(SS.size() != 2)
    {
        return 0;
    }
    if(SS[0].size() < 5 || SS[0].size() > 11)
    {
        return 0;
    }
    if(SS[1] != "qq.com")
    {
        return 0;
    }
    return 1;//检查邮箱格式对不对
}
bool isValidName(const QString &name) {
    // 空字符串直接返回 false
    if (name.isEmpty()) {
        qDebug() << "The name is empty.";
        return false;
    }

    // 允许的名字字符为汉字和字母
    QRegularExpression regex(R"(^[\p{Han}a-zA-Z]+$)"); // \p{Han} 匹配所有汉字，a-zA-Z 匹配英文字母

    // 检查正则表达式是否合法
    if (!regex.isValid()) {
        qDebug() << "Invalid regular expression: " << regex.errorString();
        return false;
    }

    // 检查输入是否匹配正则表达式
    bool match = regex.match(name).hasMatch();
    if (!match) {
        qDebug() << "Name does not match the pattern.";
    }

    return match;
}
