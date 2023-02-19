#include <fstream>
#include <iostream>
#include "Buffer.h"

using namespace std;

void Buffer::ListBuffer::insert(int &n,const string &text)
{
    ListBuffer *tmp=this;
    for(int i=0;i<n-1;++i)
        tmp=tmp->next;
    ListBuffer *tmp2=tmp->next;
    tmp->next=new ListBuffer(text);
    tmp->next->next=tmp2;
}

void Buffer::ListBuffer::add(int &n, const string &text)
{
    ListBuffer *tmp=this;
    ListBuffer *tmp2;
    for(int i=0;i<n;++i)
        tmp=tmp->next;
    tmp2=tmp->next;
    tmp->next=new ListBuffer (text);
    tmp->next->next=tmp2;
    ++n;
}

int Buffer::ListBuffer::showAll()
{
    ListBuffer *tmp=this;
    int n=1;
    while(tmp->next!=NULL)
    {
        cout<<n<<'\t'<<tmp->next->a<<'\n';
        tmp=tmp->next;
        n=n+1;
    }
    return n-1;
}

const string Buffer::ListBuffer::moveToLine(int idx)
{
    ListBuffer *tmp=this;
    for(int i=0; i<idx; ++i)
        tmp=tmp->next;
    return tmp->a;
}

void Buffer::ListBuffer::showlines(int from, int to)
{
    int n=from;
    ListBuffer* tmp=this;
    for(int i=0;i<from;++i)
        tmp=tmp->next;
    for(int j=from;j<to+1;++j)
    {
        cout<<n<<'\t'<<tmp->a<<'\n';
        n=n+1;
        tmp=tmp->next;
    }
}

void Buffer::ListBuffer::deletelines(int from, int to)
{
    ListBuffer* tmp=this;
    ListBuffer* tmp2=this;
    ListBuffer* tmp3,*tmp4;
    for(int i=0; i<from-1; ++i)
    {
        tmp=tmp->next;
    }
    for(int i=0; i<to+1; ++i)
    {
        tmp2=tmp2->next;
    }
    tmp3=tmp->next;
    for(int i=from; i<=to; ++i)
    {
        tmp4=tmp3;
        tmp3=tmp3->next;
        delete tmp4;
    }
    tmp->next=tmp2;
}

int Buffer::ListBuffer::getMaxsize()
{
    int n=0;
    ListBuffer *tmp=this;
    while(tmp->next!=NULL)
    {
        n=n+1;
        tmp=tmp->next;
    }
    return n;
}

Buffer::Buffer()
{
    currentLineNum=0;
}

Buffer::~Buffer()
{
    ListBuffer *tmp=Head;
    ListBuffer *tmp1;
    while(tmp->next!=NULL)
    {
        tmp1=tmp;
        tmp=tmp->next;
        delete tmp1;
    }
}

void Buffer::writeToFile(const string &filename) const
{
    int n=0;
    ofstream out(filename);
    if(out.fail())
        cout<<"error";
    ListBuffer *tmp=Head;
    while(tmp->next!=NULL)
    {
        out<<tmp->next->a<<'\n';
        n=n+tmp->next->a.size()+1;
        tmp=tmp->next;
    }
    cout<<n<<" byte(s) written"<<endl;
}
void Buffer::showAll()
{
    if(Head->next==NULL) throw range_error("Number range error");
    currentLineNum=Head->showAll();
}
void Buffer::showLines(int from, int to)
{
    int a=Head->getMaxsize();
    if(from>to)
        throw range_error("Number range error");
    else if(from>a||to>a||from<=0||to<=0)
        throw out_of_range("Line number out of range");
    currentLineNum=to;
    Head->showlines(from,to);
}

void Buffer::deleteLines(int from, int to)
{
    int a=Head->getMaxsize();
    if(from>to)
        throw range_error("Delete range error");
    else if(from>a||to>a||from<=0||to<=0)
        throw out_of_range("Line number out of range");
    currentLineNum=from;
    Head->deletelines(from,to);
}

void Buffer::insertLine(const string &text)
{
    if(currentLineNum==0)
        Head->add(currentLineNum,text);
    else
        Head->insert(currentLineNum,text);
}

void Buffer::appendLine(const string &text)
{
    Head->add(currentLineNum,text);
}

const string Buffer::moveToLine(int idx)
{
    int a=Head->getMaxsize();
    if(a<idx||idx<=0)
        throw out_of_range("Line number out of range");
    currentLineNum=idx;
    return Head->moveToLine(idx);
}
