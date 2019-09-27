#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //存储所有站点信息，用 stations 的索引作为站点的唯一索引
    QVector<Station> stations;
    //<站点名,站点在 stations 中的索引>
    QHash<QString, int> stationsHash;
    //graph[i]代表 stations[i]站点的头结点// graph[i]容器内存储的是与 stations[i]站点相连的站点的唯一索引
    QVector<QVector<Node>>graph;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
