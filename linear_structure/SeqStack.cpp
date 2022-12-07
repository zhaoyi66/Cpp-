#include<iostream>
using namespace std;

//顺序栈->数组实现
#if 1
class SeqStack
{
private:
   int* mpStack;
   int mtop; // 栈顶位置
   int mcap;// 栈空间大小

   void expand(int size)
   {
        int* p=new int[size];
        for(int i=0;i<mtop;i++)
        {
            p[i]=mpStack[i];
        }
        delete[] mpStack;
        mpStack=p;
        mcap=size;
   }
public:
    SeqStack(int size=10)
    :mtop(0),mcap(size),mpStack(new int[size])
    {}
    ~SeqStack()
    {
        delete[] mpStack;
        mpStack=nullptr;
    }

    // 入栈
    void push(int val)
    {
        if(mtop==mcap)
        {
            expand(2*mcap);
        }
        mpStack[mtop++]=val;
    }
    // 出栈
    void pop()
    {
        if(mtop==0)
            throw "stack is empty";
        mtop--;
    }
    // 获取栈顶元素
    int top()const
    {
        if(mtop==0)
            throw "stack is empty";
        return mpStack[mtop-1];
    }
    //栈空
    bool empty()const
    {
        return mtop==0;
    }
    int size()const{return mtop;}
};



int main()
{
	int arr[] = { 12,4,56,7,89,31,53,75 };
	SeqStack s;
	
	for (int v : arr)
	{
		s.push(v);
	}

	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}

#endif

























