#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <omp.h>

const int INF = INT_MAX; 

class Graph {
private:
    std::vector<std::vector<int>> adjMatrix;
    int V; 

public:
    Graph(int V) : V(V) {
        adjMatrix.resize(V, std::vector<int>(V, INF));
        for (int i = 0; i < V; i++) {
            adjMatrix[i][i] = 0; 
        }
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
    }

    int findOptimalMeetingPoint() {
        std::vector<std::vector<int>> dist = adjMatrix;

        // Floyd-Warshall algorithm
        for (int k = 0; k < V; k++) {
	  // #pragma omp parallel for
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
	// you have obtained all pairs shortest paths
	
        int optimalV = -1;
        int minMaxDist = INF;
	/*
	  we are minimizing the "worst-case" travel time for
	  any individual traveling to the meeting point. Specifically,
	  for each potential meeting point, we determine the maximum
	  distance from that point to all other points. The optimal
	  meeting point is the one for which this maximum distance is
	  minimized.

	  This approach ensures that no individual has to travel more
	  than a certain distance, and this distance is as small as
	  possible. It does not optimize the total travel distance
	  over all vertices. If you wanted to optimize the total
	  travel distance, the approach would be different: you'd sum
	  up the distances from a potential meeting point to all other
	  points and then choose the point for which this sum is
	  minimized.
	 */
	//#pragma omp parallel for
	// for each vertex i, you want to find the furthest reachable vertex
	for (int i = 0; i < V; i++) {
            int currentMaxDist = 0;
            for (int j = 0; j < V; j++) {
                if (i != j) {
                    currentMaxDist = std::max(currentMaxDist, dist[i][j]);
                }
            }
	    //   #pragma omp critical
	    //{
            if (currentMaxDist < minMaxDist) {
                minMaxDist = currentMaxDist;
                optimalV = i;
            }
	    //}
        }

        return optimalV;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 3, 10);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 1);

    int meetingPoint = g.findOptimalMeetingPoint();
    std::cout << "The optimal meeting point is node: " << meetingPoint << std::endl;

    return 0;
}
