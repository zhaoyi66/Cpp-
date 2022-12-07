#include<iostream>
using namespace std;

// 定义双向循环链表的节点类型
struct Node
{
    Node(int data=0)
    :data_(data),next_(nullptr),pre_(nullptr)
    {}
    int data_;
    Node* next_;
    Node* pre_;
};

// 双向循环链表
class DoubleCircleLink
{
private:
    Node* head_;
public:
    DoubleCircleLink()
    {
        head_=new Node();
        head_->next_=head_;
        head_->pre_=head_;
    }
    ~DoubleCircleLink()
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

    // 头插法 O(1)
    void InsertHead(int val)
    {
        Node* node=new Node(val);

        node->next_=head_->next_;
        node->pre_=head_;
        head_->next_->pre_=node;
        head_->next_=node;
    }

    // 尾插法  O(1)
    void InsertTail(int val)
    {
        Node* p=head_->pre_;
        Node* node=new Node(val);

        node->pre_=p;
        node->next_=head_;
        p->next_=node;
        head_->pre_=node;
    }

    // 节点删除
    void Remove(int val)
    {
        Node* p=head_->next_;
        while (p!=head_)
        {
            if(p->data_==val)
            {
                p->pre_->next_=p->next_;
                p->next_->pre_=p->pre_;
                delete p;
                return ;
            }
            p=p->next_;
        }
        
    }

    // 节点搜索
    bool Find(int val)
    {
        Node* p=head_->next_;
        while (p!=head_)
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
    void Show()
    {
        Node* p=head_->next_;
        while (p!=head_)
        {
            cout<<p->data_<<",";
            p=p->next_;
        }
        cout<<endl;
    }
};
int main()
{
    DoubleCircleLink dlink;

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





































