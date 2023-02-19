#include "gamewidget.h"
#include "widget.h"
#include <QDebug>

int Gamewidget::m_setDirection = 4;
Gamewidget::Gamewidget(QWidget *parent) : QWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus); //不知道原理，本来不加这个函数，好像对键盘事件没有响应，加了这个后解决了。
    qsrand(time(NULL));//随机数的种子

    this->setAutoFillBackground(true);//设置父窗口背景可被覆盖填充
    this->resize(890,510);
    this->setWindowTitle("贪吃蛇");
    this->setWindowIcon(QIcon(":/Picture/img/WindowPicture.jpg"));

    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/Gamewindow/GameBack.jpg").scaled(this->size())));//设置游戏背景，大小自适应
    this->setPalette(palette);

    StartPush = new QPushButton(this);
    ExitPush = new QPushButton(this);
    RestartPush = new QPushButton(this);

    StartPush->setIconSize(QSize(90,45));
    StartPush->setGeometry(650,400,90,45);
    StartPush->setFlat(1);
    StartPush->setIcon(QIcon(":/Picture/single.png"));

    ExitPush->setIconSize(QSize(90,45));
    ExitPush->setGeometry(780,400,90,45);
    ExitPush->setIcon(QIcon(":/Picture/exit.jpg"));
    ExitPush->setFlat(1);

    RestartPush->setIconSize(QSize(60,60));
    RestartPush->setGeometry(720,330,60,60);
    RestartPush->setIcon(QIcon(":/Picture/restart.jpg"));
    RestartPush->setFlat(1);

    Timer = new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(M_timeout()));
    connect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));//事件关联处理，和widget中相同
    connect(ExitPush,SIGNAL(clicked(bool)),this,SLOT(M_exitPush()));
    connect(RestartPush,SIGNAL(clicked(bool)),this,SLOT(M_restartPush()));

    file = new QFile ("memory.txt");
    file->open(QIODevice::ReadOnly);
    QTextStream stream(&*file);
    if(file->atEnd()){
        Score = 0;
        Difficulty = 1;
        life = 1;
        snake[0][0] = (rand()%17+2)*30;
        snake[0][1] = (rand()%13+2)*30;
        m_setDirection = (rand()%4)+1;
        foodx = (rand()%19+1)*30;
        foody = (rand()%15+1)*30;
        lfoodx = 1000;
        lfoody = 1000;
        speedfoodx = 1000;
        speedfoody = 1000;
        gapplex = 1000;
        gappley = 1000;
        snailx = 1000;
        snaily = 1000;
        sign = 3;
        sign2 = 15;
        constbodycount = bodycount = 1;  //包含蛇的头和尾巴
        Nobite = 1;
    }
    else{
        stream >> life >> Difficulty >> bodycount >> constbodycount;
        for(int i=0;i<=bodycount;++i)
            stream >> snake[i][0] >> snake[i][1];
        stream >> Score;
        stream >> m_setDirection;
        stream >> foodx >> foody;
        stream >> lfoodx >> lfoody;
        stream >> speedfoodx >> speedfoody;
        stream >> gapplex >> gappley;
        stream >> snailx >> snaily;
        stream >> sign >> sign2;
        stream >> Nobite;
        file->close();
    }

    ScoreLabel = new QLabel(this); //设置标签，一个得分标签，一个难度标签
    LevelLabel = new QLabel(this);
    LifeLabel = new QLabel(this);
    LifeLabel -> setText("Life:");
    LifeLabel -> setGeometry(690,90,120,90);
    ScoreLabel -> setText("Score:");
    ScoreLabel -> setGeometry(690,10,120,90);
    LevelLabel -> setText("Level:");
    LevelLabel -> setGeometry(690,50,120,90);

    ScoreLabelNumber = new QLabel(this);
    LevelLabelNumber = new QLabel(this);
    LifeLabelNumber = new QLabel(this);
    ScoreLabelNumber -> setText(QString::number(Score)+"分"); //将得分作为字符串输出到label中
    ScoreLabelNumber -> setGeometry(750,10,120,90);
    LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
    LevelLabelNumber -> setGeometry(750,50,120,90);
    LifeLabelNumber -> setText(QString::number(life));
    LifeLabelNumber -> setGeometry(750,90,120,90);
    this -> update();
}
void Gamewidget::keyPressEvent(QKeyEvent *e)//按键处理
{
    qDebug () << e -> key();
    switch(e -> key())
    {
    case Qt::Key_Up:
        if(m_setDirection != 2)m_setDirection = 1;
        break; //如果键盘为上键，则将方向变量置为1，且不能为相反方向
    case Qt::Key_W:
        if(m_setDirection != 2)m_setDirection = 1;
        break;
    case Qt::Key_Down:
        if(m_setDirection != 1)m_setDirection = 2;
        break;
    case Qt::Key_S:
        if(m_setDirection != 1)m_setDirection = 2;
        break;
    case Qt::Key_Left:
        if(m_setDirection != 4)m_setDirection = 3;
        break;
    case Qt::Key_A:
        if(m_setDirection != 4)m_setDirection = 3;
        break;
    case Qt::Key_Right:
        if(m_setDirection != 3)m_setDirection = 4;
        break;
    case Qt::Key_D:
        if(m_setDirection != 3)m_setDirection = 4;
        break;
    default: break;

    }
}
void Gamewidget::paintEvent(QPaintEvent*)//绘图事件
{
    QPainter painter(this);
    if(30 <= snake[0][0] && snake[0][0] <= 570 && 30 <= snake[0][1] && snake[0][1] <= 450 && Nobite)//蛇头要在界面内，设定碰壁为失败
    {
        qDebug() << snake[0][0];
        qDebug() << m_setDirection;
        if(bodycount > 1)
        for(int i=bodycount;i>0;i--)
            painter.drawImage(QRect(snake[i][0],snake[i][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));//画出蛇
    }
    painter.drawImage(QRect(foodx,foody,30,30),QImage(":/new/Gamewindow/img/Apple.png")); //画出食物
    painter.drawImage(QRect(lfoodx,lfoody,30,30),QImage(":/new/Gamewindow/life.jpg"));
    painter.drawImage(QRect(snailx,snaily,30,30),QImage(":/Picture/snail.png"));
    painter.drawImage(QRect(speedfoodx,speedfoody,30,30),QImage(":/Picture/speedfood.png"));
    painter.drawImage(QRect(gapplex,gappley,30,30),QImage(":/Picture/gapple.png"));

    painter.setPen(Qt::black);

    for(int i=1;i<=widthnumber-1;i++)
    {
        for(int j=1;j<=longnumber-1;j++)
        {
            painter.drawRect(QRect(30 * j,30 * i,30,30));//画出游戏方格
        }
    }
        painter.drawImage(QRect(0,0,30,510),QImage(":/Picture/blick.jpg"));
        painter.drawImage(QRect(0,0,630,30),QImage(":/Picture/blick.jpg"));
        painter.drawImage(QRect(0,480,630,30),QImage(":/Picture/blick.jpg"));
        painter.drawImage(QRect(600,0,30,510),QImage(":/Picture/blick.jpg"));
    switch (m_setDirection)
    {
        case 1: painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));
            if(bodycount == 1)  painter.drawImage(QRect(snake[0][0],snake[0][1] + 30,30,30),QImage(":/new/Gamewindow/snake.jpg"));
            break;
        case 2: painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));
            if(bodycount == 1) painter.drawImage(QRect(snake[0][0],snake[0][1] - 30,30,30),QImage(":/new/Gamewindow/snake.jpg"));
            break;
        case 3: painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));
            if(bodycount == 1) painter.drawImage(QRect(snake[0][0] + 30,snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));
            break;
        case 4: painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));
            if(bodycount == 1)  painter.drawImage(QRect(snake[0][0] - 30,snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));
            break;
        default:
            break;
    }
}

