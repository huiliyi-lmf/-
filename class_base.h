#ifndef CLASS_BASE_H
#define CLASS_BASE_H

#include <QStringList>
#include <QVector>
#include<cstdlib>
#include<QDebug>

class Vote
{
public:
    QString id;//帐号
    QString name;
    int votes;//得票数
    int state_vote;//是否已经投票，0否1是
    QString password;//密码
    QString email;//邮箱

    Vote(){}
    Vote(const QString& id,const QString& name,int& votes,int& state_vote,const QString& password,const QString& email)
        :id(id),name(name),votes(votes),state_vote(state_vote),password(password),email(email){}
    ~Vote(){}

};


#endif // CLASS_BASE_H
