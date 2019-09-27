#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "subwaygraph.h"
QGraphicsScene *scene; //场景
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void on_actionLineMap_triggered();
    void drawStations (const QList<int>& stationsList);
    void drawEdges(const QList<Edge>& edgesList);
    void transferDstLineChanged(QString lineName);
    void updateTranserQueryInfo();
    void transferStartLineChanged(QString lineName);


    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int posX=0;
};

#endif // MAINWINDOW_H
