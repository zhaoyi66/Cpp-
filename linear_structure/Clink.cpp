#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

// 节点类型
struct Node
{
    Node(int data=0)
    :data_(data),next_(nullptr)
    {}
    int data_;
    Node* next_;
};

// 单链表代码实现
class Clink
{
private:
    Node *head_;//虚拟头结点
    friend void ReverseLink(Clink& link);// 单链表逆序
    friend bool GetLaskKNode(Clink& link,int k,int& val);// 求倒数第k个节点的值
    friend void MergeLink(Clink& link1,Clink& link2);// 合并两个有序的单链表
public:
    Clink()
    {
        // 给head_初始化指向头节点
        head_=new Node();
    }
    ~Clink()
    {
        //节点一个个的释放
        Node* p=head_;
        while (p!=nullptr)
        {
            head_=head_->next_;
            delete p;
            p=head_;
        }
        head_=nullptr;
    }

    // 链表尾插法 O(n)
    void InsertTail(int val)
    {
        Node *p=head_;
        while (p->next_!=nullptr)
        {
            p=p->next_;
        }

        Node* node=new Node(val);
        p->next_=node;
        
    }

    // 链表的头插法  O(1)
    void InsertHead(int val)
    {
        Node* node=new Node(val);
        node->next_=head_->next_;
        head_->next_=node;
    }

    // 链表节点的删除
    void Remove(int val)
    {
        Node* q=head_;
        Node* p=head_->next_;

        while (p!=nullptr)
        {
            if(p->data_==val)
            {
                q->next_=p->next_;
                delete p;
                return ;
            }

            q=q->next_;
            p=p->next_;
        }
    }

    // 删除多个节点
    void RemoveAll(int val)
    {
        Node* q=head_;
        Node* p=head_->next_;

        while (p->next_!=nullptr)
        {
            if(p!=nullptr)
            {
                q->next_=p->next_;
                delete p;
                // 对指针p进行重置
                p=q->next_;
            }
            else{
                q=q->next_;
                p=p->next_;
            }
        }
        
    }

    // 搜索O(n)
    bool Find(int val)
    {
        Node* p=head_->next_;
        while (p!=nullptr)
        {
            if(p->data_==val)
            return true;
            else
            p=p->next_;
        }
        return false;        
    }

    // 链表打印
    void Show()
    {
        Node* p=head_->next_;
        while (p!=nullptr)
        {
            cout<<p->data_<<" ";
            p=p->next_;
        }
        cout<<endl;
    }
};

// 单链表逆序
void ReverseLink(Clink &link)
{
    /*将虚拟头节点与剩下节点分两部分
    将虚拟节点next置空，将剩下节点从左到右用头插法插入
    */
    Node* head=link.head_;
    Node* p=head->next_;
    if(p==nullptr)
    {
        return;
    }
    head->next_=nullptr;

    while(p!=nullptr)
    {
        Node* q=p->next_;
        //头插法
        p->next_=head->next_;
        head->next_=p;

        p=q;
    }
}

//求倒数第k个节点的值
bool GetLaskKNode(Clink& link,int k,int& val)
{
    if(k<1)
    return false;

    //一个指针先走k(不为空)，之后两指针一起走 直到为空
    Node* head=link.head_;
    Node* p=head;
    Node* q=head;

    for(int i=0;i<k;i++)
    {
        p=p->next_;
        if(p==nullptr)
        return false;
    }
    while (p!=nullptr)
    {
        p=p->next_;
        q=q->next_;
    }

    val=q->data_;
    return true;
}

// 合并两个有序的单链表
void MergeLink(Clink& link1,Clink& link2)
{
    Node* q=link1.head_->next_;
    Node* p=link2.head_->next_;

    Node* head=link1.head_;
    head->next_=nullptr;
    link2.head_->next_=nullptr;

    while ((q!=nullptr)&&(p!=nullptr))
    {
        if(q->data_<p->data_)
        {
            head->next_=q;
            q=q->next_;
        }
        else
        {
            head->next_=p;
            p=p->next_;
        }
        head=head->next_;
    }
    if(q!=nullptr)
    {
        head->next_=q;
    }
    else if(p!=nullptr)
    {
         head->next_=p;
    }
}

