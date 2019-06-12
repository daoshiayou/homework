/**P159 习题6
 * 编写一个函数，以一棵树为输入，返回树的结点数目
 */
//其实就是树的周游
template <class T>
int preorder(TreeNode<T> *root)
{
    int count = 0;
    stack<TreeNode<T> *> aStack;
    aStack.push(NULL);      //监视哨
    while (root != NULL)
    {
        count++;
        if (root->rightChild())
        {
            aStack.push(root->rightChild());
        }
        if (root->leftChild())
        {
            root = root->leftChild();
        }
        else
        {
            aStack.pop(root);
        }
    }
    return count;
}