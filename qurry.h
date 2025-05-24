#ifndef QURRY_H
#define QURRY_H

#include <QStringList>
#include <QVector>
#include<cstdlib>
#include<QDebug>
#include"io_baseB.h"
#include<QDateTime>

//账号查询信息
QVector<Vote> queryVotesById(const QHash<QString, QVector<Vote>>& voteHash, const QString& id);
//精确的姓名查询
QVector<Vote> queryVotesByName(const QVector<Vote>& Votes, const QString& name);
//模糊姓名查询
QVector<Vote> queryVotesByPartialName(const QVector<Vote>& Votes, const QString& partialName);

#endif // QURRY_H
