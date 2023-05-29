#include<iostream>
#include<omp.h>
#include<stack>
#include<queue>

using namespace std;

class TreeNode{
    public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x){
        val = x;
        left = NULL;
        right = NULL;
    }
};

void pBFS(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int qs = q.size();
        #pragma omp parallel for
        for(int i = 0; i < qs; i++){
            TreeNode* node;
            #pragma omp critical
            {
                node = q.front();
                cout << node->val << " ";
                q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
    }
}

void pDFS(TreeNode* root){
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()){
        int ss = s.size();
        #pragma omp parallel for
        for(int i = 0; i < ss; i++){
            TreeNode* node;
            #pragma omp critical
            {
                node = s.top();
                cout << node->val << " ";
                s.pop();
                if(node->right) s.push(node->right);
                if(node->left) s.push(node->left);
            }
        }
    }
}


int main(){
    // Construct Tree
    TreeNode* tree = new TreeNode(1);
    tree->left = new TreeNode(2);
    tree->right = new TreeNode(3); 
    tree->left->left = new TreeNode(4);
    tree->left->right = new TreeNode(5);
    tree->right->left = new TreeNode(6);
    tree->right->right = new TreeNode(7);

    /*
    Our Tree Looks like this:
                1
            2       3
        4     5   6    7
        
    */

    cout << "Parallel BFS: ";
    pBFS(tree);
    cout << "\n";
    cout << "Parallel DFS: ";
    pDFS(tree);
}


// using openmp =================

#include <iostream>
#include <queue>
#include <stack>
#include <omp.h>

// Define the number of threads to be used
#define NUM_THREADS 4

// Function for parallel Breadth First Search (BFS)
void parallelBFS(int startNode, const std::vector<std::vector<int>>& graph, std::vector<bool>& visited) {
    std::queue<int> bfsQueue;
    bfsQueue.push(startNode);
    visited[startNode] = true;

    while (!bfsQueue.empty()) {
        int currentNode = bfsQueue.front();
        bfsQueue.pop();

        // Process the current node
        std::cout << "BFS: Visiting Node " << currentNode << " on Thread " << omp_get_thread_num() << std::endl;

        // Enqueue adjacent nodes
        #pragma omp parallel for shared(graph, visited, bfsQueue)
        for (size_t i = 0; i < graph[currentNode].size(); ++i) {
            int adjacentNode = graph[currentNode][i];
            if (!visited[adjacentNode]) {
                visited[adjacentNode] = true;
                bfsQueue.push(adjacentNode);
            }
        }
    }
}

// Function for parallel Depth First Search (DFS)
void parallelDFS(int startNode, const std::vector<std::vector<int>>& graph, std::vector<bool>& visited) {
    std::stack<int> dfsStack;
    dfsStack.push(startNode);
    visited[startNode] = true;

    while (!dfsStack.empty()) {
        int currentNode = dfsStack.top();
        dfsStack.pop();

        // Process the current node
        std::cout << "DFS: Visiting Node " << currentNode << " on Thread " << omp_get_thread_num() << std::endl;

        // Push unvisited adjacent nodes to the stack
        #pragma omp parallel for shared(graph, visited, dfsStack)
        for (size_t i = 0; i < graph[currentNode].size(); ++i) {
            int adjacentNode = graph[currentNode][i];
            if (!visited[adjacentNode]) {
                #pragma omp critical
                {
                    visited[adjacentNode] = true;
                    dfsStack.push(adjacentNode);
                }
            }
        }
    }
}

int main() {
    // Example graph represented as an adjacency list
    std::vector<std::vector<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1, 6},
        {2},
        {4}
    };

    std::vector<bool> visited(graph.size(), false);

    // Parallel Breadth First Search (BFS)
    std::cout << "Parallel BFS" << std::endl;
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp single nowait
        parallelBFS(0, graph, visited);
    }

    // Reset visited array for parallel DFS
    std::fill(visited.begin(), visited.end(), false);

    // Parallel Depth First Search (DFS)
    std::cout << "\nParallel DFS" << std::endl;
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp single nowait
        parallelDFS(0, graph, visited);
    }

    return 0;
}
