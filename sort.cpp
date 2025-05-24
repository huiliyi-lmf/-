#include"sort.h"

QVector<Vote> sort_up(QVector<Vote>& t) {
    std::sort(t.begin(), t.end(), [](const Vote &a, const Vote &b) {
        return a.votes > b.votes; // 按票数升序排列
    });
    return t;
}
QVector<Vote> sort_down(QVector<Vote>& t) {
    std::sort(t.begin(), t.end(), [](const Vote &a, const Vote &b) {
        return a.votes < b.votes; // 按票数降序排列
    });
    return t;
}
