#include "vote.h"
#include "ui_vote.h"
#include"io_baseB.h"
#include"sort.h"
#include"qurry.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QBarSet>
#include <QBarSeries>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QPushButton>
#include <QList>
#include <QStringList>
#include <algorithm>
#include<QLabel>


#include<QMessageBox>
using namespace QtCharts;

QString id_now;
vote::vote(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vote)
{
    ui->setupUi(this);
    //使用下面两句可以实现
    UpdateVotes();
}
void vote::UpdateVotes()
{
    QVector<Vote> voters = ReadVote();
    UpdateInfo(voters,ui->table);
    displayTopCandidates();
    ui->peo_result->setReadOnly(true);
}

vote::~vote()
{
    delete ui;
}

void vote::on_btn_vote_clicked()
{
    int currentRow = ui->table->currentRow(); // 获取当前所选行
    if (currentRow < 0) {
        QMessageBox::warning(this, "警告", "请先选择一个候选人。");
        return;
    }
    QVector<Vote> voters = ReadVote();
    QHash<QString, QVector<Vote> > votes_table = hashTable_Vote(voters);
    QVector<Vote> vote_now = queryVotesById(votes_table,id_now);
    if(vote_now.size() == 0)
        return;
    if (vote_now[0].state_vote == 1) {
        QMessageBox::warning(this, "投票警告", "您已经投过票，不能再次投票。");
        return;
    }

    // 假设我们在表格中有候选人的票数在某一列，比如第1列（index从0开始）
    QTableWidgetItem* item = ui->table->item(currentRow, 2); // 根据你的设计选择合适的列
    if (item)
    {
        // 获取当前票数并加1
        int currentVotes = item->text().toInt();
        item->setText(QString::number(currentVotes + 1)); // 更新票数
        QTableWidgetItem* item1 = ui->table->item(currentRow, 0);
        QString candidateId = item1->text();
        castVote(voters, id_now, candidateId);
        displayTopCandidates();
    }
    else
    {
        QMessageBox::warning(this, "错误", "无法获取候选人信息。");
    }

}

void vote::on_btn_back_clicked()
{
    emit Show_login_Widget();
    this->close();
}

void vote::on_btn_quit_clicked()
{
    qApp->quit();
}
void Set_Id(QString id)
{
    id_now = id;
}
void UpdateInfo(const QVector<Vote>& Votes,QTableWidget *VoteTable)
{
    VoteTable->setRowCount(Votes.size());
    for (int i = 0; i < Votes.size(); ++i)
    {
        const Vote& Vote = Votes[i];
        // 在表格中显示员工信息
        VoteTable->setItem(i, 0, new QTableWidgetItem(Vote.id));
        VoteTable->setItem(i, 1, new QTableWidgetItem(Vote.name));
        VoteTable->setItem(i, 2, new QTableWidgetItem(QString::number(Vote.votes)));//这里要记得转化成QString

    }
    // 调整表格大小
    VoteTable->resizeColumnsToContents();
}

void vote::on_box_sort_currentIndexChanged(int index)
{
    QVector<Vote> em = ReadVote();
    QVector<Vote> voters;
    switch(index)
    {
    case 0:
        break;
    case 1:
        voters = sort_up(em);
        UpdateInfo(voters,ui->table);
        ui->box_sort->setCurrentIndex(0);
        break;
    case 2:
        voters = sort_down(em);
        UpdateInfo(voters,ui->table);
        ui->box_sort->setCurrentIndex(0);
        break;
    default:
        break;
    }

}

