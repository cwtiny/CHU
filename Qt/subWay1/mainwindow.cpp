#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "subwaygraph.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //重置窗口大小
    resize(800,500);
    //菜单栏创建
    QMenuBar * bar = menuBar();
    //将菜单栏放入窗口中
    setMenuBar(bar);

    //创建菜单
    QMenu * fileMenu = bar->addMenu("文件(F)");
    QMenu * editMenu = bar->addMenu("编辑(E)");
    QMenu * viveMenu = bar->addMenu("视图(V)");
    QMenu * watchMenu = bar->addMenu("查看(W)");

    QMenu * toolsMenu = bar->addMenu("工具(T)");
    QMenu * helpMenu = bar->addMenu("帮助(H)");
    QMenu * aboutMenu = bar->addMenu("关于(A)");

    //创建菜单项
    QAction * amplifyAction = viveMenu->addAction("放大");
    //添加分割线
    fileMenu->addSeparator();

    QAction * reduceAction = viveMenu->addAction("缩小");

    QAction * findAction = watchMenu->addAction("查找");
    QAction * helpAction = helpMenu->addAction("帮助");
    QAction * locationAction = viveMenu->addAction("定位");

    fileMenu->addAction("新建");
    fileMenu->addAction("打开");
    fileMenu->addAction("保存");
    fileMenu->addAction("另存为");
    fileMenu->addAction("打印");
    fileMenu->addAction("退出");

    editMenu->addAction("复制");
    editMenu->addAction("剪切");
    editMenu->addAction("粘贴");
    editMenu->addAction("全选");
    editMenu->addAction("撤销");

    //viveMenu->addAction("放大");
    //viveMenu->addAction("缩小");
    //viveMenu->addAction("全屏");

    //watchMenu->addAction("查找");

    toolsMenu->addAction("换乘指南");

    //helpMenu->addAction("使用帮助");
    //工具栏，可以有多个
    QToolBar * toolBar = new QToolBar;
    addToolBar(Qt::LeftToolBarArea,toolBar);//放入工具栏

    //后期设置只允许成员停靠范围(左|右)
    toolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea);
    //设置浮动
    toolBar->setFloatable(false);
    //设置移动（总开关）
    toolBar->setMovable(true);
    //工具栏中设置内容
    toolBar->addAction(amplifyAction);
    //添加分割线
    toolBar->addSeparator();
    toolBar->addAction(reduceAction);
    toolBar->addSeparator();
    toolBar->addAction(findAction);
    toolBar->addSeparator();
    toolBar->addAction(helpAction);
    toolBar->addSeparator();
    toolBar->addAction(locationAction);
    toolBar->addSeparator();
    //工具栏添加控件（按钮）
    QPushButton * btn = new QPushButton("测试",this);
    btn->setText("测试");
    toolBar->addWidget(btn);
    //信号槽
    connect(helpAction,&QAction::triggered,[=](){
        //对话框 分类
        //模态对话框 （不可以对其他窗口进行操作）  非模态（可以对其他窗口操作）
        //模态创建  阻塞
//    QDialog helpdlg(this);
//    helpdlg.resize(300,200);
//    helpdlg.exec();//阻塞显示
//    qDebug()<<"模态对话框";

        //非模态对话框
//    QDialog * helpdlg = new QDialog(this);  //new 给他放堆上，防止一闪而过
//    helpdlg->resize(300,200);
//    helpdlg->show();
//    helpdlg->setAttribute(Qt::WA_DeleteOnClose);  //记得关闭呦
//    qDebug()<<"非模态对话框";
        //消息对话框 QMessageBox 静态成员函数 创建对话框
        //错误对话框
        //QMessageBox::critical(this,"critical","错误");

        //消息对话框
        //QMessageBox::information(this,"information","消息");
        //提问对话框
        //参数一：基类  参数2：标题 参数3：提示内容 参数四 ：按键内容  参数5：默认关联回车按键
//       if (QMessageBox::Save == QMessageBox::question(this,"question","询问",QMessageBox::Save|QMessageBox::Cancel))
//       {
//               qDebug() << "选择的是保存";
//       }
//       else
//       {
//               qDebug() << "选择的是取消";
//       }

        //警告对话框
       //QMessageBox::warning(this,"warning","警告！");


        //其他标准对话框
        //颜色对话框
//        QColor color = QColorDialog::getColor(QColor(255,0,0));
//        qDebug() << "r = "<< color.red() << "g = "<< color.green() << "b = "<< color.blue();
//        qDebug() << color;

        //文件对话框  参数一：基类 参数二： 标题 参数三：默认打开路径  参数四：过滤文件格式
        //返回值是选中文件路径
//        QString addrStr = QFileDialog::getOpenFileName(this,"打开文件","C:/Users/Dell-PC/Desktop","(*.cpp)");
//        qDebug() << addrStr;

        //字体对话框
        bool flag;
        QFont font =  QFontDialog::getFont(&flag,QFont("华文彩云",36));
        qDebug() << "字体：" << font.family().toUtf8().data() << "字号：" << font.pointSize() << "是否加粗：" << font.bold();

    });



    //状态栏 最多一个
    QStatusBar * stBar =statusBar();
    //设置到窗口中
    setStatusBar(stBar);
    //放标签控件
    QLabel * label = new QLabel("提示信息:",this);
    stBar->addWidget(label);
    QLabel * label2 = new QLabel("RIGHT提示信息",this);
    stBar->addPermanentWidget(label2);

    //铆接部件 （浮动窗口） 可以有多个
    QDockWidget * dockWidget = new QDockWidget("浮动窗口",this);
    addDockWidget(Qt::BottomDockWidgetArea,dockWidget);
    //设置后期停靠区域，（只允许上下）
    dockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);

    //设置中心部件，只能一个
    //QTextEdit * edit = new QTextEdit(this);
    //setCentralWidget(edit);
    scene=new QGraphicsScene;
    // 设置边框大小，中心点并不是左上角
    scene->setSceneRect(-LINE_INFO_WIDTH,0,SCENE_WIDTH,SCENE_
    HEIGHT);
    //将场景添加到视图中
    ui->graphicsView->setScene(scene);
    //设置可左键拖动
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    // 消除基元边缘的锯齿
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    manageLines=new ManageLines(this);
    subwayGraph=new SubwayGraph;
    appHelp=new AppHelp();

    // 读取已有的地铁信息文件
    bool flag = subwayGraph->readFileData(":/data/data/userAdd.txt");
    if (!flag)
    {
    QMessageBox box;
    box.setWindowTitle(tr("error information"));
    box.setIcon(QMessageBox::Warning);
    box.setText("读取数据错误!\n 将无法展示内置线路！ ");
    box.addButton(tr("确定"), QMessageBox::AcceptRole);
    if (box.exec() == QMessageBox::Accepted)
    {
    box.close();
    }
    }
    // 关联信号和槽
    myConnect();
    updateTranserQueryInfo();
    // 在画板上画出折线及站点
    on_actionLineMap_triggered();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);

