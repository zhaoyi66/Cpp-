#include<iostream>
#include<vector>
#include"stringhash.h"
#include<string>
using namespace std;

// 布隆过滤器实现
class BloomFilter
{
public:
    //指定大小,越长其误报率越小.不像位图根据最大值定义大小
    BloomFilter(int bitSize=1471)
    :bitSize_(bitSize)
    {
        bitMap_.resize(bitSize_/32+1);
    }

    // 添加元素 O(1)
    void setBit(const char* str)
    {
        // 通过k组哈希函数,得到不同的key
        int idx1 = BKDRHash(str) % bitSize_;
        int idx2 = RSHash(str) % bitSize_;
        int idx3 = APHash(str) % bitSize_;

        int index=0;
        int offset=0;

        index=idx1/32;
        offset=idx1%32;
        bitMap_[index]|=(1<<offset);

        index=idx2/32;
        offset=idx2%32;
        bitMap_[index]|=(1<<offset);

        index=idx3/32;
        offset=idx3%32;
        bitMap_[index]|=(1<<offset);
    }

    // 查询元素 O(1)
    bool getBit(const char* str)
    {
        int idx1 = BKDRHash(str) % bitSize_;
        int idx2 = RSHash(str) % bitSize_;
        int idx3 = APHash(str) % bitSize_;

        int index=0;
        int offset=0;

        //有一个为0一定不存在
        index=idx1/32;
        offset=idx1%32;
        if(0==(bitMap_[index]&(1<<offset)))
        {
            return false;
        }

        index=idx2/32;
        offset=idx2%32;
        if(0==(bitMap_[index]&(1<<offset)))
        {
            return false;
        }

        index=idx3/32;
        offset=idx3%32;
        if(0==(bitMap_[index]&(1<<offset)))
        {
            return false;
        }
        //可能存在，有误判
        return true;  
    }

private:
    int bitSize_;// 位图的长度
    vector<int> bitMap_;   // 位图数组
};

// URL黑名单
class BlackList
{
public:
    void add(string url)
    {
        blockList_.setBit(url.c_str());
    }
    bool query(string url)
    {
        return blockList_.getBit(url.c_str());
    }
private:
    BloomFilter blockList_;
};

int main()
{
    BlackList list;
    list.add("http://www.baidu.com");
    list.add("http://www.360buy.com");
    list.add("http://www.tmall.com");
    list.add("http://www.tencent.com");

    string url = "http://www.baidu.com";
    cout << list.query(url) << endl;
}




















