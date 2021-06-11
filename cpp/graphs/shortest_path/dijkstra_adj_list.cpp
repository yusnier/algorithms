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
    const std::vector<int> prev;
};

dijkstra_result dijkstra(const graph &graph, int src_vertex) {
    const int vertices = static_cast<int>(graph.size());
    // Initialize the distance to all vertices to be infinity except for the start vertex which is zero.
    // dist[i] is the current shortest distance from 'src_vertex' to vertex i.
    std::vector<double> dist(vertices, POSITIVE_INFINITY);
    dist[src_vertex] = 0;
    // This array will allows for shortest path reconstruction (if required) after the algorithm has terminated.
    // prev[i] is the vertex where vertex i comes from in the shortest path.
    std::vector<int> prev(vertices, -1);
    // Boolean array to mark visited/unvisited for each node.
    std::vector<bool> visited(vertices, false);
    // The first vertex to start with the shortest distance is 'src_vertex'.
    int min_vertex = src_vertex;

    // The loop stops either when:
    // min_vertex == vertices -> All vertices were already visited and relaxed. OR
    // dist[min_vertex] == POSITIVE_INFINITY -> remaining unvisited nodes are not reachable from 'src_node'.
    while (min_vertex < vertices && dist[min_vertex] != POSITIVE_INFINITY) {
        visited[min_vertex] = true;
        // For each vertex from 'min_vertex', apply relaxation for all the edges.
        for (const auto &edge: graph.adj_list(min_vertex)) {
            if (!visited[edge.to] && dist[edge.from] + edge.cost < dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.cost;
                prev[edge.to] = edge.from;
            }
        }

        // If what we want is just to find the shortest path between 2 vertices: 'src_vertex' -> 'dest_vertex',
        // we can return earlier at this point once we reach 'dest_vertex' improving the performance.
        // We just need to add 'dest_vertex' as a new parameter and uncomment this conditional block:
        //if (min_vertex == dest_vertex) {
        //    break;
        //}

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

    return dijkstra_result{src_vertex, dist, prev};
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
        display_shortest_paths(result);
    }
    return 0;
}