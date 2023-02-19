#include "gamewidget2.h"
#include "widget.h"
#include <QDebug>

int Gamewidget2::m_setDirection1 = 4;
int Gamewidget2::m_setDirection2 = 4;
Gamewidget2::Gamewidget2(QWidget *parent) : QWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus);
    qsrand(time(NULL));//随机数的种子
    this->setAutoFillBackground(true);//设置父窗口背景可被覆盖填充
    this->resize(891,510);
    this->setWindowTitle("贪吃蛇");
    this->setWindowIcon(QIcon(":/Picture/img/WindowPicture.jpg"));

    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/Gamewindow/GameBack.jpg").scaled(this->size())));//设置游戏背景，大小自适应
    this->setPalette(palette);

    StartPush=new QPushButton(this);
    ExitPush=new QPushButton(this);
    RestartPush=new QPushButton(this);

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

    ScoreLabel1 = new QLabel(this); //设置标签，一个得分标签，一个难度标签
    ScoreLabel2 = new QLabel(this);
    LevelLabel = new QLabel(this);
    LifeLabel1 = new QLabel(this);
    LifeLabel2 = new QLabel(this);
    ScoreLabel1 -> setText("Score1:");
    ScoreLabel1 -> setGeometry(710,10,120,90);
    LifeLabel1 -> setText("Life1:");
    LifeLabel1 -> setGeometry(710,50,120,90);
    ScoreLabel2 -> setText("Score2:");
    ScoreLabel2 -> setGeometry(710,90,120,90);
    LevelLabel -> setText("Level:");
    LevelLabel -> setGeometry(710,170,120,90);
    LifeLabel2 -> setText("Life2");
    LifeLabel2 -> setGeometry(710,130,120,90);

    ScoreLabelNumber1 = new QLabel(this);
    ScoreLabelNumber2 = new QLabel(this);
    LevelLabelNumber = new QLabel(this);
    LifeLabelNumber1 = new QLabel(this);
    LifeLabelNumber2 = new QLabel(this);

    Timer = new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(M_timeout()));
    connect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));//事件关联处理，和widget中相同
    connect(ExitPush,SIGNAL(clicked(bool)),this,SLOT(M_exitPush()));
    connect(RestartPush,SIGNAL(clicked(bool)),this,SLOT(M_restartPush()));

    file = new QFile ("memory2.txt");
    file->open(QIODevice::ReadOnly);
    QTextStream stream(&*file);
    if(file->atEnd()){
        Score1 = 0;
        Score2 = 0;
        Difficulty = 1;
        life1 = 1;
        life2 = 1;
        judge = true;
        snake[0][0] = (rand()%17+2)*30 + 30;
        snake[0][1] = (rand()%13+2)*30 + 30;
        dsnake[0][0] = (rand()%17+2)*30 + 30;
        dsnake[0][1] = (rand()%13+2)*30 + 30;
        m_setDirection1 = (rand()%4) + 1;
        m_setDirection2 = (rand()%4) + 1;
        foodx = (rand()%19+1)*30;
        foody = (rand()%15+1)*30;
        food2x = (rand()%19+1)*30;
        food2y = (rand()%15+1)*30;
        lfoodx = 1500;
        lfoody = 1500;
        speedfoodx = 1500;
        speedfoody = 1500;
        gapplex = 1500;
        gappley = 1500;
        snailx = 1500;
        snaily = 1500;
        sign = 3;
        sign2 = 15;
        bodycount1 = 1;
        constbodycount1 = 1;
        bodycount2 = 1;
        constbodycount2 = 1;
        Nobite1 = true;
        Nobite2 = true;
        Nobiteach = true;
    }
    else{
        stream >> judge;
        stream >> life1 >> life2;
        stream >> Difficulty;
        stream >> bodycount1 >> bodycount2;
        stream >> constbodycount1 >> constbodycount2;
        for(int i=0;i<=bodycount1;++i)
            stream >> snake[i][0] >> snake[i][1];
        for(int i=0;i<=bodycount2;++i)
            stream >> dsnake[i][0] >> dsnake[i][1];
        stream >> Score1 >> Score2;
        stream >> m_setDirection1 >> m_setDirection2;
        stream >> foodx >> foody;
        stream >> food2x >> food2y;
        stream >> lfoodx >> lfoody;
        stream >> speedfoodx >> speedfoody;
        stream >> gapplex >>gappley;
        stream >> snailx >> snaily;
        stream >> sign >> sign2;
        stream >> Nobite1 >> Nobite2 >> Nobiteach;
    }

    ScoreLabelNumber1 -> setText(QString::number(Score1)+"分"); //将得分作为字符串输出到label中
    ScoreLabelNumber1 -> setGeometry(760,10,120,90);
    LifeLabelNumber1 -> setText(QString::number(life1)); //将得分作为字符串输出到label中
    LifeLabelNumber1 -> setGeometry(760,50,120,90);
    ScoreLabelNumber2 -> setText(QString::number(Score2)+"分");
    ScoreLabelNumber2 -> setGeometry(760,90,120,90);
    LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
    LevelLabelNumber -> setGeometry(760,170,120,90);
    LifeLabelNumber2 -> setText(QString::number(life2)); //将得分作为字符串输出到label中
    LifeLabelNumber2 -> setGeometry(760,130,120,90);
    this -> update();
}
void Gamewidget2::keyPressEvent(QKeyEvent *e)//按键处理
{
    qDebug () << e -> key();
    switch(e -> key())
    {
    case Qt::Key_Up:
        if(m_setDirection1 != 2)m_setDirection1 = 1;
        break; //如果键盘为上键，则将方向变量置为1，且不能为相反方向
    case Qt::Key_W:
        if(m_setDirection2 != 2)m_setDirection2 = 1;
        break;
    case Qt::Key_Down:
        if(m_setDirection1 != 1)m_setDirection1 = 2;
        break;
    case Qt::Key_S:
        if(m_setDirection2 != 1)m_setDirection2 = 2;
        break;
    case Qt::Key_Left:
        if(m_setDirection1 != 4)m_setDirection1 = 3;
        break;
    case Qt::Key_A:
        if(m_setDirection2 != 4)m_setDirection2 = 3;
        break;
    case Qt::Key_Right:
        if(m_setDirection1 != 3)m_setDirection1 = 4;
        break;
    case Qt::Key_D:
        if(m_setDirection2 != 3)m_setDirection2 = 4;
        break;
    default: break;

    }
}
void Gamewidget2::paintEvent(QPaintEvent*)//绘图事件
{
    QPainter painter(this);
    if(30 <= snake[0][0] && snake[0][0] <= 570 && 30 <= snake[0][1] && snake[0][1] <= 450 && Nobite1 && Nobite2 && Nobiteach)//蛇头要在界面内，设定碰壁为失败
    {
        qDebug() << snake[0][0];
        if(bodycount1 > 1)
        for(int i=bodycount1;i>0;i--)
            painter.drawImage(QRect(snake[i][0],snake[i][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));//画出蛇
    }
    if(30 <= dsnake[0][0] && dsnake[0][0] <= 570 && 30 <= dsnake[0][1] && dsnake[0][1] <= 450 && Nobite1 && Nobite2 && Nobiteach)//蛇头要在界面内，设定碰壁为失败
    {
        qDebug() << dsnake[0][0];
        if(bodycount2 > 1)
        for(int i=bodycount2;i>0;i--)
            painter.drawImage(QRect(dsnake[i][0],dsnake[i][1],30,30),QImage(":/Picture/snake2.jpg"));//画出蛇
    }
    painter.drawImage(QRect(foodx,foody,30,30),QImage(":/new/Gamewindow/img/Apple.png")); //画出食物
    painter.drawImage(QRect(food2x,food2y,30,30),QImage(":/new/Gamewindow/img/Apple.png"));
    painter.drawImage(QRect(lfoodx,lfoody,30,30),QImage(":/new/Gamewindow/life.jpg"));
    painter.drawImage(QRect(snailx,snaily,30,30),QImage(":/Picture/snail.png"));
    painter.drawImage(QRect(speedfoodx,speedfoody,30,30),QImage(":/Picture/speedfood.png"));
    painter.drawImage(QRect(gapplex,gappley,30,30),QImage(":/Picture/gapple.png"));

    painter.setPen(Qt::black);

    for(int i=0;i<=widthnumber;i++)
    {
        for(int j=0;j<=longnumber;j++)
        {
            painter.drawRect(QRect(30 * j,30 * i,30,30));//画出游戏方格
        }
    }
    painter.drawImage(QRect(0,0,30,510),QImage(":/Picture/blick.jpg"));
    painter.drawImage(QRect(0,0,630,30),QImage(":/Picture/blick.jpg"));
    painter.drawImage(QRect(0,480,630,30),QImage(":/Picture/blick.jpg"));
    painter.drawImage(QRect(600,0,30,510),QImage(":/Picture/blick.jpg"));
    switch (m_setDirection1)
    {
        case 1: painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));
            if(bodycount1 == 1)  painter.drawImage(QRect(snake[0][0],snake[0][1] + 30,30,30),QImage(":/new/Gamewindow/snake.jpg"));
            break;
        case 2: painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));
            if(bodycount1 == 1) painter.drawImage(QRect(snake[0][0],snake[0][1] - 30,30,30),QImage(":/new/Gamewindow/snake.jpg"));
            break;
        case 3: painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));
            if(bodycount1 == 1) painter.drawImage(QRect(snake[0][0] + 30,snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));
            break;
        case 4: painter.drawImage(QRect(snake[0][0],snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));
            if(bodycount1 == 1)  painter.drawImage(QRect(snake[0][0] - 30,snake[0][1],30,30),QImage(":/new/Gamewindow/snake.jpg"));
            break;
        default:
            break;
    }
    switch (m_setDirection2)
    {
        case 1: painter.drawImage(QRect(dsnake[0][0],dsnake[0][1],30,30),QImage(":/Picture/snake2.jpg"));
            if(bodycount2 == 1)  painter.drawImage(QRect(dsnake[0][0],dsnake[0][1] + 30,30,30),QImage(":/Picture/snake2.jpg"));
            break;
        case 2: painter.drawImage(QRect(dsnake[0][0],dsnake[0][1],30,30),QImage(":/Picture/snake2.jpg"));
            if(bodycount2 == 1) painter.drawImage(QRect(dsnake[0][0],dsnake[0][1] - 30,30,30),QImage(":/Picture/snake2.jpg"));
            break;
        case 3: painter.drawImage(QRect(dsnake[0][0],dsnake[0][1],30,30),QImage(":/Picture/snake2.jpg"));
            if(bodycount2 == 1) painter.drawImage(QRect(dsnake[0][0] + 30,dsnake[0][1],30,30),QImage(":/Picture/snake2.jpg"));
            break;
        case 4: painter.drawImage(QRect(dsnake[0][0],dsnake[0][1],30,30),QImage(":/Picture/snake2.jpg"));
            if(bodycount2 == 1)  painter.drawImage(QRect(dsnake[0][0] - 30,dsnake[0][1],30,30),QImage(":/Picture/snake2.jpg"));
            break;
        default:
            break;
    }
}

