#include<stdio.h>
void swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void Selection_sort(int a[],int size)
{
    for(int step=0;step<size-1;step++)
    {
        int min_idx=step;
        for(int i=step+1;i<size;i++)
        {
            if(a[i]<a[min_idx])
            {
                min_idx=i;
            }
        }
        swap(&a[min_idx],&a[step]);
    }
}

void print_array(int a[],int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}

int main()
{
    int data[5];
    int size;
    printf("\nTushar Bhatia\n");
    printf("\nA2305221202\n");
    printf("Enter the number of elements: ");
    scanf("%d",&size);
    for(int i=0;i<size;i++)
    {
        printf("Enter element A[%d]: ",i);
        scanf("%d",&data[i]);
    }
    printf("\nElements before sorting are: ");
    print_array(data,size);
    
    Selection_sort(data,size);

    printf("\nElements after sorting are: ");
    print_array(data,size);
    return 0;
}
