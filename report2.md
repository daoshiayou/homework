
# <center>数据结构第二次上机

<center>一位不愿意透露姓名的陈雎</center>

## 题目：

实现表达式求值算法，要求分2步实现。

1.中缀表达式变换为后缀  
2.后缀表达式求值  

## 需求分析：

* __输入形式__：从键盘输入表达式字符串。

* __输入值的范围__：数字、运算符的字符。

* __输出形式__：在控制台上显示即可。

* __程序功能__：中缀表达式转换为后缀表达式求值。

* __测试数据__：  
有效输入：23.678+(45.8*432)/(5.88+6.95-7.89)  
正确输出：  
输出的后缀表达式为：  
23.678 45.8 432 * 5.88 6.95 + 7.89 - / +  
求值结果为：  
4028.86  
无效输入：giuagfss=dfsfsudjlawr-=  
正确输出：输入中有未知符号，请检查后重新输入  

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

中缀表达式转换为后缀表达式：

    string infixToP(const string &infix);

后缀表达式求值：

    double postfixCal(const string &postfix);

主程序流程：  
提示用户输入->获取用户输入的中缀表达式->调用中缀表达式转换函数->显示转换后的后缀表达式->用转换后的后缀表达式调用后缀表达式求值函数->显示求值结果  
调用关系：  
![调用关系](https://github.com/daoshiayou/data-structures-and-algorithms-homework/blob/master/source/2模块调用关系.png)

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

后缀表达式求值：

    double postfixCal(const string &postfix)
    {
        Stack<double> stack;
        for (int i = 0; i <= postfix.length(); i++)
        {
            static char fixch;
            static int pos = 0;
            fixch = postfix[i];
            if (fixch == ' ' || fixch == '\0')
            {
                if (postfix[i - 1] >= 48 && postfix[i - 1] <= 57)
                {
                    const char *str = postfix.substr(pos, i - pos).c_str();
                    double op = atof(str);
                    stack.push(op);
                    pos = i;
                }
                else if (postfix[i - 1] == '+' || postfix[i - 1] == '-' || postfix[i - 1] == '*' || postfix[i - 1] == '/')
                {
                    double op1, op2;
                    if (!stack.isEmpty())
                    {
                        stack.pop(op1);
                    }
                    if (!stack.isEmpty())
                    {
                        stack.pop(op2);
                    }
                    switch (postfix[i - 1])
                    {
                    case '+':
                        stack.push(op2 + op1);
                        break;
                    case '-':
                        stack.push(op2 - op1);
                        break;
                    case '*':
                        stack.push(op2 * op1);
                        break;
                    case '/':
                        stack.push(op2 / op1);
                        break;
                        break;

                    default:
                        break;
                    }
                    pos = i;
                }
            }
        }
        double result;
        if (!stack.isEmpty())
        {
            stack.pop(result);
        }
        return result;
    }

算法描述：从左到右扫描，pos记录空格的位置。

1. 遇到空格或\0，判断前头是不是数字

>(1)数字，入栈  
>(2)运算符，从栈中取出两个操作数，运算后将结果入栈

2. pos更新

函数调用关系：  
![函数调用关系](https://github.com/daoshiayou/data-structures-and-algorithms-homework/blob/master/source/2函数调用关系.PNG)

## 调试分析

__对设计与实现的分析讨论__：  
看到题目的时候就想好了中缀表达式转换后缀时的输入输出形式是字符串，但不知道后续后缀表达式计算时，如何使输入的字符串数字转换为浮点数。查找了相关资料后决定用空格以区分数字和运算符，记录字符串长度后利用C语言的atof函数转为为浮点数计算，不知道还有没有更好的办法。

__调试中遇到的问题__：  
因为动手前思考了很久调试时没有什么异常，令人纠结的就是函数循环入栈出栈的途中，添加空格的位置总是出错，使得输出的后缀表达式不美观的同时影响了后续的计算。  
__解决方式__：  
反复尝试将语句添加在循环不同的位置上。

## 算法分析

__前缀表达式转化为后缀表达式__：  
_时间复杂度_：O(n)  
_空间复杂度_：O(n)  
__后缀表达式计算__：  
_时间复杂度_：O(n)  
_空间复杂度_：O(n)  

## 用户使用说明

* 根据提示输入表达式，请不用使用空格。
* 支持的运算有：浮点加减和浮点乘除
* 当表达式错误（出现未知符号或括号不匹配）时会报错中止程序

## 测试结果

![输入](https://github.com/daoshiayou/data-structures-and-algorithms-homework/blob/master/source/2测试1.PNG)
![输出](https://github.com/daoshiayou/data-structures-and-algorithms-homework/blob/master/source/2测试2.PNG)

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

    //中缀表达式转换为后缀表达式
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

    //后缀表达式求值
    double postfixCal(const string &postfix)
    {
        Stack<double> stack;
        for (int i = 0; i <= postfix.length(); i++)
        {
            static char fixch;
            static int pos = 0;
            fixch = postfix[i];
            /**
            *  从左到右扫描，pos记录空格的位置
            *      1.遇到空格或\0，判断前头是不是数字
            *          数字，入栈
            *          运算符，从栈中取出两个操作数，运算后将结果入栈
            *      2.pos更新
            * */
            if (fixch == ' ' || fixch == '\0')
            {
                if (postfix[i - 1] >= 48 && postfix[i - 1] <= 57)
                {
                    const char *str = postfix.substr(pos, i - pos).c_str();
                    double op = atof(str);
                    stack.push(op);
                    pos = i;
                }
                else if (postfix[i - 1] == '+' || postfix[i - 1] == '-' || postfix[i - 1] == '*' || postfix[i - 1] == '/')
                {
                    double op1, op2;
                    if (!stack.isEmpty())
                    {
                        stack.pop(op1);
                    }
                    if (!stack.isEmpty())
                    {
                        stack.pop(op2);
                    }
                    switch (postfix[i - 1])
                    {
                    case '+':
                        stack.push(op2 + op1);
                        break;
                    case '-':
                        stack.push(op2 - op1);
                        break;
                    case '*':
                        stack.push(op2 * op1);
                        break;
                    case '/':
                        stack.push(op2 / op1);
                        break;
                        break;

                    default:
                        break;
                    }
                    pos = i;
                }
            }
        }
        double result;
        if (!stack.isEmpty())
        {
            stack.pop(result);
        }
        return result;
    }

    /**
    *测试：
    请输入中缀表达式
    23+(34*45)/(5+6+7)
    栈空
    栈空
    栈空
    23 34 45 * 5 6 + 7 + / +
    */

    int main()
    {
        string infix;
        while (1)
        {
            cout << "请输入中缀表达式:" << endl;
            cin >> infix;
            string postfix = infixToP(infix);
            cout << "输出的后缀表达式为：" << endl;
            cout << postfix << endl;
            cout << "求值结果为：" << endl;
            cout << postfixCal(postfix) << endl;
        }
        return 0;
    }