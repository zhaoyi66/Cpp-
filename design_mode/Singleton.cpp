#include <iostream>
#include <pthread.h>
using namespace std;

/*
单例模式:无论怎么获取，永远只能得到该类类型的唯一一个实例对象
1.构造函数私有化，2.定义该类型唯一的对象，3.static静态成员方法返回唯一的对象实例
*/

//饿汉单例模式:程序启动时就实例化了，静态对象在代码段上

class CSingleton
{
public:
    static CSingleton *getInstance()
    {
        return &single;
    }

private:
    static CSingleton single;
    CSingleton() { cout << "CSingleton()" << endl; }
    CSingleton(const CSingleton &);
};
CSingleton CSingleton::single;

//懒汉单例模式:在第一次调用方法时才实例化，需要加锁维护线程安全
class CSingleton
{
public:
    static CSingleton *getInstance()
    {
        // 锁加双重判断
        if (nullptr == single)
        {
            pthread_mutex_lock(&mutex);
            if (nullptr == single)
            {
                single = new CSingleton();
            }
            pthread_mutex_unlock(&mutex);
        }
        return single;
    }

private:
    static CSingleton *single;
    // 定义线程间的互斥锁
    static pthread_mutex_t mutex;
    CSingleton() { cout << "CSingleton()" << endl; }
    ~CSingleton() { cout << "~CSingleton()" << endl; }
    CSingleton(const CSingleton &);
};
CSingleton *CSingleton::single = nullptr;
// 互斥锁的初始化
pthread_mutex_t CSingleton::mutex = PTHREAD_MUTEX_INITIALIZER;
