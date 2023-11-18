#include<stdio.h>
int main()
{
    int a[100];
    int temp=0;
    int size=0;
    printf("\nTushar Bhatia\n");
    printf("A2305221202\n");
    printf("Enter the size of the array: ");
    scanf("%d",&size);
    for(int i=0;i<size;i++)
    {
        printf("Enter the value for A[%d]: ",i);
        scanf("%d",&a[i]);
    }

    for(int i=0;i<size-1;i++)
    {
        for(int j=0;j<size-1;j++)
        {
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    printf("\nList after sorting:\n");
    
    for (int i=0; i<size; i++)
    {
        printf("%d ",a[i]);
    }
}