#include <stdio.h>

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve the 0/1 knapsack problem using dynamic programming
int knapsack(int values[], int weights[], int n, int capacity) {
    int dp[n + 1][capacity + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

int main() {
    int capacity=0;
    int N=0;
    int weights[1000];
    int values[1000];
    printf("Enter the number of items: ");
    scanf("%d", &N);
    for(int i=0;i<N;i++)
    {
        printf("Enter the value I[%d]: ",i+1);
        scanf("%d", &values[i]);
        printf("Enter the weights W[%d]: ",i+1);
        scanf("%d", &weights[i]);
    }
    printf("Enter the capacity of knapsack: ");
    scanf("%d", &capacity);

    int max_value = knapsack(values, weights, N, capacity);
    printf("Tushar Bhatia\n");
    printf("A2305221202");
    printf("\nMaximum value that can be obtained: %d\n", max_value);

    return 0;
}
