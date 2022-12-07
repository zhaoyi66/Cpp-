#include <iostream>
#include <functional>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 优先级队列实现   priority_queue(vector)  push pop top empty size
class PriorityQueue
{
public:
    using Comp=function<bool(int,int)>;
    PriorityQueue(int cap=20,Comp comp=greater<int>())
    :que_(new int[cap]),
    size_(0),
    cap_(cap),
    comp_(comp)
    {}

    PriorityQueue(Comp comp=greater<int>())
    :que_(new int[20]),
    size_(0),
    cap_(20),
    comp_(comp)
    {}


    ~PriorityQueue()
    {
        delete[] que_;
        que_=nullptr;
    }

    void push(int val)
    {
        // 判断扩容
        if(size_==cap_)
        {
            int *p=new int[size_*2];
            //浅拷贝
            memcpy(p,que_,cap_*sizeof(int));
            delete[] que_;
            que_=p;
            cap_=size_*2;
        }

        if(size_==0)
        {
            que_[size_]=val;
        }
        else
        {
            // 入堆操作,作为最后的叶子节点，再把该节点上浮
            siftUp(size_,val);
        }
        size_++;

    }


    
    void pop()
     {
        if(size_==0)
        {
            throw "empty!";
        }

        // 出堆操作，只能删除根节点，放入最后的叶子节点，最后该节点下沉
        size_--;
        if(size_>0)
        {
            siftDown(0,que_[size_]);
        }
     }

    bool empty() const { return size_ == 0; }

    int top() const 
    { 
        if (size_ == 0)
            throw "container is empty!";
        return que_[0];
    }
    int size() const { return size_; }

private:
    int *que_;// 指向动态扩容的数组
    int size_;// 数组元素的个数
    int cap_;// 数组的总空间大小
    Comp comp_;// 函数对象

    // 入堆上浮调整 O(logn)
    void siftUp(int i,int val)
    {
        // 最多计算到根节点(0号位)
        while (i>0)
        {
            int father=(i-1)/2;
            if(comp_(val,que_[father]))
            {
                que_[i]=que_[father];
                i=father;
            }
            else
            {
                break;
            }
        }
        //当val<que_[father]||大于根节点
        que_[i]=val;
    }

    // 出堆下沉调整 O(logn)
    void siftDown(int i,int val)
    {
        // i下沉不能超过最后一个有孩子的节点
        while (i<size_/2)
        {
            int child=i*2+1;
            if(child+1<size_&&comp_(que_[child+1],que_[child]))
            {
                // 如果i节点右孩子的值大/小于左孩子, child记录右孩子的下标
                child=child+1;
            }

            if(comp_(que_[child],val))
            {
                que_[i]=que_[child];
                i=child;
            }
            else
            {
                break;// 已经满足堆的性质，提前结束
            }
        }
         que_[i]=val;
    }


};

int main()
{
    
    // 基于小根堆实现的优先级队列
    PriorityQueue que([](int a, int b) {return a < b; });
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        que.push(rand() % 100);
    }

    while (!que.empty())
    {
        cout << que.top() << " ";
        que.pop();
    }
    cout << endl;
}


























