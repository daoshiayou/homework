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
//注意一下完工时保存为gbk，如果你不想再纠结垃圾控制台乱码问题的话