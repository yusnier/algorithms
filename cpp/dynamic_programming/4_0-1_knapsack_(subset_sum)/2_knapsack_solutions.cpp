#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

constexpr int MIN = std::numeric_limits<int>::min();

struct item {
    int weight, value;
};

typedef std::vector<std::vector<int>> vector2d_int;
typedef std::vector<std::vector<item>> vector2d_item;

struct knapsack_result {
    const int max_weight;
    const int max_value;
    const vector2d_item solutions;

    knapsack_result(int max_weight, int max_value, vector2d_item solutions) :
            max_weight(max_weight), max_value(max_value), solutions(std::move(solutions)) {}
};

knapsack_result knapsack_solutions(int limit, const std::vector<item> &items) {
    vector2d_int table(items.size(), std::vector<int>(limit + 1, MIN));
    vector2d_int parents(items.size(), std::vector<int>(limit + 1,MIN));

    // Initial values (base case).
    table[0][limit] = 0;
    if (limit - items[0].weight >= 0) {
        table[0][limit - items[0].weight] = items[0].value;
    }

    for (int i = 1; i < items.size(); ++i) {
        for (int j = 0; j <= limit; ++j) {
            if (table[i - 1][j] != MIN) {

                table[i][j] = table[i - 1][j];
                parents[i][j] = parents[i - 1][j];

                if (j - items[i].weight < 0) { continue; }  // to prevent array index out of bound
                if (table[i - 1][j] + items[i].value > table[i][j - items[i].weight]) {
                    table[i][j - items[i].weight] = table[i - 1][j] + items[i].value;
                    parents[i][j - items[i].weight] = j;
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

    vector2d_item solutions;
    for (int k = 0; k <= limit; ++k) {
        if (table[items.size() - 1][k] == max_value) {
            int i = static_cast<int>(items.size()) - 1;
            int j = k;
            std::vector<item> solution;
            while (i >= 0 && j >= 0) {
                while (i > 0 && parents[i][j] == parents[i - 1][j]) { --i; }
                if (j < limit) {
                    solution.push_back(items[i]);
                }
                j = parents[i][j];
                --i;
            }
            std::reverse(solution.begin(), solution.end());
            solutions.push_back(solution);
        }
    }

    return knapsack_result(max_weight, max_value, solutions);
}

void test_algorithm(int limit, const std::vector<item> &items) {
    const knapsack_result result = knapsack_solutions(limit, items);
    std::cout << "max weight: " << result.max_weight
              << ", max value: " << result.max_value
              << ", solutions: " << result.solutions.size() << std::endl;
    for (const auto &solution: result.solutions) {
        if (solution.empty()) { continue; }
        int total_weight = solution[0].weight;
        int total_value = solution[0].value;
        std::cout << "(w:" << solution[0].weight << ", v:" << solution[0].value << ")";
        for (int i = 1; i < solution.size(); ++i) {
            total_weight += solution[i].weight;
            total_value += solution[i].value;
            std::cout << " -> (w:" << solution[i].weight << ", v:" << solution[i].value << ")";
        }
        std::cout << " : [total w:" << total_weight << ", total v:" << total_value << "]" << std::endl;
    }
    std::cout << std::endl;
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

        // Parents Table
        //       |   0   1   2   3   4   5   6   7   8   9  10  11  12
        //-------------------------------------------------------------
        // item0 |   _   _   _   _   _   _   _   _   _   _   _   _   _
        // item1 |   _   _   _   _   _   _   _   _  12   _   _   _   _
        // item2 |   _   _   8   _   _   _  12   _  12   _   _   _   _
        // item3 |  12   _   8   _   _   _  12   _  12   _   _   _   _
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

        // Parents Table
        //       |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        //-------------------------------------------------------------------------
        // item0 |   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _
        // item1 |   _   _   _   _  10   _   _   _   _  15   _   _   _   _   _   _
        // item2 |   _   _   9  10  10   _   _   _  15  15   _   _   _   _   _   _
        // item3 |   8   9  10  10  10   _   _  15  15  15   _   _   _   _   _   _
        // item4 |   8   9  10  10  10   _  15  15  15  15   _   _   _   _   _   _
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

        // Parents Table
        //       |   0   1   2   3   4   5   6   7   8   9  10
        //-----------------------------------------------------
        // item0 |   _   _   _   _   _   _   _   _   _   _   _
        // item1 |   _   _   _   _   6   _   _   _  10   _   _
        // item2 |   _   8   _  10   6   _   _   _  10   _   _
        // item3 |   _   6   _   8   6  10   _   _  10   _   _
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

        // Parents Table
        //       |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        //-------------------------------------------------------------------------
        // item0 |   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _   _
        // item1 |   _   _   _   _  11   _   _   _  15   _   _   _   _   _   _   _
        // item2 |   _   _  11   _  11   _  15   _  15   _   _   _   _   _   _   _
        const std::vector<item> items = {
                {4, 4},
                {7, 7},
                {9, 9},
        };
        test_algorithm(15, items);  // 13, 13
    }
    return 0;
}
