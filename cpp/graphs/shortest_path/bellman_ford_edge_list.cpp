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
    // Initialize the distance to all nodes to be infinity
    // except for the start node which is zero.
    std::vector<double> dist(vertices, POSITIVE_INFINITY);
    dist[src_vertex] = 0;
    // Initialize parent array which will allows for shortest path
    // reconstruction after the algorithm has terminated.
    std::vector<int> parent(vertices, -1);

    // Only in the worst case does it take 'vertices'-1 iterations for the Bellman-Ford
    // algorithm to complete. Another stopping condition is when we're unable to relax
    // an edge, this means we have reached the optimal solution early.
    bool some_edge_relaxed = true;
    // For each vertex, apply relaxation for all the edges.
    for (auto _ = 0; _ < vertices - 1 && some_edge_relaxed; ++_) {
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
    for (auto _ = 0; _ < vertices - 1 && some_edge_relaxed; ++_) {
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
        for (auto at = dest_vertex; at != -1; at = result.parent[at]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());
        std::cout << "[" << path[0];
        for (auto i = 1; i < path.size(); ++i) {
            std::cout << " -> " << path[i] << "";
        }
        std::cout << "]";
    }
    std::cout << std::endl;
}

void display_all_shortest_paths(const bellman_ford_result &result) {
    const int vertices = static_cast<int>(result.dist.size());
    for (auto dest_vertex = 0; dest_vertex < vertices; ++dest_vertex) {
        display_shortest_path(result, dest_vertex);
    }
}

int main() {
    std::cout << "Example 1" << std::endl;  // https://www.youtube.com/watch?v=pSqmAO-m7Lk (graph example 2)
    {
        std::vector<edge> edges{
                edge{0, 1, 5},
                edge{0, 2, 1},
                edge{1, 2, 2},
                edge{1, 3, 3},
                edge{1, 4, 20},
                edge{2, 1, 3},
                edge{2, 4, 12},
                edge{3, 2, 3},
                edge{3, 4, 2},
                edge{3, 5, 6},
                edge{4, 5, 1},
        };
        const bellman_ford_result result = bellman_ford(edges, 6, 0);
        display_all_shortest_paths(result);
    }
    std::cout << "Example 2" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 1)
    {
        std::vector<edge> edges{
                edge{0, 1, 4},
                edge{0, 6, 2},
                edge{1, 1, -1},
                edge{1, 2, 3},
                edge{2, 3, 3},
                edge{2, 4, 1},
                edge{3, 5, -2},
                edge{4, 5, 2},
                edge{6, 4, 2},
        };
        const bellman_ford_result result = bellman_ford(edges, 7, 0);
        display_all_shortest_paths(result);
    }
    std::cout << "Example 3" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 2)
    {
        std::vector<edge> edges{
                edge{0, 1, 5},
                edge{1, 2, 20},
                edge{1, 5, 30},
                edge{1, 6, 60},
                edge{2, 3, 10},
                edge{2, 4, 75},
                edge{3, 2, -15},
                edge{4, 9, 100},
                edge{5, 4, 25},
                edge{5, 6, 5},
                edge{5, 8, 50},
                edge{6, 7, -50},
                edge{7, 8, -10},
        };
        const bellman_ford_result result = bellman_ford(edges, 10, 0);
        display_all_shortest_paths(result);
    }
    std::cout << "Example 4" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 3 from github)
    {
        std::vector<edge> edges{
                edge{0, 1, 1},
                edge{1, 2, 1},
                edge{2, 4, 1},
                edge{4, 3, -3},
                edge{3, 2, 1},
                edge{1, 5, 4},
                edge{1, 6, 4},
                edge{5, 6, 5},
                edge{6, 7, 4},
                edge{5, 7, 3},
        };
        const bellman_ford_result result = bellman_ford(edges, 9, 0);
        display_all_shortest_paths(result);
    }
    std::cout << "Example 5" << std::endl;  // resources/digraph_weighted_neg_cycles.svg
    {
        std::vector<edge> edges{
                edge{0, 1, 1},
                edge{1, 2, 8},
                edge{1, 3, 4},
                edge{1, 4, 1},
                edge{2, 5, 2},
                edge{3, 5, 2},
                edge{4, 3, 2},
                edge{4, 4, 3},
                edge{4, 6, 6},
                edge{5, 2, 1},
                edge{5, 6, 1},
                edge{5, 7, 2},
                edge{6, 9, 1},
                edge{7, 8, 1},
                edge{7, 10, 1},
                edge{8, 6, 3},
                edge{9, 8, -6},
                edge{10, 10, -1},
        };
        const bellman_ford_result result = bellman_ford(edges, 12, 1);
        display_all_shortest_paths(result);
    }
    return 0;
}
