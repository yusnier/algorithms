#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

typedef  std::vector<int> combination_type;
// Using a set instead of a vector to keep the combinations always in the same order, and also
// to avoid duplicates (keeping only unique combinations) if we sort each combination before
// inserting it into the set.
typedef  std::set<combination_type> combinations_type;

// Generates all unique combinations in 'values' (values order doesn't matter) that add up to 'target_sum'.
// Since the values order doesn't matter, we won't have duplicated combinations with the same set of values,
// e.g. combinations like [1, 1, 4], [1, 4, 1] and [4, 1, 1] will be merged as the unique combination [1, 1, 4].
// It uses an DP approach (with tabulation), where the combinations have always the same order.
combinations_type all_sums_no_rep(int target_sum, const std::vector<int> &values) {
    // 'all_combinations[i]' is a list with all possible combinations of values that add up to 'i'.
    // If it is empty it means that there is no possible combination of values that add up to 'i'.
    std::vector<combinations_type> all_combinations(target_sum + 1, combinations_type());
    // Initializing first position with an empty combination (selecting no value), since this is
    // the only combination that adds up to 0.
    all_combinations[0].insert(combination_type());

    for (int i = 0; i < target_sum; ++i) {
        if (!all_combinations[i].empty()) {
            for (auto value: values) {
                const int j = i + value;
                if (j > target_sum) { continue; }  // avoid checking out of bounds
                for (const auto &combination: all_combinations[i]) {
                    combination_type new_combination(combination);
                    new_combination.push_back(value);
                    // Sorting each combination before inserting it into the set to avoid duplicates.
                    std::sort(new_combination.begin(), new_combination.end());
                    all_combinations[j].insert(new_combination);
                }
            }
        }
    }

    return all_combinations[target_sum];
}

void display_all_combinations(int target, const combinations_type &combinations) {
    std::cout << "Target: " << target << " Combinations: " << combinations.size() << std::endl;
    if (combinations.empty()) {
        std::cout << "[no combinations]" << std::endl;
        return;
    }
    for (const auto &combination: combinations) {
        std::cout << "[";
        auto it = combination.begin();
        std::cout << *it;
        for (++it; it != combination.end(); ++it) {
            std::cout << ", " << *it;
        }
        std::cout << "]" << std::endl;
    }
}

int main() {
    {
        const int target = 7;
        const combinations_type combinations = all_sums_no_rep(target, std::vector<int>{5, 7, 4, 3});
        display_all_combinations(target, combinations);
    }
    std::cout << std::endl;
    {
        const int target = 7;
        const combinations_type combinations = all_sums_no_rep(target, std::vector<int>{4, 2});
        display_all_combinations(target, combinations);
    }
    std::cout << std::endl;
    {
        const int target = 8;
        const combinations_type combinations = all_sums_no_rep(target, std::vector<int>{2, 3, 5});
        display_all_combinations(target, combinations);
    }
    std::cout << std::endl;
    {
        const int target = 8;
        const combinations_type combinations = all_sums_no_rep(target, std::vector<int>{5, 1, 4});
        display_all_combinations(target, combinations);
    }
    std::cout << std::endl;
    {
        const int target = 9;
        const combinations_type combinations = all_sums_no_rep(target, std::vector<int>{4, 6, 7});
        display_all_combinations(target, combinations);
    }
    return 0;
}
