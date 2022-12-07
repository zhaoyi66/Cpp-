
#include <iostream>
#include <unordered_map>
using namespace std;

/*
发布订阅/观察者模式:
基类Observer定义 virtual handle方法
继承于Observer的重写handle方法，根据msgid有不同的表现
Subject用unordered_map<int,list<Observer*>>保存对多类信息感兴趣的多组对象
当发生改变，通过取出msgid对应的list对象，通知改变

在多线程环境下，裸指针不能确定对象是否存在
unordered_map<int,list<weak_ptr<Observer>>>
weak_ptr观察资源，调用lock方法判断对象是否存活
*/
class Observer
{
public:
    virtual void handle(int mid) = 0; //信息编号
};

class Observer1 : public Observer
{
public:
    void handle(int mid)
    {
        switch (mid)
        {
        case 1:
            cout << "Observer1 receive 1 mid!" << endl;
            break;
        case 2:
            cout << "Observer1 receive 2 mid!" << endl;
            break;
        default:
            cout << "Observer1 receive unknown mid!" << endl;
            break;
        }
    }
};

class Observer2 : public Observer
{
public:
    void handle(int mid)
    {
        switch (mid)
        {
        case 2:
            cout << "Observer2 receive 2 mid!" << endl;
            break;
        default:
            cout << "Observer2 receive unknown mid!" << endl;
            break;
        }
    }
};

class Observer3 : public Observer
{
public:
    void handle(int mid)
    {
        switch (mid)
        {
        case 1:
            cout << "Observer3 receive 1 mid!" << endl;
            break;
        case 3:
            cout << "Observer3 receive 3 mid!" << endl;
            break;
        default:
            cout << "Observer3 receive unknown mid!" << endl;
            break;
        }
    }
};

//主题
class Subject
{
public:
    //给主题增加观察者对象
    void addObserver(int mid, Observer *ob)
    {
        _subMap[mid].push_back(ob);
    }

    //主题检测发生改变，通知相应的观察者对象处理事件
    void dispatch(int mid)
    {
        auto it = _subMap.find(mid);
        if (it != _subMap.end()) //存在该事件的观察者
        {
            for (Observer *ob : it->second)
            {
                ob->handle(mid); //处理消息
            }
        }
    }

private:
    unordered_map<int, list<Observer *>> _subMap;
};

int main()
{
    Subject subject;
    Observer *p1 = new Observer1();
    Observer *p2 = new Observer2();
    Observer *p3 = new Observer3();

    subject.addObserver(1, p1);
    subject.addObserver(2, p1);
    subject.addObserver(2, p2);
    subject.addObserver(1, p3);
    subject.addObserver(3, p3);

    int mid = 0;
    while (1)
    {
        cout << "输入消息id:";
        cin >> mid;
        if (mid == -1)
            break;
        subject.dispatch(mid);
    }

    return 0;
}
