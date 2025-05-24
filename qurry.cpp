#include"qurry.h"
#include"io_baseB.h"
#include"io_baseB.h"
#include<QDebug>
#include<QDateTime>
#include"qurry.h"
//账号查询信息
QVector<Vote> queryVotesById(const QHash<QString, QVector<Vote>>& voteHash, const QString& id) {
    if (voteHash.contains(id))
    {
        return voteHash[id]; // 返回对应的投票内容
    }
    else
    {
        return QVector<Vote>(); // 如果没有找到，返回空的 QVector
    }
}
//精确姓名查询
QVector<Vote> queryVotesByName(const QVector<Vote>& Votes, const QString& name) {
    QVector<Vote> result;
    for (const Vote& vote : Votes) {
        if (vote.name == name) { // 精确匹配姓名
            result.push_back(vote);//添加函数
        }
    }
    return result; // 返回所有匹配的投票信息
}

//模糊姓名查询
QVector<Vote> queryVotesByPartialName(const QVector<Vote>& Votes, const QString& partialName) {
    QVector<Vote> result;
    for (const Vote& vote : Votes) {
        if (vote.name.contains(partialName)) {
            result.push_back(vote);
        }
    }
    return result; // 返回所有匹配的投票信息
}
