#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
using namespace std;


// 基数排序代码
// 时间复杂度：O(nd)  空间复杂度:O(n)  稳定性：稳定的排序
void RadixSort(int arr[], int size)
{
	//找最大值，获取位数
	int maxData=arr[0];
	for(int i=1;i<size;i++)
	{
		if(maxData<arr[i])
		{
			maxData=arr[i];
		}
	}
	int len=to_string(maxData).size();

	vector<vector<int>> vecs;
	int mod=10;
	int dev=1;

	for(int i=0;i<len;mod*=10,dev*=10,i++)// O(d) d：数据的长度
	{
		vecs.resize(20);// 20个桶，为了能处理负数 -9 - 9
		for(int j=0;j<size;j++)
		{
			// 得到当前元素第i个位置的数字
			int index=arr[j]%mod/dev+10;
			vecs[index].push_back(arr[j]);
		}
		// 依次遍历所有的桶，把元素拷贝回原始的数组当中
		int idx=0;
		for(auto vec:vecs)
		{
			for(int v:vec)
			{
				arr[idx++]=v;
			}
		}
		vecs.clear();
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

	arr[9] = -123;
	arr[6] = -38;

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	RadixSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}





