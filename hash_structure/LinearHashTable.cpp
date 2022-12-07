

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

// 桶的状态
enum State
{
    STATE_UNUSE, // 从未使用过的桶
	STATE_USING, // 正在使用的桶
	STATE_DEL,   // 元素被删除了的桶
};

// 桶的类型
struct Bucket
{
    Bucket(int key=0,State state=STATE_UNUSE)
    :key_(key),
    state_(state)
    {}
    int key_;// 存储的数据
    State state_;// 桶的当前状态
};

// 线性探测哈希表(不去重)
class LinearHashTable
{
private:
    Bucket* table_;    // 指向动态开辟的哈希表
	int tableSize_;    // 哈希表当前空间长度(数组大小)
	int useBucketNum_; // 已经使用的桶的个数(已经存储元素的个数)
	double loadFactor_;// 哈希表的装载因子(扩容判断条件)

	static const int PRIME_SIZE = 10; // 素数表的大小
	static int primes_[PRIME_SIZE];   // 素数表
	int primeIdx_; // 当前使用的素数表的下标

    // 扩容操作
    void expand()
    {
        primeIdx_++;
        if(primeIdx_==PRIME_SIZE)
        {
            throw "too large";
        }
        Bucket* newtable=new Bucket[primes_[primeIdx_]];

        //旧表有效的数据，重新哈希放到扩容后的新表
        for(int i=0;i<tableSize_;i++)
        {
            if(table_[i].state_==STATE_USING)
            {
                int idx=table_[i].key_%primes_[primeIdx_];
                int k=idx;

                do
                {
                    if(newtable[k].state_!=STATE_USING)
                    {
                        newtable[k].state_=STATE_USING;
                        newtable[k].key_=table_[i].key_;
                        break;
                    }
                    k=(k+1)%primes_[primeIdx_];
                } while (k!=idx);
            }
        }
        delete[] table_;
        table_=newtable;
        tableSize_=primes_[primeIdx_];
    }

public:
    LinearHashTable(int size=primes_[0],double loadFactor=0.75)
    :useBucketNum_(0),
    loadFactor_(loadFactor),
    primeIdx_(0)
    {
        // 把用户传入的size调整到最近的比较大的素数上
        if(size!=primes_[0])
        {
            for(;primeIdx_<PRIME_SIZE;primeIdx_++)
            {
                if(primes_[primeIdx_]>size)
                {
                    break;
                }
            }
            // 用户传入的size值过大，已经超过最后一个素数，调整到最后一个素数
            if(primeIdx_==PRIME_SIZE)
            {
                primeIdx_--;
            }
        }
        tableSize_=primes_[primeIdx_];
        table_=new Bucket[tableSize_];
    }
    
    ~LinearHashTable()
    {
        delete[] table_;
        table_=nullptr;
    }

    // 插入元素
    bool insert(int key)
    {
        // 考虑扩容
        if((useBucketNum_*1.0/tableSize_)>loadFactor_)
        {
            expand();
        }

        //找到为状态不为正在使用的桶就插入
        int idx=key%tableSize_;
        int i=idx;
        do
        {
            //O(1)
            if(table_[i].state_!=STATE_USING)
            {
                table_[i].state_=STATE_USING;
                table_[i].key_=key;
                useBucketNum_++;
                return true;
            }
            i=(i+1)%tableSize_;
        } while (i!=idx);//O(n)
        return false;
    }

    // 删除多个相同key的元素
    bool erase(int key)
    {
        int idx=key%tableSize_;
        int i=idx;
        do
        {
            if(table_[i].state_==STATE_USING&&table_[i].key_==key)
            {
                table_[i].state_=STATE_DEL;
                useBucketNum_--;
            }
            i=(i+1)%tableSize_;
        } while (table_[i].state_!=STATE_UNUSE&&i!=idx);
        return true;
    }

    // 查询
    bool find(int key)
    {
        int idx=key%tableSize_;
        int i=idx;

        do
        {
            if(table_[i].state_==STATE_USING&&table_[i].key_==key)
            {
                return true;
            }
            i=(i+1)%tableSize_;
        } while (table_[i].state_!=STATE_UNUSE&&i!=idx);
        return false;
    }

};
int LinearHashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };

int main()
{
	LinearHashTable htable;
	htable.insert(21);
	htable.insert(32);
	htable.insert(14);
	htable.insert(15);
	htable.insert(22);

	cout << htable.find(21) << endl;
	htable.erase(21);
	cout << htable.find(21) << endl;
}





