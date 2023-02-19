#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QIcon>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QPushButton>
#include <QMessageBox>
#include <QPaintEvent>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <ctime>
#include <QButtonGroup>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>
#define longnumber 20//宏定义游戏界面方格的多少
#define widthnumber 16

class Gamewidget : public QWidget
{
    Q_OBJECT
public:
    explicit Gamewidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent *e) override;
    QPushButton *StartPush;
    QPushButton *ExitPush;
    QPushButton *RestartPush;
    QLabel *ScoreLabel;
    QLabel *LevelLabel;
    QLabel *ScoreLabelNumber;
    QLabel *LevelLabelNumber;
    QLabel *LifeLabel;
    QLabel *LifeLabelNumber;
    QFile *file;
    QTimer *Timer;
    int snake[200][2];//创建了一个包含蛇的身体坐标的数组
    int snake1[200][2];//这个数组只是上一个坐标的复制，在最后一步（咬到身体或者撞到边缘）需要将它的身体坐标还原
    static int m_setDirection;//对方向的更改的存储
    int foodx;//食物的X坐标
    int foody;//食物的Y坐标
    int life;
    int lfoodx;//生命食物的坐标
    int lfoody;
    int gapplex;//减半食物的坐标
    int gappley;
    int snailx;//减速食物的坐标
    int snaily;
    int speedfoodx;//加速食物的坐标
    int speedfoody;
    int sign; //出现加速减速食物的判断标准
    int sign2;// 出现减半食物的判断标准
    int bodycount;
    int constbodycount; //固定的身长，不受后面对bodycount的操作的影响
    int Nobite;//判断有没有咬到自己
    int Score;
    int Difficulty;//难度级别，时间变化
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

#endif // GAMEWIDGET_H
