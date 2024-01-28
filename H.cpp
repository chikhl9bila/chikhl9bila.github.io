#include <iostream>
#include <vector>
 
constexpr long long MAX_NODES = 100;
 
void dfs(long long node, const std::vector<long long>& weights, std::vector<long long>& leafCount, const std::vector<std::vector<long long>>& adj) {
    if (adj[node].empty()) {
        leafCount[node] = 1;
        return;
    }
 
    for (long long child : adj[node]) {
        dfs(child, weights, leafCount, adj);
        leafCount[node] += leafCount[child];
    }
}
 
void dfs2(long long node, long long& sum, long long& mini, const std::vector<long long>& weights, const std::vector<long long>& leafCount, const std::vector<std::vector<long long>>& adj) {
    sum += weights[node] * leafCount[node];
    if (weights[node] < 0) {
        if (weights[node] * leafCount[node] < mini) {
            mini = weights[node] * leafCount[node];
        }
    }
    for (long long child : adj[node]) {
        dfs2(child, sum, mini, weights, leafCount, adj);
    }
}
 
int main() {
    long long numTestCases;
    std::cin >> numTestCases;
 
    while (numTestCases--) {
        long long numNodes;
        std::cin >> numNodes;
 
        std::vector<long long> weights(numNodes + 1, 0);
        std::vector<long long> leafCount(numNodes + 1, 0);
        std::vector<std::vector<long long>> adj(numNodes + 1);
 
        for (long long i = 1; i <= numNodes; ++i) {
            std::cin >> weights[i];
        }
 
        for (long long i = 1; i < numNodes; ++i) {
            long long parent, child;
            std::cin >> parent >> child;
            adj[parent].push_back(child);
        }
 
        dfs(1, weights, leafCount, adj);
 
        long long sum = 0;
        long long mini = 0;
        dfs2(1, sum, mini, weights, leafCount, adj);
 
        std::cout << sum - mini << std::endl;
    }
 
    return 0;
}
