
#include <iostream>

using namespace std;

template <class T>
class BinaryTree;

template <class T>
class BinaryTreeNode
{
	friend class BinaryTree<T>;

  private:
	T info;
	BinaryTreeNode<T> *lChild;
	BinaryTreeNode<T> *rChild;

  public:
	BinaryTreeNode() : lChild(NULL), rChild(NULL){};
	BinaryTreeNode(const T ele) : info(ele), lChild(NULL), rChild(NULL) {}
	BinaryTreeNode(const T ele, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : info(ele), lChild(l), rChild(r) {}

	T value() { return info; }
	BinaryTreeNode<T> *leftChild() { return lChild; }
	BinaryTreeNode<T> *rightChild() { return rChild; }

	void setLeftChild(BinaryTreeNode<T> *lc) { this->lChild = lc; }
	void setRightChild(BinaryTreeNode<T> *rc) { this->rChild = rc; }
	void setValue(const T val) { this->info = val; }
	bool isLeaf()
	{
		if (lChild == NULL && rChild == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

template <class T>
class BinaryTree
{
  private:
	BinaryTreeNode<T> *root;

  public:
	BinaryTree() { root = NULL; }
	BinaryTree(BinaryTreeNode<T> *node)
	{
		root = node;
	}
	bool isEmpty()
	{
		return root == NULL;
	}
	BinaryTreeNode<T> *Root() { return root; }
};

//写一个递归函数计算二叉树的高度
template <class T>
int heightOfTree(BinaryTreeNode<T> *root)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->leftChild() == NULL && root->rightChild() == NULL)
	{
		return 1;
	}
	return heightOfTree(root->leftChild()) > heightOfTree(root->rightChild()) ? heightOfTree(root->leftChild()) + 1 : heightOfTree(root->rightChild()) + 1;
}

//递归search
template <class T>
bool search(BinaryTreeNode<T> *root, const T &key)
{
	if (root != NULL)
	{
		if (root->value() == key)
		{
			return true;
		}
		return search(root->leftChild()) || search(root->rightChild());
	}
	return false;
}

int main()
{
	BinaryTreeNode<int> *root = new BinaryTreeNode<int>(0, new BinaryTreeNode<int>(1, new BinaryTreeNode<int>(3), new BinaryTreeNode<int>(4)), new BinaryTreeNode<int>(2, NULL, new BinaryTreeNode<int>(5, new BinaryTreeNode<int>(6), NULL)));
	cout << heightOfTree(root) << endl;
	cout << search(new BinaryTree<int>(root), 7) << endl;
}