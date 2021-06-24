#include <cassert>
#include <iostream>
#include <vector>

typedef  std::vector<int> combination_type;
typedef  std::vector<combination_type> combinations_type;

// Generates all unique combinations in 'values' (values order doesn't matter) that add up to 'target_sum'.
// Since the values order doesn't matter, we won't have duplicated combinations with the same set of values,
// e.g. combinations like [1, 1, 4], [1, 4, 1] and [4, 1, 1] will be merged as the unique combination [1, 1, 4].
// It uses an iterative DFS approach, where the combinations order depends on the order in 'values'.
combinations_type all_sums_no_rep_dfs(int target_sum, const combination_type &values) {
    assert(!values.empty());
    // This vector keeps a counter for each value in 'values', where 'counter[i]' are the times
    // that 'values[i]' is used in a possible combination.
    std::vector<int> counters(values.size(), 0);

    int i = 0;
    int sum = target_sum;
    combinations_type result;

    while (i >= 0) {
        // We try to divide 'sum' between all the values on 'values' starting from 'i'.
        while (i < values.size()) {
            counters[i] = sum / values[i];
            sum -= values[i] * counters[i];
            ++i;
        }
        // If there is no remainder, we have a new combination.
        if (sum == 0) {
            //********** In this block we process the current combination. **********
            combination_type new_combination;
            for (int j = 0; j < values.size(); ++j) {
                if (counters[j] != 0) {
                    new_combination.insert(new_combination.end(), counters[j], values[j]);
                }
            }
            result.push_back(new_combination);
            //***********************************************************************
        }
        // Reset the last counter, since we can't get a new combination by decreasing it.
        sum += counters[i - 1] * values[i - 1];
        counters[i - 1] = 0;
        --i;
        // Looking for the last counter that can be decremented.
        while (i >= 0 && counters[i] == 0) {
            --i;
        }
        // Decrementing the last counter found, returning value to 'sum'.
        if (i >= 0) {
            sum += values[i];
            --counters[i];
            ++i;
        }
    }

    return result;
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

int main()
{
    {
        const int target = 7;
        const combinations_type combinations = all_sums_no_rep_dfs(target, {5, 7, 4, 3});
        display_all_combinations(target, combinations);
    }
    std::cout << std::endl;
    {
        const int target = 7;
        const combinations_type combinations = all_sums_no_rep_dfs(target, {4, 2});
        display_all_combinations(target, combinations);
    }
    std::cout << std::endl;
    {
        const int target = 8;
        const combinations_type combinations = all_sums_no_rep_dfs(target, {2, 3, 5});
        display_all_combinations(target, combinations);
    }
    std::cout << std::endl;
    {
        const int target = 8;
        const combinations_type combinations = all_sums_no_rep_dfs(target, {5, 1, 4});
        display_all_combinations(target, combinations);
    }
    std::cout << std::endl;
    {
        const int target = 9;
        const combinations_type combinations = all_sums_no_rep_dfs(target, {4, 6, 7});
        display_all_combinations(target, combinations);
    }
    return 0;
}
