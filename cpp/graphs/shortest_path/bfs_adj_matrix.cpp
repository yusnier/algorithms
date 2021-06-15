/**
 * An implementation of BFS with an adjacency matrix.
 *
 * @author Yusnier M. Sosa, yusnier.msv@gmail.com
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();

typedef std::vector<std::vector<double>> adjacency_matrix;

struct bfs_result {
    const int src_vertex;
    const std::vector<double> dist;
    const std::vector<int> parent;
};

bfs_result bfs(const adjacency_matrix &m, int src_vertex) {
    const int vertices = static_cast<int>(m.size());
    // Initialize the distance to all vertices to be infinity except for the start vertex which is zero.
    // dist[i] is the current shortest distance from 'src_vertex' to vertex i.
    std::vector<double> dist(vertices, POSITIVE_INFINITY);
    dist[src_vertex] = 0;
    // This array will allows for shortest path reconstruction (if required) after the algorithm has terminated.
    // parent[i] is the vertex where vertex i comes from in the shortest path.
    std::vector<int> parent(vertices, -1);
    // Start by visiting 'src_vertex' and add it to the queue.
    std::queue<int> q;
    q.push(src_vertex);

    while (!q.empty()) {
        const int vertex = q.front(); q.pop();
        for (auto i = 0; i < vertices; ++i) {
            // Ignoring invalid edges.
            if (m[vertex][i] == POSITIVE_INFINITY) { continue; }
            // We enqueue only the unvisited neighboring vertices.
            if (dist[i] == POSITIVE_INFINITY) {
                dist[i] = dist[vertex] + 1;
                q.push(i);
                parent[i] = vertex;
            }
        }
        // If we are trying to solve 'Single Pair Shortest Path (SPSP)' we can add a new function parameter
        // 'dest_vertex' and stop early at this point once we meet the condition: 'vertex == dest_vertex'.
        // If we want to return a 'bfs_result' for path reconstruction we can just break the loop.
        // But if we want just to return the shortest distance we can make a 'return dist[dest_vertex]' at
        // at this point, also putting a 'return POSITIVE_INFINITY' at the end of the function, instead of
        // returning a 'bfs_result', which means that 'dest_vertex' is not reachable from 'src_vertex'.
    }

    return bfs_result{src_vertex, dist, parent};
}

void display_shortest_path(const bfs_result &result, int dest_vertex) {
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

void display_all_shortest_paths(const bfs_result &result) {
    const int vertices = static_cast<int>(result.dist.size());
    for (auto dest_vertex = 0; dest_vertex < vertices; ++dest_vertex) {
        display_shortest_path(result, dest_vertex);
    }
}

adjacency_matrix setup_disconnected_adjacency_matrix(int vertices) {
    // Fill all edges with infinity by default.
    adjacency_matrix result(vertices, std::vector<double>(vertices, POSITIVE_INFINITY));
    // Assuming the distance for a vertex to reach itself is 0.
    for (auto i = 0; i < vertices; ++i) {
        result[i][i] = 0;
    }
    return result;
}

int main() {
    std::cout << "Example 1" << std::endl;  // resources/digraph_unweighted.svg
    {
        adjacency_matrix m = setup_disconnected_adjacency_matrix(12);
        m[0][1] = 1;
        m[1][2] = 1;
        m[1][3] = 1;
        m[1][4] = 1;
        m[2][5] = 1;
        m[3][5] = 1;
        m[4][3] = 1;
        m[4][4] = 1;
        m[4][6] = 1;
        m[5][2] = 1;
        m[5][6] = 1;
        m[5][7] = 1;
        m[6][9] = 1;
        m[7][8] = 1;
        m[7][10] = 1;
        m[8][6] = 1;
        m[9][8] = 1;
        const bfs_result result = bfs(m, 1);
        display_all_shortest_paths(result);
    }
    return 0;
}
