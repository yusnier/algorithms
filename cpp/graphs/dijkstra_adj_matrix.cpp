#include <algorithm>
#include <iostream>
#include <vector>

// Large enough to exceed the total sum of weights of the entire graph
// and small enough to avoid possible integer overflow in operations.
const int32_t INFINITY = 999999999;

typedef std::vector<std::vector<int32_t>> adjacency_matrix;

struct dijkstra_result {
    const std::vector<int32_t> dist;
    const std::vector<int32_t> prev;
};

dijkstra_result dijkstra(const adjacency_matrix &m_src, uint32_t src_node) {
    const uint32_t n = m_src.size();  // number of nodes constant
    // Integer array to save the shortest distance from 'src_node' to each node.
    // dist[i] is the current shortest distance from 'src_node' to node i.
    std::vector<int32_t> dist(n, INFINITY);
    // Integer array to save the predecessor of each node in the shortest path.
    // prev[i] is the node where node i comes from in the shortest path.
    // This array is only used for the shortest path construction purposes, it is not necessarily required.
    std::vector<int32_t> prev(n, INFINITY);
    // Boolean array to mark visited/unvisited for each node.
    std::vector<bool> visited(n, false);
    // We make a copy of the adjacency matrix, putting INFINITY on the nodes with no connection.
    adjacency_matrix m = m_src;
    for (uint32_t i = 0; i < n; ++i) {
        for (uint32_t j = 0; j < n; ++j) {
            if (m_src[i][j] == 0) {
                m[i][j] = INFINITY;
            }
        }
    }
    dist[src_node] = 0;  // distance to 'src_node' is set to 0
    prev[src_node] = -1;  // 'src_node' doesn't come from any node since it is the path root
    for (uint32_t _ = 0; _ < n; ++_) {  // we perform an iteration per node
        // Looking for the most promising node, which is the unvisited node with the lowest weight.
        // A more efficient approach to improve the O(n) lookup time would be to use priority queues.
        int32_t current_node = 0;
        while (visited[current_node]) ++current_node;
        for (uint32_t i = current_node + 1; i < n; ++i) {
            if (!visited[i] && dist[i] < dist[current_node]) {
                current_node = i;
            }
        }
        // If the current node has infinite weight, it means that the
        // remaining unvisited nodes are not reachable from 'src_node'.
        if (dist[current_node] == INFINITY) {
            break;
        }
        visited[current_node] = true;
        for (uint32_t i = 0; i < n; ++i) {
            if (!visited[i] && dist[current_node] + m[current_node][i] < dist[i]) {
                dist[i] = dist[current_node] + m[current_node][i];
                prev[i] = current_node;
            }
        }
        // if what we want is just to find the shortest path between 2 nodes, let's say 'src_node' -> 'dest_node',
        // we can return earlier at this point once we reach 'dest_node' improving the performance:
        //if (current_node == dest_node) {
        //    break;
        //}
    }
    return dijkstra_result{dist, prev};
}

void display_shortest_paths(uint32_t src_node, const dijkstra_result &result) {
    const uint32_t n = result.dist.size();
    for (uint32_t i = 0; i < n; ++i) {
        if (i == src_node) continue;
        std::cout << i << ": ";
        if (result.dist[i] == INFINITY) {
            std::cout << "[UNREACHABLE]";
        } else {
            std::vector<uint32_t> path(1, i);
            for (uint32_t j = result.prev[i]; j != -1; j = result.prev[j]) {
                path.push_back(j);
            }
            std::reverse(path.begin(), path.end());
            std::cout << "w[" << result.dist[i] << "] " << path[0];
            for (std::size_t j = 1; j < path.size(); ++j) {
                std::cout << " -> " << path[j] << "";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    adjacency_matrix m{
            {0, 5, 1, 0, 0,  0},
            {0, 0, 2, 3, 20, 0},
            {0, 3, 0, 0, 12, 0},
            {0, 0, 3, 0, 2,  6},
            {0, 0, 0, 0, 0,  1},
            {0, 0, 0, 0, 0,  0}
    };

    const uint32_t src_node = 0;
    const dijkstra_result result = dijkstra(m, src_node);
    display_shortest_paths(src_node, result);

    return 0;
}