// 判断单链表是否存在环，存在返回环的入口节点
bool IsLinkHasCircle(Node *head,int& val)
{
    Node* fast=head;
    Node* slow=head;

    while (fast!=nullptr&&fast->next_!=nullptr)
    {
        slow=slow->next_;
        fast=fast->next_->next_;

        /*fast遍历节点数量=slow遍历数量*2
        假设起点到入口距离为x，入口到相遇处为y，相遇处到最后一个节点为a
        x+y+a+y=2(x+y),a=x
        slow回到起点，fast在相遇处，fast与slow一起移动，最后在入口处相遇
        */
        if(slow==fast)
        {
            fast=head;
            while (fast!=slow)
            {
                fast=fast->next_;
                slow=slow->next_;
            }
            val=slow->data_;
            return true;
        }
    }
    return false;
}

// 判断两个单链表是否相交，如果相交，返回相交节点的值
bool IsLinkHasMerge(Node* head1,Node* head2,int& val)
{
    //计算链表长度，长的链表先移动相差节点数，再一起移动直到节点相同
    int length1=0,length2=0;
    Node* q=head1;
    Node* p=head2;

    while (q!=nullptr)
    {
        length1++;
        q=q->next_;
    }
    
    while (p!=nullptr)
    {
        length2++;
        p=p->next_;
    }

    q=head1;
    p=head2;

    if(length1<length2)
    {
        int offerset=length2-length1;
        while(offerset-->0)
        {
            p=p->next_;
        }
    }
    else
    {
        int offerset=length1-length2;
        while(offerset-->0)
        {
            q=q->next_;
        }
    }
    while ((q!=nullptr)&&(p!=nullptr))
    {
        if(q==p)
        {
            val=q->data_;
            return true;
        }
        q=q->next_;
        p=p->next_;

    }

    return false;
}


//测试链表类
#if 0
int main()
{
    Clink link;
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        int val = rand() % 100;
        link.InsertHead(val);
        cout << val << " ";
    }
    cout << endl;

    link.InsertTail(23);
    link.InsertHead(23);
    link.InsertHead(23);

    link.Show();

    link.RemoveAll(23);
    link.Show();
}
#endif

//测试单链表逆序
#if 0
int main()
{
    Clink link;
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        int val = rand() % 100;
        link.InsertTail(val);
    }
    link.Show();

    ReverseLink(link);
    link.Show();

}
#endif

//测试单链表逆序,求倒数第k个节点的值
#if 0
int main()
{
    Clink link;
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        int val = rand() % 100;
        link.InsertTail(val);
    }
    link.Show();

    ReverseLink(link);
    link.Show();

    int kval;
    int k = 10;
    if (GetLaskKNode(link, k, kval))
    {
        cout << "倒数第" << k << "个节点的值:" << kval << endl;
    }
}
#endif

//测试合并两个有序的单链表
#if 0
int main()
{
    int arr[] = {25, 37, 52, 78, 88, 92, 98, 108};
    int brr[] = { 13, 23, 40, 56, 62, 77, 109 };

    Clink link1;
    Clink link2;

    for (int v : arr)
    {
        link1.InsertTail(v);
    }
    
    for (int v : brr)
    {
        link2.InsertTail(v);
    }

    link1.Show();
    link2.Show();

    MergeLink(link1, link2);
    link1.Show();
    link2.Show();
}
#endif


//测试单链表是否存在环，存在返回环的入口节点
#if 0
int main()
{
    Node head;

    Node n1(25), n2(67), n3(32), n4(18);
    head.next_ = &n1;
    n1.next_ = &n2;
    n2.next_ = &n3;
    n3.next_ = &n4;
    n4.next_ = &n4;

    int val;
    if (IsLinkHasCircle(&head, val))
    {
        cout << "链表存在环，环的入口节点是：" << val << endl;
    }
}
#endif

//测试 两个单链表是否相交，如果相交，返回相交节点的值
#if 1
int main()
{
    Node head1;
    Node n1(25), n2(67), n3(32), n4(18);
    head1.next_ = &n1;
    n1.next_ = &n2;
    n2.next_ = &n3;
    n3.next_ = &n4;

    Node head2;
    Node n5(31);
    head2.next_ = &n5;
    n5.next_ = &n1;

    int val;
    if (IsLinkHasMerge(&head1, &head2, val))
    {
        cout << "链表相交，相交节点是：" << val << endl;
    }
}
#endif










