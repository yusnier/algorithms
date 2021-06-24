#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

typedef std::vector<std::vector<int>> matrix;

// Transforms the argument matrix 'm' into a cumulative sum matrix applying the inclusion-exclusion
// principle. With the sum matrix, we can answer the sum of any sub-matrix (i, j) to (k, l) in O(1).
// In terms of performance, we could take advantage, doing this transformation (if required), while
// reading the matrix from the input in O(n^2).
//  *  *  *  .  _
//  *  *  *  .  _
//  *  *  *  .  _
//  .  .  .  X  _
//  _  _  _  _  _
void transform_to_sum_matrix(matrix &m) {
    assert(!m.empty());
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m[0].size(); ++j) {
            if (i > 0) {  // if possible, add from top
                m[i][j] += m[i - 1][j];
            }
            if (j > 0) {  // if possible, add from left
                m[i][j] += m[i][j - 1];
            }
            if (i > 0 && j > 0) {  // avoid double count
                m[i][j] -= m[i - 1][j - 1];
            }
        }
    }
}

// Returns the maximum sum of a sub-matrix on 'm' in O(n^4).
int max_sub_matrix_sum(const matrix &m) {
    assert(!m.empty());
    const int rows = static_cast<int>(m.size());
    const int cols = static_cast<int>(m[0].size());

    matrix sum_m = m;
    transform_to_sum_matrix(sum_m);

    int max_sub_matrix_sum = std::numeric_limits<int>::min();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = i; k < rows; ++k) {
                for (int l = j; l < cols; ++l) {
                    int sub_matrix_sum = sum_m[k][l];  // sum of all items from (0, 0) to (k, l): O(1)
                    if (i > 0) {  // if possible, subtract from top
                        sub_matrix_sum -= sum_m[i - 1][l];
                    }
                    if (j > 0) {  // if possible, subtract from left
                        sub_matrix_sum -= sum_m[k][j - 1];
                    }
                    if (i > 0 && j > 0) {  // avoiding double subtraction
                        sub_matrix_sum += sum_m[i - 1][j - 1];
                    }
                    max_sub_matrix_sum = std::max(max_sub_matrix_sum, sub_matrix_sum);
                }
            }
        }
    }

    return max_sub_matrix_sum;
}

// Returns the maximum sum of a square sub-matrix on 'm' in O(n^3).
int max_square_sub_matrix_sum(const matrix &m) {
    assert(!m.empty());
    const int rows = static_cast<int>(m.size());
    const int cols = static_cast<int>(m[0].size());

    matrix sum_m = m;
    transform_to_sum_matrix(sum_m);

    int max_sub_square_sum = std::numeric_limits<int>::min();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; (i + k < rows) && (j + k < cols); ++k) {
                int sub_square_sum = sum_m[i + k][j + k];  // sum of all items from (0, 0) to (i + k, j + k): O(1)
                if (i > 0) {  // if possible, subtract from top
                    sub_square_sum -= sum_m[i - 1][j + k];
                }
                if (j > 0) {  // if possible, subtract from left
                    sub_square_sum -= sum_m[i + k][j - 1];
                }
                if (i > 0 && j > 0) {  // avoiding double subtraction
                    sub_square_sum += sum_m[i - 1][j - 1];
                }
                max_sub_square_sum = std::max(max_sub_square_sum, sub_square_sum);
            }
        }
    }

    return max_sub_square_sum;
}

struct sub_matrix_result {
    int sum, i, j, k, l;
};

// Return the sub-matrix of 'm' with the maximum sum in O(n^4).
sub_matrix_result max_sub_matrix_sum_result(const matrix &m) {
    assert(!m.empty());
    const int rows = static_cast<int>(m.size());
    const int cols = static_cast<int>(m[0].size());

    matrix sum_m = m;
    transform_to_sum_matrix(sum_m);

    sub_matrix_result result = {std::numeric_limits<int>::min(), 0, 0, 0, 0};

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = i; k < rows; ++k) {
                for (int l = j; l < cols; ++l) {
                    int sub_matrix_sum = sum_m[k][l];  // sum of all items from (0, 0) to (k, l): O(1)
                    if (i > 0) {  // if possible, subtract from top
                        sub_matrix_sum -= sum_m[i - 1][l];
                    }
                    if (j > 0) {  // if possible, subtract from left
                        sub_matrix_sum -= sum_m[k][j - 1];
                    }
                    if (i > 0 && j > 0) {  // avoiding double subtraction
                        sub_matrix_sum += sum_m[i - 1][j - 1];
                    }
                    if (sub_matrix_sum > result.sum) {
                        result.sum = sub_matrix_sum;
                        result.i = i;
                        result.j = j;
                        result.k = k;
                        result.l = l;
                    }
                }
            }
        }
    }

    return result;
}

