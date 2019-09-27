#ifndef SUBWAYGRAPH_H
#define SUBWAYGRAPH_H
#include <QMenuBar>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>//记事本头文件
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QMouseEvent>
#include <QPainter>//画家类
#include <QGraphicsView>
#include <QVector>
typedef QPair<int,int> Edge;

//线路类
class Line
{
protected:
int id; //线路 ID
QString name; //线路名称
QColor color; //线路颜色
QVector <QString> fromTo; //线路起始站点QSet<int> stationsSet; //线路站点集合
QSet<Edge> edges; //线路站点连接关系
public:
//构造函数
Line(){};
Line(QString lineName, QColor lineColor):name(lineName), color(lineColor)
{};
//声明友元
friend class SubwayGraph;
friend class QTextStream;
};

//图的邻接点结构
class Node{
public:
int stationID; //邻接点 ID
double distance; //两点距离
//构造函数
Node(){};
Node(int s, double dist) :stationID(s), distance(dist)
{};
//">"运算重载，用于小顶堆
bool operator > (const Node& n) const
{return this->distance>n.distance;
}
};

class Station
{
protected:
int id; //站点 ID
QString name; //站点名称
double longitude, latitude; //站点经纬度
QSet<int> linesInfo; //站点所属线路
//所有站点的边界位置
static double minLongitude, minLatitude, maxLongitude, maxLatitude;
public:
//构造函数
Station();
Station(QString nameStr, double longi, double lati, QList<int> linesList);
protected:
//求取站点间实地直线距离
int distance(Station other);
//声明友元
friend class SubwayGraph;
friend class QTextStream;
};

class SubwayGraph
{

public:
    SubwayGraph();
    bool readFileData(QString fileName);
    void makeGraph();
    bool insertEdge(int n1, int n2);
protected:
    QVector<Station> stations; //存储所有站点
    QVector<Line> lines; //存储所有线路
    QHash<QString, int> stationsHash; //站点名到存储位置的 hash
    QHash<QString, int> linesHash; //线路名到存储位置的 hash
    QSet<Edge> edges; //所有边的集合
    QVector<QVector<Node>> graph; //地铁线路网络图
private:


};




#endif // SUBWAYGRAPH_H
