#ifndef GAMEWIDGET2_H
#define GAMEWIDGET2_H

#include <QWidget>
#include<QIcon>
#include<QPalette>
#include<QBrush>
#include<QPixmap>
#include<QPushButton>
#include<QMessageBox>
#include<QPaintEvent>
#include<QPainter>
#include<QLabel>
#include<QTimer>
#include<QTime>
#include<ctime>
#include<QButtonGroup>
#include<QKeyEvent>
#include<QStyle>
#include<algorithm>
#include<QFile>
#include<QTextStream>
#define longnumber 20//宏定义游戏界面方格的多少
#define widthnumber 16

class Gamewidget2 : public QWidget
{
    Q_OBJECT
public:
    explicit Gamewidget2(QWidget *parent = 0);
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent *e) override;
    QPushButton *StartPush;
    QPushButton *ExitPush;
    QPushButton *RestartPush;
    QLabel *ScoreLabel1;
    QLabel *ScoreLabel2;
    QLabel *LevelLabel;
    QLabel *LifeLabel1;
    QLabel *LifeLabel2;
    QLabel *ScoreLabelNumber1;
    QLabel *ScoreLabelNumber2;
    QLabel *LevelLabelNumber;
    QLabel *LifeLabelNumber1;
    QLabel *LifeLabelNumber2;
    QTimer *Timer;
    QFile *file;
    int snake[200][2];//创建了一个包含蛇的身体坐标的数组
    int snake1[200][2];//这个数组只是上一个坐标的复制，在最后一步（咬到身体或者撞到边缘）需要将它的身体坐标还原
    int dsnake[200][2];
    int dsnake1[200][2];
    static int m_setDirection1;//对方向的更改的存储
    static int m_setDirection2;
    int foodx;//食物的X坐标
    int foody;//食物的Y坐标
    int food2x;
    int food2y;
    int speedfoodx;
    int speedfoody;
    int snailx;
    int snaily;
    int lfoodx;
    int lfoody;
    int bodycount1;
    int bodycount2;
    int constbodycount1;
    int constbodycount2;
    int gapplex;
    int gappley;
    int Nobite1;//判断有没有咬到自己
    int Nobite2;
    int Nobiteach;//判断相互咬
    int Score1;
    int Score2;
    int life1;
    int life2;
    int judge;
    int Difficulty;//难度级别，时间变化
    int sign;
    int sign2;
private:
    QPalette *palette;

signals:

public slots:
    void M_timeout();
    void M_startPush();
    void M_exitPush();
    void M_pausePush();
    void M_restartPush();
    void M_CheckGameOver();
};


#endif // GAMEWIDGET2_H
