#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;


//链式哈希表(去重)
class ChainHashTable
{
public:
   ChainHashTable(int size = primes_[0], double loadFactor = 0.75)
		: useBucketNum_(0)
		, loadFactor_(loadFactor)
		, primeIdx_(0)
	{
		if (size != primes_[0])
		{
			for (; primeIdx_ < PRIME_SIZE; primeIdx_++)
			{
				if (primes_[primeIdx_] >= size)
					break;
			}

			if (primeIdx_ == PRIME_SIZE)
			{
				primeIdx_--;
			}
		}
		//resize开辟内存空间并添加元素
		table_.resize(primes_[primeIdx_]);
	}

    // 增加元素 不能重复插入key
    void insert(int key)
    {
        // 判断扩容
        if((useBucketNum_*1.0/table_.size())>loadFactor_)
        {
            expand();
        }

        //O(1)
        int idx=key%table_.size();
        if(table_[idx].empty())
        {
            useBucketNum_++;
            table_[idx].emplace_front(key);
        }
        else
        {
            auto it=::find(table_[idx].begin(),table_[idx].end(),key);
            if(it==table_[idx].end())
            {
                // key不存在
                table_[idx].emplace_front(key);
            }
        }
    }

    // 删除元素
    void erase(int key)
    {
        int idx=key%table_.size();
        auto it=::find(table_[idx].begin(),table_[idx].end(),key);
        if(it!=table_[idx].end())
        {
            table_[idx].erase(it);
            if(table_[idx].empty())
            {
                useBucketNum_--;
            }
        }
    }

    // 搜索元素
    bool find(int key)
    {
        int idx=key%table_.size();
        auto it=::find(table_[idx].begin(),table_[idx].end(),key);
        return it!=table_[idx].end();
    }

private:

    // 扩容函数
    void expand()
    {
        if(primeIdx_+1==PRIME_SIZE)
        {
            throw "can not expand";
        }

        primeIdx_++;
        useBucketNum_=0;
        vector<list<int>> oldTable;//存储旧的
        //容器空间配置器相同，直接交换数据成员
        table_.swap(oldTable);
        table_.resize(primes_[primeIdx_]);

        //每个元素重新哈希放入新的哈希表中
        for(auto list:oldTable)
        {
            for(auto key:list)
            {
                int idx=key%table_.size();
                if(table_[idx].empty())
                {
                    useBucketNum_++;
                }
                table_[idx].emplace_front(key);
            }
        }
    }

    vector<list<int>> table_; // 哈希表的数据结构
	int useBucketNum_;        // 记录桶的个数
	double loadFactor_;       // 记录哈希表装载因子

	static const int PRIME_SIZE = 10; // 素数表的大小
	static int primes_[PRIME_SIZE];   // 素数表
	int primeIdx_; // 当前使用的素数下标
};
int ChainHashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };

int main()
{
	ChainHashTable htable;
	htable.insert(21);
	htable.insert(32);
	htable.insert(14);
	htable.insert(15);

	htable.insert(22);

	htable.insert(67);

	cout << htable.find(67) << endl;
	htable.erase(67);
	cout << htable.find(67) << endl;

	return 0;
}


















