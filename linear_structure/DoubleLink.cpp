#include<iostream>
using namespace std;

// 定义双向链表的节点类型
struct Node
{
    Node(int data=0)
    :data_(data),next_(nullptr),pre_(nullptr)
    {}
    int data_;
    Node* next_;
    Node* pre_;
};

//双向链表
class DoubleLink
{
private:
    Node* head_;
public:
    DoubleLink()
    {
        head_=new Node();
    }
    ~DoubleLink()
    {
        Node* p=head_;
        while (p!=nullptr)
        {
            head_=head_->next_;
            delete p;
            p=head_;
        }
    }

    // 头插法
    void InsertHead(int val)
    {
        Node* node=new Node(val);

        node->next_=head_->next_;
        node->pre_=head_;
        //插入的是第一个节点
        if(head_->next_!=nullptr)
        {
            head_->next_->pre_=node;
        }
        head_->next_=node;
    }

    // 尾插法
    void InsertTail(int val)
    {
        Node* p=head_;
        while (p->next_!=nullptr)
        {
            p=p->next_;
        }
        Node* node=new Node(val);
        node->pre_=p;
        p->next_=node;
    }

    // 节点删除
    void Remove(int val)
    {
        Node* p=head_->next_;

        while (p!=nullptr)
        {
            if(p->data_==val)
            {
                p->pre_->next_=p->next_;
                if(p->next_!=nullptr)
                {
                    p->next_->pre_=p->pre_;
                }
                delete p;
                return ;
            }else{
                p=p->next_;
            }
        }
    }
    // 节点搜索
    bool Find(int val)
    {
        Node* p=head_->next_;
        while (p!=nullptr)
        {
            if(p->data_==val)
            {
                return true;
            }
            p=p->next_;
        }
        return false;
    }

    // 链表节点输出
    void Show()const
    {
        Node* p=head_->next_;
        while (p!=nullptr)
        {
            cout<<p->data_<<",";
            p=p->next_;
        }
        cout<<endl;
    }
};
int main()
{
    DoubleLink dlink;

    dlink.InsertHead(100);

    dlink.InsertTail(20);
    dlink.InsertTail(12);
    dlink.InsertTail(78);
    dlink.InsertTail(32);
    dlink.InsertTail(7);
    dlink.InsertTail(90);
    dlink.Show();

    dlink.InsertHead(200);
    dlink.Show();

    dlink.Remove(200);
    dlink.Show();

    dlink.Remove(90);
    dlink.Show();

    dlink.Remove(78);
    dlink.Show();
}
