void Gamewidget::M_timeout()
{
    int tmp = Difficulty;
    if(snake[0][0] == foodx && snake[0][1] == foody)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        foodx = (rand()%19+1)*30;
        foody = (rand()%15+1)*30;
        bodycount++;  //蛇的身体加一
        constbodycount++;
        Difficulty = constbodycount/5 + 1;
        Score = Score + Difficulty;
        ScoreLabelNumber -> setText(QString::number(Score)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        Timer->start(Difficulty <= 9 ? 500-Difficulty * 50 : 50 / (Difficulty - 9));
    }
    if(snake[0][0] == lfoodx && snake[0][1] == lfoody)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        life = life + 1;
        lfoodx = 1000;
        lfoody = 1000;
        bodycount++;  //蛇的身体加一
        constbodycount++;
        Difficulty = constbodycount/5 + 1;
        Score = Score + Difficulty;
        ScoreLabelNumber -> setText(QString::number(Score)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        LifeLabelNumber -> setText(QString::number(life));
        Timer->start(Difficulty <= 9 ? 500-Difficulty * 50 : 50 / (Difficulty - 9));
    }
    if(snake[0][0] == speedfoodx && snake[0][1] == speedfoody)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        speedfoodx = 1000;
        speedfoody = 1000;
        Score = Score + Difficulty;
        Difficulty++;
        constbodycount = (Difficulty - 1) * 5;
        ScoreLabelNumber -> setText(QString::number(Score)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        Timer->start(Difficulty <= 9 ? 500-Difficulty * 50 : 50 / (Difficulty - 9));
    }
    if(snake[0][0] == snailx && snake[0][1] == snaily)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        snailx = 1000;
        snaily = 1000;
        Score = Score + Difficulty;
        Difficulty--;
        constbodycount = (Difficulty - 1) * 5;
        ScoreLabelNumber -> setText(QString::number(Score)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        Timer->start(Difficulty <= 9 ? 500-Difficulty * 50 : 50 / (Difficulty - 9));
    }
    if(snake[0][0] == gapplex && snake[0][1] == gappley)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        gapplex = 1000;
        gappley = 1000;
        Score = Score + Difficulty;
        bodycount = bodycount / 2;
        for(int i = constbodycount;i>bodycount;--i)
        {
            snake[i][0] = 1000;
            snake[i][1] = 1000;
        }
        ScoreLabelNumber -> setText(QString::number(Score)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
    }
    if(Difficulty > tmp) //难度改变时，出现加一条命的果实,且只能有一个
    {
        lfoodx = (rand()%19+1)*30;
        lfoody = (rand()%15+1)*30;
    }
    if(Difficulty > sign) //难度大于设定值时，出现加速减速食物，且分别只能有一个
    {
        sign = sign * 2;
        speedfoodx = (rand()%19+1)*30;
        speedfoody = (rand()%15+1)*30;
        snailx = (rand()%19+1)*30;
        snaily = (rand()%15+1)*30;
    }
    if(bodycount > sign2)
    {
        sign2 = sign2 * 2;
        gapplex = (rand()%19+1)*30;
        gappley = (rand()%15+1)*30;
    }
    memcpy(snake1,snake,sizeof(snake));
    for(int i=bodycount;i>0;i--)//将蛇身体的前一个坐标赋值给后一个坐标，实现蛇身体的连续出现
    {

        snake[i][0] = snake[i-1][0];
        snake[i][1] = snake[i-1][1];
    }
    QPainter painter(this);

    switch (m_setDirection)
    {
    case 1: snake[0][1] = snake[0][1] - 30,painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"))
                ;break;
    case 2: snake[0][1] = snake[0][1] + 30,painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"))
                ; break;
    case 3: snake[0][0] = snake[0][0] - 30,painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"))
                ; break;
    case 4: snake[0][0] = snake[0][0] + 30,painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"))
                ;break;
    default:
        break;
    }

    for(int i=bodycount+1;i>3;i--) //检查是否相撞
    {
        if(snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1])
        {
            memcpy(snake,snake1,sizeof(snake));
            Nobite = 0;
            life = life - 1;
            LifeLabelNumber -> setText(QString::number(life));
        }
    }

    if(30 > snake[0][0] || snake[0][0] > 570 || 30 > snake[0][1] || snake[0][1] > 450)
    {
        memcpy(snake,snake1,sizeof(snake));
        Nobite = 0;
        life = life - 1;
        LifeLabelNumber -> setText(QString::number(life));
    }
    this -> update(); // 调用绘图事件，显示蛇身
    connect(Timer,SIGNAL(timeout()),this,SLOT(M_CheckGameOver()));
}

