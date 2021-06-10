/**
 * An implementation of the Bellman-Ford algorithm. The algorithm finds the shortest path between
 * a starting node and all other nodes in the graph. The algorithm also detects negative cycles.
 *
 * @author Yusnier M. Sosa, yusnier.msv@gmail.com
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
constexpr double NEGATIVE_INFINITY = -POSITIVE_INFINITY;

typedef std::vector<std::vector<double>> adjacency_matrix;

struct bellman_ford_result {
    const int src_vertex;
    const std::vector<double> dist;
    const std::vector<int> prev;
};

bellman_ford_result bellman_ford(const adjacency_matrix &m, int src_vertex) {
    const int vertices = static_cast<int>(m.size());
    // Initialize the distance to all nodes to be infinity
    // except for the start node which is zero.
    std::vector<double> dist(vertices, POSITIVE_INFINITY);
    dist[src_vertex] = 0;
    // Initialize prev array which will allows for shortest path
    // reconstruction after the algorithm has terminated.
    std::vector<int> prev(vertices, -1);
    // Only in the worst case does it take 'vertices'-1 iterations for the Bellman-Ford
    // algorithm to complete. Another stopping condition is when we're unable to relax
    // an edge, this means we have reached the optimal solution early.
    bool some_edge_relaxed = true;
    // For each vertex, apply relaxation for all the edges.
    for (auto _ = 0; _ < vertices - 1 && some_edge_relaxed; ++_) {
        some_edge_relaxed = false;
        for (auto i = 0; i < vertices; ++i) {
            for (auto j = 0; j < vertices; ++j) {
                if (dist[i] + m[i][j] < dist[j]) {
                    dist[j] = dist[i] + m[i][j];
                    prev[j] = i;
                    some_edge_relaxed = true;
                }
            }
        }
    }
    // Run algorithm a second time to detect which nodes are part of a negative cycle.
    // A negative cycle has occurred if we can find a better path beyond the optimal solution.
    for (auto _ = 0; _ < vertices - 1 && some_edge_relaxed; ++_) {
        some_edge_relaxed = false;
        for (auto i = 0; i < vertices; ++i) {
            for (auto j = 0; j < vertices; ++j) {
                if (dist[i] + m[i][j] < dist[j]) {
                    dist[j] = NEGATIVE_INFINITY;
                    prev[j] = -1;
                    some_edge_relaxed = true;
                }
            }
        }
    }
    return bellman_ford_result{src_vertex, dist, prev};
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

void display_shortest_paths(const bellman_ford_result &res) {
    const int vertices = static_cast<int>(res.dist.size());
    for (auto i = 0; i < vertices; ++i) {
        std::cout << "From " << res.src_vertex << " to " << i << ": [" << std::setw(4) << res.dist[i] << "] ";
        if (res.dist[i] == POSITIVE_INFINITY) {
            std::cout << "[unreachable]";
        } else if (res.dist[i] == NEGATIVE_INFINITY) {
            std::cout << "[negative cycle]";
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
        const bellman_ford_result result = bellman_ford(m, 0);
        display_shortest_paths(result);
    }
    std::cout << "Example 2" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 1)
    {
        adjacency_matrix m = setup_disconnected_adjacency_matrix(7);
        m[0][1] = 4;
        m[0][6] = 2;
        m[1][1] = -1;
        m[1][2] = 3;
        m[2][3] = 3;
        m[2][4] = 1;
        m[3][5] = -2;
        m[4][5] = 2;
        m[6][4] = 2;
        const bellman_ford_result result = bellman_ford(m, 0);
        display_shortest_paths(result);
    }
    std::cout << "Example 3" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 2)
    {
        adjacency_matrix m = setup_disconnected_adjacency_matrix(10);
        m[0][1] = 5;
        m[1][2] = 20;
        m[1][5] = 30;
        m[1][6] = 60;
        m[2][3] = 10;
        m[2][4] = 75;
        m[3][2] = -15;
        m[4][9] = 100;
        m[5][4] = 25;
        m[5][6] = 5;
        m[5][8] = 50;
        m[6][7] = -50;
        m[7][8] = -10;
        const bellman_ford_result result = bellman_ford(m, 0);
        display_shortest_paths(result);
    }
    std::cout << "Example 4" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 3 from github)
    {
        adjacency_matrix m = setup_disconnected_adjacency_matrix(9);
        m[0][1] = 1;
        m[1][2] = 1;
        m[2][4] = 1;
        m[4][3] = -3;
        m[3][2] = 1;
        m[1][5] = 4;
        m[1][6] = 4;
        m[5][6] = 5;
        m[6][7] = 4;
        m[5][7] = 3;
        const bellman_ford_result result = bellman_ford(m, 0);
        display_shortest_paths(result);
    }
    return 0;
}
