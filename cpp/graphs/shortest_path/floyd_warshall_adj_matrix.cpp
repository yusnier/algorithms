/**
 * This file contains an implementation of the Floyd-Warshall algorithm to find all pairs of
 * shortest paths between nodes in a graph. We also demonstrate how to detect negative cycles and
 * reconstruct the shortest path.
 *
 * @author Yusnier M. Sosa, yusnier.msv@gmail.com
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
constexpr double NEGATIVE_INFINITY = -POSITIVE_INFINITY;

template <typename T>
struct matrix {
    typedef std::vector<std::vector<T>> type;
};

typedef matrix<double>::type adjacency_matrix;
typedef matrix<int>::type parent_matrix;

struct floyd_warshall_result {
    const adjacency_matrix dp;
    const parent_matrix parent;
};

floyd_warshall_result floyd_warshall(const adjacency_matrix &m) {
    const int vertices = static_cast<int>(m.size());
    // This matrix is the one that will be processed by the algorithm.
    adjacency_matrix dp(vertices, std::vector<double>(vertices, 0));
    // This matrix will allows for shortest path reconstruction (if required) after the algorithm has terminated.
    // parent[i][j] is the vertex where vertex j comes from in the shortest path.
    parent_matrix parent(vertices, std::vector<int>(vertices, -1));

    // Copy input matrix and setup 'parent' matrix for path reconstruction.
    for (auto i = 0; i < vertices; ++i) {
        for (auto j = 0; j < vertices; ++j) {
            dp[i][j] = m[i][j];
            if (m[i][j] != POSITIVE_INFINITY) {
                parent[i][j] = i;
            }
        }
//        if (m[i][i] == 0) {
//            dp[i][i] = POSITIVE_INFINITY;
//        }
    }
    // Compute all pairs shortest paths.
    for (int k = 0; k < vertices; ++k) {
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (dp[i][k] + dp[k][j] < dp[i][j]) {
                    dp[i][j] = dp[i][k] + dp[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }


    std::cout << "  | ";
    for (int j = 0; j < vertices; ++j) {
        std::cout << std::setw(4) << j << " ";
    }
    std::cout << std::endl;
    std::cout << "----";
    for (int j = 0; j < vertices; ++j) {
        std::cout << "-----";
    }
    std::cout << std::endl;
    for (int i = 0; i < vertices; ++i) {
        std::cout << std::setw(2) << i << "| ";
        for (int j = 0; j < vertices; ++j) {
            std::cout << std::setw(4) << dp[i][j] << " ";
        }
        std::cout << std::endl;
    }


    // Identify negative cycles by propagating the value 'NEGATIVE_INFINITY'
    // to every edge that is part of or reaches into a negative cycle.
    for (int k = 0; k < vertices; ++k) {
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (dp[i][k] != POSITIVE_INFINITY && dp[k][j] != POSITIVE_INFINITY && dp[k][k] < 0) {
                    dp[i][j] = NEGATIVE_INFINITY;
                    parent[i][j] = -1;
                }
            }
        }
    }
    std::cout << "  | ";
    for (int j = 0; j < vertices; ++j) {
        std::cout << std::setw(4) << j << " ";
    }
    std::cout << std::endl;
    std::cout << "----";
    for (int j = 0; j < vertices; ++j) {
        std::cout << "-----";
    }
    std::cout << std::endl;
    for (int i = 0; i < vertices; ++i) {
        std::cout << std::setw(2) << i << "| ";
        for (int j = 0; j < vertices; ++j) {
            std::cout << std::setw(4) << dp[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return floyd_warshall_result{dp, parent};
}

void display_shortest_path(const floyd_warshall_result &result, int src_vertex, int dest_vertex) {
    std::cout << "From " << src_vertex << " to " << dest_vertex << ": ["
              << std::setw(4) << result.dp[src_vertex][dest_vertex] << "] ";
    if (result.dp[src_vertex][dest_vertex] == POSITIVE_INFINITY) {
        std::cout << "[unreachable]";
    } else if (result.dp[src_vertex][dest_vertex] == NEGATIVE_INFINITY) {
        std::cout << "[negative cycle]";
    } else {
        std::vector<int> path;
        auto at = dest_vertex;
        for (; at != src_vertex; at = result.parent[src_vertex][at]) {
            path.push_back(at);
        }
        path.push_back(at);
        std::reverse(path.begin(), path.end());
        std::cout << "[" << path[0];
        for (auto i = 1; i < path.size(); ++i) {
            std::cout << " -> " << path[i] << "";
        }
        std::cout << "]";
    }
    std::cout << std::endl;
}

void display_all_shortest_paths(const floyd_warshall_result &result, int src_vertex) {
    const int vertices = static_cast<int>(result.dp.size());
    for (auto dest_vertex = 0; dest_vertex < vertices; ++dest_vertex) {
        display_shortest_path(result, src_vertex, dest_vertex);
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
//    std::cout << "Example 1" << std::endl;  // https://www.youtube.com/watch?v=pSqmAO-m7Lk (graph example 2)
//    {
//        adjacency_matrix m = setup_disconnected_adjacency_matrix(6);
//        m[0][1] = 5;
//        m[0][2] = 1;
//        m[1][2] = 2;
//        m[1][3] = 3;
//        m[1][4] = 20;
//        m[2][1] = 3;
//        m[2][4] = 12;
//        m[3][2] = 3;
//        m[3][4] = 2;
//        m[3][5] = 6;
//        m[4][5] = 1;
//        const floyd_warshall_result result = floyd_warshall(m);
//        display_all_shortest_paths(result, 0);
//    }
//    std::cout << "Example 2" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 1)
//    {
//        adjacency_matrix m = setup_disconnected_adjacency_matrix(7);
//        m[0][1] = 4;
//        m[0][6] = 2;
//        m[1][1] = -1;
//        m[1][2] = 3;
//        m[2][3] = 3;
//        m[2][4] = 1;
//        m[3][5] = -2;
//        m[4][5] = 2;
//        m[6][4] = 2;
//        const floyd_warshall_result result = floyd_warshall(m);
//        display_all_shortest_paths(result, 0);
//    }
//    std::cout << "Example 3" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 2)
//    {
//        adjacency_matrix m = setup_disconnected_adjacency_matrix(10);
//        m[0][1] = 5;
//        m[1][2] = 20;
//        m[1][5] = 30;
//        m[1][6] = 60;
//        m[2][3] = 10;
//        m[2][4] = 75;
//        m[3][2] = -15;
//        m[4][9] = 100;
//        m[5][4] = 25;
//        m[5][6] = 5;
//        m[5][8] = 50;
//        m[6][7] = -50;
//        m[7][8] = -10;
//        const floyd_warshall_result result = floyd_warshall(m);
//        display_all_shortest_paths(result, 0);
//    }
//    std::cout << "Example 4" << std::endl;  // https://www.youtube.com/watch?v=lyw4FaxrwHg (graph example 3 from github)
//    {
//        adjacency_matrix m = setup_disconnected_adjacency_matrix(9);
//        m[0][1] = 1;
//        m[1][2] = 1;
//        m[2][4] = 1;
//        m[4][3] = -3;
//        m[3][2] = 1;
//        m[1][5] = 4;
//        m[1][6] = 4;
//        m[5][6] = 5;
//        m[6][7] = 4;
//        m[5][7] = 3;
//        const floyd_warshall_result result = floyd_warshall(m);
//        display_all_shortest_paths(result, 0);
//    }
    std::cout << "Example 5" << std::endl;  // resources/digraph_weighted_neg_cycles.svg
    {
        adjacency_matrix m = setup_disconnected_adjacency_matrix(12);
        m[0][1] = 1;
        m[1][2] = 8;
        m[1][3] = 4;
        m[1][4] = 1;
        m[2][5] = 2;
        m[3][5] = 2;
        m[4][3] = 2;
        m[4][4] = 3;
        m[4][6] = 6;
        m[5][2] = 1;
        m[5][6] = 1;
        m[5][7] = 2;
        m[6][9] = 1;
        m[7][8] = 1;
        m[7][10] = 1;
        m[8][6] = 3;
        m[9][8] = -6;
        m[10][10] = -1;
        const floyd_warshall_result result = floyd_warshall(m);
        display_all_shortest_paths(result, 1);
    }
//    std::cout << "Example 5" << std::endl;  // resources/digraph_weighted_neg_cycles.svg
//    {
//        adjacency_matrix m = setup_disconnected_adjacency_matrix(2);
//        m[0][1] = 1;
//        const floyd_warshall_result result = floyd_warshall(m);
//        display_all_shortest_paths(result, 0);
//    }
//    return 0;
}