void Gamewidget::M_startPush()//时间函数开始计时
{
    Timer -> start(475);//开始计时
    disconnect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));//断开和start的链接
    StartPush -> setIcon(QIcon(":/Picture/pause.jpg"));
    connect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_pausePush()));//建立与pause的链接
}
void Gamewidget::M_pausePush()//实现开始与暂停按钮的管理
{
    Timer -> stop();//停止计时
    connect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));
    StartPush -> setIcon(QIcon(":/Picture/single.png"));
    disconnect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_pausePush()));//重新和start建立链接
}

void Gamewidget::M_exitPush()
{
    file = new QFile ("memory.txt");
    file->open(QIODevice::WriteOnly);
    QTextStream stream(&*file);
    stream << life << QString('\n');
    stream << Difficulty << QString('\n');
    stream << bodycount << QString('\n');
    stream << constbodycount << QString('\n');
    for(int i=0;i<=bodycount;++i)
        stream << snake[i][0] << QString(' ') << snake[i][1] << QString('\n');
    stream << Score << QString('\n');
    stream << m_setDirection << QString('\n');
    stream << foodx << QString('\n');
    stream << foody << QString('\n');
    stream << lfoodx << QString('\n');
    stream << lfoody << QString('\n');
    stream << speedfoodx << QString('\n');
    stream << speedfoody << QString('\n');
    stream << gapplex << QString('\n');
    stream << gappley << QString('\n');
    stream << snailx << QString('\n');
    stream << snaily << QString('\n');
    stream << sign << QString('\n');
    stream << sign2 << QString('\n');
    stream << Nobite << QString('\n');
    file->close();
    this -> close();
    delete this;
}

