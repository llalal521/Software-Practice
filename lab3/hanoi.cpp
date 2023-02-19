#include "termio.h"
#include "stack.h"
#include <string>

using namespace std;

char Termio::buffer[Termio::CANVAS_HEIGHT][Termio::CANVAS_WIDTH + 1];
void initialbuffer();
int transfer(string a);
void autoRun(int n,Stack *A,Stack *B,Stack *C);

int main()
{
    string cmd;
    int nloop=0;
    int step[10000][2];
    int disknum,record=0;
    int judge;
    int from,to;
    Stack *rod[3];
    for(int i=0;i<3;++i)
        rod[i]=new Stack(i+1);
    while(true)
    {
        Termio::Clear();
        cout << "How many disks do you want? (1 ~ 5)" << endl;
        cin>>cmd;
        if(cmd=="Q")
            break;
        disknum=transfer(cmd);
        if(disknum>5||disknum<=0)
            continue;
        initialbuffer();
        for(int i=disknum;i>0;--i)
            rod[0]->push(i);
        Termio::Draw();
        while(true)
        {
            Termio::Clear();
            cout << "Move a disk. Format: x y" << endl;
            cin>>from>>to;
            if(from>3||to>3)
            {
                Termio::Draw();
                continue;
            }
            if(from==0&&to==0)
            {
                if(nloop!=0)
                for(int i=nloop-1;i>=0;--i)
                {
                    record=rod[step[i][1]-1]->pop();
                    rod[step[i][0]-1]->push(record);
                    Termio::Clear();
                    cout << "Auto moving:" << step[i][1] << "->" << step[i][0] << std::endl;
                    Termio::Draw();
                }
                autoRun(disknum,rod[0],rod[1],rod[2]);
                cout << "Congratulations! You win!" << std::endl;
                for(int i=0;i<3;++i)
                    rod[i]->clear();
                break;
            }
            if(!rod[from-1]->isEmpty())
            {
                record=rod[from-1]->pop();
                judge=rod[to-1]->push(record);
            }
            else {Termio::Draw();continue;}
            if(judge==0)
            {
                rod[from-1]->push(record);
            }
            Termio::Draw();
            if(rod[0]->isEmpty()&&rod[2]->isEmpty())
            {
                cout << "Congratulations! You win!" << std::endl;
                for(int i=0;i<3;++i)
                    rod[i]->clear();
                break;
            }
            if(judge!=0)
            {
                step[nloop][0]=from;
                step[nloop][1]=to;
                nloop=nloop+1;
            }
        }
    }
}
int transfer(string a)
{
    int record;
    record=a[0]-'0';
    return record;
}
void initialbuffer()
{
    for(int i=0;i<11;++i)
        for(int j=0;j<41;++j)
            Termio::buffer[i][j]=' ';
    for(int j=0;j<41;++j)
       Termio::buffer[10][j]='-';
    for(int i=0;i<11;++i)
    {
        Termio::buffer[i][5]='|';
        Termio::buffer[i][20]='|';
        Termio::buffer[i][35]='|';
    }
}
void autoRun(int n,Stack *a,Stack *b,Stack *c)
{
    if(n==0)
        return;
    int record;
    autoRun(n-1,a,c,b);
    record=a->pop();
    b->push(record);
    Termio::Clear();
    cout << "Auto moving:" << a->rod << "->" << b->rod << std::endl;
    Termio::Draw();
    autoRun(n-1,c,b,a);
}
