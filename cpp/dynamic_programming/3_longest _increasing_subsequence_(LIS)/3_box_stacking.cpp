#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>

struct Box {
    int h, w, d;

    // This operator overload is only required for testing proposes on 'test_algorithm()'.
    friend bool operator<(const Box &a, const Box &b) {
        return (a.w * a.d) < (b.w * b.d);
    }
};

typedef std::vector<std::vector<int>> vector2d_int;
typedef std::vector<std::vector<Box>> vector2d_box;

// ---------- LIS variants algorithms ----------

// LIS algorithm variant ('lis_v1()') for the 'Box Stacking Problem', in O(n^2).
int lis_box_stacking_v1(const std::vector<Box> &sequence) {
    if (sequence.empty()) { return 0; }

    // Let 'lis[i]' be the LIS (highest cumulative height) ending at index 'i'.
    std::vector<int> lis(sequence.size());
    for (int i = 0; i < sequence.size(); ++i) {
        lis[i] = sequence[i].h;
    }

    int max_subsequence = 0;
    for (int i = 1; i < sequence.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (sequence[j].w < sequence[i].w && sequence[j].d < sequence[i].d &&
                lis[j] + sequence[i].h > lis[i]) {
                lis[i] = lis[j] + sequence[i].h;
            }
        }
        max_subsequence = std::max(max_subsequence, lis[i]);
    }

    return max_subsequence;
}

// LIS algorithm variant ('lis_v2()') for the 'Box Stacking Problem', in O(n^2).
int lis_box_stacking_v2(const std::vector<Box> &sequence) {
    if (sequence.empty()) { return 0; }

    // Let 'lis[i]' be the LIS (highest cumulative height) ending at index 'i'.
    std::vector<int> lis(sequence.size());
    for (int i = 0; i < sequence.size(); ++i) {
        lis[i] = sequence[i].h;
    }

    int max_subsequence = 0;
    for (int i = 0; i < sequence.size(); ++i) {
        for (int j = i + 1; j < sequence.size(); ++j) {
            if (sequence[i].w < sequence[j].w && sequence[i].d < sequence[j].d &&
                lis[i] + sequence[j].h > lis[j]) {
                lis[j] = lis[i] + sequence[j].h;
                max_subsequence = std::max(max_subsequence, lis[j]);
            }
        }
    }

    return max_subsequence;
}

// Utility recursive function to construct LIS solutions.
vector2d_box build_solutions(const std::vector<Box> &sequence, const vector2d_int &parents, int index) {
    // If 'sequence[index]' has no parents, then it is an initial value of a sequence.
    if (parents[index].empty()) {
        return {{sequence[index]}};
    }
    // Building all solutions traversing 'parents' tree recursively using a BFS approach.
    vector2d_box solutions;
    for (const int parent_index: parents[index]) {
        vector2d_box sub_solutions = build_solutions(sequence, parents, parent_index);
        for (auto &solution: sub_solutions) {
            solution.push_back(sequence[index]);
            solutions.push_back(std::move(solution));
        }
    }
    return solutions;
}

// LIS algorithm variant ('lis_solutions_v1()') for the 'Box Stacking Problem', in O(n^2).
vector2d_box lis_box_stacking_solutions_v1(const std::vector<Box> &sequence) {
    if (sequence.empty()) { return {}; }

    // Let 'lis[i]' be the LIS (highest cumulative height) ending at index 'i'.
    std::vector<int> lis(sequence.size());
    for (int i = 0; i < sequence.size(); ++i) {
        lis[i] = sequence[i].h;
    }
    // 'parents[i]' is a list of parent values that precedes to sequence[i] in the LIS.
    vector2d_int parents(sequence.size(), std::vector<int>());

    int max_lis_size = 0;
    for (int i = 1; i < sequence.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (sequence[j].w < sequence[i].w && sequence[j].d < sequence[i].d) {
                if (lis[j] + sequence[i].h == lis[i]) {
                    parents[i].push_back(j);
                } else if (lis[j] + sequence[i].h > lis[i]) {
                    lis[i] = lis[j] + sequence[i].h;
                    parents[i].clear();
                    parents[i].push_back(j);
                }
            }
        }
        max_lis_size = std::max(max_lis_size, lis[i]);
    }

    // Block to construct the solutions.
    vector2d_box result;
    for (int i = 0; i < lis.size(); ++i) {
        if (lis[i] == max_lis_size) {
            vector2d_box solutions = build_solutions(sequence, parents, i);
            std::move(solutions.begin(), solutions.end(), std::back_inserter(result));
        }
    }

    return result;
}

