#include <iostream>
#include <stack>
using namespace std;

template <class T>
class treeNode
{
  private:
    treeNode<T> *leftc;
    T info;
    int father;
    treeNode<T> *rightb;

  public:
    treeNode(const T &value)
    {
        info = value;
    }
    treeNode(treeNode<T> *lc, const T &value, int &f, treeNode<T> *rb) : leftc(lc), info(value), father(f), rightb(rb) {}
    treeNode() {}
    treeNode<T> *getLeftChird()
    {
        return this->leftc;
    }
    treeNode<T> *getRightBrother()
    {
        return this->rightb;
    }
};

template <class T>
class tree
{
  private:
    treeNode<T> *root;

  public:
    tree(int num) { root = new treeNode<T>[num]; }
};

template <class T>  
int countNode(tree<T> *t)       //采用深度优先周游左子右兄二叉树
{
    int count = 0;
    treeNode<T> *point = t->Root();
    stack<treeNode<T> *> aStack;
    aStack.push(NULL);
    while (point != NULL)
    {
        count++;
        if (point->getRightBrother() != NULL)
        {
            aStack.push(point->getRightBrother());
        }
        if (point->getLeftChird() != NULL)
        {
            point = point->getLeftChird();
        }
        else
        {
            point = aStack.top();
            aStack.pop();
        }
    }
}