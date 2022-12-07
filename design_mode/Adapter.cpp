#include<iostream>
#include<memory>
using namespace std;

//适配器
class VGA 
{
public:
	virtual void play() = 0;
};

class HDMI
{
public:
	virtual void play() = 0;
};


class TV01: public VGA
{
public:
	void play()
	{
		cout << "通过VGA接口连接投影仪,进行视频播放" << endl;
	}
};

class TV02 : public HDMI
{
public:
	void play()
	{
		cout << "通过HDMI接口连接投影仪,进行视频播放" << endl;
	}
};


class Computer
{
public: 
	//电脑只支持VGA接口
	void playVGA(VGA* pVGA)
	{
		pVGA->play();
	}
	void playHDMI(HDMI* pHDMI)
	{
		pHDMI->play();
	}
};


//适配器
class VGA_to_HDMI :public VGA //适配器继承了VGA 所以playVideo()参数pVGA指向适配器对象时                           
{                           //调用的是适配器对象的play()
public:
	VGA_to_HDMI(HDMI* p) :pHdmi(p) {}
	void play() 
	{
		pHdmi->play();
	}

private:
	HDMI* pHdmi; 
};

class HDMI_to_VGA :public HDMI
{
public:
	HDMI_to_VGA(VGA* p) :pVGA(p) {}
	void play()
	{
		pVGA->play();
	}

private:
	VGA* pVGA;
};



int main()
{
    /*
    VGA_to_HDMI的基类指针HDMI指向HDMI的派生类TV02
    VGA_to_HDMI是VGA的派生类，继承它的play虚函数并重写该函数即调用TV02的play
    */
	Computer computer; //提供接口的对象
	computer.playVGA(new VGA_to_HDMI(new TV02())); //把VGA接口转换成HDMI接口
	computer.playHDMI(new HDMI_to_VGA(new TV01())); //把HDMI接口转换成VGA接口
	return 0;
}