void Gamewidget::M_restartPush()
{
    for(int i=0;i<=bodycount;++i)
    {
        snake[i][0] = 1000;
        snake[i][1] = 1000;
    }
    Score = 0;
    Difficulty = 1;
    life = 1;
    snake[0][0] = (rand()%17+2)*30;
    snake[0][1] = (rand()%13+2)*30;
    m_setDirection = (rand()%4)+1;
    foodx = (rand()%19+1)*30;
    foody = (rand()%15+1)*30;
    lfoodx = 1000;
    lfoody = 1000;
    speedfoodx = 1000;
    speedfoody = 1000;
    gapplex = 1000;
    gappley = 1000;
    snailx = 1000;
    snaily = 1000;
    sign = 3;
    sign2 = 15;
    constbodycount = bodycount = 1;  //包含蛇的头和尾巴
    Nobite = 1;
    ScoreLabelNumber -> setText(QString::number(Score)+"分");
    ScoreLabelNumber -> setGeometry(750,10,120,90);
    LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
    LevelLabelNumber -> setGeometry(750,50,120,90);
    LifeLabelNumber -> setText(QString::number(life));
    LifeLabelNumber -> setGeometry(750,90,120,90);
    this -> update();
    Timer -> stop();
    connect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));
    StartPush -> setIcon(QIcon(":/Picture/single.png"));
    disconnect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_pausePush()));
}
void Gamewidget::M_CheckGameOver()
{
    if((30 > snake[0][0] || snake[0][0] > 570 || 30 > snake[0][1] || snake[0][1] > 450 || (!Nobite)) && life == 0)
    {
        Nobite = 1;
        this ->update();
        Timer -> stop();
        if(QMessageBox::Yes == QMessageBox::information(this,"Tips：","Game Over!",QMessageBox::Yes))
        {
            this -> hide();
            delete this;
            return;
        }
    }
    if((30 > snake[0][0] || snake[0][0] > 570 || 30 > snake[0][1] || snake[0][1] > 450 || (!Nobite)) && life != 0)
    {
        Nobite = 1;
        this -> update();
        if(QMessageBox::No == QMessageBox::information(this,"Tips：","Game Over, but you have got another chance! Click Yes to continue",QMessageBox::Yes|QMessageBox::No))
        {
            this -> hide();
            delete this;
            return;
        }
        else
        {
            snake[0][0] = (rand()%17+1)*30+30;
            snake[0][1] = (rand()%13+1)*30+30;
            for(int i = bodycount;i>0;i--)
            {
                snake[i][0] = 1000;
                snake[i][1] = 1000;
            }
            m_setDirection = (rand()%4)+1;
            bodycount = 1;
        }
    }
}







