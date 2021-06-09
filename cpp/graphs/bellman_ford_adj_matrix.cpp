#include <algorithm>
#include <iostream>
#include <vector>

constexpr int32_t POSITIVE_INFINITY = 999999999;
constexpr int32_t NEGATIVE_INFINITY = -POSITIVE_INFINITY;

typedef std::vector<std::vector<int32_t>> adjacency_matrix;

struct bellman_ford_result {
    const std::vector<int32_t> dist;
    const std::vector<int32_t> prev;
};

bellman_ford_result bellman_ford(const adjacency_matrix &m_src, uint32_t src_node) {
    const uint32_t n = m_src.size();
    // Initialize the distance to all nodes to be infinity
    // except for the start node which is zero.
    std::vector<int32_t> dist(n, POSITIVE_INFINITY);
    dist[src_node] = 0;
    // Initialize prev array which will allows for shortest path
    // reconstruction after the algorithm has terminated.
    std::vector<int32_t> prev(n, -1);
    // We make a copy of the adjacency matrix, putting INFINITY on the nodes with no connection.
    adjacency_matrix m = m_src;
    for (uint32_t i = 0; i < n; ++i) {
        for (uint32_t j = 0; j < n; ++j) {
            if (i != j && m_src[i][j] == 0) {
                m[i][j] = POSITIVE_INFINITY;
            }
        }
    }
    // For each vertex, apply relaxation for all the edges.
    for (auto _ = 0; _ < n - 1; ++_) {
        for (uint32_t i = 0; i < n; ++i) {
            for (uint32_t j = 0; j < n; ++j) {
                if (dist[i] + m[i][j] < dist[j]) {
                    dist[j] = dist[i] + m[i][j];
                    prev[j] = i;
                }
            }
        }
    }
    // Run algorithm a second time to detect which nodes are part of a negative cycle.
    // A negative cycle has occurred if we can find a better path beyond the optimal solution.
    for (auto _ = 0; _ < n - 1; ++_) {
        for (uint32_t i = 0; i < n; ++i) {
            for (uint32_t j = 0; j < n; ++j) {
                if (m[i][j] == POSITIVE_INFINITY) continue;
                if (dist[i] + m[i][j] < dist[j]) {
                    dist[j] = NEGATIVE_INFINITY;
                    prev[j] = -1;
                }
            }
        }
    }
    return bellman_ford_result{dist, prev};
}

void display_shortest_paths(uint32_t src_node, const bellman_ford_result &result) {
    const uint32_t n = result.dist.size();
    for (uint32_t i = 0; i < n; ++i) {
        if (i == src_node) continue;
        std::cout << i << ": ";
        if (result.dist[i] == POSITIVE_INFINITY) {
            std::cout << "[UNREACHABLE]";
        } else if (result.dist[i] == NEGATIVE_INFINITY) {
            std::cout << "[NEGATIVE CYCLE]";
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
            {0, 4, 0, 0, 0, 0, 2},
            {0,-1, 3, 0, 0, 0, 0},
            {0, 0, 0, 3, 1, 0, 0},
            {0, 0, 0, 0, 0,-2, 0},
            {0, 0, 0, 0, 0, 2, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 2, 0, 0}
    };

//    adjacency_matrix m{
//            {0, 5, 1, 0, 0,  0},
//            {0, 0, 2, 3, 20, 0},
//            {0, 3, 0, 0, 12, 0},
//            {0, 0, 3, 0, 2,  6},
//            {0, 0, 0, 0, 0,  1},
//            {0, 0, 0, 0, 0,  0}
//    };

    const uint32_t src_node = 0;
    const bellman_ford_result result = bellman_ford(m, src_node);
    display_shortest_paths(src_node, result);

    return 0;
}
