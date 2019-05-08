/*
题目：
对于简单的四则运算表达式，请实现以下功能：

1.对于任意给出的前缀表达式（不含括号）、中缀表达式（可以带括号）或后缀表达式（不带括号），能够在计算机内部构造出一颗表达式二叉树，并且以图示显示出来（字符图或图形的形式）。
2.对于构造好的内部表达式二叉树，按照用户的要求，输出相应的前缀表达式（不带括号）、中缀表达式（可以带括号，但不允许冗余括号）、后缀表达式（不带括号）。
*/
#include <iostream>
#include <string>
using namespace std;

//链表结点
template <class T>
class Link
{
private:
    T data;
    Link<T> *next;

public:
    Link(const T value = NULL, Link<T> *nextValue = NULL) : data(value), next(nextValue) {}
    void setData(const T value) { this->data = value; }
    void setNext(const Link<T> *nextP) { this->next = nextP; }
    T getData() { return this->data; }
    Link<T> *getNext() { return this->next; }
};

//自定义栈
template <class T>
class Stack
{
private:
    Link<T> *topE; //指向栈顶元素
    int size;      //栈中存放元素数量

public:
    Stack() : topE(NULL), size(0) {}
    void clear()
    {
        while (!this->isEmpty())
        {
            T ch;
            this->pop(ch);
        }
    }
    bool push(const T item)
    {
        if (this->isEmpty())
        {
            topE = new Link<T>(item);
            size++;
            return true;
        }
        else
        {
            Link<T> *temp = topE;
            topE = new Link<T>(item, temp); //error:建个新的，指向之前那个
            size++;
            return true;
        }
        return false;
    }
    bool pop(T &item)
    {
        if (this->isEmpty())
        {
            cout << "栈空，不能出栈" << endl; //The stack is empty, pop failed
            return false;
        }
        item = topE->getData();
        Link<T> *temp = topE->getNext();
        delete topE;
        topE = temp;
        size--;
        return true;
    }
    bool top(T &item)
    {
        if (this->isEmpty())
        {
            return false;
        }
        item = topE->getData();
        return true;
    }
    bool isEmpty()
    {
        return topE == NULL || size == 0;
    }
};

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
        return false;
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

