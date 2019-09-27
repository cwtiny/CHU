#include "subwaygraph.h"

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
SubwayGraph::SubwayGraph()
{

}
bool SubwayGraph::readFileData(QString fileName)
{
QFile file(fileName);
if(!file.open(QIODevice::ReadOnly))
return false;
QTextStream in(&file);
while(!in.atEnd())
{
Line line;
QString id, name, colour, fromTo, totalStations;
QString color, froms, tos;
bool ok;
int total;
Station station;
int lvIndex, svIndex1, svIndex2;
in>>id>>line.id;
in>>name>>line.name;
in>>colour>>color;
line.color.setRgba(color.remove(0,1).toUInt(&ok, 16));
in>>fromTo>>froms>>tos;
in>>totalStations>>total;
line.fromTo.push_back(froms);
line.fromTo.push_back(tos);
if (linesHash.count(line.name))
{
lvIndex = linesHash[line.name];
lines[lvIndex].fromTo.push_back(froms);lines[lvIndex].fromTo.push_back(tos);
}
else
{
lvIndex = linesHash[line.name] = lines.size();
lines.push_back(line);
}
QString longlat;
QStringList strList;
for (int i=0; !in.atEnd()&&i<total; ++i)
{
in>>station.id>>station.name>>longlat;
strList=longlat.split(QChar(','));
station.longitude=strList.first().toDouble();
station.latitude=strList.last().toDouble();
if (stationsHash.count(station.name))
{
svIndex2 = stationsHash[station.name];
}
else
{
svIndex2 = stationsHash[station.name] = stations.size();
stations.push_back(station);
}
stations[svIndex2].linesInfo.insert(lvIndex);
lines[lvIndex].stationsSet.insert(svIndex2);
if (i)
{
lines[lvIndex].edges.insert(Edge(svIndex1, svIndex2));
lines[lvIndex].edges.insert(Edge(svIndex2, svIndex1));
insertEdge(svIndex1, svIndex2);
}
svIndex1 = svIndex2;
}
bool flag = id=="id:" && name=="name:" && colour=="colour:" &&
fromTo=="fromTo:"
&& totalStations=="totalStations:" && ok && !in.atEnd();
if(flag==false){
file.close();
clearData();
return false ;
}
in.readLine();
}
file.close();
// 更新经纬度最大最小边界
updateMinMaxLongiLati();
makeGraph();
return true;
}

void SubwayGraph::makeGraph()
{
graph.clear();
graph=QVector<QVector<Node>>(stations.size(), QVector<Node>());
for (auto &a : edges)
{
double dist=stations[a.first].distance(stations[a.second]);
graph[a.first].push_back(Node(a.second, dist));
graph[a.second].push_back(Node(a.first, dist));
}
}

bool SubwayGraph::insertEdge(int n1, int n2)
{
if (edges.contains(Edge(n1, n2)) || edges.contains(Edge(n2, n1)))
{
return false;
}
edges.insert(Edge(n1, n2));
return true;
}
