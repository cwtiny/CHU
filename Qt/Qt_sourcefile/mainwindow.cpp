#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // ui->actionnew->setIcon(QIcon("C:/Users/Dell-PC/Desktop/20150225060808_wuANL.jpeg"));
    //使用添加QT资源“： + 前缀名 + 文件名 ”
    ui->actionnew->setIcon(QIcon(":/Image/20150225060808_wuANL.jpeg"));
    ui->actionopen->setIcon(QIcon(":/Image/20150225060808_wuANL.jpeg"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
