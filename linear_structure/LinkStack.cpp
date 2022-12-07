#include <iostream>
#include <string>
#include <stack>
using namespace std;


//测试链式栈
#if 0
class LinkStack
{
private:
    struct Node
    {
        Node(int data=0)
        :data_(data),next_(nullptr)
        {}
        int data_;
        Node* next_;
    };
    Node* head_;
    int size_;

public:
    LinkStack()
    :size_(0),head_(new Node)
    {}
    ~LinkStack()
    {
        Node* p=head_;
        while (p!=nullptr)
        {
            head_=head_->next_;
            delete p;
            p=head_;
        }
    }

    // 入栈 O(1)   把链表头节点后面，第一个有效节点的位置，当作栈顶位置
    //头插法
    void push(int val)
    {
        Node* node=new Node(val);
        node->next_=head_->next_;
        head_->next_=node;
        size_++;
    }
    // 出栈 O(1)
    void pop()
    {
        if(head_->next_==nullptr)
        return;
        Node* p=head_->next_;
        head_->next_=p->next_;
        delete p;
        size_--;
    }
    // 获取栈顶元素
    int top()const
    {
        if(head_->next_==nullptr)
        return 0;
        return head_->next_->data_;
    }
    // 判空
    bool empty()const{return head_->next_==nullptr;}

    // 返回栈元素个数   遍历一遍链表，记录节点个数O(n)    想达到O(1)
    int size()const{return size_;}

};


int main()
{
	int arr[] = { 12,4,56,7,89,31,53,75 };
	LinkStack s;

	for (int v : arr)
	{
		s.push(v);
	}

	cout << s.size() << endl;

	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;

	cout << s.size() << endl;
}




#endif

//匹配括号
#if 0
stack<char> p;
        for(char i:s)
        {
            if(i==')'||i==']'||i=='}')
            {
                if(p.empty())
                return false;
                if((i==')'&&p.top()=='(')||(i==']'&&p.top()=='[')||(i=='}'&&p.top()=='{'))
                p.pop();
                else 
                return false;
            }
            else
            {
                p.push(i);
            }
        }
        if(p.empty())
        return true;
        
        return false;
#endif


//逆波兰表达式，后缀表达式
#if 0
    int evalRPN(vector<string>& tokens)
    {
        stack<int> p;
        for(int i=0;i<tokens.size();i++)
        {
            if(tokens[i]=="+"||tokens[i]=="-"||tokens[i]=="*"||tokens[i]=="/")
            {
                int num1=p.top();
                p.pop();
                int num2=p.top();
                p.pop();
                if(tokens[i]=="+") p.push(num1+num2);
                else if(tokens[i]=="-") p.push(num2-num1);
                else if(tokens[i]=="*") p.push(num2*num1);
                else if(tokens[i]=="/") p.push(num2/num1);
            }
            else
            {
                p.push(stoi(tokens[i]));
            }
        }
        return p.top();

    }
#endif




















