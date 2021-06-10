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

struct edge {  // a directed edge with a cost
    const int from, to;
    const double cost;
};

struct bellman_ford_result {
    const int src_vertex;
    const std::vector<double> dist;
    const std::vector<int> prev;
};

bellman_ford_result bellman_ford(const std::vector<edge> &edges, int vertices, int src_vertex) {
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
        for (const auto &edge: edges) {
            if (dist[edge.from] + edge.cost < dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.cost;
                prev[edge.to] = edge.from;
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
                prev[edge.to] = -1;
                some_edge_relaxed = true;
            }
        }
    }
    return bellman_ford_result{src_vertex, dist, prev};
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
        int d = bellman_ford(edges, 6, 0).src_vertex;
        const bellman_ford_result result = bellman_ford(edges, 6, 0);
        display_shortest_paths(result);
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
        display_shortest_paths(result);
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
        display_shortest_paths(result);
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
        display_shortest_paths(result);
    }
    return 0;
}
