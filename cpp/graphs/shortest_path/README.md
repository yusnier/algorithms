# Graphs algorithms
### Single source shortest path (SSSP)
- **SSSP on Unweighted Graph**
  - Breadth First Search (BFS)
    - [Adjacency list](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/bfs_adj_list.cpp) **O(EV)**
    - [Adjacency matrix](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/bfs_adj_matrix.cpp) **O(EV)**
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
- > **SPSP** algorithms are implemented by making modifications on the **SSSP** algorithms,
  > generally stopping the search as soon as the destination vertex is reached.
### Single destination shortest path (SDSP)
- > **SDSP** algorithms are implemented by making modifications on **SSSP** algorithms, generally
  > using the destination as the starting vertex, then we can build the paths by reversing the order.
  > For the particular case of directed graphs, we also need to reverse the edges before applying the
  > **SSSP** algorithm.
### Finding the (Cheapest/Negative) Cycle
- > Bellman Ford’s can be used to check if the given graph has negative cycle. Floyd Warshall’s also terminates
after O(V^3 ) steps regardless of the type of input graph. This feature allows Floyd Warshall’s
to be used to detect whether the (small) graph has a cycle, a negative cycle, and even finding
the cheapest (non-negative) cycle among all possible cycles (the girth of the graph).
To do this, we initially set the main diagonal of the Adjacency Matrix to have a very
large value, i.e. AdjMat[i][i] = INF (1B). Then, we run the O(V 3 ) Floyd Warshall’s
algorithm. Now, we check the value of AdjMat[i][i], which now means the shortest cyclic
path weight starting from vertex i that goes through up to V -1 other intermediate vertices
and returns back to i. If AdjMat[i][i] is no longer INF for any i ∈ [0..V-1], then we
have a cycle. The smallest non-negative AdjMat[i][i] ∀i ∈ [0..V-1] is the cheapest cycle.
If AdjMat[i][i] < 0 for any i ∈ [0..V-1], then we have a negative cycle because if we
take this cyclic path one more time, we will get an even shorter ‘shortest’ path.
### Finding the Diameter of a Graph