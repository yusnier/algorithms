#include <iostream>
#include <vector>

template <typename T>
struct vector2d {
    typedef std::vector<std::vector<T>> type;
};

// This algorithm solve the problem "UVa 11450 - Wedding Shopping", using the
// Bottom-Up DP approach (tabular method). To see other variants of solution check:
// Competitive Programming 3, P. 95, Steven & Felix Halim.
int maximum_amount_to_buy(int budget, const vector2d<int>::type &all_prices) {
    const int garments = static_cast<int>(all_prices.size());
    vector2d<bool>::type reachable(garments, std::vector<bool>(budget + 1, false));

    // Initial values (base cases).
    for (const auto model_price: all_prices[0]) {
        if (budget - model_price >= 0) {  // to prevent array index out of bound
            reachable[0][budget - model_price] = true;
        }
    }
    // Complete 'reachable' table for each remaining garment.
    for (int g = 1; g < garments; ++g) {
        for (int money = 0; money < budget; ++money) {
            if (reachable[g - 1][money]) {
                for (const auto model_price: all_prices[g]) {
                    if (money - model_price >= 0) {  // to prevent array index out of bound
                        reachable[g][money - model_price] = true;
                    }
                }
            }
        }
    }

    int money = 0;
    for (; money <= budget && !reachable[garments-1][money]; ++money) {}

    if (money > budget) {
        return -1;  // no solution
    }

    return budget - money;
}

void test_algorithm(int budget, const vector2d<int>::type &all_prices) {
    const int result = maximum_amount_to_buy(budget, all_prices);
    if (result >= 0) {
        std::cout << result << std::endl;
    } else {
        std::cout << "no solution" << std::endl;
    }
}

int main() {
    {
        //     | 0  1  2  3  4  5  6  7  8  9 10
        //  ------------------------------------
        //  g0 | _  _  _  _  _  _  1  _  1  _  _
        //  g1 | _  1  _  1  _  1  _  1  _  _  _
        //  g2 | 1  _  1  _  1  _  _  _  _  _  _
        const vector2d<int>::type all_prices = {
                {2, 4},
                {1, 5},
                {3},
        };
        test_algorithm(10, all_prices);
    }
    {
        const vector2d<int>::type all_prices = {
                {8,  6,  4},
                {5,  10},
                {1,  3,  3,  7},
                {50, 14, 23, 8},
        };
        test_algorithm(100, all_prices);
    }
    {
        const vector2d<int>::type all_prices = {
                {4, 6, 8},
                {5,  10},
                {1,  3,  5, 5},
        };
        test_algorithm(20, all_prices);
    }
    {
        const vector2d<int>::type all_prices = {
                {6, 4, 8},
                {10, 6},
                {7, 3, 1, 7},
        };
        test_algorithm(5, all_prices);
    }
    return 0;
}
