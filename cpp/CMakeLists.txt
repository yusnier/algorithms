cmake_minimum_required(VERSION 3.19)
project(algorithms)

set(CMAKE_CXX_STANDARD 14)

add_executable(next_permutation combinatorics/permutations/next_permutation.cpp)
add_executable(prev_permutation combinatorics/permutations/prev_permutation.cpp)
add_executable(heap_generator combinatorics/permutations/heap_generator.cpp)

add_executable(bellman_ford_adj_matrix graphs/bellman_ford_adj_matrix.cpp)
add_executable(dijkstra_adj_matrix graphs/dijkstra_adj_matrix.cpp)