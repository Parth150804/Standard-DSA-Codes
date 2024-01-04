#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> iPair;

class TreeNode {
    public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

int Successor(TreeNode* root, int data) {
    int S = -1;
    while (root != nullptr) {
        if (root -> data > data) {
            S = root -> data;
            root = root -> left;
        }
        else {
            root = root -> right;
        }
    }
    return S;
}

void pre_order_iter(TreeNode* root) {
    stack<TreeNode*> stk;
    TreeNode* curr = root;

    while (curr != nullptr || !stk.empty()) {
        if (curr != nullptr) {
            std::cout << curr->data << " ";
            stk.push(curr->right); // Push right child first
            curr = curr->left;
        } else {
            curr = stk.top();
            stk.pop();
        }
    }
}

void in_order_iter(TreeNode* root) {
    stack<TreeNode*> stk;
    TreeNode* curr = root;

    while (curr != nullptr or !stk.empty()) {
        if (curr != nullptr) {
            stk.push(curr);
            curr = curr->left;
        } else {
            curr = stk.top();
            stk.pop();
            std::cout << curr->data << " ";
            curr = curr->right;
        }
    }
}

void post_order_iter(TreeNode* root) {
    stack<TreeNode*> stk;
    TreeNode* curr = root;
    TreeNode* last_visited = nullptr;

    while (curr != nullptr || !stk.empty()) {
        if (curr != nullptr) {
            stk.push(curr);
            curr = curr->left;
        } else {
            TreeNode* peek_node = stk.top();

            if (peek_node->right != nullptr && last_visited != peek_node->right) {
                // If the right subtree exists and hasn't been visited yet, traverse it.
                curr = peek_node->right;
            } else {
                // Otherwise, visit the current node and mark it as the last visited.
                std::cout << peek_node->data << " ";
                last_visited = peek_node;
                stk.pop();
            }
        }
    }
}

// Merge two sorted arrays
void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int left_half[n1];
    int right_half[n2];

