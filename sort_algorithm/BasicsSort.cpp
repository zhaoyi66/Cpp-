#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 冒泡排序算法
void BubbleSort(int arr[],int size)
{
    for(int i=0;i<size;i++)
    {
    bool flag=false;
    for(int j=1;j<size-i;j++)
    {
        if(arr[j-1]>arr[j])
        {
            int temp;
            temp=arr[j-1];
            arr[j-1]=arr[j];
            arr[j]=temp;
            flag=true;
        }
    }
    if(!flag)
    {
        return ;
    }

    }
}


// 选择排序算法
void ChoiceSort(int arr[],int size)
{
    for(int i=0;i<size;i++)
    {
    int res=i;
    for(int j=i+1;j<size;j++)
    {
        if(arr[j]<arr[res])
        {
            res=j;
        }
    }
    int temp=arr[res];
    arr[res]=arr[i];
    arr[i]=temp;
    }
}


// 插入排序算法
void InsertSort(int arr[],int size)
{
    for(int i=1;i<size;i++)
    {
        int val=arr[i];
        int j=i-1;
        for(;j>=0;j--)
        {
            if(arr[j]<=val)
            {
                break;
            }
            arr[j+1]=arr[j];
        }
        arr[j+1]=val;
    }
}




// 希尔排序
void ShellSort(int arr[],int size)
{
    for(int gap=size/2;gap>0;gap/=2)
    {
        for(int i=gap;i<size;i++)
        {
            int val=arr[i];
            int j=i-gap;
            for(;j>=0;j-=gap)
            {
                if(arr[j]<=val)
                {
                    break;
                }
                arr[j+gap]=arr[j];
            }
            arr[j+gap]=val;
        }
    }
    
}

void ShellSort(int arr[],int size)
{
    for(int gap=size/2;gap>0;gap/=2)
    {
        for(int i=gap;i<size;i++)
        {
            int val=arr[i];
            int j=i-gap;
            for(;j>=0;j-=gap)
            {
                if(arr[j]<=val)
                {
                    break;
                }
                arr[j+gap]=arr[j];
            }
            arr[j+gap]=val;
        }
    }
}




int main()
{
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100 + 1;
	}

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	ShellSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}


























