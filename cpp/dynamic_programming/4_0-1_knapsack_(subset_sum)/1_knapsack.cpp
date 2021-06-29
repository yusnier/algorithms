#include <iostream>
#include <limits>
#include <vector>

constexpr int MIN = std::numeric_limits<int>::min();

struct item {
    int weight, value;
};

struct knapsack_result {
    const int max_weight;
    const int max_value;
};

knapsack_result knapsack(int limit, const std::vector<item> &items) {
    std::vector<std::vector<int>> table(items.size(), std::vector<int>(limit + 1, MIN));

    // Initial values (base case).
    table[0][limit] = 0;
    if (limit - items[0].weight >= 0) {
        table[0][limit - items[0].weight] = items[0].value;
    }

    for (int i = 1; i < items.size(); ++i) {
        for (int j = 0; j <= limit; ++j) {
            if (table[i - 1][j] != MIN) {
                table[i][j] = table[i - 1][j];
                if (j - items[i].weight < 0) { continue; }  // to prevent array index out of bound
                if (table[i - 1][j] + items[i].value > table[i][j - items[i].weight]) {
                    table[i][j - items[i].weight] = table[i - 1][j] + items[i].value;
                }
            }
        }
    }

    int max_weight = 0;
    int max_value = 0;
    // The solution is the highest value in the last row.
    for (int i = 0; i <= limit; ++i) {
        if (table[items.size() - 1][i] == MIN) { continue; }
        if (table[items.size() - 1][i] > max_value) {
            max_value = table[items.size() - 1][i];
            max_weight = limit - i;
        }
    }

    return {max_weight, max_value};
}

void test_algorithm(int limit, const std::vector<item> &items) {
    const knapsack_result result = knapsack(limit, items);
    std::cout << "max weight: " << result.max_weight << ", max value: " << result.max_value << std::endl;
}

int main() {
    {
        // Tabulation Table
        //       |   0   1   2   3   4   5   6   7   8   9  10  11  12
        //-------------------------------------------------------------
        // item0 |   _   _ 100   _   _   _   _   _   _   _   _   _   0
        // item1 |   _   _ 100   _   _   _   _   _  70   _   _   _   0
        // item2 |   _   _ 120   _   _   _  50   _  70   _   _   _   0
        // item3 |  10   _ 120   _   _   _  50   _  70   _   _   _   0
        const std::vector<item> items = {
                {10, 100},
                {4,  70},
                {6,  50},
                {12, 10},
        };
        test_algorithm(12, items);  // 10, 120
    }
    {
        // Tabulation Table
        //       |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        //-------------------------------------------------------------------------
        // item0 |   _   _   _   _   _   _   _   _   _   _  50   _   _   _   _   0
        // item1 |   _   _   _   _ 100   _   _   _   _  50  50   _   _   _   _   0
        // item2 |   _   _ 100 100 100   _   _   _  50  50  50   _   _   _   _   0
        // item3 | 150 150 150 100 100   _   _ 100  50  50  50   _   _   _   _   0
        // item4 | 150 150 150 100 100   _ 100 100  50  50  50   _   _   _   _   0
        const std::vector<item> items = {
                {5, 50},
                {6, 50},
                {7, 50},
                {8, 100},
                {9, 100},
        };
        test_algorithm(15, items);  // 15, 150
    }
    {
        // Tabulation Table
        //       |   0   1   2   3   4   5   6   7   8   9  10
        //-----------------------------------------------------
        // item0 |   _   _   _   _   _   _  30   _   _   _   0
        // item1 |   _   _   _   _  80   _  30   _  50   _   0
        // item2 |   _  70   _  20  80   _  30   _  50   _   0
        // item3 |   _ 100   _ 120  80  70  30   _  50   _   0
        const std::vector<item> items = {
                {4, 30},
                {2, 50},
                {7, 20},
                {5, 70},
        };
        test_algorithm(10, items);  // 7, 120
    }
    {
        // Tabulation Table
        //       |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        //-------------------------------------------------------------------------
        // item0 |   _   _   _   _   _   _   _   _   _   _   _   4   _   _   _   0
        // item1 |   _   _   _   _  11   _   _   _   7   _   _   4   _   _   _   0
        // item2 |   _   _  13   _  11   _   9   _   7   _   _   4   _   _   _   0
        const std::vector<item> items = {
                {4, 4},
                {7, 7},
                {9, 9},
        };
        test_algorithm(15, items);  // 13, 13
    }
    return 0;
}
