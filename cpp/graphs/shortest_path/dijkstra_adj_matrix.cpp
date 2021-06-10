#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();

typedef std::vector<std::vector<double>> adjacency_matrix;

struct dijkstra_result {
    const int src_vertex;
    const std::vector<double> dist;
    const std::vector<int> prev;
};

dijkstra_result dijkstra(const adjacency_matrix &m, int src_vertex) {
    const int vertices = static_cast<int>(m.size());
    // Integer array to save the shortest distance from 'src_node' to each node.
    // dist[i] is the current shortest distance from 'src_node' to node i.
    std::vector<double> dist(vertices, POSITIVE_INFINITY);
    dist[src_vertex] = 0;  // distance to 'src_node' is set to 0
    // Integer array to save the predecessor of each node in the shortest path.
    // prev[i] is the node where node i comes from in the shortest path.
    // This array is only used for the shortest path construction purposes, it is not necessarily required.
    std::vector<int> prev(vertices, -1);
    // Boolean array to mark visited/unvisited for each node.
    std::vector<bool> visited(vertices, false);

    for (auto _ = 0; _ < vertices; ++_) {  // we perform an iteration per node
        // Looking for the most promising node, which is the unvisited node with the lowest weight.
        // A more efficient approach to improve the O(vertices) lookup time would be to use priority queues.
        int32_t current_node = 0;
        while (visited[current_node]) ++current_node;
        for (uint32_t i = current_node + 1; i < vertices; ++i) {
            if (!visited[i] && dist[i] < dist[current_node]) {
                current_node = i;
            }
        }
        // If the current node has infinite weight, it means that the
        // remaining unvisited nodes are not reachable from 'src_node'.
        if (dist[current_node] == POSITIVE_INFINITY) {
            break;
        }
        visited[current_node] = true;
        for (uint32_t i = 0; i < vertices; ++i) {
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
    return dijkstra_result{src_vertex, dist, prev};
}

adjacency_matrix setup_disconnected_adjacency_matrix(int vertices) {
    // Fill all edges with infinity by default.
    adjacency_matrix result(vertices, std::vector<double>(vertices, POSITIVE_INFINITY));
    // Assuming the distance for a vertex to reach itself is 0.
    for (auto i = 0; i < vertices; ++i) {
        result[i][i] = 0;
    }
    return result;
}

void display_shortest_paths(const dijkstra_result &res) {
    const int vertices = static_cast<int>(res.dist.size());
    for (auto i = 0; i < vertices; ++i) {
        std::cout << "From " << res.src_vertex << " to " << i << ": [" << std::setw(4) << res.dist[i] << "] ";
        if (res.dist[i] == POSITIVE_INFINITY) {
            std::cout << "[unreachable]";
        } else {
            std::vector<int> path(1, i);
            for (auto j = res.prev[i]; j != -1; j = res.prev[j]) {
                path.push_back(j);
            }
            std::reverse(path.begin(), path.end());
            std::cout << "[" << path[0];
            for (auto j = 1; j < path.size(); ++j) {
                std::cout << " -> " << path[j] << "";
            }
            std::cout << "]";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "Example 1" << std::endl;  // https://www.youtube.com/watch?v=pSqmAO-m7Lk (graph example 2)
    {
        adjacency_matrix m = setup_disconnected_adjacency_matrix(6);
        m[0][1] = 5;
        m[0][2] = 1;
        m[1][2] = 2;
        m[1][3] = 3;
        m[1][4] = 20;
        m[2][1] = 3;
        m[2][4] = 12;
        m[3][2] = 3;
        m[3][4] = 2;
        m[3][5] = 6;
        m[4][5] = 1;
        const dijkstra_result result = dijkstra(m, 0);
        display_shortest_paths(result);
    }
    return 0;
}