//    if(posX>this->width())
//    {
//        posX = 0;
//    }

//    painter.drawPixmap(78,30,QPixmap(":/Image/001"));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionLineMap_triggered()
{
statusLabel3->setText(tr("图示：上海地铁网络线路图"));
scene->clear();
// 存储站点索引 ID
QList<int> stationsList;
// 存储路线信息
QList<Edge> edgesList;
// 获取 subwaygraph 类中读取的地铁路线和站点数据
subwayGraph->getGraph(stationsList,edgesList);
// 在界面中画出地铁路线图
drawEdges(edgesList);
// 在界面的地铁路线图中，添加站点
drawStations(stationsList);
}
/*
* 函数名： drawStations
* 函数功能：绘制网络图的站点节点
* 参数： const QList<int>& stationsList 容器中存放的是站点的唯一索引
* 返回值:无
*/
void MainWindow::drawStations (const QList<int>& stationsList)
{
for (int i=0; i<stationsList.size(); ++i)
{
int s=stationsList[i];
QString name=subwayGraph->getStationName(s);
QList<int> linesList=subwayGraph->getStationLinesInfo(s);
QColor color=getLinesColor(linesList);
QPointF longiLati=subwayGraph->getStationCoord(s);
QPointF coord=transferCoord(longiLati);
QString tip="站名： "+name+"\n"+
"经度： "+QString::number(longiLati.x(),'f',7)+"\n"+
"纬度： "+QString::number(longiLati.y(),'f',7)+"\n"+
"线路： "+getLinesName(linesList);
// 在场景中添加圆形， QGraphicsEllipseItem 圆形图元类QGraphicsEllipseItem* stationItem=new QGraphicsEllipseItem;
stationItem->setRect(-NODE_HALF_WIDTH,
-NODE_HALF_WIDTH, NODE_HALF_WIDTH<<1, NODE_HALF_WIDTH<<1);
stationItem->setPos(coord);
stationItem->setPen(color);
// 设置鼠标悬浮式鼠标的形状
stationItem->setCursor(Qt::PointingHandCursor);
// 设置提示信息
stationItem->setToolTip(tip);
if(linesList.size()<=1)
{
stationItem->setBrush(QColor(QRgb(0xffffff)));
}
scene->addItem(stationItem);
// 添加站点名称 QGraphicsTextItem 文字图元
QGraphicsTextItem* textItem=new QGraphicsTextItem;
textItem->setPlainText(name);
textItem->setFont(QFont("consolas",4,1));
textItem->setPos(coord.x(),coord.y()-NODE_HALF_WIDTH*2);
scene->addItem(textItem);
}
}

