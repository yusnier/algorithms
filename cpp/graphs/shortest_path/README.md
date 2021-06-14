# Graphs algorithms
### Single source shortest path (SSSP)
- **SSSP on Unweighted Graph**
  - DFS
  - BFS
- **SSSP on Weighted Graph**
  - Dijkstra
    - [Adjacency list](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/dijkstra_adj_list.cpp) **O(EV)**
    - [Adjacency list using Priority Queue](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/dijkstra_adj_list_pq.cpp) **O(Elog(V))**
    - [Adjacency matrix](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/dijkstra_adj_matrix.cpp) **O(EV)**
    - [Adjacency matrix using Priority Queue](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/dijkstra_adj_matrix_pq.cpp) **O(Elog(V))**
- **SSSP on Graph with Negative Weight Cycle**
  - Bellman-Ford
    - [Adjacency list](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/bellman_ford_adj_list.cpp) **O(VE</sup>)**
    - [Adjacency matrix](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/bellman_ford_adj_matrix.cpp) **O(V<sup>3</sup>)**
    - [Edge list](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/bellman_ford_edge_list.cpp) **O(VE</sup>)**
### All pairs shortest path (APSP)
- **APSP on Graph with Negative Weight Cycle**
  - Floyd-Warshall
    - [Adjacency matrix](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/floyd_warshall_adj_matrix.cpp) **O(V<sup>3</sup>)**
### Single pair shortest path (SPSP)
- **SPSP** algorithms are implemented by making modifications on the **SSSP** algorithms,
  generally stopping the search as soon as the destination vertex is reached.
### Single destination shortest path (SDSP)
- **SDSP** algorithms are implemented by making modifications on **SSSP** algorithms, generally
  using the destination as the starting vertex, then we can build the paths by reversing the order.
  For the particular case of directed graphs, we also need to reverse the edges before applying the
  **SSSP** algorithm.
###Finding the (Cheapest/Negative) Cycle
###Finding the Diameter of a Graph