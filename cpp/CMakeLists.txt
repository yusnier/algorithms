cmake_minimum_required(VERSION 3.19)
project(algorithms)

set(CMAKE_CXX_STANDARD 14)


add_executable(connected_cells_in_a_grid bfs/connected_cells_in_a_grid.cpp)

add_executable(1_maximum_spend dynamic_programming/1_wedding_shopping/1_maximum_spend.cpp)

add_executable(max_1d_range_sum dynamic_programming/2_max_range_sum/max_1d_range_sum.cpp)
add_executable(max_2d_range_sum dynamic_programming/2_max_range_sum/max_2d_range_sum.cpp)

add_executable(1_lis "dynamic_programming/3_longest_increasing_subsequence_(LIS)/1_lis.cpp")
add_executable(2_lis_solutions "dynamic_programming/3_longest_increasing_subsequence_(LIS)/2_lis_solutions.cpp")
add_executable(3_box_stacking "dynamic_programming/3_longest_increasing_subsequence_(LIS)/3_box_stacking.cpp")

add_executable(1_knapsack "dynamic_programming/4_0-1_knapsack_(subset_sum)/1_knapsack.cpp")
add_executable(2_knapsack_solutions "dynamic_programming/4_0-1_knapsack_(subset_sum)/2_knapsack_solutions.cpp")

add_executable(1_can_sum "dynamic_programming/5_coin_change_(CC)/tabulation/1_can_sum.cpp")
add_executable(2_how_sum "dynamic_programming/5_coin_change_(CC)/tabulation/2_how_sum.cpp")
add_executable(3_best_sum "dynamic_programming/5_coin_change_(CC)/tabulation/3_best_sum.cpp")
add_executable(4_how_many_sums_rep "dynamic_programming/5_coin_change_(CC)/tabulation/4_how_many_sums_rep.cpp")
add_executable(5_all_sums_rep "dynamic_programming/5_coin_change_(CC)/tabulation/5_all_sums_rep.cpp")
add_executable(6_all_sums_no_rep "dynamic_programming/5_coin_change_(CC)/tabulation/6_all_sums_no_rep.cpp")
add_executable(7_all_sums_no_rep_dfs "dynamic_programming/5_coin_change_(CC)/tabulation/7_all_sums_no_rep_dfs.cpp")

add_executable(next_permutation combinatorics/permutations/next_permutation.cpp)
add_executable(prev_permutation combinatorics/permutations/prev_permutation.cpp)
add_executable(heap_generator combinatorics/permutations/heap_generator.cpp)

add_executable(kruskal_edge_list graphs/minimum_spanning_tree/kruskal_edge_list.cpp)

add_executable(bellman_ford_adj_list graphs/shortest_path/bellman_ford_adj_list.cpp)
add_executable(bellman_ford_adj_matrix graphs/shortest_path/bellman_ford_adj_matrix.cpp)
add_executable(bellman_ford_edge_list graphs/shortest_path/bellman_ford_edge_list.cpp)

add_executable(bfs_adj_list graphs/shortest_path/bfs_adj_list.cpp)
add_executable(bfs_adj_matrix graphs/shortest_path/bfs_adj_matrix.cpp)

add_executable(dijkstra_adj_list graphs/shortest_path/dijkstra_adj_list.cpp)
add_executable(dijkstra_adj_list_pq graphs/shortest_path/dijkstra_adj_list_pq.cpp)
add_executable(dijkstra_adj_matrix graphs/shortest_path/dijkstra_adj_matrix.cpp)
add_executable(dijkstra_adj_matrix_pq graphs/shortest_path/dijkstra_adj_matrix_pq.cpp)

add_executable(floyd_warshall_adj_matrix graphs/shortest_path/floyd_warshall_adj_matrix.cpp)

add_executable(test test.cpp)
