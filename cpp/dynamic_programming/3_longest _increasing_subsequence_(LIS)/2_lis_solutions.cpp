#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>

typedef std::vector<std::vector<int>> vector2d;

// Utility recursive function to construct LIS solutions.
vector2d build_solutions(const std::vector<int> &sequence, const vector2d &parents, int index) {
    // If 'sequence[index]' has no parents, then it is an initial value of a sequence.
    if (parents[index].empty()) {
        return {{sequence[index]}};
    }
    // Building all solutions traversing 'parents' tree recursively using a BFS approach.
    vector2d solutions;
    for (const int parent_index: parents[index]) {
        vector2d sub_solutions = build_solutions(sequence, parents, parent_index);
        for (auto &solution: sub_solutions) {
            solution.push_back(sequence[index]);
            solutions.push_back(std::move(solution));
        }
    }
    return solutions;
}

// Variant of 'lis_v1' to return all the solutions for the LIS on 'sequence' in O(n^2).
// Reference: Competitive Programming 3, P. 105, Steven & Felix Halim.
vector2d lis_v1_solutions(const std::vector<int> &sequence) {
    if (sequence.empty()) { return {}; }

    // Let 'lis[i]' be the LIS ending at index 'i'.
    std::vector<int> lis(sequence.size(), 1);
    // 'parents[i]' is a list of parent values that precedes to sequence[i] in the LIS.
    vector2d parents(sequence.size(), std::vector<int>());

    int max_lis_size = 1;
    for (int i = 1; i < sequence.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (sequence[j] < sequence[i]) {
                if (lis[j] + 1 == lis[i]) {
                    parents[i].push_back(j);
                } else if (lis[j] + 1 > lis[i]) {
                    lis[i] = lis[j] + 1;
                    parents[i].clear();
                    parents[i].push_back(j);
                }
            }
        }
        max_lis_size = std::max(max_lis_size, lis[i]);
    }

    vector2d result;
    for (int i = 0; i < lis.size(); ++i) {
        if (lis[i] == max_lis_size) {
            vector2d solutions = build_solutions(sequence, parents, i);
            std::move(solutions.begin(), solutions.end(), std::back_inserter(result));
        }
    }

    return result;
}

// Variant of 'lis_v2' to return all the solutions for the LIS on 'sequence' in O(n^2).
// In this variant we make the search to all 'j' from 'i' (for every j > i),
// instead of from all j to i (for every j < i), like in v1 version.
vector2d lis_v2_solutions(const std::vector<int> &sequence) {
    if (sequence.empty()) { return {}; }

    // Let 'lis[i]' be the LIS ending at index 'i'.
    std::vector<int> lis(sequence.size(), 1);
    // 'parents[i]' is a list of parent values that precedes to sequence[i] in the LIS.
    vector2d parents(sequence.size(), std::vector<int>());

    int max_lis_size = 1;
    for (int i = 0; i < sequence.size(); ++i) {
        for (int j = i + 1; j < sequence.size(); ++j) {
            if (sequence[i] < sequence[j]) {
                if (lis[i] + 1 == lis[j]) {
                    parents[j].push_back(i);
                } else if (lis[i] + 1 > lis[j]) {
                    lis[j] = lis[i] + 1;
                    max_lis_size = std::max(max_lis_size, lis[j]);
                    parents[j].clear();
                    parents[j].push_back(i);
                }
            }
        }
    }

    vector2d result;
    for (int i = 0; i < lis.size(); ++i) {
        if (lis[i] == max_lis_size) {
            vector2d solutions = build_solutions(sequence, parents, i);
            std::move(solutions.begin(), solutions.end(), std::back_inserter(result));
        }
    }

    return result;
}

void test_algorithms(const std::vector<int> &sequence) {
    const std::set<vector2d> lis_solutions = {
            lis_v1_solutions(sequence),
            lis_v2_solutions(sequence),
    };
    assert(lis_solutions.size() == 1);  // checking that all algorithms have the same result.
    if (lis_solutions.begin()->empty()) {
        std::cout << "No Solution" << std::endl;
        return;
    }
    std::cout << "LIS: " << lis_solutions.begin()->at(0).size() << std::endl;
    std::cout << "Solutions: " << std::endl;
    for (const auto &solution: *lis_solutions.begin()) {
        std::cout << "[";
        if (!solution.empty()) {
            std::cout << solution[0];
        }
        for (int i = 1; i < solution.size(); ++i) {
            std::cout << ", " << solution[i];
        }
        std::cout << "]" << std::endl;
    }
}

int main() {
    test_algorithms({-7, 10, 9, 2, 3, 8, 8, 1});
    std::cout << std::endl;
    test_algorithms({0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15});
    std::cout << std::endl;
    test_algorithms({9, 6, 7, 8, 1, 2, 3, 0});
    std::cout << std::endl;
    test_algorithms({0, 1, 2, 3, 4, 5});
    std::cout << std::endl;
    test_algorithms({5, 4, 3, 2, 1, 0});
    std::cout << std::endl;
    test_algorithms({});

    return 0;
}
