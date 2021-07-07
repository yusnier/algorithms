#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
constexpr double NEGATIVE_INFINITY = -POSITIVE_INFINITY;

typedef std::vector<std::vector<double>> adj_matrix;

struct bellman_ford_result {
    const int src_vertex;
    const std::vector<double> dist;
    const std::vector<int> parent;
};

bellman_ford_result bellman_ford(const adj_matrix &m, int src_vertex) {
    const int vertices = static_cast<int>(m.size());
    // Initialize the distance to all vertices to be infinity except for the start vertex which is zero.
    // dist[i] is the current shortest distance from 'src_vertex' to vertex i.
    std::vector<double> dist(vertices, POSITIVE_INFINITY);
    dist[src_vertex] = 0;
    // This array will allows for shortest path reconstruction (if required) after the algorithm has terminated.
    // parent[i] is the vertex where vertex i comes from in the shortest path.
    std::vector<int> parent(vertices, -1);

    // Only in the worst case does it take 'vertices'-1 iterations for the Bellman-Ford
    // algorithm to complete. Another stopping condition is when we're unable to relax
    // an edge, this means we have reached the optimal solution early.
    bool some_edge_relaxed = true;
    // For each vertex, apply relaxation for all the edges.
    for (int _ = 0; _ < vertices - 1 && some_edge_relaxed; ++_) {
        some_edge_relaxed = false;
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (dist[i] + m[i][j] < dist[j]) {
                    dist[j] = dist[i] + m[i][j];
                    parent[j] = i;
                    some_edge_relaxed = true;
                }
            }
        }
    }
    // Run algorithm a second time to detect which nodes are part of a negative cycle.
    // A negative cycle has occurred if we can find a better path beyond the optimal solution.
    // We need the same 'vertices - 1' iterations to propagate the value 'NEGATIVE_INFINITY'
    // to every edge that is part of or reaches into a negative cycle. But if the requirement
    // is only to know if there is a negative cycle or not, one iteration is enough, returning
    // early if any relaxation occurred.
    for (int _ = 0; _ < vertices - 1 && some_edge_relaxed; ++_) {
        some_edge_relaxed = false;
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (dist[i] + m[i][j] < dist[j]) {
                    dist[j] = NEGATIVE_INFINITY;
                    parent[j] = -1;
                    some_edge_relaxed = true;
                }
            }
        }
    }

    return {src_vertex, dist, parent};
}

adj_matrix setup_disconnected_adjacency_matrix(int vertices) {
    // Fill all edges with infinity by default.
    adj_matrix result(vertices, std::vector<double>(vertices, POSITIVE_INFINITY));
    // Assuming the distance for a vertex to reach itself is 0.
    for (int i = 0; i < vertices; ++i) {
        result[i][i] = 0;
    }
    return result;
}

void display_shortest_path(const bellman_ford_result &result, int dest_vertex) {
    std::cout << "From " << result.src_vertex << " to " << dest_vertex << ": ["
              << std::setw(4) << result.dist[dest_vertex] << "] ";
    if (result.dist[dest_vertex] == POSITIVE_INFINITY) {
        std::cout << "[unreachable]";
    } else if (result.dist[dest_vertex] == NEGATIVE_INFINITY) {
        std::cout << "[negative cycle]";
    } else {
        std::vector<int> path;
        for (int at = dest_vertex; at != -1; at = result.parent[at]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());
        std::cout << "[" << path[0];
        for (std::size_t i = 1; i < path.size(); ++i) {
            std::cout << " -> " << path[i] << "";
        }
        std::cout << "]";
    }
    std::cout << std::endl;
}

void display_all_shortest_paths(const bellman_ford_result &result) {
    const int vertices = static_cast<int>(result.dist.size());
    for (int dest_vertex = 0; dest_vertex < vertices; ++dest_vertex) {
        display_shortest_path(result, dest_vertex);
    }
}

int main() {
    std::cout << "Example 1" << std::endl;  // https://www.youtube.com/watch?v=pSqmAO-m7Lk (graph example 2)
    {
        adj_matrix m = setup_disconnected_adjacency_matrix(6);
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
        display_all_shortest_paths(result);
    }
    std::cout << "Example 2" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 1)
    {
        adj_matrix m = setup_disconnected_adjacency_matrix(7);
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
        display_all_shortest_paths(result);
    }
    std::cout << "Example 3" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 2)
    {
        adj_matrix m = setup_disconnected_adjacency_matrix(10);
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
        display_all_shortest_paths(result);
    }
    std::cout << "Example 4" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 3 from github)
    {
        adj_matrix m = setup_disconnected_adjacency_matrix(9);
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
        display_all_shortest_paths(result);
    }
    std::cout << "Example 5" << std::endl;  // resources/digraph_weighted_neg_cycles.svg
    {
        adj_matrix m = setup_disconnected_adjacency_matrix(12);
        m[0][1] = 1;
        m[1][2] = 8;
        m[1][3] = 4;
        m[1][4] = 1;
        m[2][5] = 2;
        m[3][5] = 2;
        m[4][3] = 2;
        m[4][4] = 3;
        m[4][6] = 6;
        m[5][2] = 1;
        m[5][6] = 1;
        m[5][7] = 2;
        m[6][9] = 1;
        m[7][8] = 1;
        m[7][10] = 1;
        m[8][6] = 3;
        m[9][8] = -6;
        m[10][10] = -1;
        const bellman_ford_result result = bellman_ford(m, 1);
        display_all_shortest_paths(result);
    }
    return 0;
}
