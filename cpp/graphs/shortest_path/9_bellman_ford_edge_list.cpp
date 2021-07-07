#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
constexpr double NEGATIVE_INFINITY = -POSITIVE_INFINITY;

// Directed edge with a cost.
struct edge {
    const int from, to;
    const double cost;
};

struct bellman_ford_result {
    const int src_vertex;
    const std::vector<double> dist;
    const std::vector<int> parent;
};

bellman_ford_result bellman_ford(const std::vector<edge> &edges, int vertices, int src_vertex) {
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
        for (const auto &edge: edges) {
            if (dist[edge.from] + edge.cost < dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.cost;
                parent[edge.to] = edge.from;
                some_edge_relaxed = true;
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
        for (const auto &edge: edges) {
            if (dist[edge.from] + edge.cost < dist[edge.to]) {
                dist[edge.to] = NEGATIVE_INFINITY;
                parent[edge.to] = -1;
                some_edge_relaxed = true;
            }
        }
    }

    return bellman_ford_result{src_vertex, dist, parent};
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
        const std::vector<edge> edges = {
                {0, 1, 5},
                {0, 2, 1},
                {1, 2, 2},
                {1, 3, 3},
                {1, 4, 20},
                {2, 1, 3},
                {2, 4, 12},
                {3, 2, 3},
                {3, 4, 2},
                {3, 5, 6},
                {4, 5, 1},
        };
        const bellman_ford_result result = bellman_ford(edges, 6, 0);
        display_all_shortest_paths(result);
    }
    std::cout << "Example 2" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 1)
    {
        const std::vector<edge> edges = {
                {0, 1, 4},
                {0, 6, 2},
                {1, 1, -1},
                {1, 2, 3},
                {2, 3, 3},
                {2, 4, 1},
                {3, 5, -2},
                {4, 5, 2},
                {6, 4, 2},
        };
        const bellman_ford_result result = bellman_ford(edges, 7, 0);
        display_all_shortest_paths(result);
    }
    std::cout << "Example 3" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 2)
    {
        const std::vector<edge> edges = {
                {0, 1, 5},
                {1, 2, 20},
                {1, 5, 30},
                {1, 6, 60},
                {2, 3, 10},
                {2, 4, 75},
                {3, 2, -15},
                {4, 9, 100},
                {5, 4, 25},
                {5, 6, 5},
                {5, 8, 50},
                {6, 7, -50},
                {7, 8, -10},
        };
        const bellman_ford_result result = bellman_ford(edges, 10, 0);
        display_all_shortest_paths(result);
    }
    std::cout << "Example 4" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 3 from github)
    {
        const std::vector<edge> edges = {
                {0, 1, 1},
                {1, 2, 1},
                {2, 4, 1},
                {4, 3, -3},
                {3, 2, 1},
                {1, 5, 4},
                {1, 6, 4},
                {5, 6, 5},
                {6, 7, 4},
                {5, 7, 3},
        };
        const bellman_ford_result result = bellman_ford(edges, 9, 0);
        display_all_shortest_paths(result);
    }
    std::cout << "Example 5" << std::endl;  // resources/digraph_weighted_neg_cycles.svg
    {
        const std::vector<edge> edges = {
                {0,  1,  1},
                {1,  2,  8},
                {1,  3,  4},
                {1,  4,  1},
                {2,  5,  2},
                {3,  5,  2},
                {4,  3,  2},
                {4,  4,  3},
                {4,  6,  6},
                {5,  2,  1},
                {5,  6,  1},
                {5,  7,  2},
                {6,  9,  1},
                {7,  8,  1},
                {7,  10, 1},
                {8,  6,  3},
                {9,  8,  -6},
                {10, 10, -1},
        };
        const bellman_ford_result result = bellman_ford(edges, 12, 1);
        display_all_shortest_paths(result);
    }
    return 0;
}
