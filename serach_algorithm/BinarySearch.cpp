#include<iostream>
using namespace std;


// 二分搜索非递归实现,左闭右开
int BinarySearch01(int arr[],int size,int val)
{
    int left=0,right=size;
    while (left<right)
    {
        int mid=(left+right)/2;
        if(arr[mid]==val)
        {
            return mid;
        }
        else if(arr[mid]<val)
        {
            left=mid+1;
        }
        else
        {
            right=mid;
        }
    }
    return -1;
}




// 二分搜索递归代码,左闭右开
int BinarySearch02(int arr[],int i,int j,int val)
{
    if(i>j)
    return -1;
    int mid=(i+j)/2;
    if(arr[mid]==val)
    {
        return middle;
    }
    else if(arr[mid]<val)
    {
        return BinarySearch02(arr,mid+1,j,val);
    }
    else if(arr[mid]>val)
    {
        return BinarySearch02(arr,i,mid,val);
    }
}





int main()
{
    int arr[] = {12, 25, 34, 39, 45, 57, 63, 78, 82, 96, 100};
    int size = sizeof arr / sizeof arr[0];
    cout << BinarySearch01(arr, size, 39) << endl;
    cout << BinarySearch01(arr, size, 45) << endl;
    cout << BinarySearch01(arr, size, 12) << endl;
    cout << BinarySearch01(arr, size, 64) << endl;
}



























