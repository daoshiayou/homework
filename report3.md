
# <center>数据结构第三次上机

<center>一位不愿意透露姓名的陈雎</center>

## 题目：

表达式可以用二叉树来表示。对于简单的四则运算表达式，请实现以下功能：

1. 对于任意给出的前缀表达式（不含括号）、中缀表达式（可以带括号）或后缀表达式（不带括号），能够在计算机内部构造出一棵表达式二叉树，并且以图示显示出来（字符图或图形的形式）。  
2. 对于构造好的内部表达式二叉树，按照用户的要求，输出相应的前缀表达式（不带括号）、中缀表达式（可以带括号，但不允许冗余括号）、后缀表达式（不带括号）。

## 需求分析：

* __输入形式__：从键盘输入表达式字符串。

* __输入值的范围__：数字、运算符的字符。

* __输出形式__：在控制台上显示即可。

* __程序功能__：能将输入的各种表达式转换为表达式二叉树并显示，还可以将构造好的树转换回各种表达式。

* __测试数据__：  
    _表达式二叉树转换_：  
    有效输入：

    >1  
    >23.678+(45.8*432)/(5.88+6.95-7.89)

    正确输出：  
    >转换后的二叉树如下：
    >
    >                            7.89
    >                    -
    >                                    6.95
    >                            +
    >                                    5.88
    >            /
    >                            432
    >                    *
    >                            45.8
    >        +
    >            23.678
    >请选择二叉树输出：  
    >1： 中缀表达式  
    >2： 前缀表达式  
    >3： 后缀表达式  
    >其他： 退回  

    无效输入：giuagfss=dfsfsudjlawr-=  
    正确输出：退出程序

    _表达式二叉树转换_：
    有效输入：

    >1

    正确输出：

    >二叉树生成的前缀表达式为：+ 23.678 / * 45.8 432 - + 5.88 6.95 7.89  
    >请选择二叉树输出：  
    >1： 中缀表达式  
    >2： 前缀表达式  
    >3： 后缀表达式  
    >其他： 退回

    无效输入：giuagfss=dfsfsudjlawr-=  
    正确输出：

    >请选择输入：  
    >1： 中缀表达式  
    >2： 前缀表达式  
    >3： 后缀表达式  
    >其他： 退出

## 概要设计：

__ADT定义__：  
链表结点：

    template <class T>
    class Link
    {
    private:
        T data;
        Link<T> *next;

    public:
        Link(const T value = NULL, Link<T> *nextValue = NULL);
        void setData(const T value) ;
        void setNext(const Link<T> *nextP) ;
        T getData() ;
        Link<T> *getNext() ;
    };

自定义栈：

    template <class T>
    class Stack
    {
    private:
        Link<T> *topE; //指向栈顶元素
        int size;      //栈中存放元素数量

    public:
        Stack() ;
        void clear() ;
        bool push(const T item) ;
        bool pop(T &item) ;
        bool top(T &item) ;
    };

二叉树结点：

    template <class T>
    class BinaryTreeNode
    {
        friend class BinaryTree<T>;

    private:
        T info;
        BinaryTreeNode<T> *lChild;
        BinaryTreeNode<T> *rChild;

    public:
        BinaryTreeNode();
        BinaryTreeNode(const T ele)；
        BinaryTreeNode(const T ele, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r)；

        T value()；
        BinaryTreeNode<T> *leftChild()；//返回左孩子
        BinaryTreeNode<T> *rightChild()；//返回右孩子

        void setLeftChild(BinaryTreeNode<T> *lc)；
        void setRightChild(BinaryTreeNode<T> *rc);
        void setValue(const T val);
        bool isLeaf();//判断结点是不是叶子
    };

二叉树：

    template <class T>
    class BinaryTree
    {
    private:
        BinaryTreeNode<T> *root;

    public:
        BinaryTree();
        BinaryTree(BinaryTreeNode<T> *node);
        bool isEmpty();
        BinaryTreeNode<T> *Root();
    };

中缀表达式转换为后缀表达式：

    string infixToP(const string &infix);

后缀表达式转换为中缀表达式

    string postfixToIn(const string &postfix)

中缀表达式转换为前缀表达式

    string infixToPre(const string &infix)

前缀表达式转换为中缀表达式

    string prefixToIn(const string &prefix)

后缀表达式转换为二叉树

    BinaryTree<string> expToTree(string expression)

二叉树的表示

    template <class T>
    void showBinaryTree(BinaryTreeNode<T> *root, int height)

二叉树转后缀表达式(后序周游)

    template <class T>
    struct stackEle
    {
        BinaryTreeNode<T> *point;
        bool tag; //true 从右子树返回  false 从左子树返回
    };
    template <class T>
    string treeToPostfix(BinaryTree<T> *tree)

