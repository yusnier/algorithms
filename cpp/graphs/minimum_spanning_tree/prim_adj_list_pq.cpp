#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

// Directed edge with a cost.
struct edge {
    int from, to;
    double cost;
    bool operator>(const edge &other) const {
        return cost > other.cost;
    }
};

// Directed graph with adjacency lists.
class graph {
private:
    std::vector<std::vector<edge>> adj_lists;
public:
    explicit graph(int vertices) : adj_lists(vertices, std::vector<edge>()) {}
    std::size_t size() const { return adj_lists.size(); }
    const std::vector<edge> &adj_list(int vertex) const { return adj_lists[vertex]; }
    void add_directed_edge(const edge &e) {
        adj_lists[e.from].push_back(e);
    }
    void add_undirected_edge(const edge &e) {
        add_directed_edge(e);
        add_directed_edge({e.to, e.from, e.cost});
    }
};

struct prim_result {
    const double min_cost;
    const std::vector<edge> mst;
};

prim_result prim(const graph &g) {
    // We can start the algorithm from any vertex, in this case we choose vertex 0.
    constexpr int src_vertex = 0;
    // Boolean vector to mark visited/unvisited for each vertex.
    std::vector<bool> visited(g.size(), false);
    visited[src_vertex] = true;
    // Priority queue (min-heap) to select the best edge (lowest cost) that are part of the MST.
    // If what we want is to determine the 'Maximum Spanning Tree' instead of the 'Minimum', we
    // only need to use a priority queue configured has a max-heap, where the best edge selected
    // each time will be the one with the highest cost.
    std::priority_queue<edge, std::vector<edge>, std::greater<>> pq;
    for (const auto &edge: g.adj_list(src_vertex)) {
        pq.push(edge);
    }

    double min_cost = 0;
    std::vector<edge> mst;

    while (!pq.empty() && mst.size() < g.size() - 1) {
        const edge current_edge = pq.top();
        pq.pop();
        // Skip any edge pointing to an already visited node.
        if (visited[current_edge.to]) { continue; }

        mst.push_back(current_edge);
        min_cost += current_edge.cost;
        visited[current_edge.to] = true;

        for (const auto &edge: g.adj_list(current_edge.to)) {
            if (visited[edge.to]) { continue; }
            pq.push(edge);
        }

    }

    // Check if MST spans entire graph.
    if (mst.size() < g.size() - 1) {
        return {0, {}};
    }

    return {min_cost, mst};
}

void display_minimum_spanning_tree(const prim_result &result) {
    if (result.mst.empty()) {
        std::cout << "No Minimum Spanning Tree (MST) found" << std::endl;
        return;
    }
    std::cout << "MST cost: " << result.min_cost << std::endl;
    for (const auto &edge: result.mst) {
        std::cout << "(" << edge.from << ", " << edge.to << ") -> " << edge.cost << std::endl;
    }
}

int main() {
    std::cout << "Example 1" << std::endl;  // resources/graph_weighted_1.svg
    {
        graph g(8);
        g.add_undirected_edge({0, 1, 10});
        g.add_undirected_edge({0, 2, 1});
        g.add_undirected_edge({0, 3, 4});
        g.add_undirected_edge({1, 2, 3});
        g.add_undirected_edge({1, 4, 0});
        g.add_undirected_edge({2, 3, 2});
        g.add_undirected_edge({2, 5, 8});
        g.add_undirected_edge({3, 5, 2});
        g.add_undirected_edge({3, 6, 7});
        g.add_undirected_edge({4, 5, 1});
        g.add_undirected_edge({4, 7, 8});
        g.add_undirected_edge({5, 6, 6});
        g.add_undirected_edge({5, 7, 9});
        g.add_undirected_edge({6, 7, 12});
        const prim_result result = prim(g);
        display_minimum_spanning_tree(result);
    }
    std::cout << "Example 2" << std::endl;  // resources/graph_weighted_2.svg
    {
        graph g(10);
        g.add_undirected_edge({0, 1, 5});
        g.add_undirected_edge({1, 2, 4});
        g.add_undirected_edge({2, 9, 2});
        g.add_undirected_edge({0, 4, 1});
        g.add_undirected_edge({0, 3, 4});
        g.add_undirected_edge({1, 3, 2});
        g.add_undirected_edge({2, 7, 4});
        g.add_undirected_edge({2, 8, 1});
        g.add_undirected_edge({9, 8, 0});
        g.add_undirected_edge({4, 5, 1});
        g.add_undirected_edge({5, 6, 7});
        g.add_undirected_edge({6, 8, 4});
        g.add_undirected_edge({4, 3, 2});
        g.add_undirected_edge({5, 3, 5});
        g.add_undirected_edge({3, 6, 11});
        g.add_undirected_edge({6, 7, 1});
        g.add_undirected_edge({3, 7, 2});
        g.add_undirected_edge({7, 8, 6});
        const prim_result result = prim(g);
        display_minimum_spanning_tree(result);
    }
    return 0;
}
