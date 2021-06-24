#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

template<class T>
struct matrix {
    typedef std::vector<std::vector<T>> type;
};
typedef matrix<int>::type grid_type;
typedef matrix<bool>::type visited_type;

struct cell {
    int row, col;
};

int scan_new_region(int start_row, int start_col, const grid_type &grid, visited_type &visited) {
    constexpr int row_dir[] = {-1, -1,  0,  1,  1,  1,  0, -1};  // 8  1  2
    constexpr int col_dir[] = { 0,  1,  1,  1,  0, -1, -1, -1};  // 7  X  3
                                                                 // 6  5  4
    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(grid[0].size());

    std::queue<cell> q;
    q.push({start_row, start_col});
    visited[start_row][start_col] = true;
    int count = 0;

    // Scanning the new region using a BFS (queue) approach.
    // We could perfectly use a DFS (stack) approach instead.
    while (!q.empty()) {
        const cell current = q.front(); q.pop();
        ++count;
        for (int i = 0; i < 8; ++i) {
            const cell neighbor = {current.row + row_dir[i], current.col + col_dir[i]};
            if (neighbor.row >= 0 && neighbor.row < rows && neighbor.col >= 0 && neighbor.col < cols &&
                grid[neighbor.row][neighbor.col] == 1 && !visited[neighbor.row][neighbor.col]) {
                visited[neighbor.row][neighbor.col] = true;
                q.push(neighbor);
            }
        }
    }

    return count;
}

int max_region(const grid_type &grid) {
    assert(!grid.empty());
    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(grid[0].size());

    matrix<bool>::type visited(rows, std::vector<bool>(cols, false));
    int max_region_size = 0;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (grid[row][col] == 1 && !visited[row][col]) {
                int region_size = scan_new_region(row, col, grid, visited);
                max_region_size = std::max(max_region_size, region_size);
            }
        }
    }

    return max_region_size;
}

int main() {
    int m, n;
    std::cin >> m >> n;
    grid_type grid(m, std::vector<int>(n, 0));

    for (int row = 0; row < m; ++row) {
        for (int col = 0; col < n; ++col) {
            std::cin >> grid[row][col];
        }
    }

    std::cout << max_region(grid) << std::endl;

    // Problem reference: https://www.hackerrank.com/challenges/ctci-connected-cell-in-a-grid/problem

    // Sample input:
    // 4
    // 4
    // 1 1 0 0
    // 0 1 1 0
    // 0 0 1 0
    // 1 0 0 0
    //
    // Sample Output:
    // 5

    // Sample input:
    // 5
    // 4
    // 0 0 1 1
    // 0 0 1 0
    // 0 1 1 0
    // 0 1 0 0
    // 1 1 0 0
    //
    // Sample Output:
    // 8
}