/*
* 函数名： drawEdges
* 函数功能：绘制网络图的边
* 参数： const QList<Edge>& edgesList 线的集合（两个点决定一条直线，
所以内部是两个点的集合）
* 返回值:无
*/
void MainWindow::drawEdges(const QList<Edge>& edgesList)
{
for(int i=0; i<edgesList.size(); ++i)
{
int s1=edgesList[i].first;
int s2=edgesList[i].second;
QList<int> linesList=subwayGraph->getCommonLines(s1, s2);
QColor color=getLinesColor(linesList);QString tip="途经：
"+subwayGraph->getStationName(s1)+"--"+subwayGraph->getStationName(s2)+"\n
线路： ";
tip+=getLinesName(linesList);
QPointF s1Pos=transferCoord(subwayGraph->getStationCoord(s1));
QPointF s2Pos=transferCoord(subwayGraph->getStationCoord(s2));
// 在场景中添加线， QGraphicsLineItem 线图元
QGraphicsLineItem* edgeItem=new QGraphicsLineItem;
edgeItem->setPen(QPen(color, EDGE_PEN_WIDTH));
edgeItem->setCursor(Qt::PointingHandCursor);
edgeItem->setToolTip(tip);
// 设置线的起始点
edgeItem->setPos(s1Pos);
// 从起始点画出线
edgeItem->setLine(0, 0, s2Pos.x()-s1Pos.x(), s2Pos.y()-s1Pos.y());
scene->addItem(edgeItem);
}
}

