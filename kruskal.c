#include <stdio.h>
#include <stdlib.h>

struct edge {
    int src;
    int dest;
    int weight;
};

struct graph {
    int v;
    int e;
    struct edge *edges;
};

struct graph *create_graph(int v, int e) {
    struct graph *g = (struct graph *)malloc(sizeof(struct graph));
    g->v = v;
    g->e = e;
    g->edges = (struct edge *)malloc(e * sizeof(struct edge));
    return g;
}

void swap(struct edge *a, struct edge *b) {
    struct edge temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct edge *arr, int low, int high) {
    int pivot = arr[high].weight;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].weight <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(struct edge *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void sort(struct edge *arr, int n) {
    quickSort(arr, 0, n - 1);
}

int find(int *parent, int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void unionSets(int *parent, int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

void kruskal(struct graph *g) {
    int *parent = (int *)malloc(g->v * sizeof(int));
    int i, j;
    for (i = 0; i < g->v; i++)
        parent[i] = -1;
    sort(g->edges, g->e);
    struct edge *result = (struct edge *)malloc((g->v - 1) * sizeof(struct edge));
    int e = 0;
    i = 0;
    while (e < g->v - 1) {
        struct edge next_edge = g->edges[i++];
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);
        if (x != y) {
            result[e++] = next_edge;
            unionSets(parent, x, y);
        }
    }
    printf("Following are the edges in the constructed MST:\n");
    for (i = 0; i < e; i++)
        printf("%d -- %d == %d\n", result[i].src + 1, result[i].dest + 1, result[i].weight);
    free(parent);
    free(result);
}

int main() {
    int v, e, i;
    printf("\nTushar Bhatia\n");
    printf("A2305221202\n");
    printf("Enter the number of vertices: ");
    scanf("%d", &v);
    printf("Enter the number of edges: ");
    scanf("%d", &e);
    struct graph *g = create_graph(v, e);
    printf("Enter the source, destination, and weight of each edge:\n");
    for (i = 0; i < e; i++) {
        printf("Enter source, destination, and weight for edge %d: ", i + 1);
        scanf("%d %d %d", &g->edges[i].src, &g->edges[i].dest, &g->edges[i].weight);
    }
    kruskal(g);

    // Free allocated memory
    free(g->edges);
    free(g);

    return 0;
}
