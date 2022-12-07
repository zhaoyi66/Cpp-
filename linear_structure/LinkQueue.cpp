#include <iostream>
using namespace std;

//链式队列
class LinkQueue
{
private:
    struct Node
    {
        Node(int data=0)
        :data_(data),
        next_(nullptr),
        pre_(nullptr)
        {}
        int data_;
        Node* next_;
        Node* pre_;
    };

    Node* head_;
    
public:
    LinkQueue()
    {
        head_=new Node();
        head_->next_=head_;
        head_->pre_=head_;
    }
    ~LinkQueue()
    {
        Node* p=head_->next_;
        while (p!=head_)
        {
            head_->next_=p->next_;
            delete p;
            p=head_->next_;
        }
        delete head_;
    }

    // 入队,因为是循环,不用判空
    void push(int val)
    {
        Node* node=new Node(val);
        node->next_=head_;
        node->pre_=head_->pre_;
        head_->pre_->next_=node;
        head_->pre_=node;
    }

    // 出队
    void pop()
    {
        if(head_->next_==head_)
        return ;
        Node* p=head_->next_;
        head_->next_=p->next_;
        p->next_->pre_=head_;
        delete p;
    }

    // 获取队头元素
    int front()const
    {
        if(head_->next_==head_)
        {
            cout<<"queue is empty";
            return 0;
        }
        return head_->next_->data_;
    }

    // 获取队尾元素
    int back()const
    {
        if(head_->next_==head_)
        {
            cout<<"queue is empty";
            return 0;
        }
        return head_->pre_->data_;
    }
    bool empty()const
    {
        return head_->next_==head_;
    }

};

int main()
{
	int arr[] = { 12,4,56,7,89,31,53,75 };
	LinkQueue que;

	for (int v : arr)
	{
		que.push(v);
	}

	cout << que.front() << endl;
	cout << que.back() << endl;

	que.push(100);
	que.push(200);
	que.push(300);
	cout << que.front() << endl;
	cout << que.back() << endl;

	while (!que.empty())
	{
		cout << que.front() << " " << que.back() << endl;
		que.pop();
	}
}