//更新换乘选择信息
void MainWindow::updateTranserQueryInfo()
{
statusLabel3->setText(tr("已更新数据"));
QComboBox* comboL1=ui->comboBoxStartLine;
QComboBox* comboL2=ui->comboBoxDstLine;
comboL1->clear();
comboL2->clear();
QList<QString> linesList=subwayGraph->getLinesNameList();
for(auto &a:linesList)
{
comboL1->addItem(a);
comboL2->addItem(a);
}
transferStartLineChanged(comboL1->itemText(0));
transferDstLineChanged(comboL2->itemText(0));
}
//换乘出发线路改变槽函数
void MainWindow::transferStartLineChanged(QString lineName)
{
QComboBox* comboS1=ui->comboBoxStartStation;
comboS1->clear();int lineHash=subwayGraph->getLineHash(lineName);
if(lineHash==-1)
{
return ;
}
QList<QString>
stationsList=subwayGraph->getLineStationsList(lineHash);
for(auto &a:stationsList)
{
comboS1->addItem(a);
}
}
//换乘目的线路改变槽函数
void MainWindow::transferDstLineChanged(QString lineName)
{
QComboBox* comboS2=ui->comboBoxDstStation;
comboS2->clear();
int lineHash=subwayGraph->getLineHash(lineName);
if(lineHash==-1)
{
return ;
}
QList<QString>
stationsList=subwayGraph->getLineStationsList(lineHash);
for(auto &a:stationsList)
{
comboS2->addItem(a);
}
}
/*
界面布局
实现窗口登陆
利用布局方式 给窗口进行美化
选取 widget 进行布局 ， 水平布局、垂直布局、栅格布局
给用户名、密码、登陆、退出按钮进行布局
默认窗口和控件之间有9间隙 ， 可以调整 layoutleftmargin
密码明文暗文

按钮组
QPushButton 常用按钮
Qtoolbutton 工具按钮 用于显示图片，如图想显示文字，修改风格
toolbuttonstyle ， 凸起风格 autoraise
radiobutton 单选按钮， 设置默认 ui->rBtnMan->setChecked(true);
checkbox 多选按钮,监听状态：2选中，1半选，0未选

qlistwigidget 列表容器
qlistwidget->additem(item)
设置居中方式 item->settextalignmentqt::alignhcgnterl
 可以利用 additem 一次性添加整首诗

 QTreeWidget 树控件
 设置头
 ui->treewidget->sethearlabels(qstring()<<"英雄"<<"属性");
 创建根节点
 qstreewidgetitem * liItem = new qtreewidgetitem(qstringlist()<<"力量");
 添加根节点到树控件上
 ui ->treewidget->addtoplevelitem(liitem);
 添加子节点
 qstringlist herol1;
 herol1 <<"刚被猪"<<"前排坦克。。。。";
 qstreewidgetitem * l22 = new qtreewidgetitem(herol1);
 liitem->addchild(l22);

 表格 tablewidget控件
 设置列数
 ui->tablewidget->setcolumncount(3);
 设置水平头
 ui->tablewidget->sethorizontalheaderlabels(qstringlist()<<"姓名"<<"性别"<<"年龄");
 设置行数
 ui->tablewidget->setrowcount(5);
 设置正文
 //ui->tablewidget->setitem(0,0,new qtablewidgetitem("亚瑟"));
qstringlist namelist;
namelist<<"亚瑟"<<"赵云"<<"张飞"<<"关羽"<<"花木兰";
qlist<qstring> sexlist;
sexlist<<"男"<<"男"<<"男"<<"男"<<"女";
for(int i = 0 ; i<5 ;i++)
 {
    int col = 0;
    ui->tablewidget->setitem(i,col++, new qtablewidgetitem(namelist[i]));//越界操作直接挂掉
    ui->tablewidget->setitem(i,col++, new qtablewidgetitem(sexlist.at(i)));//.at（）越界操作抛出异常
     ui->tablewidget->setitem(i,col++, new qtablewidgetitem(qstring::number(i+18)));
}

栈控件使用stackedwidget

下拉框
ui->combobox->additem("奔驰");
ui->combobox->additem("宝马");
ui->combobox->additem("拖拉机");

利用qlable显示图片
ui->lbl_image->setpixmap(qpixmap(":/image/"));
利用qlable显示 gif动图
qmove * movie = new qmovie(":/image/.gif");
ui->lbl_movie->setmovie(movie);
播放动图
movie->start();

封装控件
添加新文件 - Qt -设计师界面类 {.h .cpp .ui}
.ui中设计qspinbox和qslider两个控件
widget 中使用自定义控件，拖拽一个widget，点击提升为，点击添加，点击提升
实现功能，改变数字，滑动跟着移动，信号槽监听。
提供getnum 和setnum对外接口
//qspinbox移动 qslider跟着移动
void(qspinbox::* spsignal)(int) = &qspinbox::valuechanged;
connect(ui->spinbox , spsignal, ui->horizontalslider , &qslider::setvalue);
//qslider 滑动 qspinbox数字跟着改变
connect（ui->horizontalslider , &qslider::valuechanged,ui->spinbox,&qspinbox::setvlue）;

鼠标事件#include <QMouseEvent>
//设置鼠标追踪状态
setmousetracking(true);

鼠标进入事件
void mylabel::enterevent(qevent *event)
{

}
鼠标离开事件
void mylabel::leaveevent(qevent *event)
{

}
鼠标按下
void mylable::mousepressevent(qmouseevent *ev)
{
    //当鼠标左键按下 提示信息
    if （ev->button（） == qt::leftbutton）
    {
    //qt中的格式化输出 global 表示全屏的相对位置坐标
    qstring str = qstring("鼠标按下了：x=%1 y= %2 globalx = %3 globaly = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalx()).arg(ev->globaly());
    qdebug() << str;
    }
}
鼠标释放
void mylabel：：mousereleaseevent（qmouseevent *ev）
{
    qstring str = qstring("鼠标按下了：x=%1 y= %2 globalx = %3 globaly = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalx()).arg(ev->globaly());
    qdebug() << str;

}
鼠标移动
void mylabel：：mousemoveevent（qmouseevent *ev）
{
    if(ev->buttons() & qt::leftbutton)//位与操作符
    {
        qstring str = qstring("鼠标按下了：x=%1 y= %2 globalx = %3 globaly = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalx()).arg(ev->globaly());
        qdebug() << str;
    }
}

定时器
利用事件 void timerevent (qtimerevent * ev)
启动定时器 starttimer(1000)//单位毫秒
timerevent 的返回值是定时器的唯一标示 可以和ev->timerid 作比较

定时器的第二种方式<qtimer>
qtimer * timer = new qtimer(this);
启动定时器
timer->start(500);
connect(timer,&qtimer::timeout,[=](){
    static int num = 1;
    //label_4  0.5秒 +1
    ui->label_4->settext(qstring::number(num++));
});
//点击暂停按钮 实现停止定时器
connect(ui->btn,&qpushbutton::clicked,[=](){
    timer->stop();
});

//通过event事件分发器 拦截 鼠标按下事件
bool event(qevent *e)
{
    //如果是鼠标按下，在event事件分发中做拦截操作
    if(e->type() == qevent::mousebuttonpress)
    {
        qmouseevent * ev = static_cast<qmouseevent>(e);//静态类型转换或者强制类型转换
        //qstring
        //qdebug()<<
        return ture;//ture 代表用户自己处理这个事件不向下分发
    }
    //其他事件 交给父类处理 默认处理
    return qlabel::event(e);
}
事件过滤器
通过事件过滤器，可以在程序分发到event事件之前再做一次高级拦截
步骤1：给控件安装事件过滤器
步骤2： 重写eventfilter事件
ui->label ->installeventfilter(this);

bool widget::eventfilter(qobject * obj , qevent * e)
{
    if(obj == ui->label)
    {
        if(e->type() == qevent::mousebuttonpress)
        {
            qmouseevent * ev = static_cast<qmouseevent*>(e);
            //qstring
            //qdebug<<
        }
    }
}


*/
