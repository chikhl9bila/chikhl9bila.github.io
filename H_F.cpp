#include <iostream>
#include <vector>
 
using namespace std;
 
const int MAX_NODES = 100; 
 
vector<int> adj[MAX_NODES];
vector<int> weights(MAX_NODES, 0);
vector<int> leafCount(MAX_NODES, 0);
int mini = 0;
int sum = 0;
 
void dfs(int node) {
    if (adj[node].empty()) {
        // Node is a leaf
        leafCount[node] = 1;
        return;
    }
 
    for (int child : adj[node]) {
        dfs(child);
        leafCount[node] += leafCount[child];
    }
}
 
void dfs2(int node) {
    sum += weights[node] * leafCount[node];
    if (weights[node] < 0) {
 
        if (weights[node] * leafCount[node] < mini) {
            mini = weights[node] * leafCount[node];
        }
    }
    for (int child : adj[node]) {
        dfs2(child); // Change from dfs to dfs2
    }
}
 
int main() {
    int t ; cin >> t ; 
    while(t--){
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> weights[i];
        }
 
        for (int i = 1; i < n; ++i) {
            int parent, child;
            cin >> parent >> child;
            adj[parent].push_back(child);
        }
 
        dfs(1);
 
        dfs2(1);
 
        cout << sum - mini << endl;
        // Reset global variables for the next test case
        fill(weights.begin(), weights.end(), 0);
        fill(leafCount.begin(), leafCount.end(), 0);
        mini = 0;
        sum = 0;
        for (int i = 1; i <= MAX_NODES; ++i) {
            adj[i].clear();
        }
    }
    
    return 0;
}
