#include "widget.h"
#include "ui_widget.h"
#include <QPainter>//画家类
#include <QPushButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //点击移动按钮 移动图片
    connect(ui->movepushButton,&QPushButton::clicked,[=](){
        posX+=20;
     //如果要手动的调用绘图事件 用update更新
        update();
    });
}
void Widget::paintEvent(QPaintEvent *event)//1绘图事件
{
//    //2实例化画家对象  this 指的是绘图设备
//    QPainter painter(this);

//    //设置画笔(颜色)
//    QPen pen(QColor(255,0,0));
//    //设置画笔宽度
//    pen.setWidth(3);
//    //让画家使用这个笔
//    painter.setPen(pen);
//    //设置画刷
//    QBrush brush(Qt::cyan);
//    //设置画刷风格
//    brush.setStyle(Qt::Dense7Pattern);
//    //让画家使用画刷
//    painter.setBrush(brush);
//    //画线
//    painter.drawLine(QPoint(0,0),QPoint(100,100));
//    //画圆 椭圆
//    painter.drawEllipse(QPoint(100,100),50,50);
//    //画矩形
//    painter.drawRect(QRect(20,20,50,50));
//    // 画文字
//    painter.drawText(QRect(10,200,150,50),"我是你爸爸，我真伟大");


    /***********************高级设置***************************/
//    QPainter painter(this);
////    painter.drawEllipse(QPoint(100,50),50,50);
////    //设置 抗锯齿能力  效率较低
////    painter.setRenderHint(QPainter::Antialiasing);
////    painter.drawEllipse(QPoint(200,50),50,50);
//    //画矩形
//    painter.drawRect(QRect(20,20,50,50));
//    //移动画家
//    painter.translate(100,0);

//    //保存画家状态
//    painter.save();

//    painter.drawRect(QRect(20,20,50,50));

//    painter.translate(100,0);
//    //还原画家保存状态
//    painter.restore();
//    painter.drawRect(QRect(20,20,50,50));

    ////////////////////利用画家画资源图片//////////////////
    QPainter painter(this);

    if(posX>this->width())
    {
        posX = 0;
    }

    painter.drawPixmap(posX,0,QPixmap(":/Image/001"));


}

Widget::~Widget()
{
    delete ui;
}


