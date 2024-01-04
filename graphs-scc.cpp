#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
  int V;
  vector<int>* adj;
  int time;
  stack<int> Stack;
  vector<int> ids, low, inStack;
  
  void sccDFS(int v);
  
public:
  Graph(int V);
  ~Graph();
  void addEdge(int v, int w);
  void scc();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new vector<int>[V];       // array of vectors (can use vector of vector)
    ids = vector<int>(V, -1);       // node ids
    low = vector<int>(V, -1);       // low link values
    inStack = vector<int>(V, 0);    // boolean values for presence of node in a stack
    time = 0;                       // to keep track of next node id which can be assigned (in next DFS traversal)
}

Graph::~Graph() {
    delete[] adj;
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::sccDFS(int u) {
    ids[u] = low[u] = time++;       // in constructor, time is initialized from 0
    Stack.push(u);
    inStack[u] = 1;

    for (int v : adj[u]) {
        if (ids[v] == -1) {
	        sccDFS(v); // backtrack from v's exploration
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], ids[v]);

	    /*
	      v.lowlink := min(v.lowlink, w.index) is the correct way
	      to update v.lowlink if w is on stack. Because w is on
	      the stack already, (v, w) is a back-edge in the DFS tree
	      and therefore w is not in the subtree of v. Because
	      v.lowlink takes into account nodes reachable only
	      through the nodes in the subtree of v we must stop at w
	      and use w.index instead of w.lowlink
	    */

        }
    } // for loop for LL value computation has ended here. 

    // SCC computation begins
    // I am in DFS(u) 
    int w = 0;
    // u is the start of an SCC
    // Print the SCC and remove them from the stack
    if (low[u] == ids[u]) {
        while (Stack.top() != u) {
            w = Stack.top();
            cout << w << " ";
            inStack[w] = 0;
            Stack.pop();
        }
        w = Stack.top();
        cout << w << "\n";
        inStack[w] = 0;
        Stack.pop();
    }
}
    // Convince yourself of the correctness iof this LL update mechanism
    // Find the loop invariants for the SCCDFS computation

void Graph::scc() {
    for (int i = 0; i < V; i++) {
        if (ids[i] == -1) {     // if node is unvisited, perform sccDFS on it
            sccDFS(i);
        }
    }
}

int main() {
    // Example usage:           // NOTE THAT IT IS A DIRECTED GRAPH
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);
    g.scc();
/*
    Graph gr(7);
    gr.addEdge(6, 4);
    gr.addEdge(4, 1);
    gr.addEdge(1, 0); 
    gr.addEdge(0, 1);
    gr.addEdge(2, 0);
    gr.addEdge(3, 2);
    gr.addEdge(2, 3);
    gr.addEdge(5, 3);
    gr.addEdge(5, 6);
    gr.addEdge(4, 3);
    gr.addEdge(4, 5);
    gr.scc();
*/
    return 0;
}
