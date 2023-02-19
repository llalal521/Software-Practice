#ifndef STACK_H
#define STACK_H


class Stack
{
private:
    struct node{
        int data;
        node *next;
        node(const int &x,node *N=nullptr)
        {
            data=x;
            next=N;
        }
        node():next(nullptr){}
        ~node(){}
    };
    node *head;
public:
    int rod;
    int record;
    Stack(int n);
    ~Stack();
    bool isEmpty() const;
    int push(const int &x);
    int pop();
    int top() const;
    void clear();
};


#endif // STACK_H
