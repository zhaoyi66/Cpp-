#include<iostream>
using namespace std;


//双指针逆序字符串
#if 0
void Reverse(char arr[],int size)
{
    char *p=arr;
    char *q=arr+size-1;
    while(p<q)
    {
        char ch=*p;
        *p=*q;
        *q=ch;
        p++;
        q--;
    }
}
int main()
{
    char arry[]="hello,world";
    Reverse(arry,strlen(arry));
    cout<<arry<<endl;
    return 0;
}
#endif


//整形数组，把偶数调整到数组的左边，把奇数调整到数组的右边
#if 0
void AdjustArray(int arr[],int size)
{
    int *q=arr;
    int *p=arr+size-1;

    while(q<p)
    {
        while(((*q)%2==0)&&(q<p))
        {
            q++;
        }
        while(((*p)%2==1)&&(q<p))
        {
            p--;
        }
        if(q<p)
        {
            char c=*q;
            *q=*p;
            *p=c;
        }
    }
}

int main()
{
    int arr[10] = { 0 };
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 100;
    }

    for (int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;

    AdjustArray(arr, 10);
    for (int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
}
#endif

// 自动扩容数组实现
#if 1
class Array
{
public:
    Array(int size=10)
    :mCap(size),mCur(0)
    {
        mpArr=new int[size];
    }
    ~Array()
    {
        //原来heap空间被释放，但指针不为nullptr
        delete [] mpArr;
        mpArr=nullptr;
    }
    // 末尾增加元素
    void push_back(int val)
    {
        if(mCur==mCap)
            expand(2*mCap);

            mpArr[mCur++]=val;

    }
    // 末尾删除元素
    void pop_back()
    {
        if(mCur>0)
        mCur--;
    }
    // 按位置增加元素
    void insert(int pos,int val)
    {
        if(pos<0||pos>mCur)
        return;
        
        if(mCur==mCap)
        expand(2*mCap);

         // 移动元素  O(n)
         for(int i=mCur-1;i>=pos;i--)
         {
            mpArr[i+1]=mpArr[i];
         }
         mpArr[pos]=val;
         mCur++;
    }
     // 按位置删除
    void erase(int pos)
    {
        if(pos<0||pos>mCur)
        {
            return ;
        }
        for(int i=pos+1;i<mCur;i++)
        {
            mpArr[i-1]=mpArr[i];
        }
        mCur--;
    }
    // 元素查询
    int find(int val)
    {
        for(int i=0;i<mCur;i++)
        {
            if(mpArr[i]==val)
            {
                return i;
            }
        }
        return -1;
    }
    // 打印数据
    void show()const
    {
        for(int i=0;i<mCur;i++)
        {
            cout<<mpArr[i]<<",";
        }
        cout<<endl;
    }
private:
    // 内部数组扩容接口
    void expand(int size)
    {
        int *p=new int[size];
        //浅拷贝
        memcpy(p,mpArr,sizeof(int)*mCur);
        delete[] mpArr;
        mpArr=p;
        mCap=size;
    }
    int* mpArr;  // 指向可扩容的数组内存
    int mCap;    // 数组的容量
    int mCur;    // 数组有效元素个数
};
int main()
{
    Array arr;

    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        arr.push_back(rand() % 100);
    }

    arr.show();
    arr.pop_back();
    arr.show();

    arr.insert(0, 100);
    arr.show();

    arr.insert(10, 200);
    arr.show();

    int pos = arr.find(100);
    if (pos != -1)
    {
        arr.erase(pos);
        arr.show();
    }
}
#endif
