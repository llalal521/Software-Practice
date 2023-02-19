#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>

#include "Tree.h"

using namespace std;

int TreeNode::getX()
{
    return data[0];
}
int TreeNode::getY()
{
    return data[1];
}
TreeNode::TreeNode(int a,int b,int c,TreeNode *x,TreeNode *y)
{
    height = c;
    data[0] = a;
    data[1] = b;
    left = x;
    right = y;
}
BinaryDimonTree::BinaryDimonTree()
{
    root = NULL;
}
istream &operator>>(istream &in,BinaryDimonTree &tree)
{
    int Nodenum;
    in >> Nodenum;
    int **record=new int* [Nodenum];
    for(int i=0;i<Nodenum;++i)
    {
        record[i]=new int[2];
    }
    for(int i=0;i<Nodenum;++i)
    {
        in >> record[i][0] >>record[i][1];
    }
    order(record,Nodenum);
    for(int i=0;i<Nodenum;++i)
    {
        tree.insert(tree.root,record[i][0],record[i][1],0);
    }
    for(int i=0;i<Nodenum;++i)
        delete[] record[i];
    delete[] record;
    return in;
}
void BinaryDimonTree::insert(TreeNode *&a,int x, int y,int height)
{
    int p[2];
    p[0]=x;
    p[1]=y;
    if(a==NULL)
    {
        a=new TreeNode(x,y,height+1,NULL,NULL);
    }
    else
    {
        if(p[1-a->height%2]<a->data[1-a->height%2])
            this->insert(a->left,x,y,a->height);
        else
            this->insert(a->right,x,y,a->height);
    }
}
TreeNode *BinaryDimonTree::find_nearest_node(int x,int y)
{
    long long int m=~0LLU>>1;
    TreeNode *res=NULL;
    recur_search(root,x,y,m,&res);
    return res;
}
void BinaryDimonTree::recur_search(TreeNode *cur, int x, int y, long long &min_distance, TreeNode **guess)
{
    if(cur==NULL)
        return;
    TreeNode *tmp=*guess;
    int m,n,p,i,j;
    int a[2];
    a[0] = x;
    a[1] = y;
    m=cur->data[0]-x;
    n=cur->data[1]-y;
    p=cur->data[1-(cur->height%2)]-a[1-(cur->height%2)];
    if(*guess!=NULL)
    {
        i=cur->data[0]-tmp->data[0];
        j=cur->data[1]-tmp->data[1];
    }
    if(m*m+n*n<min_distance||((m*m+n*n==min_distance)&&i<0)||((m*m+n*n==min_distance)&&i==0&&j<0))
    {
        min_distance = m*m+n*n;
        *guess = cur;
    }
    if(a[1-(cur->height%2)]<cur->data[1-(cur->height%2)])
    {
        recur_search(cur->left,x,y,min_distance,guess);
        if(p*p<min_distance)
            recur_search(cur->right,x,y,min_distance,guess);
    }
    else
    {
        recur_search(cur->right,x,y,min_distance,guess);
        if(p*p<min_distance)
            recur_search(cur->left,x,y,min_distance,guess);
    }

}
BinaryDimonTree::~BinaryDimonTree()
{
    clear(root);
}
void BinaryDimonTree::clear(TreeNode *a)
{
    if(a==NULL)
        return;
    clear(a->left);
    clear(a->right);
    delete a;
}
void order(int **p,int num)
{
    bool flag =true;
    int x,y;
    while (flag)
    {
        int m=0;
        flag=false;
        for(int i=m;i<num-1;++i)
            if(p[i][0]<p[i+1][0])
            {
                x=p[i][0];
                y=p[i][1];
                p[i][0]=p[i+1][0];
                p[i][1]=p[i+1][1];
                p[i+1][0]=x;
                p[i+1][1]=y;
                flag=true;
            }
        m=m+1;
    }
    x=p[0][0];
    y=p[0][1];
    p[0][0]=p[num/2][0];
    p[0][1]=p[num/2][1];
    p[num/2][0]=x;
    p[num/2][1]=y;
}
