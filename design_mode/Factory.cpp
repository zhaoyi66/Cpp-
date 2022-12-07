#include <iostream>
#include <string>
#include <memory>
using namespace std;

/*
简单工厂:传给工厂自定义的枚举类型，返回对应的产品实例。封装了对象的创建
不满足开闭原则即对原有代码修改关闭，对功能扩展开放
随着新产品的添加，或者原有产品的删除，都会导致工厂代码的修改

Product基类派生出1,2,3产品
给工厂对象传入1,2,3枚举 返回对应的产品对象
*/
#if 0
// 产品类型
class Product
{
public:
	Product(string name) :_name(name) {}
	// 模拟产品对象的一个抽象方法
	virtual void show() = 0;
protected:
	string _name;
};
// 产品实体类型定义
class ProductA : public Product
{
public:
	ProductA(string name) :Product(name){}
	void show() { cout << "获取了一个ProductA对象:" << _name << endl; }
};
// 产品实体类型定义
class ProductB : public Product
{
public:
	ProductB(string name) :Product(name) {}
	void show() { cout << "获取了一个ProductB对象:" << _name << endl;
	}
};
// 产类枚举类型定义
enum ProductType
{
	XIAOMI,
	HUAWEI,
};
// 简单工厂类
class SimpleFactory
{
public:
	// 通过传入的枚举类型，创建相应的对象，返回所有对象的基类指针
	Product* createProduct(ProductType type)
	{
		switch (type)
		{
		case XIAOMI:
			return new ProductA("小米手机");
		case HUAWEI:
			return new ProductB("华为手机");
		}
	}
};
int main()
{
	// 创建简单工厂实例
	SimpleFactory sf;

	// 使用智能指针自动释放堆内存
	unique_ptr<Product> p1(sf.createProduct(XIAOMI));
	unique_ptr<Product> p2(sf.createProduct(HUAWEI));

	p1->show();
	p2->show();

	return 0;
}
#endif

/*
工厂方法:为每一种产品提供一个相应的实例工厂进行对象创建
新产品的添加，旧产品的删除，只需要增删派生类工厂即可，不会改变其他代码
但是一个实例工厂只负责生产一个实例产品

Product基类派生出1,2,3产品
工厂基类派生出1,2,3工厂
对应工厂负责生产对应产品
*/
#if 0
#include <iostream>
#include <string>
#include <memory>
using namespace std;
// 产品类型
class Product
{
public:
	Product(string name) :_name(name) {}
	// 模拟产品对象的一个抽象方法
	virtual void show() = 0;
protected:
	string _name;
};
// 产品实体类型定义
class ProductA : public Product
{
public:
	ProductA(string name) :Product(name){}
	void show() { cout << "获取了一个使用老外高通芯片的手机:" << _name << endl; }
};
// 产品实体类型定义
class ProductB : public Product
{
public:
	ProductB(string name) :Product(name) {}
	void show() { cout << "获取了一个使用自研麒麟芯片的手机:" << _name << endl;
	}
};

// 工厂基类
class Factory
{
public:
	virtual Product* createProduct() = 0;
};

// 生产小米手机的工厂
class XiaomiFactory : public Factory
{
public:
	Product* createProduct()
	{
		// 小米工厂肯定生产小米手机
		return new ProductA("小米手机");
	}
};
// 生产华为手机的工厂
class HuaweiFactory : public Factory
{
public:
	Product* createProduct()
	{
		// 华为工厂肯定生产华为手机
		return new ProductB("华为手机");
	}
};

int main()
{
	// 使用智能指针自动释放堆内存
	// 创建具体的工厂
	unique_ptr<Factory> f1(new XiaomiFactory);
	unique_ptr<Factory> f2(new HuaweiFactory);

	// 通过工厂方法创建产品
	unique_ptr<Product> p1(f1->createProduct());
	unique_ptr<Product> p2(f2->createProduct());

	p1->show();
	p2->show();

	return 0;
}
#endif

/*
抽象工厂:为一类品牌产品提供一个工厂派生类生产

A品牌Product基类 派生1,2,3产品
B品牌Product基类 派生1,2,3产品
工厂基类提供创建1,2,3产品的虚方法
由A工厂继承并重写这些方法
由B工厂继承并重写这些方法
*/
#if 0
#include <iostream>
#include <string>
#include <memory>
using namespace std;

// 产品簇手机类型
class ProductA
{
public:
	ProductA(string name) :_name(name) {}
	// 模拟产品对象的一个抽象方法
	virtual void show() = 0;
protected:
	string _name;
};
// 产品实体类型定义
class XiaomiPhone : public ProductA
{
public:
	XiaomiPhone(string name) :ProductA(name){}
	void show() { cout << "获取了一个小米手机:" << _name << endl; }
};
// 产品实体类型定义
class HuaweiPhone : public ProductA
{
public:
	HuaweiPhone(string name) :ProductA(name) {}
	void show() { cout << "获取了一个华为手机:" << _name << endl;
	}
};

// 产品簇智能手环类型
class ProductB
{
public:
	ProductB(string name) :_name(name) {}
	// 模拟产品对象的一个抽象方法
	virtual void show() = 0;
protected:
	string _name;
};
// 产品实体类型定义
class XiaomiCircle : public ProductB
{
public:
	XiaomiCircle(string name) :ProductB(name) {}
	void show() { cout << "获取了一个小米智能手环设备:" << _name << endl; }
};
// 产品实体类型定义
class HuaweiCircle : public ProductB
{
public:
	HuaweiCircle(string name) :ProductB(name) {}
	void show() {
		cout << "获取了一个华为智能手环设备:" << _name << endl;
	}
};

// 抽象工厂，创建通过一个产品簇的设备产品
class AbstractFactory
{
public:
	// 工厂里面创建手机的纯虚函数接口
	virtual ProductA* createPhone() = 0;
	// 工厂里面创建智能手环的纯虚函数接口
	virtual ProductB* createSmartCircle() = 0;
};

// 生产小米产品簇的工厂
class XiaomiFactory : public AbstractFactory
{
public:
	ProductA* createPhone()
	{
		// 小米工厂肯定生产小米手机
		return new XiaomiPhone("小米x9");
	}
	ProductB* createSmartCircle()
	{
		// 小米工厂肯定生产小米智能手环
		return new XiaomiCircle("小米智能手环2代时尚版");
	}
};
// 生产华为产品簇的工厂
class HuaweiFactory : public AbstractFactory
{
public:
	ProductA* createPhone()
	{
		// 华为工厂肯定生产华为手机
		return new HuaweiPhone("华为荣耀7x");
	}
	ProductB* createSmartCircle()
	{
		// 华为工厂肯定生产华为智能手环
		return new HuaweiCircle("华为智能手环B3青春版");
	}
};

int main()
{
	// 使用智能指针自动释放堆内存
	// 创建具体的工厂
	unique_ptr<AbstractFactory> f1(new XiaomiFactory);
	unique_ptr<AbstractFactory> f2(new HuaweiFactory);

	// 通过工厂方法创建手机产品
	unique_ptr<ProductA> p1(f1->createPhone());
	unique_ptr<ProductA> p2(f2->createPhone());
	p1->show();
	p2->show();

	// 通过工厂方法创建智能手环产品
	unique_ptr<ProductB> p3(f1->createSmartCircle());
	unique_ptr<ProductB> p4(f2->createSmartCircle());
	p3->show();
	p4->show();

	return 0;
}
#endif
