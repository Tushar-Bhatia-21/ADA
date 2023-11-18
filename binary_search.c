#include<stdio.h>

void binary_search(int arr[],int size)
{
    
    int el1,lb,ub,mid; //lb=Lower bound, ub= Upper bound, el1= element to be searched
   
    printf("\nEnter element to search: ");
    scanf("%d",&el1);

    lb=0;
    ub= size-1;
    mid=(lb+ub)/2;
    int location = -1;

    while (lb<=ub)
    {
        if (arr[mid]==el1)
        {
            printf("Element is present at: %d",mid+1);
            location=mid;
            break;
        }
        else if (arr[mid]>el1)
        {
            ub=mid-1;
        }
        else
        {
            lb=mid+1;
        }
        
        mid = (lb+ub)/2;
    }
    if (location == -1)
    {
        printf("Element not found");
    }
}
 int main()
{
    printf("\nTushar Bhatia\n");
    printf("A2305221202\n");
    int A[10],size,ch;
    printf("Enter the size of array:");
    scanf("%d",&size);
    for (int i=0; i<size; i++)
    {

        printf("Enter value for A[%d]: ",i);
        scanf("%d",&A[i]);
    }
    binary_search(A,size);
    return 0;
}