#include "stack.h"
#include "termio.h"

Stack::Stack(int i)
{
    head=nullptr;
    rod=i;
    record=0;
}
Stack::~Stack()
{
    node *tmp;
    while(head!=nullptr)
    {
        tmp=head;
        head=head->next;
        delete tmp;
    }
}
bool Stack::isEmpty() const
{
    return head==nullptr;
}
int Stack::push(const int &x)
{
    node *tmp=head;
    while(tmp!=nullptr)
    {
        if(tmp->data<x)
            return 0;
        tmp=tmp->next;
    }
    head=new node(x,head);
    Termio::buffer[9-record*2][15*rod-10]='*';
    for(int i=1;i<=x;++i)
    {
        Termio::buffer[9-record*2][15*rod-10-i]='*';
        Termio::buffer[9-record*2][15*rod-10+i]='*';
    }
    record=record+1;
    return 1;
}
int Stack::pop()
{
    node *tmp=head;
    int x=head->data;
    head=head->next;
    Termio::buffer[9-(record-1)*2][15*rod-10]='|';
    for(int i=1;i<=5;++i)
    {
        Termio::buffer[9-(record-1)*2][15*rod-10-i]=' ';
        Termio::buffer[9-(record-1)*2][15*rod-10+i]=' ';
    }
    record=record-1;
    delete tmp;
    return x;
}
int Stack::top() const
{
    return head->data;
}
void Stack::clear()
{
    while(head!=nullptr)
        this->pop();
}