void Gamewidget2::M_timeout()
{
    int tmp = Difficulty;
    if(snake[0][0] == foodx && snake[0][1] == foody)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        foodx = (rand()%19+1)*30;
        foody = (rand()%15+1)*30;
        bodycount1++;  //蛇的身体加一
        constbodycount1++;
        Difficulty = std::max(constbodycount1,constbodycount2)/5 + 1;
        Score1 = Score1 + Difficulty;
        ScoreLabelNumber1 -> setText(QString::number(Score1)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
    }
    if(snake[0][0] == food2x && snake[0][1] == food2y)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        food2x = (rand()%19+1)*30;
        food2y = (rand()%15+1)*30;
        bodycount1++;  //蛇的身体加一
        constbodycount1++;
        Difficulty = std::max(constbodycount1,constbodycount2)/5 + 1;
        Score1 = Score1 + Difficulty;
        ScoreLabelNumber1 -> setText(QString::number(Score1)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
    }
    if(dsnake[0][0] == foodx && dsnake[0][1] == foody)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        foodx = (rand()%19+1)*30;
        foody = (rand()%15+1)*30;
        bodycount2++;  //蛇的身体加一
        constbodycount2++;
        Difficulty = std::max(constbodycount1,constbodycount2)/5 + 1;
        Score2 = Score2 + Difficulty;
        ScoreLabelNumber2 -> setText(QString::number(Score2)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
    }
    if(dsnake[0][0] == food2x && dsnake[0][1] == food2y)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        food2x = (rand()%19+1)*30;
        food2y = (rand()%15+1)*30;
        bodycount2++;  //蛇的身体加一
        constbodycount2++;
        Difficulty = std::max(constbodycount1,constbodycount2)/5 + 1;
        Score2 = Score2 + Difficulty;
        ScoreLabelNumber2 -> setText(QString::number(Score2)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
    }
    if(snake[0][0] == lfoodx && snake[0][1] == lfoody)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        life1 = life1 + 1;
        lfoodx = 1500;
        lfoody = 1500;
        bodycount1++;  //蛇的身体加一
        constbodycount1++;
        Difficulty = std::max(constbodycount1,constbodycount2)/5 + 1;
        Score1 = Score1 + Difficulty;
        ScoreLabelNumber1 -> setText(QString::number(Score1)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        LifeLabelNumber1 -> setText(QString::number(life1));
        Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
    }
    if(dsnake[0][0] == lfoodx && dsnake[0][1] == lfoody)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        life2 = life2 + 1;
        lfoodx = 1500;
        lfoody = 1500;
        bodycount2++;  //蛇的身体加一
        constbodycount2++;
        Difficulty = std::max(constbodycount1,constbodycount2)/5 + 1;
        Score2 = Score2 + Difficulty;
        ScoreLabelNumber2 -> setText(QString::number(Score2)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        LifeLabelNumber2 -> setText(QString::number(life2));
        Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
    }
    if(snake[0][0] == speedfoodx && snake[0][1] == speedfoody)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        speedfoodx = 1500;
        speedfoody = 1500;
        Score1 = Score1 + Difficulty;
        Difficulty++;
        constbodycount1 = (Difficulty - 1) * 5;
        ScoreLabelNumber1 -> setText(QString::number(Score1)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
    }
    if(dsnake[0][0] == speedfoodx && dsnake[0][1] == speedfoody)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        speedfoodx = 1500;
        speedfoody = 1500;
        Score2 = Score2 + Difficulty;
        Difficulty++;
        constbodycount2 = (Difficulty - 1) * 5;
        ScoreLabelNumber2 -> setText(QString::number(Score2)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
    }
    if(snake[0][0] == snailx && snake[0][1] == snaily)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        snailx = 1500;
        snaily = 1500;
        Score1 = Score1 + Difficulty;
        Difficulty--;
        constbodycount1= (Difficulty - 1) * 5;
        ScoreLabelNumber1 -> setText(QString::number(Score1)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
    }
    if(dsnake[0][0] == snailx && dsnake[0][1] == snaily)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        snailx = 1500;
        snaily = 1500;
        Score2 = Score2 + Difficulty;
        Difficulty--;
        constbodycount2= (Difficulty - 1) * 5;
        ScoreLabelNumber1 -> setText(QString::number(Score1)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
    }
    if(snake[0][0] == gapplex && snake[0][1] == gappley)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        gapplex = 1500;
        gappley = 1500;
        Score1 = Score1 + Difficulty;
        bodycount1 = bodycount1 / 2;
        for(int i = constbodycount1;i>bodycount1;--i)
        {
            snake[i][0] = 1000;
            snake[i][1] = 1000;
        }
        ScoreLabelNumber1 -> setText(QString::number(Score1)+"分");
        LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
        Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
    }
    if(dsnake[0][0] == gapplex && dsnake[0][1] == gappley)//当蛇头的坐标与食物坐标重合的时候，重新布置食物的位置
    {
        gapplex = 1500;
        gappley = 1500;
        Score2 = Score2 + Difficulty;
        bodycount2 = bodycount2 / 2;
        for(int i = constbodycount2;i>bodycount2;--i)
        {
            dsnake[i][0] = 1000;
            dsnake[i][1] = 1000;
        }
        ScoreLabelNumber2 -> setText(QString::number(Score2)+"分");
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
    if(std::max(bodycount1,bodycount2) > sign2)
    {
        sign2 = sign2 * 2;
        gapplex = (rand()%19+1)*30;
        gappley = (rand()%15+1)*30;
    }

    memcpy(snake1,snake,sizeof(snake));
    memcpy(dsnake1,dsnake,sizeof(dsnake));

    for(int i=bodycount1;i>0;i--)//将蛇身体的前一个坐标赋值给后一个坐标，实现蛇身体的连续出现
    {

        snake[i][0] = snake[i-1][0];
        snake[i][1] = snake[i-1][1];
    }
    for(int i=bodycount2;i>0;i--)//将蛇身体的前一个坐标赋值给后一个坐标，实现蛇身体的连续出现
    {

        dsnake[i][0] = dsnake[i-1][0];
        dsnake[i][1] = dsnake[i-1][1];
    }
    QPainter painter(this);

    for(int i=bodycount1;i>3;i--) //检查是否相撞
    {
        if(snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1])
        {
            memcpy(snake,snake1,sizeof(snake));
            Nobite1 = false;
            life1--;
            LifeLabelNumber1 -> setText(QString::number(life1));
        }
    }
    for(int i=bodycount2;i>3;i--) //检查是否相撞
    {
        if(dsnake[0][0] == dsnake[i][0] && dsnake[0][1] == dsnake[i][1])
        {
            memcpy(dsnake,dsnake1,sizeof(dsnake));
            Nobite2 = false;
            life2--;
            LifeLabelNumber2 -> setText(QString::number(life2));
        }
    }
    for(int i=0;i<=bodycount1;i++) //检查是否相撞
    {
        if(dsnake[0][0] == snake[i][0] && dsnake[0][1] == snake[i][1])
        {
            memcpy(snake,snake1,sizeof(snake));
            memcpy(dsnake,dsnake1,sizeof(dsnake));
            Nobiteach = false;
            judge = false;
            life1--;
            life2--;
            LifeLabelNumber1 -> setText(QString::number(life1));
            LifeLabelNumber2 -> setText(QString::number(life2));
            break;
        }
    }
    if(judge)
    for(int i=0;i<=bodycount2;i++) //检查是否相撞
    {
        if(snake[0][0] == dsnake[i][0] && snake[0][1] == dsnake[i][1])
        {
            memcpy(snake,snake1,sizeof(snake));
            memcpy(dsnake,dsnake1,sizeof(dsnake));
            Nobiteach = false;
            life1--;
            life2--;
            if(life1 < 0) life1 = 0;
            if(life2 < 0) life2 = 0;
            LifeLabelNumber1 -> setText(QString::number(life1));
            LifeLabelNumber2 -> setText(QString::number(life2));
            break;
        }
    }
    judge = true;
    switch (m_setDirection1)
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
    switch (m_setDirection2)
    {
    case 1: dsnake[0][1] = dsnake[0][1] - 30,painter.drawImage(QRect(dsnake[0][0],dsnake[0][1],30,30),QImage(":/new/Gamewindow/snake2.jpg"))
                ;break;
    case 2: dsnake[0][1] = dsnake[0][1] + 30,painter.drawImage(QRect(dsnake[0][0],dsnake[0][1],30,30),QImage(":/new/Gamewindow/snake2.jpg"))
                ; break;
    case 3: dsnake[0][0] = dsnake[0][0] - 30,painter.drawImage(QRect(dsnake[0][0],dsnake[0][1],30,30),QImage(":/new/Gamewindow/snake2.jpg"))
                ; break;
    case 4: dsnake[0][0] = dsnake[0][0] + 30,painter.drawImage(QRect(dsnake[0][0],dsnake[0][1],30,30),QImage(":/new/Gamewindow/snake2.jpg"))
                ;break;
    default:
        break;
    }
    if((30 > snake[0][0] || snake[0][0] > 570 || 30 > snake[0][1] || snake[0][1] > 450) && snake[0][0] != 1000 && snake[0][1] != 1000)
    {
        memcpy(snake,snake1,sizeof(snake));
        Nobite1 = false;
        life1--;
        LifeLabelNumber1 -> setText(QString::number(life1));
    }
    if((30 > dsnake[0][0] || dsnake[0][0] > 570 || 30 > dsnake[0][1] || dsnake[0][1] > 450) && dsnake[0][0] != 1000 && dsnake[0][1] != 1000)
    {
        memcpy(dsnake,dsnake1,sizeof(dsnake));
        Nobite2 = false;
        life2--;
        LifeLabelNumber2 -> setText(QString::number(life2));
    }
    this -> update();
    connect(Timer,SIGNAL(timeout()),this,SLOT(M_CheckGameOver()));
}

