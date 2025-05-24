#ifndef VOTE_H
#define VOTE_H

#include <QWidget>
#include"io_baseB.h"
#include<QTableWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

namespace Ui {
class vote;
}

class vote : public QWidget
{
    Q_OBJECT

public:
    explicit vote(QWidget *parent = nullptr);
    void UpdateVotes();
    ~vote();

private slots:
    void on_btn_vote_clicked();

    void on_btn_back_clicked();

    void on_btn_quit_clicked();

    void on_box_sort_currentIndexChanged(int index);

    void on_box_qurry_currentIndexChanged(int index);


private:
    Ui::vote *ui;
    void displayTopCandidates();
    void setupChart(const QStringList &names, const QList<int> &votes);
    void checkWinner(QVector<Vote>& candidates);

signals:
    void Show_login_Widget();
};
void Set_Id(QString id);//为投票界面传递当前候选人的编号
void UpdateInfo(const QVector<Vote>& Votes,QTableWidget *VoteTable);
//投票函数
QVector<Vote> castVote(QVector<Vote>& votes, const QString& voterId, const QString& candidateName);

#endif // VOTE_H