//中缀表达式转换为后缀表达式
string infixToPost(const string &infix)
{
    string postfix;
    Stack<char> stack;
    char ch, fixch;
    for (int i = 0; i < infix.length(); i++)
    {
        fixch = infix[i];
        stack.top(ch);
        if (fixch == ' ')
        {
            continue;
        }
        else if ((fixch >= 48 && fixch <= 57) || fixch == '.' || (fixch >= 65 && fixch <= 90) || (fixch >= 97 && fixch <= 122))
        {
            postfix += fixch;
        }
        else if (fixch == '(')
        {
            stack.push(infix[i]);
        }
        else if (fixch == ')')
        {
            if (stack.isEmpty())
            {
                cout << "括号不匹配，请重新输入表达式" << endl;
                stack.clear();
                return NULL;
            }
            else
            {
                stack.pop(ch);
                while (ch != '(')
                {
                    postfix += ' ';
                    postfix += ch;
                    if (!stack.pop(ch))
                    {
                        cout << "括号不匹配，请重新输入表达式" << endl;
                        stack.clear();
                        return NULL;
                    }
                }
            }
        }
        else if (fixch == '+' || fixch == '-')
        {
            postfix += ' ';
            while (!(stack.isEmpty()) && ch != '(')
            {
                stack.pop(ch);
                postfix += ch;
                postfix += ' ';
                stack.top(ch);
            }
            stack.push(fixch);
        }
        else if (fixch == '*' || fixch == '/')
        {
            postfix += ' ';
            while ((!stack.isEmpty()) && ch != '(' && ch != '+' && ch != '-')
            {
                stack.pop(ch);
                postfix += ch;
                postfix += ' ';
                stack.top(ch);
            }
            stack.push(fixch);
        }
        else
        {
            cout << "输入中有未知符号" << fixch << "，请检查后重新输入" << endl;
            return NULL;
        }
    }
    while (!stack.isEmpty())
    {
        postfix += ' ';
        stack.pop(ch);
        postfix += ch;
    }
    return postfix;
}
//后缀表达式转换为中缀表达式
string postfixToIn(const string &postfix)
{
    char fixch;
    Stack<string> operands;
    int pos = 0; //用pos记录操作数位置
    for (int i = 0; i <= postfix.length(); i++)
    {
        fixch = postfix[i];
        if (fixch == ' ' || fixch == '\0')
        {
            if (postfix[i - 1] >= 48 && postfix[i - 1] <= 57 || (postfix[i - 1] >= 65 && postfix[i - 1] <= 90) || (postfix[i - 1] >= 97 && postfix[i - 1] <= 122))
            {
                string str = postfix.substr(pos, i - pos);
                operands.push(str);
                pos = i + 1;
            }
            else if (postfix[i - 1] == '+' || postfix[i - 1] == '-')
            {
                string op1, op2, temp;
                if (operands.isEmpty())
                {
                    cout << "后缀转中缀时栈空" << endl;
                    return NULL;
                }
                operands.pop(op1);
                if (operands.isEmpty())
                {
                    cout << "后缀转中缀时栈空" << endl;
                    return NULL;
                }
                operands.pop(op2);
                temp += op2 + postfix[i - 1] + op1;
                operands.push(temp);
                pos = i + 1;
            }
            else if (postfix[i - 1] == '*' || postfix[i - 1] == '/')
            {
                string op1, op2, temp;
                if (operands.isEmpty())
                {
                    cout << "后缀转中缀时栈空" << endl;
                    return NULL;
                }
                operands.pop(op1);
                if (op1.find("+") != -1 || op1.find("-") != -1)
                {
                    op1 += ")";
                    op1.insert(0, "(");
                }
                if (operands.isEmpty())
                {
                    cout << "后缀转中缀时栈空" << endl;
                    return NULL;
                }
                operands.pop(op2);
                if (op2.find("+") != -1 || op2.find("-") != -1)
                {
                    op2 += ")";
                    op2.insert(0, "(");
                }
                temp += op2 + postfix[i - 1] + op1;
                operands.push(temp);
                pos = i + 1;
            }
            else
            {
                if (i == postfix.length())
                {
                    continue;
                }
                cout << "表达式中含有未知符号" << postfix[i - 1] << "，请检查后输入" << endl;
            }
        } //- + 1 * + 2 3 4 5
    }
    string infix;
    if (operands.isEmpty())
    {
        cout << "后缀转中缀时栈空" << endl;
        return NULL;
    }
    operands.pop(infix);
    return infix;
}
//中缀表达式转换为前缀表达式
//(a+b)*(c+d)转换为* + a b + c d
string infixToPre(const string &infix)
{
    string temp;
    Stack<char> stack;
    char ch, fixch;
    for (int i = infix.length() - 1; i > -1; i--)
    {
        fixch = infix[i];
        stack.top(ch);
        if (fixch == ' ')
        {
            continue;
        }
        else if ((fixch >= 48 && fixch <= 57) || fixch == '.' || (fixch >= 65 && fixch <= 90) || (fixch >= 97 && fixch <= 122))
        {
            temp += fixch;
        }
        else if (fixch == ')')
        {
            stack.push(infix[i]);
        }
        else if (fixch == '(')
        {
            if (stack.isEmpty())
            {
                cout << "括号不匹配，请重新输入表达式" << endl;
                stack.clear();
                return NULL;
            }
            else
            {
                stack.pop(ch);
                while (ch != ')')
                {
                    temp += ' ';
                    temp += ch;
                    if (!stack.pop(ch))
                    {
                        cout << "括号不匹配，请重新输入表达式" << endl;
                        stack.clear();
                        return NULL;
                    }
                }
            }
        }
        else if (fixch == '+' || fixch == '-')
        {
            temp += ' ';
            while (!(stack.isEmpty()) && (ch == '*' || ch == '/'))
            {
                stack.pop(ch);
                temp += ch;
                temp += ' ';
                stack.top(ch);
            }
            stack.push(fixch);
        }
        else if (fixch == '*' || fixch == '/')
        {
            temp += ' ';
            stack.push(fixch);
        }
        else
        {
            cout << "输入中有未知符号，请检查后重新输入" << endl;
            return NULL;
        }
    }
    while (!stack.isEmpty())
    {
        temp += ' ';
        stack.pop(ch);
        temp += ch;
    }
    string prefix;
    for (int i = temp.length() - 1; i > -1; i--)
    {
        prefix += temp[i];
    }
    return prefix;
}
//前缀表达式转换为中缀表达式
string prefixToIn(const string &prefix)
{
    char fixch;
    Stack<string> operands;
    int pos = prefix.length(); //用pos记录操作数位置
    for (int i = prefix.length() - 1; i >= -1; i--)
    {
        if (i >= 0)
            fixch = prefix[i];
        if (fixch == ' ' || fixch == '\0' || i == -1)
        {
            if (prefix[i + 1] >= 48 && prefix[i + 1] <= 57 || (prefix[i + 1] >= 65 && prefix[i + 1] <= 90) || (prefix[i + 1] >= 97 && prefix[i + 1] <= 122))
            {
                string str = prefix.substr(i + 1, pos - i);
                operands.push(str);
                pos = i - 1;
            }
            else if (prefix[i + 1] == '+' || prefix[i + 1] == '-')
            {
                string op1, op2, temp;
                if (operands.isEmpty())
                {
                    cout << "前缀转中缀时栈空" << endl;
                    return NULL;
                }
                operands.pop(op1);
                if (operands.isEmpty())
                {
                    cout << "前缀转中缀时栈空" << endl;
                    return NULL;
                }
                operands.pop(op2);
                temp += op2 + prefix[i + 1] + op1;
                operands.push(temp);
                pos = i - 1;
            }
            else if (prefix[i + 1] == '*' || prefix[i + 1] == '/')
            {
                string op1, op2, temp;
                if (operands.isEmpty())
                {
                    cout << "前缀转中缀时栈空" << endl;
                    return NULL;
                }
                operands.pop(op1);
                if (op1.find("+") != -1 || op1.find("-") != -1)
                {
                    op1 += "(";
                    op1.insert(0, ")");
                }
                if (operands.isEmpty())
                {
                    cout << "前缀转中缀时栈空" << endl;
                    return NULL;
                }
                operands.pop(op2);
                if (op2.find("+") != -1 || op2.find("-") != -1)
                {
                    op2 += "(";
                    op2.insert(0, ")");
                }
                temp += op2 + prefix[i + 1] + op1;
                operands.push(temp);
                pos = i - 1;
            }
            else
            {
                cout << "表达式中含有未知符号，请检查后输入" << endl;
            }
        }
    }
    string temp;
    if (operands.isEmpty())
    {
        cout << "前缀转中缀时栈空" << endl;
        return NULL;
    }
    operands.pop(temp);
    string infix;
    for (int i = temp.length() - 1; i > -1; i--)
    {
        infix += temp[i];
    }
    return infix;
}