void Gamewidget2::M_startPush()//时间函数开始计时
{
    Timer -> start(475);//开始计时
    disconnect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));//断开和start的链接
    StartPush -> setIcon(QIcon(":/Picture/pause.jpg"));
    connect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_pausePush()));//建立与pause的链接
}
void Gamewidget2::M_pausePush()//实现开始与暂停按钮的管理
{
    Timer -> stop();//停止计时
    connect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));
    StartPush -> setIcon(QIcon(":/Picture/single.png"));
    disconnect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_pausePush()));//重新和start建立链接
}

void Gamewidget2::M_exitPush()
{
    file = new QFile ("memory2.txt");
    file->open(QIODevice::WriteOnly);
    QTextStream stream(&*file);
    stream << judge << QString('\n');
    stream << life1 << QString('\n');
    stream << life2 << QString('\n');
    stream << Difficulty << QString('\n');
    stream << bodycount1 << QString('\n');
    stream << bodycount2 << QString('\n');
    stream << constbodycount1 << QString('\n');
    stream << constbodycount2 << QString('\n');
    for(int i=0;i<=bodycount1;++i)
        stream << snake[i][0] << QString(' ') << snake[i][1] << QString('\n');
    for(int i=0;i<=bodycount2;++i)
        stream << dsnake[i][0] << QString(' ') << dsnake[i][1] << QString('\n');
    stream << Score1 << QString('\n');
    stream << Score2 << QString('\n');
    stream << m_setDirection1 << QString('\n');
    stream << m_setDirection2 << QString('\n');
    stream << foodx << QString('\n');
    stream << foody << QString('\n');
    stream << food2x << QString('\n');
    stream << food2y << QString('\n');
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
    stream << Nobite1 << QString('\n');
    stream << Nobite2 << QString('\n');
    stream << Nobiteach << QString('\n');
    file->close();
    this -> close();
    delete this;
}

