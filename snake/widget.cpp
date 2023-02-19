#include "widget.h"
#include "gamewidget.h"
#include "gamewidget2.h"
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(890,510);
    this->setWindowTitle("贪吃蛇");
    this->setWindowIcon(QIcon(":/Picture/img/WindowPicture.jpg"));
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/Picture/Back2.jpg").scaled(this->size())));
    this->setStyleSheet("background-image:url(qrc:/new/Gamewindow/GameBack.jpg)");
    this->setPalette(palette);

    singlePush = new QPushButton(this);//单人游戏按钮
    doublePush = new QPushButton(this);//双人游戏按钮
    exitPush = new QPushButton(this);//退出按钮
    singlePush->setIconSize(QSize(90,45));//设置按钮尺寸
    singlePush->setGeometry(400,300,90,45);//设置按钮位置
    singlePush->setIcon(QIcon(":/Picture/single.png"));//对按钮填充图片
    singlePush->setFlat(1);
    doublePush->setIconSize(QSize(90,45));
    doublePush->setGeometry(400,360,90,45);
    doublePush->setIcon(QIcon(":/Picture/double.png"));
    doublePush->setFlat(1);
    exitPush->setIconSize(QSize(90,45));
    exitPush->setGeometry(400,420,90,45);
    exitPush->setIcon(QIcon(":/Picture/exit.jpg"));
    exitPush->setFlat(1);//设置按钮的透明属性
    exitBox = new QMessageBox;//退出游戏弹窗
    connect(exitPush,SIGNAL(clicked(bool)),this,SLOT(M_exitPush()));//将按键按下和对应的函数关联，按键按下后，执行响应函数
    connect(singlePush,SIGNAL(clicked(bool)),this,SLOT(M_singlePush()));//同上
    connect(doublePush,SIGNAL(clicked(bool)),this,SLOT(M_doublePush()));
}

Widget::~Widget()
{

}

//处理单人游戏，按下后，创建新界面覆盖父界面，并在其上进行游戏
void Widget::M_singlePush()
{
    gamewindow = new Gamewidget(this);  //创建一个新的界面，仍然以原来的界面为父窗口，退出后可以直接回到上一个界面。
    gamewindow -> show();
}

void Widget::M_doublePush()
{
    gamewindow2 = new Gamewidget2(this);
    gamewindow2 -> show();
}

//QMessageBox存储用户答案，如果是no，退回游戏或开始界面，如果是yes，则执行类似析构函数的过程
void Widget::M_exitPush()
{
    if(QMessageBox::Yes==QMessageBox::question(this,"Tips：","Do you want to leave the game?",QMessageBox::Yes|QMessageBox::No))
    {
        delete this;
        exit(0);
    }
}
