/**P132 习题6
 * 写一个递归函数计算二叉树的高度（只有一个根结点的二叉树高度为1）
 */
int getBTHigh(BinaryTree tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    return getBTHigh(tree->left) > getBTHigh(tree->right) ? getBTHigh(tree->left) + 1 : getBTHigh(tree->right) + 1;
}

/**P132 习题14
 * 编写一个递归函数search()，传入参数为一棵二叉树和一个值K，如果值K出现在书中则返回true，否则返回false
 */
template <class T>
bool search(BinaryTreeNode<T> tree, const T k)
{
    if (tree == NULL)
    {
        return false;
    }
    if (r->value() == k)
    {
        return true;
    }
    else
    {
        return search(tree->leftChild(), k) || search(tree->rightChild(), k);
    }
}