void Gamewidget2::M_restartPush()
{
    for(int i=0;i<=bodycount1;++i){
        snake[i][0] = 1000;
        snake[i][1] = 1000;
    }
    for(int i=0;i<bodycount2;++i){
        dsnake[i][0] = 1000;
        dsnake[i][1] = 1000;
    }
    Score1 = 0;
    Score2 = 0;
    Difficulty = 1;
    life1 = 1;
    life2 = 1;
    ScoreLabelNumber1 -> setText(QString::number(Score1)+"分");
    ScoreLabelNumber1 -> setGeometry(760,10,120,90);
    LifeLabelNumber1 -> setText(QString::number(life1));
    LifeLabelNumber1 -> setGeometry(760,50,120,90);
    ScoreLabelNumber2 -> setText(QString::number(Score2)+"分");
    ScoreLabelNumber2 -> setGeometry(760,90,120,90);
    LevelLabelNumber -> setText(QString::number(Difficulty)+"级");
    LevelLabelNumber -> setGeometry(760,170,120,90);
    LifeLabelNumber2 -> setText(QString::number(life2));
    LifeLabelNumber2 -> setGeometry(760,130,120,90);
    snake[0][0] = (rand()%17+2)*30 + 30;
    snake[0][1] = (rand()%13+2)*30 + 30;
    dsnake[0][0] = (rand()%17+2)*30 + 30;
    dsnake[0][1] = (rand()%13+2)*30 + 30;
    m_setDirection1 = (rand()%4) + 1;
    m_setDirection2 = (rand()%4) + 1;
    foodx = (rand()%19+1)*30;
    foody = (rand()%15+1)*30;
    food2x = (rand()%19+1)*30;
    food2y = (rand()%15+1)*30;
    lfoodx = 1500;
    lfoody = 1500;
    speedfoodx = 1500;
    speedfoody = 1500;
    gapplex = 1500;
    gappley = 1500;
    snailx = 1500;
    snaily = 1500;
    sign = 3;
    sign2 = 15;
    bodycount1 = 1;
    constbodycount1 = 1;
    bodycount2 = 1;
    constbodycount2 = 1;
    Nobite1 = true;
    Nobite2 = true;
    Nobiteach = true;
    this->update();
    Timer -> stop();
    connect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));
    StartPush -> setIcon(QIcon(":/Picture/single.png"));
    disconnect(StartPush,SIGNAL(clicked(bool)),this,SLOT(M_pausePush()));
}

