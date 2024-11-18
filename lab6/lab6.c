/*Compare the performance of Dijkstra and Bellman ford algorithm for the single 
source shortest path problem.*/  

#include <stdio.h>
#include <limits.h>

#define V 5  // Number of vertices in graph

//  find the vertex with the minimum distance value
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

//  implement of  Dijkstras algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V]; 
    int sptSet[V]; 

    // Initialize all distances as infinate 
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    dist[src] = 0; 

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet); // Select the vertex with the minimum distance
        sptSet[u] = 1; // Mark the vertex as processed

        // Update the distance value of the adjacent vertices
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Dijkstra's Algorithm:\n");
    for (int i = 0; i < V; i++) {
        printf("Vertex %d -> Distance: %d\n", i, dist[i]);
    }
}

int main() {
    // Graph represented as an adjacency matrix
    int graph[V][V] = {
        {0, 10, 0, 30, 100},
        {10, 0, 50, 0, 0},
        {0, 50, 0, 20, 10},
        {30, 0, 20, 0, 60},
        {100, 0, 10, 60, 0}
    };

    dijkstra(graph, 0);  // Call Dijkstra starting from vertex 0
    return 0;
}
