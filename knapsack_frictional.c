#include<stdio.h>
#include<stdlib.h>
struct item
{
    int weight;
    int profit;
    float ratio;
};

void swap(struct item *a,struct item *b)
{
    struct item temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

int partition(struct item *arr, int low, int high) {
    float pivot = arr[high].ratio;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].ratio >= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(struct item *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void sort(struct item *arr, int n) {
    quickSort(arr, 0, n - 1);
}

float knapsack(struct item *arr,int n,int capacity)
{
    int i;
    float profit=0.0;
    for(i=0;i<n;i++)
    {
        if(arr[i].weight<=capacity)
        {
            profit+=arr[i].profit;
            capacity-=arr[i].weight;
        }
        else
        {
            profit+=arr[i].ratio*capacity;
            break;
        }
    }
    return profit;
}
int main()
{
    int n,i,capacity;
    float max_profit;
    printf("\nTushar Bhatia\n");
    printf("A2305221202\n");
    printf("Enter the number of items: ");
    scanf("%d",&n);
    struct item *arr=(struct item *)malloc(n*sizeof(struct item));
    printf("Enter the weight and profit of each item:\n");
    for(i=0;i<n;i++)
    {
        printf("Item %d:\n",i+1);
        printf("Weight: ");
        scanf("%d",&arr[i].weight);
        printf("Profit: ");
        scanf("%d",&arr[i].profit);
        arr[i].ratio=(float)arr[i].profit/arr[i].weight;
    }
    printf("Enter the capacity of knapsack: ");
    scanf("%d",&capacity);
    sort(arr,n);
    max_profit=knapsack(arr,n,capacity);
    printf("Maximum profit: %f\n",max_profit);
    return 0;
}
