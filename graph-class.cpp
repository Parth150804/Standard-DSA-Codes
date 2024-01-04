#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// assuming undirected edges                                 
class Graph {
	private:
		// map from vertices --> set of vertices  (kind of adjacency list )
		std::unordered_map<int, std::unordered_set<int> > adjList;
	public:
		// Add a vertex to the graph                                         
	void addVertex(int vertex) {
		if (adjList.find(vertex) == adjList.end()) {
			// add the vertex -> empty set entry                             
			adjList[vertex] = std::unordered_set<int>();
		}
	}


	void addEdge(int vertex1, int vertex2) {
		addVertex(vertex1);
		addVertex(vertex2);
		adjList[vertex1].insert(vertex2);
		adjList[vertex2].insert(vertex1); // since it's undirected 
	}

	// Remove an undirected edge between two vertices                    
	void removeEdge(int vertex1, int vertex2) {
		if (adjList.find(vertex1) != adjList.end() &&
			adjList.find(vertex2) != adjList.end()) {
			adjList[vertex1].erase(vertex2);
			adjList[vertex2].erase(vertex1);
		}
	}

	// DFS traversal starting from a given vertex                        
	void DFS(int startVertex) {
		std::unordered_set<int> visited;
		DFSUtil(startVertex, visited);
	}
	
	void DFSUtil(int vertex, std::unordered_set<int>& visited) {
		std::cout << vertex << " ";
		visited.insert(vertex);
		
		for (int neighbor : adjList[vertex]) {
			if (visited.find(neighbor) == visited.end()) {    // if neighbour is not visited, perform DFS
				DFSUtil(neighbor, visited);
			}
		}
	}
  
};

int main(){
	Graph g;
	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addVertex(4);
	g.addVertex(5);
	
	g.addEdge(1,2);
	g.addEdge(1,3);
	g.addEdge(1,4);
	g.addEdge(2,5);
	g.addEdge(3,4);
	g.addEdge(3,5);

	g.DFS(1);
	
	return 0; 
}
