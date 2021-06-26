#include <iostream>
#include <vector>

// Returns whether or not there is a combination in 'values' that add up to 'target_sum'.
bool can_sum(int target_sum, const std::vector<int> &values) {
    // 'table[i]' indicates whether or not we can combine values on 'values' that add up to 'i'.
    std::vector<bool> table(target_sum + 1, false);
    table[0] = true;
    for (int i = 0; i < target_sum; ++i) {
        if (table[i]) {
            for (auto value: values) {
                if (i + value > target_sum) { continue; }  // avoid checking out of bounds
                table[i + value] = true;
                // We could return 'true' early at this point if: 'i + value == target_sum'.
            }
        }
    }
    return table[target_sum];
}

int main() {
    std::cout << std::boolalpha << can_sum(7, {2, 3}) << std::endl;       // true
    std::cout << std::boolalpha << can_sum(7, {5, 3, 4, 7}) << std::endl; // true
    std::cout << std::boolalpha << can_sum(7, {2, 4}) << std::endl;       // false
    std::cout << std::boolalpha << can_sum(8, {2, 3, 5}) << std::endl;    // true
    std::cout << std::boolalpha << can_sum(300, {7, 14}) << std::endl;    // false
}
