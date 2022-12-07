#include <iostream>
#include <memory>

using namespace std;

/*
通过子类继承基类并新增方法/重写方法实现新的功能,代码量多

装饰器模式:不改变现有类的情况下添加新的功能
由基类派生的装饰类有基类的指针，指向需要添加功能的派生类对象
在装饰类中新增方法/重写方法添加新功能
*/

class Car
{
public:
    virtual void show() = 0;
};

class Bmw : public Car
{
public:
    void show()
    {
        cout << "这是一辆宝马汽车，配置为: 基本配置";
    }
};

class Audi : public Car
{
public:
    void show()
    {
        cout << "这是一辆奥迪汽车，配置为: 基本配置";
    }
};

class Benz : public Car
{
public:
    void show()
    {
        cout << "这是一辆奔驰汽车，配置为: 基本配置";
    }
};

//各装饰类没有公共方法则可以不写装饰基类

//定速巡航
class Decorator01 : public Car
{
public:
    Decorator01(Car *p) : pCar(p) {}
    void show()
    {
        pCar->show();
        cout << ",定速巡航";
    }

private:
    Car *pCar;
};

class Decorator02 : public Car
{
public:
    Decorator02(Car *p) : pCar(p) {}
    void show()
    {
        pCar->show();
        cout << ",自动刹车";
    }

private:
    Car *pCar;
};

class Decorator03 : public Car
{
public:
    Decorator03(Car *p) : pCar(p) {}
    void show()
    {
        pCar->show();
        cout << ",车道偏离";
    }

private:
    Car *pCar;
};

int main()
{
    Car *p1 = new Decorator01(new Bmw());
    p1->show();
    cout << endl;

    p1 = new Decorator02(p1);
    p1->show();
    cout << endl;

    p1 = new Decorator03(p1);
    p1->show();
    cout << endl;
    //每次new 指针所指向的地址都在变化，但是每次调用show()
    //调用的内容都是new之前指针指向内存的show和本次添加的新功能
    return 0;
}
