#include <stdio.h>

int main()
{   
    printf("\nTushar Bhatia\n");
    printf("A2305221202\n");
    int ctr=0,ntr=0;;
    int n,key;
    int arr[200];
    printf("Enter the size of elements: ");
    scanf("%d", &n);

    printf("Enter the number of elements: ");
    for(int i=0;i<n;i++)
    {   
        scanf("%d", &arr[i]);
    }

    printf("Enter the element to be searched: ");
    scanf("%d", &key);
        for(int i=0;i<n;i++)
        {
            
            if(arr[i]==key)
            {
                printf("Element found at %d", i+1);
                break;
            }
            else
            {
                ntr++; //a variable to count the number of times if the condition was false.
            }

        }
        if (ntr==n) //If the counter variable is equal to the size of array, it means loop was executed n times
                    //so we can say that element was not found in the array.
        {   
            printf("Element not found");
        }
}