// Return the square sub-matrix of 'm' with the maximum sum in O(n^3).
sub_matrix_result max_square_sub_matrix_sum_result(const matrix &m) {
    assert(!m.empty());
    const int rows = static_cast<int>(m.size());
    const int cols = static_cast<int>(m[0].size());

    matrix sum_m = m;
    transform_to_sum_matrix(sum_m);

    sub_matrix_result result = {std::numeric_limits<int>::min(), 0, 0, 0, 0};

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; (i + k < rows) && (j + k < cols); ++k) {
                int sub_square_sum = sum_m[i + k][j + k];  // sum of all items from (0, 0) to (i + k, j + k): O(1)
                if (i > 0) {  // if possible, subtract from top
                    sub_square_sum -= sum_m[i - 1][j + k];
                }
                if (j > 0) {  // if possible, subtract from left
                    sub_square_sum -= sum_m[i + k][j - 1];
                }
                if (i > 0 && j > 0) {  // avoiding double subtraction
                    sub_square_sum += sum_m[i - 1][j - 1];
                }
                if (sub_square_sum > result.sum) {
                    result.sum = sub_square_sum;
                    result.i = i;
                    result.j = j;
                    result.k = i + k;
                    result.l = j + k;
                }
            }
        }
    }

    return result;
}

void test_max_2d_range_sum_algorithms(const matrix &m) {
    // Testing algorithms for maximum sum in sub-matrix of 'm'.
    std::cout << "Sub-matrix with the maximum sum:" << std::endl;
    const int max_2d_range_sum = max_sub_matrix_sum(m);
    const sub_matrix_result max_2d_range_sum_result = max_sub_matrix_sum_result(m);
    assert(max_2d_range_sum == max_2d_range_sum_result.sum);
    std::cout << "from (" << max_2d_range_sum_result.i << ", " << max_2d_range_sum_result.j << ") to ("
              << max_2d_range_sum_result.k << ", " << max_2d_range_sum_result.l << "), sum: "
              << max_2d_range_sum_result.sum << std::endl;

    // Testing algorithms for maximum sum in square sub-matrix of 'm'.
    std::cout << "Square sub-matrix with the maximum sum:" << std::endl;
    const int max_2d_square_range_sum = max_square_sub_matrix_sum(m);
    const sub_matrix_result max_2d_square_range_sum_result = max_square_sub_matrix_sum_result(m);
    assert(max_2d_square_range_sum == max_2d_square_range_sum_result.sum);
    std::cout << "from (" << max_2d_square_range_sum_result.i << ", " << max_2d_square_range_sum_result.j << ") to ("
              << max_2d_square_range_sum_result.k << ", " << max_2d_square_range_sum_result.l << "), sum: "
              << max_2d_square_range_sum_result.sum << std::endl;
}

int main() {
    std::cout << std::endl << "Example 1" << std::endl;
    {
        const matrix m = {
                { 0, -2, -7,  0},
                { 9,  2, -6,  2},
                {-4,  1, -4,  1},
                {-1,  8,  0, -2},
        };
        test_max_2d_range_sum_algorithms(m);
    }
    std::cout << std::endl << "Example 2" << std::endl;
    {
        const matrix m = {
                { 2, -8,  4},
                { 7,  1, -5},
                {-9,  7,  6},
        };
        test_max_2d_range_sum_algorithms(m);
    }
    std::cout << std::endl << "Example 3" << std::endl;
    {
        const matrix m = {
                { 2, -8,  4, -6},
                { 7,  1, -5,  3},
                {-9,  7,  6,  5},
                { 8,  3,  2, -4},
        };
        test_max_2d_range_sum_algorithms(m);
    }
    std::cout << std::endl << "Example 4" << std::endl;
    {
        const matrix m = {
                { 1,  2, -1, -4,-20},
                {-8, -3,  4,  2,  1},
                { 3,  8, 10,  1,  3},
                {-4, -1,  1,  7, -6},
        };
        test_max_2d_range_sum_algorithms(m);
    }
    return 0;
}
