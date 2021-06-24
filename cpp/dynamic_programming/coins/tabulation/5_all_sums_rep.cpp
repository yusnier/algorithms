#include <algorithm>
#include <iostream>
#include <vector>

typedef  std::vector<int> combination_type;
typedef  std::vector<combination_type> combinations_type;

// Generates all combinations in 'values' (values order matters) that add up to 'target_sum'.
// Since the values order matters, we could have not unique combinations with the same set of
// values, e.g. [1, 1, 4], [1, 4, 1] and [4, 1, 1] will be included as 3 separated combinations.
// It uses an DP approach (with tabulation), where the combinations have always the same order.
combinations_type all_sums_rep(int target_sum, const std::vector<int> &values) {
    // 'all_combinations[i]' is a list with all possible combinations of values (with repetition)
    // that add up to 'i'. If it is empty it means that there is no possible combination of values
    // that add up to 'i'.
    std::vector<combinations_type> all_combinations(target_sum + 1, combinations_type());
    // Initializing first position with an empty combination (selecting no value), since this is
    // the only combination that adds up to 0.
    all_combinations[0].push_back(combination_type());

    for (int i = 0; i < target_sum; ++i) {
        if (!all_combinations[i].empty()) {
            for (auto value: values) {
                const int j = i + value;
                if (j > target_sum) { continue; }  // avoid checking out of bounds
                for (const auto &combination: all_combinations[i]) {
                    combination_type new_combination(combination);
                    new_combination.push_back(value);
                    all_combinations[j].push_back(new_combination);
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
        std::cout << combination[0];
        for (int i = 1; i < combination.size(); ++i) {
            std::cout << ", " << combination[i];
        }
        std::cout << "]" << std::endl;
    }
}

int main() {
    {
        const int target = 7;
        const combinations_type combinations = all_sums_rep(target, {5, 7, 4, 3});
        display_all_combinations(target, combinations);
    }
    std::cout << std::endl;
    {
        const int target = 7;
        const combinations_type combinations = all_sums_rep(target, {4, 2});
        display_all_combinations(target, combinations);
    }
    std::cout << std::endl;
    {
        const int target = 8;
        const combinations_type combinations = all_sums_rep(target, {2, 3, 5});
        display_all_combinations(target, combinations);
    }
    std::cout << std::endl;
    {
        const int target = 8;
        const combinations_type combinations = all_sums_rep(target, {5, 1, 4});
        display_all_combinations(target, combinations);
    }
    std::cout << std::endl;
    {
        const int target = 9;
        const combinations_type combinations = all_sums_rep(target, {4, 6, 7});
        display_all_combinations(target, combinations);
    }
    return 0;
}
