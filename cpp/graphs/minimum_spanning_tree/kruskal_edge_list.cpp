/**
 * An implementation of Kruskal's MST algorithm using an edge list Time Complexity: O(ElogE)
 *
 * @author Yusnier M. Sosa, yusnier.msv@gmail.com
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class UnionFind {
private:
    // Number of elements in this union find.
    int uf_size;
    // Track the union of the components in the union find.
    int n_components;
    // id[i] points to the parent of i, if id[i] == i then i is a root node.
    std::vector<int> id;
    // Used to track the sizes of each of the components.
    std::vector<int> sz;
public:
    explicit UnionFind(int size) : uf_size(size), n_components(size), id(size, 0), sz(size, 0) {
        assert(size >= 0);
        for (auto i = 0; i < size; ++i) {
            id[i] = i;  // Link to itself (self root).
            sz[i] = 1;  // Each component is originally of size one.
        }
    }
    // Return the number of elements in this UnionFind/Disjoint set.
    int size() const {
        return uf_size;
    }
    // Returns the number of remaining components/sets.
    int num_components() const {
        return n_components;
    }
    // Find which components/set 'p' belongs to, takes amortized constant time.
    int find(int p) {
        // Find the root of the component/set.
        int root = p;
        while (root != id[root]) {
            root = id[root];
        }
        // Compress the path leading back to the root.
        // Doing this operation is called "path compression" and is what give us amortized constant time complexity.
        while (p != root) {
            int next = id[p];
            id[p] = root;
            p = next;
        }
        return root;
    }
    // Return whether or not the elements 'p' and 'q' are in the same components/set.
    bool connected(int p, int q) {
        return find(p) == find(q);
    }
    // Return the size of components/set 'p' belong to.
    int component_size(int p) {
        return sz[find(p)];
    }
    // Unify the components/sets containing elements 'p' and 'q'.
    void union_set(int p, int q) {
        int root1 = find(p);
        int root2 = find(q);
        // These elements are in the same group!
        if (root1 == root2) { return; }
        // Merge two components/sets together. Merge smaller component/set into the larger one.
        if (sz[root1] < sz[root2]) {
            sz[root2] += sz[root1];
            id[root1] = root2;
        } else {
            sz[root1] += sz[root2];
            id[root2] = root1;
        }
        // Since roots found are different we know that the number of components/sets has decreased by one.
        --n_components;
    }
};

// Undirected edge with a cost.
struct edge {
    int from, to;
    double cost;
    edge(int from, int to, int cost): from(from), to(to), cost(cost) {}
};

struct kruskal_result {
    const double min_cost;
    const std::vector<edge> mts;
};

kruskal_result kruskal(int vertices, const std::vector<edge> &edges) {
    double min_cost = 0;
    std::vector<edge> mst;

    std::vector<edge> sorted_edges = edges;
    std::sort(sorted_edges.begin(), sorted_edges.end(), [](const edge &a, const edge &b) -> bool {
        return a.cost < b.cost;
    });

    UnionFind uf(vertices);
    for (const auto &edge: sorted_edges) {
        // Skip this edge to avoid creating a cycle in MST
        if (uf.connected(edge.from, edge.to)) { continue; };
        // Include this edge
        uf.union_set(edge.from, edge.to);
        min_cost += edge.cost;
        mst.push_back(edge);
        // Optimization to stop early if we found a MST that includes all the nodes.
        if (uf.component_size(0) == vertices) { break; }
    }

    // Make sure we have a MST that includes all the nodes.
    if (uf.component_size(0) != vertices) {
        return kruskal_result{0, std::vector<edge>()};
    }

    return kruskal_result{min_cost, mst};
}

void display_minimum_spanning_tree(const kruskal_result &result) {
    if (result.mts.empty()) {
        std::cout << "No Minimum Spanning Tree (MST) found" << std::endl;
        return;
    }
    std::cout << "MTS Cost: " << result.min_cost << std::endl;
    for (const auto &edge: result.mts) {
        std::cout << "Used edge (" << edge.from << ", " << edge.to << ") with cost: " << edge.cost << std::endl;
    }
}

int main() {
    std::cout << "Example 1" << std::endl;  // https://www.youtube.com/watch?v=JZBQLXgSGfs
    {
        std::vector<edge> edges{
                edge(0, 1, 5),
                edge(1, 2, 4),
                edge(2, 9, 2),
                edge(0, 4, 1),
                edge(0, 3, 4),
                edge(1, 3, 2),
                edge(2, 7, 4),
                edge(2, 8, 1),
                edge(9, 8, 0),
                edge(4, 5, 1),
                edge(5, 6, 7),
                edge(6, 8, 4),
                edge(4, 3, 2),
                edge(5, 3, 5),
                edge(3, 6, 11),
                edge(6, 7, 1),
                edge(3, 7, 2),
                edge(7, 8, 6),
        };
        const kruskal_result result = kruskal(10, edges);
        display_minimum_spanning_tree(result);
    }
    return 0;
}