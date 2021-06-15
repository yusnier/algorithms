# Graphs algorithms
### Single source shortest path (SSSP)
- SSSP on Unweighted Graph
  - **Breadth First Search (BFS)**
    - [Adjacency list](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/bfs_adj_list.cpp) **O(V+E)**
    - [Adjacency matrix](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/bfs_adj_matrix.cpp) **O(V<sup>2</sup>)**
- SSSP on Weighted Graph
  - **Dijkstra**
    - [Adjacency list](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/dijkstra_adj_list.cpp) **O(EV)**
    - [Adjacency list using Priority Queue](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/dijkstra_adj_list_pq.cpp) **O(Elog(V))**
    - [Adjacency matrix](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/dijkstra_adj_matrix.cpp) **O(EV)**
    - [Adjacency matrix using Priority Queue](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/dijkstra_adj_matrix_pq.cpp) **O(Elog(V))**
- SSSP on Graph with Negative Weight Cycle
  - **Bellman-Ford**
    - [Adjacency list](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/bellman_ford_adj_list.cpp) **O(VE)**
    - [Adjacency matrix](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/bellman_ford_adj_matrix.cpp) **O(V<sup>3</sup>)**
    - [Edge list](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/bellman_ford_edge_list.cpp) **O(VE)**
### All pairs shortest path (APSP)
- **APSP** on Graph with Negative Weight Cycle
  - **Floyd-Warshall**
    - [Adjacency matrix](https://github.com/yusnier/algorithms/blob/main/cpp/graphs/shortest_path/floyd_warshall_adj_matrix.cpp) **O(V<sup>3</sup>)**
    - Finding the (Cheapest/Negative) Cycle
      > Floyd-Warshall algorithm can be used to detect whether the (small) graph has a **cycle**,
      a **negative cycle**, and even finding the **cheapest (non-negative) cycle** among all possible
      cycles. To do this, we initially set the *main diagonal* of the adjacency matrix to have a very
      large default value (i.e. **POSITIVE_INFINITY**) instead of **0**, then, we run the **O(V<sup>3</sup>)**
      Floyd-Warshall algorithm. Now, we check the value of **adjacency_matrix[i][i]**, which now means the
      shortest cyclic path weight starting from vertex **i** that goes through up to **V-1** other intermediate
      vertices and returns back to **i**. If **adjacency_matrix[i][i]** is no longer **POSITIVE_INFINITY** for
      any **i ∈ [0..V-1]**, then we have a cycle. The smallest non-negative **adjacency_matrix[i][i] ∀i ∈ [0..V-1]**
      is the cheapest cycle. If **adjacency_matrix[i][i] < 0** for any **i ∈ [0..V-1]**, then we have a negative
      cycle because if we take this cyclic path one more time, we will get an even shorter 'shortest' path.
    - Finding the Diameter of a Graph
      > The **diameter of a graph** is defined as *the maximum shortest path distance between
      any pair of vertices of that graph.* To find the diameter of a graph, we first find the
      shortest path between each pair of vertices, the maximum distance found is the diameter of
      the graph. To solve this problem, we can first run an **O(V<sup>3</sup>)** Floyd-Warshall’s
      to compute the required APSP information. Then, we can figure out what is the diameter of the
      graph by finding the maximum value in the resulting adjacent matrix in **O(V<sup>2</sup>)**.
      We should only do this for a small graph with **V ≤ 400**.
### Single pair shortest path (SPSP)
> **SPSP** algorithms are implemented by making modifications on the **SSSP** algorithms, generally
stopping the search as soon as the destination vertex is reached.
### Single destination shortest path (SDSP)
> **SDSP** algorithms are implemented by making modifications on **SSSP** algorithms, generally using the
destination as the starting vertex, then we can build the paths by reversing the order. For the particular
case of directed graphs, we also need to reverse the edges before applying the **SSSP** algorithm.
### SSSP/APSP Algorithm Decision Table
Presenting an **SSSP/APSP** algorithm decision table within the context of programming
contest, to help the readers in deciding which algorithm to choose depending on
various graph criteria. The terminologies used are as follows: ‘Best’ → the most suitable
algorithm; ‘Ok’ → a correct algorithm but not the best; ‘Bad’ → a (very) slow algorithm;
‘WA’ → an incorrect algorithm; and ‘Overkill’ → a correct algorithm but unnecessary.

| Graph Criteria  | BFS            | Dijkstra          | Bellman-Ford   | Floyd-Warshall       |
|-----------------|----------------|-------------------|----------------|----------------------|
| Complexity      | **O(V+E)**     | **O((V+E)logV )** | **O(VE)**      | **O(V<sup>3</sup>)** |
| Max Size        | V, E ≤ 10M     | V, E ≤ 300K       | V E ≤ 10M      | V ≤ 400              |
| Unweighted      | Best           | Ok                | Bad            | Bad in general       |
| Weighted        | WA             | Best              | Ok             | Bad in general       |
| Negative weight | WA             | Our variant Ok    | Ok             | Bad in general       |
| Negative cycle  | Cannot detect  | Cannot detect     | Can detect     | Can detect           |
| Small graph     | WA if weighted | Overkill          | Overkill       | Best                 |


