#ifndef C_BINARYDIMEN_TREE_H
#define C_BINARYDIMEN_TREE_H

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

void order(int **p,int num);

class TreeNode
{
  friend ostream &operator<<(ostream &out, const TreeNode &b);
  friend class BinaryTree;
  friend class BinaryDimonTree;

private:
  /* data */
  int data[2];
  int height;
  TreeNode *left;
  TreeNode *right;
public:
  /* methods */
  TreeNode(int x,int y,int height,TreeNode* left,TreeNode* right);
  int getX();  /* DO NOT CHANGE */
  int getY();  /* DO NOT CHANGE */
  ~TreeNode(){}; /* DO NOT CHANGE */
};

class BinaryDimonTree
{
friend istream &operator>>(istream &in, BinaryDimonTree &tree);  /* DO NOT CHANGE */
private:
  /* data */
  TreeNode *root;
public:
  /* methods */
  BinaryDimonTree();          /* DO NOT CHANGE */
  TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */
  void insert(TreeNode *&a,int x,int y,int height);
  void recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode **guess);
  void clear(TreeNode *a);
  ~BinaryDimonTree();

};

#endif //C_BINARYDIMEN_TREE_H
