#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <functional>
#include <unordered_map>
using namespace std;
//大/小根堆,快排分割处理topk问题

//大小根堆解决topk问题
#if 0
int main()
{
    vector<int> vec;
    srand(time(NULL));
    for (int i = 0; i < 1000; i++)
    {
        vec.push_back(rand() % 10000);
    }

    // 求vec中值最小的前5个元素
    priority_queue<int> maxheap;//默认大根堆

    // 由前k个元素构建一个大根堆
    for(int i=0;i<5;i++)
    {
        maxheap.push(vec[i]);
    }

    //淘汰堆顶元素，把较小元素插入,最后剩下的都是最小元素
    for(int i=5;i<vec.size();i++)
    {
        if(maxheap.top()>vec[i])
        {
            maxheap.pop();
            maxheap.push(vec[i]);
        }
    }
    while (!maxheap.empty())
    {
        cout<<maxheap.top()<<",";
        maxheap.pop();
    }
    cout<<endl;

    // 求vec中值最大的前5个元素
    //存储元素类型，底层容器类型，函数对象
    priority_queue<int, vector<int>, greater<int>> minheap;

    // 由前k个元素构建一个大根堆
    for (int i = 0; i < 5; i++)
    {
        minheap.push(vec[i]);
    }

    //淘汰堆顶元素，把更大元素插入，最后剩下的都是最大元素
    for (int i = 5; i < vec.size(); i++)
    {
        if (minheap.top() < vec[i])
        {
            minheap.pop();
            minheap.push(vec[i]);
        }
    }

    while (!minheap.empty())
    {
        cout << minheap.top() << " ";
        minheap.pop();
    }
    cout << endl;
}

#endif

//快排分割处理topk问题
#if 1
// 快排分割函数
int Partation(vector<int> &arr, int begin, int end)
{
    int i=begin;
    int j=end;
    int val=arr[0];
    
    while (i<j)
    {
        while ((i<j)&&(arr[j]>val))
        {
            j--;
        }
        if(i<j)
        {
            arr[i]=arr[j];
            i++;
        }

        while ((i<j)&&(arr[i]<val))
        {
            i++;
        }
        if(i<j)
        {
            arr[j]=arr[i];
            j--;
        }
    }
    arr[i]=val;
    return i;
}

// 求top k的函数
void SelectTopK(vector<int> &arr, int begin, int end, int k)
{
    //利用快排分割函数每次返回的基准数的位置，找出前top k大的或者前top k小的数据
    int pos = Partation(arr, begin, end);

    if (pos == k - 1)
    {
        return;
    }
    else if (pos > k - 1)
    {
        SelectTopK(arr, begin, pos - 1, k);
    }
    else
    {
        SelectTopK(arr, pos + 1, end, k);
    }
}

int main()
{
    vector<int> arr;
    arr.reserve(1000);
    srand(time(0));
    for (int i = 0; i < 1000; i++)
    {
        arr.push_back(rand() % 100);
    }
    int size = arr.size();

    // 求值最小的前100个元素
    int k = 100;
    SelectTopK(arr, 0, size - 1, k);

    for (int i = 0; i < k; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
#endif

// 查重和topk问题综合
#if 0
int main()
{
    vector<int> vec;
    srand(time(NULL));
    for (int i = 0; i < 10000; i++)
    {
        vec.push_back(rand() % 1000);
    }

    // 统计重复次数最小的前3个数字
    int k = 3;
    //先统计重复次数
    unordered_map<int,int> map;
    for(auto key:vec)
    {
        map[key]++;
    }

    // 放入大根堆的时候，需要放pair
    using Type=pair<int,int>;
    using Comp=function<bool(Type&,Type&)>;//传入函数对象的类型，还需要初始化
    priority_queue<Type,vector<Type>,Comp> maxheap(
        [](Type& a,Type& b)->bool{
            return a.second<b.second;
        });
    //k个pair组成大根堆
    auto it=map.begin();
    for(int i=0;i<k;i++,++it)
    {
        maxheap.push(*it);
    }

    //淘汰堆顶元素，放入重复次数小的pair,最后剩下的都是重复次数小的pair
    for(;it!=map.end();++it)
    {
        if(maxheap.top().second>it->second)
        {
            maxheap.pop();
            maxheap.push(*it);
        }
    }
    while (!maxheap.empty())
    {
        cout << "key:" << maxheap.top().first
            << " cnt:" << maxheap.top().second << endl;
        maxheap.pop();
    }
    return 0;
}

#endif
















