#include <cassert>
#include <iostream>
#include <vector>

// The key idea of Kadane’s algorithm is to keep a running sum of the integers seen so far and greedily
// reset that to 0 if the running sum dips below 0. This is because re-starting from 0 is always better
// than continuing from a negative running sum.

// Returns the maximum (1D) range sum of 'values' using the Kadane's algorithm in O(n).
int kadane_max_1d_range_sum(const std::vector<int> &values) {
    int sum = 0, max_sum = 0;
    for (auto value: values) {
        sum += value;
        max_sum = std::max(max_sum, sum);
        if (sum < 0) {
            sum = 0;
        }
    }
    return max_sum;
}

struct sub_range_result {
    int sum, i, j;
};

// Returns the maximum (1D) range sum of 'values' and the range indices, using the Kadane's algorithm in O(n).
sub_range_result kadane_max_1d_range_sum_result(const std::vector<int> &values) {
    sub_range_result result = {0, 0, 0};
    int sum = 0;
    for (int i = 0, j = 0; j < values.size(); ++j) {
        sum += values[j];
        if (sum > result.sum) {
            result.sum = sum;
            result.i = i;
            result.j = j;
        }
        if (sum < 0) {
            sum = 0;
            i = j;
        }
    }
    return result;
}

int main() {
    std::vector<int> values = {4, -5, 4, -3, 4, 4, -4, 4, -5};

    const int max_1d_range_sum = kadane_max_1d_range_sum(values);
    const sub_range_result max_2d_range_sum_result = kadane_max_1d_range_sum_result(values);
    assert(max_1d_range_sum == max_2d_range_sum_result.sum);
    std::cout << "Range with the maximum sum:" << std::endl;
    std::cout << "from: " << max_2d_range_sum_result.i << " to: " << max_2d_range_sum_result.j
              << " (inclusive), sum: " << max_2d_range_sum_result.sum << std::endl;

    return 0;
}