主程序流程：  
提示用户输入->获取用户输入的选项->获取用户输入的表达式->调用对应转换函数将表达式转换为后缀表达式->用后缀表达式构造表达式二叉树->显示构造好的表达式二叉树->获取用户输入的选项->调用对应转换函数将转换好的后缀表达式转换为对应表达式->输出转换后的对应表达式  
调用关系：  
![调用关系](https://github.com/daoshiayou/data-structures-and-algorithms-homework/blob/master/source/3模块调用关系.PNG)

## 详细设计

__ADT定义__：  
链表结点：  

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

自定义栈：

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

二叉树结点：

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

二叉树：

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

中缀表达式转换为后缀表达式：

    string infixToP(const string &infix)
    {
        string postfix;
        Stack<char> stack;
        char ch, fixch;
        for (int i = 0; i < infix.length(); i++)
        {
            fixch = infix[i];
            stack.top(ch);
            if ((fixch >= 48 && fixch <= 57) || fixch == '.' || fixch == ' ')
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
                cout << "输入中有未知符号，请检查后重新输入" << endl;
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

算法描述：

1. 为输出的后缀表达式字符串分配空间，新建一个空的操作符栈，从左到右扫描传入的中缀表达式字符串。
2. A、 遇到数字或者小数点，直接将其加入要输出的后缀表达式的末尾。  
   B、遇到左括号，直接入栈。  
   C、遇到右括号，连续出栈并添加其和一个空格到后缀表达式的末尾以区分操作符和操作数，直到将一个左括号出栈；若栈空，则提示括号不匹配，函数返回。  
   D、遇到加号或者减号，先添加一个空格到后缀表达式末尾以区分操作符和操作数，判断栈顶元素优先级是否低于加减  

    >(1)若栈非空且栈顶优先级不低于加减，连续出栈并添加其和一个空格到后缀表达式的末尾。  
    >(2)入栈

   E、遇到乘号或者除号，先添加一个空格到后缀表达式末尾以区分操作符和操作数，判断栈顶元素优先级是否低于乘除

    >(1)若栈非空且栈顶优先级不低于乘除，连续出栈并添加其和一个空格到后缀表达式的末尾。
    >(2)入栈。

    F、其他情况，提示输入中有未知符号，函数返回。  
3. 将空格栈内储存的操作符连续加入后缀表达式末尾直到栈空。  
4. 返回后缀表达式。

后缀表达式转换为中缀表达式

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

算法描述：从左到右扫描，pos记录操作数的位置。

1. 遇到空格或\0，判断前头是不是操作数  
    A. 操作数，入栈  
    B. 运算符
    >(1)运算符是加减，从栈中取出两个操作数连接表达式，重新入栈
    >(2)运算符是乘除，从栈中取出两个操作数连接表达式。如果操作数中含加减的运算符，再在连接后的表达式左右加上括号，入栈
2. pos更新
3. 扫描结束后，栈中剩余的最后一个元素即为转换好的中缀表达式

中缀表达式转换为前缀表达式

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

算法描述：

1. 新建一个临时字符串变量，新建一个空的操作符栈，从右到左扫描传入的中缀表达式字符串。
2. A、 遇到数字或者小数点，直接将其加入临时字符串的末尾。  
   B、遇到右括号，直接入栈。  
   C、遇到左括号，连续出栈并添加其和一个空格到临时字符串的末尾以区分操作符和操作数，直到将一个右括号出栈；若栈空，则提示括号不匹配，函数返回。  
   D、遇到加号或者减号，先添加一个空格到后缀表达式末尾以区分操作符和操作数，判断栈顶元素优先级是否高于加减  

    >(1)若栈非空且栈顶优先级不高于加减，连续出栈并添加其和一个空格到后缀表达式的末尾。  
    >(2)入栈

   E、遇到乘号或者除号，先添加一个空格到临时字符串中，然后直接入栈  
   F、其他情况，提示输入中有未知符号，函数返回。  
3. 将空格栈内储存的操作符连续加入临时字符串末尾直到栈空。  
4. 将临时字符串逆序输出，得到前缀表达式
5. 返回前缀表达式。

前缀表达式转换为中缀表达式

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

算法描述：从右到左扫描，pos记录操作数的位置。

1. 遇到空格或\0，判断前头是不是操作数  
    A. 操作数，入栈  
    B. 运算符
    >(1)运算符是加减，从栈中取出两个操作数连接表达式，重新入栈
    >(2)运算符是乘除，从栈中取出两个操作数连接表达式。如果操作数中含加减的运算符，再在连接后的表达式左右加上括号，入栈
2. pos更新
3. 扫描结束后，栈中剩余的最后一个元素用临时字符串存储
4. 将临时字符串逆序输出，得到转换好的中缀表达式
5. 输出转换好的中缀表达式

后缀表达式转换为二叉树

    BinaryTree<string> expToTree(string expression)
    {
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

算法描述：

1. 扫描表达式
2. 遇到操作数，封装为一个二叉树结点入栈
3. 遇到操作符，连续从栈中取出两个结点封装为二叉树结点入栈（第一个pop出的结点作为右孩子）
4. 扫描结束后将栈中最后一个结点作为二叉树的根

二叉树的表示

    template <class T>
    void showBinaryTree(BinaryTreeNode<T> *root, int height)
    {
        if (root == NULL)
        {
            return;
        }
        showBinaryTree(root->rightChild(), height + 1);
        for (int i = 0; i < height; i++)
        {
            cout << " \t";
        }
        cout << root->value() << endl;
        showBinaryTree(root->leftChild(), height + 1);
    }

算法描述：横向输出二叉树的结点们，height记录层数。

1. 判断传入的结点是否有右孩子。有，则传入右孩子和+1层数，调用自己。
2. 输出显示传入结点。
3. 判断传入的结点是否有左孩子。有，则传入左孩子和+1层数，调用自己。

二叉树转后缀表达式

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
                cout << "栈空" << endl;
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

算法描述：与二叉树后序周游相同，将访问结点改为在欲输出的后缀表达式末尾添加空格与结点的值即可。

1. 新建用于后序周游的栈的结点
2. 判断传入的二叉树是否为空，为空则直接返回
3. 新建后缀表达式字符串，新建一个指针一路下沉并将结点入栈，直到指向NULL
4. 将结点出栈，判断该结点是从左子树回来还是从右子树回来
    >(1)从左子树回来，将标志位改为从右子树回来，指针指向该结点的右孩子，重复3、4
    >(2)从右子树回来，在欲输出的后缀表达式末尾添加空格与结点的值，重复4，直到栈空
5. 输出后缀表达式

函数调用关系：  
![函数调用关系](https://github.com/daoshiayou/data-structures-and-algorithms-homework/blob/master/source/3函数调用关系.PNG)

## 调试分析

__对设计与实现的分析讨论__：  
一开始就想要用上上机2完成的算法，然后想法就偏到各种表达式的转换上面了。表达式转换为树和树的图形显示参考了网上的实现方式。树的图形显示还有更美观的形式，但最简单的应该就是横向输出了

__调试中遇到的问题__：  
前缀表达式转换错误、出现栈空。  
__解决方式__：  
检查代码，在不同位置插入测试输出，修改逻辑错误。

## 算法分析

__中缀表达式转化为后缀表达式__：  
_时间复杂度_：O(n)  
_空间复杂度_：O(n)  
__后缀表达式转化为中缀表达式__：  
_时间复杂度_：O(n)  
_空间复杂度_：O(n)  
__中缀表达式转化为前缀表达式__：  
_时间复杂度_：O(n)  
_空间复杂度_：O(n)  
__前缀表达式转化为中缀表达式__：  
_时间复杂度_：O(n)  
_空间复杂度_：O(n)  
__后缀表达式转换为二叉树__：  
_时间复杂度_：O(n)  
_空间复杂度_：O(n)  
__二叉树的表示__：  
_时间复杂度_：O(log n)  
_空间复杂度_：O(1)  
__二叉树转后缀表达式__：  
_时间复杂度_：O(log n)  
_空间复杂度_：O(n)  

## 用户使用说明

* 根据提示输入选项，回车确定。
* 支持的运算符有：加减乘除
* 操作数可以为浮点小数或者英文字母
* 当表达式错误（出现未知符号或括号不匹配）时会报错并中止程序

## 测试结果

![输入1](https://github.com/daoshiayou/data-structures-and-algorithms-homework/blob/master/source/3测试1.PNG)
![输出1](https://github.com/daoshiayou/data-structures-and-algorithms-homework/blob/master/source/3测试2.PNG)  
![输入2](https://github.com/daoshiayou/data-structures-and-algorithms-homework/blob/master/source/3测试3.PNG)
![输出2](https://github.com/daoshiayou/data-structures-and-algorithms-homework/blob/master/source/3测试4.PNG)

## 源程序

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

    //后缀表达式转换为二叉树
    BinaryTree<string> expToTree(string expression)
    {
    //后缀表达式转换为二叉树
    BinaryTree<string> expToTree(string expression)
    {
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
        if (root == NULL)
        {
            return;
        }
        showBinaryTree(root->rightChild(), height + 1);
        for (int i = 0; i < height; i++)
        {
            cout << " \t";
        }
        cout << root->value() << endl;
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
            cin.sync();
            BinaryTree<string> tree;
            switch (choice)
            {
            case '1':
            {
                cout << "请输入中缀表达式:" << endl;
                char buff[1024];
                cin.getline(buff, 100, '\n');
                cin.clear();
                cin.sync();
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
                cin.clear();
                cin.sync();
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
                cin.clear();
                cin.sync();
                string postfix(buff);
                tree = expToTree(postfix);
                cout << "转换后的二叉树如下：" << endl;
                showBinaryTree(tree.Root(), 0);
                break;
            }
            default:
                return 0;
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
                cin.sync();
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
