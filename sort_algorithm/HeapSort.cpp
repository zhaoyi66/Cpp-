#include<iostream>
#include<time.h>
using namespace std;


void siftDown(int arr[],int i,int size)
{
    int val=arr[i];

    while (i<size/2)
    {
        int child=i*2+1;
        if(child+1<size&&arr[child+1]>arr[child])
        {
            child=child+1;
        }

        if(arr[child]>val)
        {
            arr[i]=arr[child];
            i=child;
        }
        else
        {
            break;
        }
    }
    arr[i]=val;
}

// 堆排序
void HeapSort(int arr[],int size)
{
    int n=size-1;
    // 从第一个非叶子节点，所有的父节点都会进行堆的下沉，之后根节点成为最大的元素
    for(int i=(n-1)/2;i>=0;i--)
    {
        siftDown(arr,i,size);
    }

    // 把堆顶元素和末尾元素进行交换，从堆顶开始进行下沉操作
	for(int i=n;i>0;i--)
    {
        int tmp=arr[0];
        arr[0]=arr[i];
        arr[i]=tmp;

        siftDown(arr,0,i);//调整参与的元素的个数,大的元素放在数组的最后，不参与下沉
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

	HeapSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}

