//中(a+b*(c-d))-e/f -> 后a b c d - * + e f / - -> 前 - + a * b - c d / e f
//后缀表达式转换为二叉树
BinaryTree<string> expToTree(string expression)
{
    /**
        1.扫描表达式
        2.遇到操作数，封装为一个二叉树结点入栈
        3.遇到操作符，连续从栈中取出两个结点封装为二叉树结点入栈（第一个pop出的结点作为右孩子）
        4.扫描结束后将栈中最后一个结点作为二叉树的根
     */
    char fixch;
    Stack<BinaryTreeNode<string> *> operands;
    int pos = 0; //用pos记录操作数位置
    for (int i = 0; i <= expression.length(); i++)
    {
        fixch = expression[i];
        if (fixch == ' ' || fixch == '\0')
        {
            if ((expression[i - 1] >= 48 && expression[i - 1] <= 57) || (expression[i - 1] >= 65 && expression[i - 1] <= 90) || (expression[i - 1] >= 97 && expression[i - 1] <= 122))
            {
                BinaryTreeNode<string> *node = new BinaryTreeNode<string>(expression.substr(pos, i - pos));
                // cout << expression.substr(pos, i - pos) << "入栈" << endl;
                operands.push(node);
                pos = i + 1;
            }
            else if (expression[i - 1] == '+' || expression[i - 1] == '-' || expression[i - 1] == '*' || expression[i - 1] == '/')
            {
                BinaryTreeNode<string> *node = new BinaryTreeNode<string>(expression.substr(i - 1, 1));
                BinaryTreeNode<string> *op1, *op2;
                if (operands.isEmpty())
                {
                    cout << i << "栈空" << endl;
                }
                operands.pop(op1);
                node->setRightChild(op1);
                if (operands.isEmpty())
                {
                    cout << i << "栈空" << endl;
                }
                operands.pop(op2);
                node->setLeftChild(op2);
                operands.push(node);
                pos = i + 1;
            }
            else
            {
                cout << "表达式中含有未知符号，请检查后输入" << endl;
            }
        }
    }
    if (!operands.isEmpty())
    {
        BinaryTreeNode<string> *root;
        operands.pop(root);
        BinaryTree<string> tree(root);
        return tree;
    }
    else
    {
        cout << "不知道哪里栈空了，检查一下吧" << endl;
        return NULL;
    }
}