void Gamewidget2::M_CheckGameOver()
{
    int i;
    if((!Nobite1) && life1 == 0)
    {
        Nobite1 = true;
        this ->update();
        Timer -> stop();
        if(QMessageBox::Yes == QMessageBox::information(this,"Tips：","Player1 Game Over!",QMessageBox::Yes))
        {
            for(int j=0;j<=bodycount1;++j){
                snake[j][1] = 1000;
                snake[j][0] = 1000;
            }
            bodycount1 = 0;
            if(bodycount2 == 0)
            {
                this -> hide();
                delete this;
                return;
            }
            Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
        }
    }
    if((!Nobite1) && life1 != 0)
    {
        Nobite1 = true;
        this -> update();
        if(QMessageBox::No == QMessageBox::information(this,"Tips：","Player1 Game Over, but you have got another chance! Click Yes to continue",QMessageBox::Yes|QMessageBox::No))
        {
            for(int j=0;j<=bodycount1;++j){
                snake[j][1] = 1000;
                snake[j][0] = 1000;
            }
            bodycount1 = 0;
            if(bodycount2 == 0)
            {
                this -> hide();
                delete this;
                return;
            }
            Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
        }
        else
        {
            while(true){
                snake[0][0] = (rand()%17+1)*30+30;
                snake[0][1] = (rand()%13+1)*30+30;
                for(i=0;i<bodycount2;++i)
                    if(snake[0][0] == dsnake[i][0] && snake[0][1] == dsnake[i][1])
                        break;
                if(i == bodycount2)
                    break;
            }
            for(int j = bodycount1;j>0;j--)
            {
                snake[j][0] = 1000;
                snake[j][1] = 1000;
            }
            m_setDirection1 = (rand()%4)+1;
            bodycount1 = 1;
            Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
        }
    }
    if((!Nobite2) && life2 == 0)
    {
        Nobite2 = true;
        this ->update();
        Timer -> stop();
        if(QMessageBox::Yes == QMessageBox::information(this,"Tips：","Player2 Game Over!",QMessageBox::Yes))
        {
            for(int j = bodycount2;j>=0;j--)
            {
                dsnake[j][0] = 1000;
                dsnake[j][1] = 1000;
            }
            bodycount2 = 0;
            if(bodycount1 == 0)
            {
                this -> hide();
                delete this;
                return;
            }
            Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
        }
    }
    if((!Nobite2) && life2 != 0)
    {
        Nobite2 = true;
        this -> update();
        if(QMessageBox::No == QMessageBox::information(this,"Tips：","Player2 Game Over, but you have got another chance! Click Yes to continue",QMessageBox::Yes|QMessageBox::No))
        {
            for(int j = bodycount2;j>=0;j--)
            {
                dsnake[j][0] = 1000;
                dsnake[j][1] = 1000;
            }
            bodycount2 = 0;
            if(bodycount1 == 0)
            {
                this -> hide();
                delete this;
                return;
            }
            Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
        }
        else
        {
            while(true){
                dsnake[0][0] = (rand()%17+1)*30+30;
                dsnake[0][1] = (rand()%13+1)*30+30;
                for(i=0;i<bodycount1;++i)
                    if(dsnake[0][0] == snake[i][0] && dsnake[0][1] == snake[i][1])
                        break;
                if(i == bodycount1)
                    break;
            }
            for(int j = bodycount2;j>0;j--)
            {
                dsnake[j][0] = 1000;
                dsnake[j][1] = 1000;
            }
            m_setDirection2 = (rand()%4)+1;
            bodycount2 = 1;
            Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
        }
    }
    if(!Nobiteach && life1 == 0 && life2 != 0)
    {
        Nobiteach = true;
        this ->update();
        Timer -> stop();
        if(QMessageBox::Yes == QMessageBox::information(this,"Tips：","Player1 Game Over!",QMessageBox::Yes))
        {
            for(int j = bodycount1;j>=0;j--)
            {
                snake[j][0] = 1000;
                snake[j][1] = 1000;
            }
            bodycount1 = 0;
            if(bodycount2 == 0)
            {
                this -> hide();
                delete this;
                return;
            }
            Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
        }
    }
    if(!Nobiteach && life2 == 0 && life1 != 0)
    {
        Nobiteach = true;
        this ->update();
        Timer -> stop();
        if(QMessageBox::Yes == QMessageBox::information(this,"Tips：","Player2 Game Over!",QMessageBox::Yes))
        {
            for(int j = bodycount2;j>=0;j--)
            {
                dsnake[j][0] = 1000;
                dsnake[j][1] = 1000;
            }
            bodycount2 = 0;
            if(bodycount1 == 0)
            {
                this -> hide();
                delete this;
                return;
            }
            Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
        }
    }
    if(!Nobiteach && life1 != 0 && life2 != 0)
    {
        Nobiteach = true;
        this -> update();
        if(QMessageBox::No == QMessageBox::information(this,"Tips：","You bit each other, but you have got another chance! Click Yes to continue",QMessageBox::Yes|QMessageBox::No))
        {
                this -> hide();
                delete this;
                return;
        }
        else{
            snake[0][0] = (rand()%17+1)*30+30;
            dsnake[0][0] = (rand()%17+1)*30+30;
            snake[0][1] = (rand()%13+1)*30+30;
            dsnake[0][1] = (rand()%13+1)*30+30;
            for(int j = bodycount1;j>0;j--)
            {
                snake[j][0] = 1000;
                snake[j][1] = 1000;
            }
            for(int j = bodycount2;j>0;j--)
            {
                dsnake[j][0] = 1000;
                dsnake[j][1] = 1000;
            }
            m_setDirection1 = (rand()%4)+1;
            bodycount1 = 1;
            m_setDirection2 = (rand()%4)+1;
            bodycount2 = 1;
            Timer->start(Difficulty <= 20 ? 500-Difficulty * 25 : 50 / (Difficulty - 20));
        }
    }
    if(!Nobiteach && life1 == 0 && life2 == 0)
    {
        Nobiteach = true;
        this -> update();
        if(QMessageBox::Yes == QMessageBox::information(this,"Tips：","You bit each other, Game over",QMessageBox::Yes))
        {
                this -> hide();
                delete this;
                return;
        }
    }

}