// LIS algorithm variant ('lis_solutions_v2()') for the 'Box Stacking Problem', in O(n^2).
vector2d_box lis_box_stacking_solutions_v2(const std::vector<Box> &sequence) {
    if (sequence.empty()) { return {}; }

    // Let 'lis[i]' be the LIS (highest cumulative height) ending at index 'i'.
    std::vector<int> lis(sequence.size());
    for (int i = 0; i < sequence.size(); ++i) {
        lis[i] = sequence[i].h;
    }
    // 'parents[i]' is a list of parent values that precedes to sequence[i] in the LIS.
    vector2d_int parents(sequence.size(), std::vector<int>());

    int max_lis_size = 0;
    for (int i = 0; i < sequence.size(); ++i) {
        for (int j = i + 1; j < sequence.size(); ++j) {
            if (sequence[i].w < sequence[j].w && sequence[i].d < sequence[j].d) {
                if (lis[i] + sequence[j].h == lis[j]) {
                    parents[j].push_back(i);
                } else if (lis[i] + sequence[j].h > lis[j]) {
                    lis[j] = lis[i] + sequence[j].h;
                    max_lis_size = std::max(max_lis_size, lis[j]);
                    parents[j].clear();
                    parents[j].push_back(i);
                }
            }
        }
    }

    // Block to construct the solutions.
    vector2d_box result;
    for (int i = 0; i < lis.size(); ++i) {
        if (lis[i] == max_lis_size) {
            vector2d_box solutions = build_solutions(sequence, parents, i);
            std::move(solutions.begin(), solutions.end(), std::back_inserter(result));
        }
    }

    return result;
}

// ---------- Box Stacking Algorithms ----------

std::vector<Box> rotate_and_sort_boxes(const std::vector<Box> &boxes) {
    // Generate all 3 rotations of all boxes. The size of rotation array becomes 3 times the size of
    // the original array. For simplicity, we consider width as always bigger than or equal to depth.
    std::vector<Box> boxes_rotated;
    for (const auto &box: boxes) {
        Box new_box;
        // First rotation.
        new_box.h = box.h;
        new_box.w = std::max(box.w, box.d);
        new_box.d = std::min(box.w, box.d);
        boxes_rotated.push_back(new_box);
        // Second rotation.
        new_box.h = box.w;
        new_box.w = std::max(box.h, box.d);
        new_box.d = std::min(box.h, box.d);
        boxes_rotated.push_back(new_box);
        // Third rotation.
        new_box.h = box.d;
        new_box.w = std::max(box.h, box.w);
        new_box.d = std::min(box.h, box.w);
        boxes_rotated.push_back(new_box);
    }

    // Sorting by area in ascending order.
    std::sort(boxes_rotated.begin(), boxes_rotated.end(), [] (const Box &a, const Box &b) -> bool {
        return (a.w * a.d) < (b.w * b.d);
    });

    return boxes_rotated;
}

int box_stacking_v1(const std::vector<Box> &boxes) {
    const std::vector<Box> boxes_rotated_and_sorted = rotate_and_sort_boxes(boxes);
    return lis_box_stacking_v1(boxes_rotated_and_sorted);
}

int box_stacking_v2(const std::vector<Box> &boxes) {
    const std::vector<Box> boxes_rotated_and_sorted = rotate_and_sort_boxes(boxes);
    return lis_box_stacking_v2(boxes_rotated_and_sorted);
}

vector2d_box box_stacking_solutions_v1(const std::vector<Box> &boxes) {
    const std::vector<Box> boxes_rotated_and_sorted = rotate_and_sort_boxes(boxes);
    return lis_box_stacking_solutions_v1(boxes_rotated_and_sorted);
}

vector2d_box box_stacking_solutions_v2(const std::vector<Box> &boxes) {
    const std::vector<Box> boxes_rotated_and_sorted = rotate_and_sort_boxes(boxes);
    return lis_box_stacking_solutions_v2(boxes_rotated_and_sorted);
}

// ---------- Test cases ----------

void test_algorithm(const std::vector<Box> &boxes) {
    // Testing box stacking algorithms.
    const std::set<int> box_stacking_set = {
            box_stacking_v1(boxes),
            box_stacking_v2(boxes),
    };
    assert(box_stacking_set.size() == 1);  // checking that all algorithms have the same result.
    int box_stacking = *box_stacking_set.begin();
    std::cout << "LIS: " << box_stacking << (box_stacking == 0 ? " -> No Solution" : "") << std::endl;

    // Testing box stacking algorithms with solutions.
    const std::set<vector2d_box> box_stacking_solutions_set = {
            box_stacking_solutions_v1(boxes),
            box_stacking_solutions_v2(boxes),
    };
    assert(box_stacking_solutions_set.size() == 1);  // checking that all algorithms have the same result.
    const vector2d_box &box_stacking_solutions = *box_stacking_solutions_set.begin();
    if (!box_stacking_solutions.empty()) {
        std::cout << "Solutions: " << std::endl;
        for (const auto &solution: box_stacking_solutions) {
            for (auto box: solution) {
                std::cout << "[ h:" << box.h << " ," << box.w << ", " << box.d << "]" << std::endl;
            }
        }
    }
}

int main() {
    {
        const std::vector<Box> boxes = {  // 60
                {4,  6,  7},
                {1,  2,  3},
                {4,  5,  6},
                {10, 12, 32}
        };
        test_algorithm(boxes);
    }
    std::cout << std::endl;
    {
        const std::vector<Box> boxes = {  // 22
                {4, 2, 5},
                {3, 1, 6},
                {3, 2, 1},
                {6, 3, 8}
        };
        test_algorithm(boxes);
    }
    return 0;
}
