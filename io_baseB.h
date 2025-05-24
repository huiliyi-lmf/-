#ifndef IO_BASE_H
#define IO_BASE_H
#include <QFile>
#include <QTextStream>
#include"class_base.h"

Vote GetVote(QString line);
QVector<Vote> ReadVote();//读取投票表
QHash<QString, QVector<Vote> > hashTable_Vote(const QVector<Vote>& votes);//用哈希表的结构，用于快速查找
QString VoteToString(Vote& vote_per);//将一个对象转换为字符串
int WriteVoteToFile(QVector<Vote> votes_all);//将投票信息写回文件
void AddVote(Vote& newvoter);//添加新的候选人信息


#endif // IO_BASE_H