//二叉树的表示
template <class T>
void showBinaryTree(BinaryTreeNode<T> *root, int height)
{
    // cout << "I'm testing" << height << endl;
    if (root == NULL)
    {
        return;
    }
    // cout << "I'm testing r" << height << endl;
    showBinaryTree(root->rightChild(), height + 1);
    for (int i = 0; i < height; i++)
    {
        cout << " \t";
    }
    cout << root->value() << endl;
    // cout << "I'm testing l" << height << endl;
    showBinaryTree(root->leftChild(), height + 1);
}

//二叉树转后缀表达式(后序周游)
template <class T>
struct stackEle
{
    BinaryTreeNode<T> *point;
    bool tag; //true 从右子树返回  false 从左子树返回
};

template <class T>
string treeToPostfix(BinaryTree<T> *tree)
{
    string postfix;
    if (tree->isEmpty())
    {
        cout << "二叉树为空" << endl;
        return NULL;
    }
    Stack<stackEle<T>> node;
    BinaryTreeNode<T> *point = tree->Root();
    stackEle<T> ele;
    while (!node.isEmpty() || point)
    {
        while (point)
        {
            ele.point = point;
            ele.tag = false;
            node.push(ele);
            point = point->leftChild();
        }
        if (node.isEmpty())
        {
            cout << "栈空，看你写的好算法" << endl;
        }
        node.pop(ele);
        point = ele.point;
        if (!ele.tag)
        {
            ele.tag = true;
            node.push(ele);
            point = point->rightChild();
        }
        else
        {
            postfix += point->value() + " ";
            point = NULL;
        }
    }
    return postfix;
}

int main()
{
    while (1)
    {
        cout << "请选择输入：" << endl;
        cout << "1： 中缀表达式" << endl;
        cout << "2： 前缀表达式" << endl;
        cout << "3： 后缀表达式" << endl;
        cout << "其他： 退出" << endl;
        char choice;
        cin >> choice;
        cin.clear();
        cin.ignore(1024,'\n');
        BinaryTree<string> tree;
        switch (choice)
        {
        case '1':
        {
            cout << "请输入中缀表达式:" << endl;
            char buff[1024];
            cin.getline(buff, 100, '\n');
            string infix(buff);
            string postfix = infixToPost(infix);
            tree = expToTree(postfix);
            cout << "转换后的二叉树如下：" << endl;
            showBinaryTree(tree.Root(), 0);
            break;
        }
        case '2':
        {
            cout << "请输入前缀表达式（请用空格分隔）:" << endl;
            char buff[1024];
            cin.getline(buff, 100, '\n');
            string prefix(buff);
            string postfix = infixToPost(prefixToIn(prefix));
            tree = expToTree(postfix);
            cout << "转换后的二叉树如下：" << endl;
            showBinaryTree(tree.Root(), 0);
            break;
        }
        case '3':
        {
            cout << "请输入后缀表达式（请用空格分隔）:" << endl;
            char buff[1024];
            cin.getline(buff, 100, '\n');
            string postfix(buff);
            tree = expToTree(postfix);
            cout << "转换后的二叉树如下：" << endl;
            showBinaryTree(tree.Root(), 0);
            break;
        }
        default:
            return -1;
        }
        while (1)
        {
            cout << "请选择二叉树输出：" << endl;
            cout << "1： 中缀表达式" << endl;
            cout << "2： 前缀表达式" << endl;
            cout << "3： 后缀表达式" << endl;
            cout << "其他： 退回" << endl;
            cin >> choice;
            cin.clear();
            cin.ignore(1024,'\n');
            string postfix = treeToPostfix(&tree);
            switch (choice)
            {
            case '1':
                cout << "二叉树生成的中缀表达式为：" << postfixToIn(postfix) << endl;
                break;
            case '2':
                cout << "二叉树生成的前缀表达式为：" << infixToPre(postfixToIn(postfix)) << endl;
                break;
            case '3':
                cout << "二叉树生成的后缀表达式为：" << postfix << endl;
                break;
            default:
                break;
            }
            if (choice != '1' && choice != '2' && choice != '3')
                break;
        }
    }
    return 0;
}