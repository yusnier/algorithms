#include <algorithm>
#include <cassert>
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

// Directed graph with adjacency lists.
class graph {
private:
    std::vector<std::vector<edge>> adj_lists;
public:
    explicit graph(int vertices) : adj_lists(vertices, std::vector<edge>()) {}
    std::size_t size() const { return adj_lists.size(); }
    const std::vector<edge> &adj_list(int vertex) const { return adj_lists[vertex]; }
    void add_edge(int vertex, const edge &e) {
        assert(vertex == e.from);
        adj_lists[vertex].push_back(e);
    }
};

struct bellman_ford_result {
    const int src_vertex;
    const std::vector<double> dist;
    const std::vector<int> parent;
};

bellman_ford_result bellman_ford(const graph &graph, int src_vertex) {
    const int vertices = static_cast<int>(graph.size());
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
            for (const auto & edge: graph.adj_list(i)) {
                if (dist[edge.from] + edge.cost < dist[edge.to]) {
                    dist[edge.to] = dist[edge.from] + edge.cost;
                    parent[edge.to] = edge.from;
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
            for (const auto &edge: graph.adj_list(i)) {
                if (dist[edge.from] + edge.cost < dist[edge.to]) {
                    dist[edge.to] = NEGATIVE_INFINITY;
                    parent[edge.to] = -1;
                    some_edge_relaxed = true;
                }
            }
        }
    }

    return {src_vertex, dist, parent};
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
        graph g(6);
        g.add_edge(0, {0, 1, 5});
        g.add_edge(0, {0, 2, 1});
        g.add_edge(1, {1, 2, 2});
        g.add_edge(1, {1, 3, 3});
        g.add_edge(1, {1, 4, 20});
        g.add_edge(2, {2, 1, 3});
        g.add_edge(2, {2, 4, 12});
        g.add_edge(3, {3, 2, 3});
        g.add_edge(3, {3, 4, 2});
        g.add_edge(3, {3, 5, 6});
        g.add_edge(4, {4, 5, 1});
        const bellman_ford_result result = bellman_ford(g, 0);
        display_all_shortest_paths(result);
    }
    std::cout << "Example 2" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 1)
    {
        graph g(7);
        g.add_edge(0, {0, 1, 4});
        g.add_edge(0, {0, 6, 2});
        g.add_edge(1, {1, 1, -1});
        g.add_edge(1, {1, 2, 3});
        g.add_edge(2, {2, 3, 3});
        g.add_edge(2, {2, 4, 1});
        g.add_edge(3, {3, 5, -2});
        g.add_edge(4, {4, 5, 2});
        g.add_edge(6, {6, 4, 2});
        const bellman_ford_result result = bellman_ford(g, 0);
        display_all_shortest_paths(result);
    }
    std::cout << "Example 3" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 2)
    {
        graph g(10);
        g.add_edge(0, {0, 1, 5});
        g.add_edge(1, {1, 2, 20});
        g.add_edge(1, {1, 5, 30});
        g.add_edge(1, {1, 6, 60});
        g.add_edge(2, {2, 3, 10});
        g.add_edge(2, {2, 4, 75});
        g.add_edge(3, {3, 2, -15});
        g.add_edge(4, {4, 9, 100});
        g.add_edge(5, {5, 4, 25});
        g.add_edge(5, {5, 6, 5});
        g.add_edge(5, {5, 8, 50});
        g.add_edge(6, {6, 7, -50});
        g.add_edge(7, {7, 8, -10});
        const bellman_ford_result result = bellman_ford(g, 0);
        display_all_shortest_paths(result);
    }
    std::cout << "Example 4" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 3 from github)
    {
        graph g(9);
        g.add_edge(0, {0, 1, 1});
        g.add_edge(1, {1, 2, 1});
        g.add_edge(2, {2, 4, 1});
        g.add_edge(4, {4, 3, -3});
        g.add_edge(3, {3, 2, 1});
        g.add_edge(1, {1, 5, 4});
        g.add_edge(1, {1, 6, 4});
        g.add_edge(5, {5, 6, 5});
        g.add_edge(6, {6, 7, 4});
        g.add_edge(5, {5, 7, 3});
        const bellman_ford_result result = bellman_ford(g, 0);
        display_all_shortest_paths(result);
    }
    std::cout << "Example 5" << std::endl;  // resources/digraph_weighted_neg_cycles.svg
    {
        graph g(12);
        g.add_edge(0, {0, 1, 1});
        g.add_edge(1, {1, 2, 8});
        g.add_edge(1, {1, 3, 4});
        g.add_edge(1, {1, 4, 1});
        g.add_edge(2, {2, 5, 2});
        g.add_edge(3, {3, 5, 2});
        g.add_edge(4, {4, 3, 2});
        g.add_edge(4, {4, 4, 3});
        g.add_edge(4, {4, 6, 6});
        g.add_edge(5, {5, 2, 1});
        g.add_edge(5, {5, 6, 1});
        g.add_edge(5, {5, 7, 2});
        g.add_edge(6, {6, 9, 1});
        g.add_edge(7, {7, 8, 1});
        g.add_edge(7, {7, 10, 1});
        g.add_edge(8, {8, 6, 3});
        g.add_edge(9, {9, 8, -6});
        g.add_edge(10, {10, 10, -1});
        const bellman_ford_result result = bellman_ford(g, 1);
        display_all_shortest_paths(result);
    }
    return 0;
}
