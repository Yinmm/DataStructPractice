#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <stdio.h>
int count = 0;//全局变量
int feibo(int n){
	int pr1 ;
	int pr2 ;
	int result;
	result = pr1 =1;
	while (n>2)
	{
		pr2 = pr1;
		pr1 = result;
		result = pr2+pr1;
		// result = pr1+pr2;
		// pr1 = pr2;
		// pr2 = result;
		n--;
	}
	return result;

}


int fib(int n)
{
    int result;
    int pre_result;
    int next_older_result;
    result = pre_result = 1;
    while (n > 2)
    {
        n -= 1;
        next_older_result = pre_result;
        pre_result = result;
        result = pre_result + next_older_result;
    }
    return result;
}



#include <stdio.h>
void bubble_sort(int arr[],int sz)
{
    int i = 0;
    for (i = 0; i < sz - 1; i++)
    {
        int j = 0;
        for (j = 0; j < sz - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}



int main()
{
	// int arr[] = { 3,1,7,5,8,9,0,2,4,6 };
    // bubble_sort(arr,sizeof(arr) / sizeof(arr[0]));//是否可以正常排序？
    // for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    // {
    //     printf("%d ", arr[i]);
    // }
	printf("%d ", sizeof(int*));
	printf("%d ", sizeof(int*));
	printf("%d ", sizeof(long*));
	printf("%d ", sizeof(float*));
	printf("%d ", sizeof(char*));

	


    system("pause");
	return 0;
}