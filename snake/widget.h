#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIcon>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QPushButton>
#include <QMessageBox>

#include "gamewidget.h"
#include "gamewidget2.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QPushButton *singlePush;//设置按键
    QPushButton *doublePush;
    QPushButton *exitPush;
    QMessageBox *exitBox;//设置退出弹窗
    Gamewidget  *gamewindow;//声明一个新的界面,即游戏时界面
    Gamewidget2 *gamewindow2;

private slots:
    void M_singlePush();
    void M_doublePush();
    void M_exitPush();

};

#endif // WIDGET_H
