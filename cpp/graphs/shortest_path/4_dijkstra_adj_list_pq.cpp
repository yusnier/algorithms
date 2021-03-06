#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <queue>
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
    void add_edge(int vertex, const edge &e) {
        assert(vertex == e.from);
        adj_lists[vertex].push_back(e);
    }
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
    // Keep a priority queue of the next most promising vertex to visit, which is the unvisited one with the
    // shortest distance. We start with 'src_vertex'.
    typedef std::pair<double, int> pq_entry;
    std::priority_queue<pq_entry, std::vector<pq_entry>, std::greater<>> pq;
    pq.push({0, src_vertex});

    while (!pq.empty()) {
        const double distance = pq.top().first;
        const int vertex = pq.top().second;
        pq.pop();
        visited[vertex] = true;
        // The usual implementation of Dijkstra???s requires heapDecreaseKey operation in binary heap data
        // structure that is not supported by priority queue in STL, so every time we update the distance
        // to a vertex, we enqueue a pair (newer/shorter distance, vertex) into pq and leave the inferior
        // pair (older/longer distance, vertex) inside pq, This is called 'Lazy Deletion' and it causes more
        // than one copy of the same vertex in pq with different distances from source. That is why we have
        // the check earlier to process only the first dequeued vertex information pair which has the
        // correct/shorter distance (other copies will have the outdated/longer distance). This is no ideal,
        // but inserting a new pair in O(log(n)) is much faster than searching for the key in the pq in O(n).
        if (distance > dist[vertex]) { continue; }
        // For each vertex from 'vertex', apply relaxation for all the edges, except those already visited,
        // because this means that they already have the best possible distance.
        for (const auto &edge: graph.adj_list(vertex)) {
            if (visited[edge.to]) { continue; }
            if (dist[edge.from] + edge.cost < dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.cost;
                pq.push({dist[edge.to], edge.to});
                parent[edge.to] = edge.from;
            }
        }
        // If we are trying to solve 'Single Pair Shortest Path (SPSP)' we can add a new function parameter
        // 'dest_vertex' and stop early at this point once we meet the condition: 'vertex == dest_vertex'.
        // If we want to return a 'bfs_result' for path reconstruction we can just break the loop.
        // But if we want just to return the shortest distance we can make a 'return dist[dest_vertex]' at
        // at this point, also putting a 'return POSITIVE_INFINITY' at the end of the function, instead of
        // returning a 'dijkstra_result', which means that 'dest_vertex' is not reachable from 'src_vertex'.
    }

    return {src_vertex, dist, parent};
}

void display_shortest_path(const dijkstra_result &result, int dest_vertex) {
    std::cout << "From " << result.src_vertex << " to " << dest_vertex << ": ["
              << std::setw(4) << result.dist[dest_vertex] << "] ";
    if (result.dist[dest_vertex] == POSITIVE_INFINITY) {
        std::cout << "[unreachable]";
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

void display_all_shortest_paths(const dijkstra_result &result) {
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
