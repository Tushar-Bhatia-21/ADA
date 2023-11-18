//Dijkstra's algorithm
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define MAX 100
#define INF INT_MAX
int n;
int adj[MAX][MAX];
int dist[MAX];
int visited[MAX];
int parent[MAX];
int minDistance() {
    int min = INF, min_index;
    for (int v = 0; v < n; v++)
        if (visited[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}
void printPath(int j) {
    if (parent[j] == -1)
        return;
    printPath(parent[j]);
    printf("%d ", j);
}
void printSolution() {
    int src = 0;
    printf("Vertex\t\tDistance\tPath");
    for (int i = 1; i < n; i++) {
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        printPath(i);
    }
}
void dijkstra(int src) {
    for (int i = 0; i < n; i++)
        dist[i] = INF, visited[i] = 0, parent[i] = -1;
    dist[src] = 0;
    for (int count = 0; count < n - 1; count++) {
        int u = minDistance();
        visited[u] = 1;
        for (int v = 0; v < n; v++)
            if (!visited[v] && adj[u][v] && dist[u] != INF && dist[u] + adj[u][v] < dist[v])
                parent[v] = u, dist[v] = dist[u] + adj[u][v];
    }
    printSolution();
}
int main() {
    printf("\nTushar Bhatia\n");
    printf("\nA2305221202\n");
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);
    dijkstra(0);
    return 0;
}