void vote::on_box_qurry_currentIndexChanged(int index)
{
    QString s1 = ui->qurry_1->text();
    QVector<Vote> voters = ReadVote();
    //int index = ui->comboBox_2->currentIndex();
    switch(index)
    {
    case 0:
        break;
    case 1:
        if(ui->qurry_1->text().isEmpty())//编号
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            ui->box_qurry->setCurrentIndex(0);
            return ;
        }
        else
        {
            QHash<QString, QVector<Vote> > votes_table = hashTable_Vote(voters);
            QVector<Vote> vote_per = queryVotesById(votes_table,ui->qurry_1->text());
            ui->table->clear();
            ui->table->setHorizontalHeaderLabels({"编号", "姓名", "当前票数"});
            UpdateInfo(vote_per,ui->table);
            ui->box_qurry->setCurrentIndex(0);
        }
        break;
    case 2:
        if(ui->qurry_1->text().isEmpty())//姓名
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            ui->box_qurry->setCurrentIndex(0);
            return ;
        }
        else
        {
            QVector<Vote> vote_per = queryVotesByName(voters,ui->qurry_1->text());
            ui->table->clear();
            ui->table->setHorizontalHeaderLabels({"编号", "姓名", "当前票数"});
            UpdateInfo(vote_per,ui->table);
            ui->box_qurry->setCurrentIndex(0);
        }
        break;
    case 3:
        if(ui->qurry_1->text().isEmpty())//姓名模糊
        {
            QMessageBox::information(nullptr, "提示","请输入您要查询的信息");
            ui->qurry_1->setFocus();
            ui->box_qurry->setCurrentIndex(0);
            return ;
        }
        else
        {
            QVector<Vote> vote_per = queryVotesByPartialName(voters,ui->qurry_1->text());
            ui->table->clear();
            ui->table->setHorizontalHeaderLabels({"编号", "姓名", "当前票数"});
            UpdateInfo(vote_per,ui->table);
            ui->box_qurry->setCurrentIndex(0);
        }
        break;
    case 4:
    {
        UpdateInfo(voters,ui->table);
        break;
    }
    default:
        break;
    }

}
void vote::displayTopCandidates() {
    QVector<Vote> candidates = ReadVote();
    QVector<Vote> sortedCandidates = sort_up(candidates); // 获取排序后的候选人

    // 提取票数最高的三名候选人
    QStringList names;
    QList<int> votes;
    for (int i = 0; i < qMin(3, sortedCandidates.size()); ++i) {
        names.append(sortedCandidates[i].name);
        votes.append(sortedCandidates[i].votes);
    }

    setupChart(names, votes);
    checkWinner(candidates);
}
void vote::checkWinner(QVector<Vote>& candidates) {

    // 计算总票数
    int totalVotes = 0;
    for (const Vote &candidate : candidates) {
        totalVotes += candidate.votes;
    }

    // 找到票数最高的候选人
    Vote winner = *std::max_element(candidates.begin(), candidates.end(),
                                    [](const Vote &a, const Vote &b) {
                                        return a.votes < b.votes;
                                    });

    // 判断是否超过总票数的一半
    if (winner.votes > totalVotes / 2) {
        qDebug() << "优胜者是：" << winner.name << "，票数：" << winner.votes;
        ui->peo_result->setText(winner.name);
    } else {
        ui->peo_result->setText("无优胜者");
        qDebug() << "无优胜者";
    }
}

//void vote::setupChart(const QStringList &names, const QList<int> &votes) {
//    QBarSet *set = new QBarSet("Votes");
//    for (int vote : votes) {
//        *set << vote;
//    }

//    QBarSeries *series = new QBarSeries();
//    series->append(set);

//    QChart *chart = new QChart();
//    chart->addSeries(series);
//    chart->setTitle("票数最高的三位候选人");

//    QBarCategoryAxis *axisX = new QBarCategoryAxis();
//    axisX->append(names); // 添加候选人姓名到 X 轴
//    chart->setAxisX(axisX, series);

//    QValueAxis *axisY = new QValueAxis();
//    int maxVote = *std::max_element(votes.begin(), votes.end());
//    axisY->setRange(0, maxVote); // 设置 Y 轴最大值
//    axisY->setTickCount(maxVote + 1); // 设置刻度数量为 (maxVote + 1)
//    chart->setAxisY(axisY, series);

//    chart->setAnimationOptions(QChart::AllAnimations);

//    QChartView *chartView = new QChartView(chart);
//    chartView->setMinimumSize(800, 600);
//    setCentralWidget(chartView);
//}
void vote::setupChart(const QStringList &names, const QList<int> &votes) {
    QBarSet *set = new QBarSet("Votes");
    for (int vote : votes) {
        *set << vote;
    }


    QBarSeries *series = new QBarSeries();
    series->append(set);

    series->setLabelsVisible(true);  // 显示每个柱子的标签,直接用这个就好了啊，还改了那么多次

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("票数最高的三位候选人");

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(names);

    QFont axisXFont = axisX->labelsFont();
    axisXFont.setPointSize(8);
    axisX->setLabelsFont(axisXFont);

    chart->setAxisX(axisX, series);

    QValueAxis *axisY = new QValueAxis();
    int maxVote = *std::max_element(votes.begin(), votes.end());

    axisY->setRange(0, (maxVote / 5 + 1) * 5); // Y 轴范围设置为 5 的倍数
    axisY->setTickCount(maxVote / 5 + 1);      // 每隔 5 显示一个刻度
    axisY->setLabelFormat("%d");              // 格式化为整数
    chart->setAxisY(axisY, series);

    chart->setAnimationOptions(QChart::AllAnimations);

    // 增加图表左边距，确保 Y 轴刻度值显示
    chart->setMargins(QMargins(50, 5, 5, 5));

    QChartView *chartView = new QChartView(chart,this);
    chartView->setMinimumSize(800, 600);

    chartView->setGeometry(500, 400, 800, 600);

    // 显示图表视图
    chartView->show();
}
QVector<Vote> castVote(QVector<Vote>& votes, const QString& voterId, const QString& candidateId) {
    for (Vote& vote : votes)
    {
        // 查找投票者
        if (vote.id == voterId)
        {
            if (vote.state_vote == 0)// 如果未投票
            {
                vote.state_vote = 1; // 更新状态为已投票
                // 更新被投票人票数
                for (Vote& candidate : votes)
                {
                    if (candidate.id == candidateId)
                    {
                        candidate.votes += 1; // 被投票人的票数加一
                        break;
                    }
                }
                break; // 找到投票者后退出循环
            } else
            {
                qDebug() << "该用户已经投过票。";
                break; // 如果已经投票，退出循环
            }
        }
    }

    WriteVoteToFile(votes); // 更新文件
    return votes; // 返回更新后的投票数据
}
