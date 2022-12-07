#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;


//测试单向循环链表
#if 1
class CircleLink
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
    Node* tail_;
    
public:
    CircleLink()
    {
        head_=new Node();
        tail_=head_;
        head_->next_=head_;
    }
    //不同于单向链表释放
    ~CircleLink()
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

    // 尾插法   O(1)
    void InsertTail(int val)
    {
        Node* node=new Node(val);
        node->next_=head_;
        tail_->next_=node;
        tail_=node;
    }

    // 头插法
    void InsertHead(int val)
    {
        Node* node=new Node(val);
        node->next_=head_->next_;
        head_->next_=node;
        if(head_->next_==node)
        {
            tail_=node;
        }
    }

    // 删除节点
    void Remove(int val)
    {
        Node* q=head_;
        Node* p=head_->next_;

        while (p!=head_)
        {
            if(p->data_==val)
            {
                q->next_=p->next_;
                delete p;
                //删除尾节点
                if(q->next_=head_)
                {
                    tail_=q;
                }
                return;
            }
            else
            {
                q=p;
                p=p->next_;
            }
        }
    }
    // 查询
    bool Find(int val)const
    {
        Node* p=head_->next_;
        while (p!=head_)
        {
            if(p->data_==val)
            {
                cout<<p->data_<<endl;
                return true;
            }
        }
        return false;
    }
    // 打印链表
    void Show()const
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
    CircleLink clink;
    srand(time(NULL));

    clink.InsertHead(100);

    for (int i = 0; i < 10; i++)
    {
        clink.InsertTail(rand() % 100);
    }

    clink.InsertTail(200);
    clink.Show();

    clink.Remove(200);
    clink.Show();

    clink.InsertTail(300);
    clink.Show();
}
#endif

//单向循环链表解决约瑟夫环问题(不带虚拟头节点)

#if 1
struct Node
{
    Node(int data = 0) : data_(data), next_(nullptr) {}
    int data_;
    Node* next_;
};
/*
约瑟夫环是一个数学的应用问题：已知n个人（以编号1，2，3...n分别表示）围坐在一张圆桌周围，从
编号为k的人开始报数，数到m的那个人出列，它的下一个人又从1开始报数，数到m的那个人又出列，
依此规律重复下去，直到圆桌周围的人全部出列，输出人的出列顺序
*/
void Joseph(Node* head,int k,int m)
{
    Node* q=head;
    Node* p=head;

    //找到尾节点
    while (q->next_!=head)
    {
        q=q->next_;
    }
    for(int i=0;i<k;i++)
    {
        q=p;
        p=p->next_;
    }

    while (1)
    {
        for(int i=0;i<m;i++)
        {
            q=p;
            p=p->next_;
        }
        cout<<p->data_<<",";

        if(q==p)
        {
            delete p;
            return ;
        }

        q->next_=p->next_;
        delete p;
        p=q->next_;
    }
    
}
int main()
{
    Node* head = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);
    Node* n8 = new Node(8);

    head->next_ = n2;
    n2->next_ = n3;
    n3->next_ = n4;
    n4->next_ = n5;
    n5->next_ = n6;
    n6->next_ = n7;
    n7->next_ = n8;
    n8->next_ = head;

    Joseph(head, 1, 5);
}


#endif