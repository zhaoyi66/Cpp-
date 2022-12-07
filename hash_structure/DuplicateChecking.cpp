#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<stdlib.h>
#include<time.h>
#include<string>
using namespace std;
//大数据查重,哈希表
#if 0
int main()
{
    // 模拟问题，vector中放原始的数据
    vector<int> vec;
    vec.reserve(10000);//只开辟空间
    srand(time(NULL));
    for(int i=0;i<10000;i++)
    {
        vec.push_back(rand()%10000);
    }

    //找第一个出现重复的数字
    /*
    unordered_set<int> s1;
    for(auto key:vec)
    {
        auto it=s1.find(key);
        if(it==s1.end())
        {
            s1.insert(key);
        }
        else
        {
            cout<<"第一个出现重复的数字key="<<key<<endl;
            break;
        }
    }
    */
   
    // 统计重复数字以及出现的次数
    /*
    unordered_map<int,int> m1;
    for(auto key:vec)
    {
        //运算符重载
        m1[key]++;
    }

    for(auto pair:m1)
    {
        if(pair.first>1)
        {
            cout<<pair.first<<"出现"<<pair.second<<"次,";
        }
    }
    cout<<endl;
    */

   // 一组数据有些数字是重复的，把重复的数字过滤掉，每个数字只出现一次
   /*
   unordered_set<int> s1;
   for(auto key:vec)
   {
        s1.emplace(key);
   }
   */
}
#endif
//找出来第一个没有重复出现过的字符
#if 0
int main()
{
    string str="qidhbbbkJDHNSAlkofhbwigHCKMAlwj";
    unordered_map<int,int> m1;
    for(auto key:str)
    {
        m1[key]++;
    }
    for(char ch:str)
    {
        //[]运算符重载有查询和插入功能
        if(m1[ch]==1)
        {
            cout << "第一个没有重复出现过的字符是:" << ch << endl;
            return 0;
        }
    }
    cout << "所有字符都有重复出现过!" << endl;
    return 0;
}
#endif

//大数据查重,位图
#if 1
int main()
{
    vector<int> vec;
    vec.reserve(10000);//只开辟空间
    srand(time(NULL));
    for(int i=0;i<10000;i++)
    {
        vec.push_back(rand()%10000);
    }
    //找到最大值,定义位图数组
    int max=vec[0];
    for(auto val:vec)
    {
        if(val>max)
        {
            max=val;
        }
    }
    int* bitmap=new int[max/32+1]();

    //找出重复出现的数字
    for(auto key:vec)
    {
        int index=key/32;
        int offset=key%32;

        if(0==(bitmap[index]&(1<<offset)))
        {
            //key没有出现过,插入
            bitmap[index]|=(1<<offset);
        }
        else
        {
            cout<<"重复出现过"<<key<<endl;
        }
    }
    return 0;
}
#endif