    for (int i = 0; i < n1; i++) {
        left_half[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        right_half[i] = arr[middle + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (left_half[i] <= right_half[j]) {
            arr[k] = left_half[i];
            i++;
        } else {
            arr[k] = right_half[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left_half[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right_half[j];
        j++;
        k++;
    }
}

// Iterative merge sort using a stack
void mergeSort(int arr[], int n) {
    stack<pair<int, int>> s;

    s.push({0, n - 1});

    while (!s.empty()) {
        int left = s.top().first;
        int right = s.top().second;
        s.pop();

        if (left < right) {
            int middle = left + (right - left) / 2;
            s.push({left, middle});
            s.push({middle + 1, right});
            merge(arr, left, middle, right);
        }
    }
}

// Function to partition the array into two segments and return the pivot index
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Iterative Quick Sort using a stack
void quickSort(int arr[], int low, int high) {
    stack<pair<int, int>> s;
    s.push(make_pair(low, high));

    while (!s.empty()) {
        low = s.top().first;
        high = s.top().second;
        s.pop();

        int pivotIndex = partition(arr, low, high);

        if (pivotIndex - 1 > low) {
            s.push(make_pair(low, pivotIndex - 1));
        }

        if (pivotIndex + 1 < high) {
            s.push(make_pair(pivotIndex + 1, high));
        }
    }
}

// class Base {
//     public:
//     virtual ~Base() {
//         std::cout << "Base Destructor" << "\n";
//     }
// };

// class Derived : Base {
//     public:
//     ~Derived() {
//         std::cout << "Derived Destructor" << "\n";
//     }
// };

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if (preorder.size() == 0) {
        return nullptr;
    }
    else {
        TreeNode* root = new TreeNode(preorder[0]);

        int idx = 0;
        while (inorder[idx] != preorder[0]) {
            idx++;
        }

        vector<int> pre1, in1;
        for (int i = 1; i < idx + 1; i++) {
            pre1.push_back(preorder[i]);
            in1.push_back(inorder[i-1]);
        }
        vector<int> pre2, in2;
        for (int i = idx + 1; i < preorder.size(); i++) {
            pre2.push_back(preorder[i]);
            in2.push_back(inorder[i]);
        }

        root -> left = buildTree(pre1, in1);
        root -> right = buildTree(pre2, in2);
        return root;
    }
}

void inorder(TreeNode* root, vector<int>& v) {
    if (root == nullptr) {
        return;
    }
    else {
        inorder(root -> left, v);
        v.push_back(root -> data);
        inorder(root -> right, v);
    }
}

bool checkBST(TreeNode* root) {
	vector<int> v;
    inorder(root, v);
        
    for (int i = 0; i < v.size() - 1; i++) {
        if (v[i] >= v[i+1]) {
            return false;
        }
    }
    return true;
}

int sum(vector<int> v) {
    int sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    if (sum > 0) {
        return sum;
    }
    else {
        return 0;
    }
}

int maxSumBST(TreeNode* root) {
    vector<int> v;
    if (checkBST(root)) {
        inorder(root, v);
        int a = max(sum(v), maxSumBST(root -> left));
        return max(a, maxSumBST(root -> right));
    }
    else {
        return max(maxSumBST(root -> left), maxSumBST(root -> right));
    }
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    if (root == nullptr) {
        return ans;
    }

    queue<TreeNode*> Q;
    Q.push(root);

    while (!Q.empty()) {
        int levelSize = Q.size(); // Number of nodes at the current level
        vector<int> v; // Create a new vector for the current level

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = Q.front();
            Q.pop();
            v.push_back(node -> data);

            if (node -> left) {
                Q.push(node -> left);
            }
            if (node -> right) {
                Q.push(node -> right);
            }
        }
        
        ans.push_back(v); // Add the current level's vector to ans
    } 

    return ans;
}

// class Graph {
// private:
//     vector<vector<int>> adj_list;
// public:
//     Graph(int vertices, vector<vector<int>> edges) {
//         adj_list.resize(vertices);
//         for (int i = 0; i < edges.size(); i++) {
//             adj_list[edges[i][0]-1].push_back(edges[i][1]);
//             adj_list[edges[i][1]-1].push_back(edges[i][0]);            
//         }
//     }

//     void DFS_helper(int startvertex, unordered_set<int>& visited) {
//         visited.insert(startvertex);
//         for (int neighbour: adj_list[startvertex-1]) {
//             if (visited.find(neighbour) == visited.end()) {
//                 DFS_helper(neighbour, visited);
//             }
//         }
//     }

//     int min_number_of_roads(int no_of_vertices) {
//         unordered_set<int> visited;
//         int count = -1;
//         for (int i = 1; i <= no_of_vertices; i++) {
//             if (visited.find(i) == visited.end()) {
//                 DFS_helper(i, visited);
//                 count++;
//             }
//         }
//         return count;
//     }
// };

// class Graph_2 {
// private:
//     vector<vector<pair<int, int>>> adj_l;
//     int no_of_vertices;
// public:
//     Graph_2(int vertices, vector<vector<int>> edges) {
//         no_of_vertices = vertices;
//         adj_l.resize(vertices);
//         for (int i = 0; i < edges.size(); i++) {
//             adj_l[edges[i][0]-1].push_back(make_pair(edges[i][1], edges[i][2]));            
//         }
//     }

//     vector<int> pred_for_sp() {
//         vector<bool> visited(no_of_vertices, false);
//         vector<int> dist(no_of_vertices, INT_MAX);
//         priority_queue<int, vector<int>, greater<int>> pq;
//         vector<int> pred;
//         pred.resize(no_of_vertices);
//         dist[0] = 0;
//         pq.push(0);

//         while (!pq.empty()) {
//             int Curr = pq.top();
//             pq.pop();

//             if (visited[Curr]) continue;
//             visited[Curr] = true;

//             for (const pair<int, int> &p: adj_l[Curr]) {
//                 int alt = dist[Curr] + p.second;
//                 if (alt < dist[p.first - 1]) {
//                     dist[p.first - 1] = alt;
//                     pred[p.first - 1] = Curr+1;
//                     pq.push(p.first - 1);
//                 }
//             }
//         }
//         return pred;
//     }

//     int cost(int from, int to) {
//         for (int i = 0; i < adj_l[from-1].size(); i++) {
//             if (adj_l[from-1][i].first == to) {
//                 return adj_l[from-1][i].second;
//             }
//         }
//     }

//     vector<int> weights(vector<int>& predecessors) {
//         vector<int> ans;
//         int next = predecessors.size();
//         for (int i = predecessors.size() - 1; i > 0; i--) {
//             ans.push_back(cost(predecessors[i], next));
//             next = predecessors[i];
//         }
//         return ans;
//     }

//     int min_cost() {
//         vector<int> sp = pred_for_sp();
//         vector<int> w = weights(sp);
//         int mx = 0;
//         int sum = 0;

//         for (int i = 0; i < w.size(); i++) {
//             sum += w[i];
//             mx = max(mx, w[i]);
//         }
//         sum -= mx;
//         mx /= 2;
//         sum += mx;
//         return sum;
        
//     }
// };


// ## Prim's Algorithm

// Time complexity is O((E+V)logV)
// For weighted undirected graph

class Graph {
    int V;
    vector<vector<iPair>> adj;
public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void primMST();
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

// This one doesn't handle the case of disjoint graph

void Graph::primMST() {
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;    // min-heap

    int src = 0; // Start from the first vertex

    vector<int> key(V, INT_MAX); // Key values used to pick 'minimum weight edge' in cut
    vector<int> parent(V, -1);   // To represent set of vertices included in MST 

    vector<bool> inMST(V, false); // To keep track of vertices included in MST

    pq.push(make_pair(0, src));         // stores edge weight and vertex (pair) as said in video of graph theory
    key[src] = 0;                       

    // starting node will have parent as -1 and edge weight as 0

    while (!pq.empty()) {
        int u = pq.top().second;        // here u is the vertex
        pq.pop();

        inMST[u] = true;

        for (const auto &neighbor : adj[u]) {       // start checking neighbours of u
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }


    // Print the constructed MST
    cout << "Edges of Minimum Spanning Tree:\n";
    for (int i = 1; i < V; i++)
        cout << "Edge: " << parent[i] << " - " << i << " Weight: " << key[i] << "\n";
}


// class Graph {
// private:
//     int vertices;
//     vector<vector<int>> adjList;

// public:
//     Graph(int v) : vertices(v), adjList(v) {}

//     void addEdge(int v, int w) {
//         adjList[v].push_back(w);
//         adjList[w].push_back(v);
//     }

//     void BFS(int startVertex) {
//         vector<bool> visited(vertices, false);
//         queue<int> q;

//         visited[startVertex] = true;
//         q.push(startVertex);

//         while (!q.empty()) {
//             int currentVertex = q.front();
//             cout << currentVertex << " ";
//             q.pop();

//             for (int adjacentVertex : adjList[currentVertex]) {
//                 if (!visited[adjacentVertex]) {
//                     visited[adjacentVertex] = true;
//                     q.push(adjacentVertex);
//                 }
//             }
//         }
//     }
// };

// ## Kruskal's Algorithm

// Time complexity is O(|E|log|E|)

// class Graph {
//     int V;
//     vector<pair<int, pair<int, int>>> edges; // {weight, {src, dest}}
// public:
//     Graph(int V);
//     void addEdge(int u, int v, int w);
//     int kruskalMST();           // returns weight of min spanning tree
// };

// Graph::Graph(int V) {
//     this->V = V;
// }

// void Graph::addEdge(int u, int v, int w) {      // src, dest, weight
//     edges.push_back({w, {u, v}});               // {weight, {src, dest}}
// }

// // Find set of an element i
// int find(vector<int> &parent, int i) {
//     while (parent[i] != -1)
//         i = parent[i];         
//     return i;
// }

// // Union of two sets
// void unionSets(vector<int> &parent, int x, int y) {
//     int xset = find(parent, x);
//     int yset = find(parent, y);
//     parent[xset] = yset;
// }

// // Simple bubble sort for sorting edges based on weights
// void bubbleSort(vector<pair<int, pair<int, int>>> &arr) {
//     int n = arr.size();
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (arr[j].first > arr[j + 1].first) {
//                 swap(arr[j], arr[j + 1]);
//             }
//         }
//     }
// }

// int Graph::kruskalMST() {
//     bubbleSort(edges);

//     vector<int> parent(V, -1);
//     int mstWeight = 0;

//     for (auto edge : edges) {
//         int u = edge.second.first;          // src
//         int v = edge.second.second;         // dest
//         int w = edge.first;                 // weight

//         int setU = find(parent, u);
//         int setV = find(parent, v);

//         if (setU != setV) {
//             cout << "Edge: " << u << " - " << v << " Weight: " << w << "\n";
//             mstWeight += w;
//             unionSets(parent, setU, setV);
//         }
//     }

//     return mstWeight;
// }


// ## Bellman Ford

// struct Edge {
//     int src, dest, weight;
// };

// class Graph {
// public:
//     int V, E;
//     vector<Edge> edges;

//     Graph(int v, int e) : V(v), E(e) {}

//     void addEdge(int src, int dest, int weight) {
//         edges.push_back({src, dest, weight});
//     }

//     void bellmanFord(int src) {
//         vector<int> dist(V, INT_MAX);
//         dist[src] = 0;

//         // Relax all edges V-1 times
//         for (int i = 0; i < V - 1; i++) {
//             for (const Edge& edge : edges) {
//                 int u = edge.src;
//                 int v = edge.dest;
//                 int w = edge.weight;

//                 if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
//                     dist[v] = dist[u] + w;
//                 }
//             }
//         }

//         // Check for negative weight cycles
//         for (const Edge& edge : edges) {
//             int u = edge.src;
//             int v = edge.dest;
//             int w = edge.weight;

//             if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
//                 std::cout << "Graph contains negative weight cycle.\n";
//                 return;
//             }
//         }

//         // Print the shortest distances
//         std::cout << "Vertex   Distance from Source\n";
//         for (int i = 0; i < V; ++i) {
//             std::cout << i << "\t\t" << dist[i] << "\n";
//         }
//     }
// };

int main() {
    // Create a graph given in the example

    // int V, E;
    // cout << "Enter the number of vertices and edges: ";
    // cin >> V >> E;

    // Graph graph(V, E);

    // cout << "Enter the edges (source, destination, weight):\n";
    // for (int i = 0; i < E; ++i) {
    //     int src, dest, weight;
    //     cin >> src >> dest >> weight;
    //     graph.addEdge(src, dest, weight);
    // }

    // int source;
    // cout << "Enter the source vertex: ";
    // cin >> source;

    // graph.bellmanFord(source);
/*
    int V = 5;
    Graph g(V);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 8);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 5);
    g.addEdge(1, 4, 7);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 4, 4);

    cout << "Edges of Minimum Spanning Tree:\n";
    int mstWeight = g.kruskalMST();
    cout << "Total Weight of MST: " << mstWeight << "\n";
*/

/*
    int V = 5;
    Graph g(V);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 8);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 5);
    g.addEdge(1, 4, 7);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 4, 4);

    g.primMST();
*/

/*
    Graph graph(8);

    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 3, 4);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 4, 0);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 5, 8);
    graph.addEdge(3, 5, 2);
    graph.addEdge(3, 6, 7);
    graph.addEdge(4, 5, 1);
    graph.addEdge(4, 7, 8);
    graph.addEdge(5, 7, 9);
    graph.addEdge(5, 6, 6);
    graph.addEdge(6, 7, 12);

    graph.primMST();
*/

    // TreeNode* root = new TreeNode(5);
    // TreeNode* n1 = new TreeNode(0);
    // TreeNode* n2 = new TreeNode(1);
    // TreeNode* n3 = new TreeNode(3);
    // TreeNode* n4 = new TreeNode(4);
    // TreeNode* n5 = new TreeNode(6);
    // TreeNode* n6 = new TreeNode(7);
    // TreeNode* n7 = new TreeNode(8);

    // root -> left = n2;
    // n2 -> left = n1;
    // n2 -> right = n3;
    // root -> right = n5;
    // n5 -> right = n6;
    // n6 -> right = n7;
    // n5 -> left = n4;  

    // pre_order_iter(root);
    // std::cout << "\n";
    // in_order_iter(root);  
    // std::cout << "\n";
    // post_order_iter(root);

// vector<int> preorder = {5,3,2,4,6,7};
// vector<int> inorder = {2,3,4,5,6,7};
// TreeNode* tree = buildTree(preorder, inorder);

// pre_order_iter(tree);
// std::cout << "\n";
// in_order_iter(tree);

}