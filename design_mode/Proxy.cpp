#include <iostream>
#include <memory>
using namespace std;

/*
代理模式:通过代理类控制实际对象的访问方式
基类包含所有权限  派生类包含每个级别的用户所能拥有的权限
派生类与基类是委托关系 继承的虚函数表调用基类方法重写
*/

class VideoSite //抽象类
{
public:
    virtual void freeMovie() = 0;   //免费电影
    virtual void vipMovie() = 0;    // vip电影
    virtual void ticketMovie() = 0; //用券观看电影
};

class Fix : public VideoSite //委托类
{
public:
    virtual void freeMovie()
    {
        cout << "观看免费电影" << endl;
    }

    virtual void vipMovie()
    {
        cout << "观看VIP电影" << endl;
    }

    virtual void ticketMovie()
    {
        cout << "观看用券电影" << endl;
    }
};

// Free代理类
class Free : public VideoSite
{
public:
    Free() { pVideo = new Fix(); }
    ~Free() { delete pVideo; }

    virtual void freeMovie()
    {
        pVideo->freeMovie();
    }

    virtual void vipMovie()
    {
        cout << "升级VIP即可观看" << endl;
    }

    virtual void ticketMovie()
    {
        cout << "用券即可观看" << endl;
    }

private:
    VideoSite *pVideo;
};

// VIP代理类
class VIP : public VideoSite
{
public:
    VIP() { pVideo = new Fix(); }
    ~VIP() { delete pVideo; }

    virtual void freeMovie() //通过代理对象的freeMovie()访问真正委托类对象的freeMovie()
    {
        pVideo->freeMovie();
    }

    virtual void vipMovie()
    {
        pVideo->vipMovie();
    }

    virtual void ticketMovie()
    {
        cout << "用券即可观看" << endl;
    }

private:
    VideoSite *pVideo;
};

void watch(unique_ptr<VideoSite> &ptr)
{
    ptr->freeMovie();
    ptr->vipMovie();
    ptr->ticketMovie();
}

int main()
{
    unique_ptr<VideoSite> p1(new Free());
    unique_ptr<VideoSite> p2(new VIP());

    watch(p1);
    watch(p2);

    return 0;
}
