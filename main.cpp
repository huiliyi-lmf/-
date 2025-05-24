#include "mainwindow.h"
#include"io_baseB.h"
#include<QTextCodec>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setFont(QFont("Microsoft YaHei", 10));  // 使用支持中文的字体
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QVector<Vote> vote = ReadVote();
//    qDebug()<<vote[0].id;
//    QHash<QString,Vote> test = hashTable_Vote(vote);
//    QString idString = "1323701";
//    if (test.contains(idString))
//    {
//        Vote t2 = test.value(idString);
//        qDebug()<<t2.name;
//    }
//    else
//    {
//        qDebug()<<"dd";
//    }
//    int x = WriteVoteToFile(vote);
//    qDebug()<<x;



    return a.exec();
}
