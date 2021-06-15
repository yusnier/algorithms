/**
 * Implementation of Dijkstra's shortest path algorithm from a start node to all other nodes.
 * Dijkstra's can also be modified to find the shortest path between a starting node and a
 * specific ending node in the graph with minimal effort.
 *
 * @author Yusnier M. Sosa, yusnier.msv@gmail.com
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();

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
    void add_edge(int vertex, const edge &e) { adj_lists[vertex].push_back(e); }
};

struct dijkstra_result {
    const int src_vertex;
    const std::vector<double> dist;
    const std::vector<int> parent;
};

dijkstra_result dijkstra(const graph &graph, int src_vertex) {
    const int vertices = static_cast<int>(graph.size());
    // Initialize the distance to all vertices to be infinity except for the start vertex which is zero.
    // dist[i] is the current shortest distance from 'src_vertex' to vertex i.
    std::vector<double> dist(vertices, POSITIVE_INFINITY);
    dist[src_vertex] = 0;
    // This array will allows for shortest path reconstruction (if required) after the algorithm has terminated.
    // parent[i] is the vertex where vertex i comes from in the shortest path.
    std::vector<int> parent(vertices, -1);
    // Boolean array to mark visited/unvisited for each node.
    std::vector<bool> visited(vertices, false);
    // The first vertex to start with the shortest distance is 'src_vertex'.
    int min_vertex = src_vertex;

    // The loop stops either when:
    // min_vertex == vertices -> All vertices were already visited and relaxed OR
    // dist[min_vertex] == POSITIVE_INFINITY -> remaining unvisited nodes are not reachable from 'src_node'.
    while (min_vertex < vertices && dist[min_vertex] != POSITIVE_INFINITY) {
        visited[min_vertex] = true;
        // For each vertex from 'vertex', apply relaxation for all the edges, except those already visited,
        // because this means that they already have the best possible distance.
        for (const auto &edge: graph.adj_list(min_vertex)) {
            if (visited[edge.to]) { continue; }
            if (dist[edge.from] + edge.cost < dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.cost;
                parent[edge.to] = edge.from;
            }
        }

        // If we are trying to solve 'Single Pair Shortest Path (SPSP)' we can add a new function parameter
        // 'dest_vertex' and stop early at this point once we meet the condition: 'vertex == dest_vertex'.
        // If we want to return a 'bfs_result' for path reconstruction we can just break the loop.
        // But if we want just to return the shortest distance we can make a 'return dist[dest_vertex]' at
        // at this point, also putting a 'return POSITIVE_INFINITY' at the end of the function, instead of
        // returning a 'dijkstra_result', which means that 'dest_vertex' is not reachable from 'src_vertex'.

        // Looking for the most promising vertex, which is the unvisited one with the shortest distance,
        // that distance not equal to infinity which means that it's a reachable vertex from 'src_vertex.
        // A better approach in the algorithm to finding this vertex would be to use an indexed priority queue.
        min_vertex = 0;
        while ((min_vertex < vertices) && visited[min_vertex]) ++min_vertex;
        for (auto i = min_vertex + 1; i < vertices; ++i) {
            if (!visited[i] && dist[i] < dist[min_vertex]) {
                min_vertex = i;
            }
        }
    }

    return dijkstra_result{src_vertex, dist, parent};
}

void display_shortest_path(const dijkstra_result &result, int dest_vertex) {
    std::cout << "From " << result.src_vertex << " to " << dest_vertex << ": ["
              << std::setw(4) << result.dist[dest_vertex] << "] ";
    if (result.dist[dest_vertex] == POSITIVE_INFINITY) {
        std::cout << "[unreachable]";
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

void display_all_shortest_paths(const dijkstra_result &result) {
    const int vertices = static_cast<int>(result.dist.size());
    for (auto dest_vertex = 0; dest_vertex < vertices; ++dest_vertex) {
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
        const dijkstra_result result = dijkstra(g, 0);
        display_all_shortest_paths(result);
    }
    std::cout << "Example 2" << std::endl;  // resources/digraph_weighted_no_neg_cycles.svg
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
        g.add_edge(9, {9, 8, 2});
        const dijkstra_result result = dijkstra(g, 1);
        display_all_shortest_paths(result);
    }
    return 0;
}
