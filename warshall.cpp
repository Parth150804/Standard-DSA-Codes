#include <iostream>
#include <vector>
#include <limits.h>

const int INF = INT_MAX; // A large value to represent infinity

class Graph {
private:
    std::vector<std::vector<int>> adjMatrix;
    int V; // Number of vertices

public:
    Graph(int V) : V(V) {
        adjMatrix.resize(V, std::vector<int>(V, INF));     // forming a V x V matrix 
        for (int i = 0; i < V; i++) {
            adjMatrix[i][i] = 0;        // distance from source to source = 0
        }
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
    }

    void floydWarshall() {
        std::vector<std::vector<int>> dist = adjMatrix;

        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF &&
			            dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        printSolution(dist);
    }

    void printSolution(const std::vector<std::vector<int>>& dist) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == INF) {
                    std::cout << "INF ";
                } else {
                    std::cout << dist[i][j] << "   ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 3, 10);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 1);

    g.floydWarshall();

    return 0;
}
