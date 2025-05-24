#include"io_baseB.h"
#include<QDebug>
#include<QDateTime>
Vote GetVote(QString line)
{
    if(line == "")
    {
        return Vote();
    }
    QStringList parts = line.split(","); //数据以，分割
    if (parts.size() < 6&&parts.size()!=1)
    {
        qDebug()<<parts.size();
        throw std::runtime_error("Invalid employee data format"); // 抛出异常，通知调用者数据格式错误
    }
    int votesValue = parts[2].toInt(); //将字符串转换为整型
    int state_voteValue = parts[3].toInt();
    Vote Vote(parts[0], parts[1], votesValue, state_voteValue, parts[4],
        parts[5]);
    return Vote;
}
QVector<Vote> ReadVote()//
{
    QVector<Vote> Votes;
    QFile file("E:/DataStutruekeshe/DataSstructurekesheB/投票表.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))// 处理文件打开失败的情况
    {
        qDebug() << "文件打开失败\n";
        return Votes;
    }

    QTextStream in(&file);
//    in.setCodec("UTF-8"); // 设置文件编码格式
//    in.setAutoDetectUnicode(true); // 自动检测编码格式

    QString line;
    if (!in.atEnd())
    {
        in.readLine(); // 读取并丢弃标题行
    }
    while (!in.atEnd())//返回bool
    {
        try//处理异常
        {
            line = in.readLine();//读取一行
            //qDebug()<<line;
            Vote vote_per = GetVote(line);
            Votes.push_back(vote_per);
        }
        catch(const std::runtime_error &e)
        {
            qDebug() << "Runtime error caught: " << e.what();
            continue;
        }

    }
    file.close();
    return Votes;
}

QHash<QString, QVector<Vote>> hashTable_Vote(const QVector<Vote>& votes)
{
    QHash<QString, QVector<Vote> > voteHash;
    for (const Vote& vote : votes)
    {
        voteHash[vote.id].append(vote); // 使用 id 作为 key，Vote 作为 value
    }
    return voteHash;
}

QString VoteToString(Vote& vote_per)//调用arg方法直接将一个对象转换为字符串
{
    return QString("%1,%2,%3,%4,%5,%6").arg(vote_per.id).arg(vote_per.name)
            .arg(vote_per.votes).arg(vote_per.state_vote).arg(vote_per.password).arg(vote_per.email);
}
int WriteVoteToFile(QVector<Vote> votes_all)//将投票信息写回文件
{
    int i = 0;
    QFile file("E:/DataStutruekeshe/DataSstructurekesheB/投票表.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "文件打开失败\n";
        return 0;
    }
    QTextStream out(&file);
    QString str =  "账号,姓名,获得票数,是否投票(0否1是),密码,邮箱\n";
    out <<str;
    int size = votes_all.size();
    while(i < size)
    {
        QString line = VoteToString(votes_all[i]);
        out<<line<<"\n";
        i++;
    }
    file.close();
    return 1;
}
void AddVote(Vote& newvoter)//添加新的候选人信息
{
    QFile file("E:/DataStutruekeshe/DataSstructurekesheB/投票表.csv");

    if (!file.open(QIODevice::Append | QIODevice::Text)) // 追加模式打开文件
    {
        qDebug() << "文件打开失败，无法追加数据";
        return;
    }

    QTextStream out(&file);
    QString line = VoteToString(newvoter);
    out << line << "\n"; // 将信息写入文件

    file.close(); // 关闭文件
    qDebug() << "新候选人信息已成功追加到文件中";
}

