#include <algorithm>
#include <iostream>
#include <vector>

// Returns how many combinations in 'values' (values order matters) add up to 'target_sum'.
// Since the values order matters, we could count not unique combinations with the same set of
// values e.g. [1, 1, 4], [1, 4, 1] and [4, 1, 1] will be counted as 3 separated combinations.
int how_many_sums(int target_sum, const std::vector<int> &values) {
    // 'table[i]' indicates how many values are needed that add up to 'i',
    // if it is 'NULL_VALUE' it means that it's not possible to complete the sum.
    std::vector<int> table(target_sum + 1, 0);
    // Initializing first position to 1, since we have only one combination that adds up to 0,
    // an empty combination (selecting no value).
    table[0] = 1;

    for (int i = 0; i < target_sum; ++i) {
        if (table[i] != 0) {
            for (auto value: values) {
                const int j = i + value;
                if (j > target_sum) { continue; }  // avoid checking out of bounds
                table[j] += table[i];
            }
        }
    }

    return table[target_sum];
}

int main() {
    std::cout << how_many_sums(7, std::vector<int>{5, 3, 4, 7}) << std::endl;  // 3
    std::cout << how_many_sums(7, std::vector<int>{2, 4}) << std::endl;        // 0
    std::cout << how_many_sums(8, std::vector<int>{2, 3, 5}) << std::endl;     // 3
    std::cout << how_many_sums(8, std::vector<int>{1, 4, 5}) << std::endl;     // 3
    std::cout << how_many_sums(9, std::vector<int>{4, 6, 7}) << std::endl;     // 0
    return 0;
}
