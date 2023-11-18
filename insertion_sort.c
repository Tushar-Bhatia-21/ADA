#include<stdio.h>
void printArray(int arr[],int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void insertionSort(int a[],int size)
{
    for(int step=1;step<size;step++)
    {
        int data=a[step];
        int j=step-1;

        while(data<a[j]&&j>=0)
        {
            a[j+1]=a[j];
            --j;
        }
        a[j+1]=data;
    }
}


int main() {
  int data[5];
  int x;
  printf("Tushar Bhatia\n");
  printf("A2305221202\n");
  printf("\nEnter the number of elements: ");
  scanf("%d",&x);
  for(int i=0;i<x;i++)
  {
      printf("\nEnter element: ");
      scanf("%d",&data[i]);
  }
  
  printf("Elements before sorting are\n");
  printArray(data, x);
  insertionSort(data, x);
  printf("Sorted array in ascending order:\n");
  printArray(data, x);
}