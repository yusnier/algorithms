#include <algorithm>
#include <iostream>
#include <vector>

constexpr int NULL_VALUE = -1;

// Returns the best combination in 'values' that add up to 'target_sum'.
// If there is more than one, any of them will be chosen.
std::vector<int> best_sum(int target_sum, const std::vector<int> &values) {
    // 'table[i]' indicates how many values are needed by the best combination that add up to 'i',
    // if it is 'NULL_VALUE' it means that it's not possible to complete the sum.
    std::vector<int> table(target_sum + 1, NULL_VALUE);
    table[0] = 0;  // initializing first position to zero
    // This vector is for the construction of the values combination that add up to 'target_sum'.
    // If 'i' is a target sum then 'parent[i]' is the previous index from which we add the last
    // value to complete 'i', so this value is 'i - parent[i]'.
    std::vector<int> parent(target_sum + 1, NULL_VALUE);

    for (int i = 0; i < target_sum; ++i) {
        if (table[i] != NULL_VALUE) {
            for (auto value: values) {
                const int j = i + value;
                if (j > target_sum) { continue; }  // avoid checking out of bounds
                // We do update if we find a better solution for 'table[j]', which in this case is
                // having as few values as possible that add up to 'j'. On the contrary, if the best
                // solution is to have as many values as possible that add up to 'j', we just need to
                // modify the condition using '>' (greater than) instead of '<' (less than).
                if (table[j] == NULL_VALUE || table[i] + 1 < table[j]) {
                    table[j] = table[i] + 1;
                    parent[j] = i;
                }
            }
        }
    }

    // Construction of the values combination that add up to 'target_sum'.
    std::vector<int> path;
    if (parent[target_sum] != NULL_VALUE) {
        for (int at = target_sum; at != 0; at=parent[at]) {
            path.push_back(at - parent[at]);
        }
        std::reverse(path.begin(), path.end());  // just in case we want the original order
    }

    return path;
}

void display_sum_combination(const std::vector<int> &coins_list) {
    int sum = 0;
    std::cout << "[";
    if (!coins_list.empty()) {
        sum += coins_list[0];
        std::cout << coins_list[0];
    }
    for (int i = 1; i < coins_list.size(); ++i) {
        sum += coins_list[i];
        std::cout << ", " << coins_list[i];
    }
    std::cout << "]: sum: " << sum << std::endl;
}

int main() {
    display_sum_combination(best_sum(7, {5, 7, 4, 3}));     // [7]: sum: 7
    display_sum_combination(best_sum(8, {2, 3, 5}));        // [3, 5]: sum: 8
    display_sum_combination(best_sum(8, {5, 1, 4}));        // [4, 4]: sum: 8
    display_sum_combination(best_sum(100, {1, 2, 5, 25}));  // [25, 25, 25, 25]: sum: 100
}
