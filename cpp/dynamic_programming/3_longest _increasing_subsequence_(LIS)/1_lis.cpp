#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>

typedef std::vector<std::vector<int>> vector2d;

// Returns the Longest Increasing Subsequence (LIS) on 'sequence' in O(n^2).
// Reference: Competitive Programming 3, P. 105, Steven & Felix Halim.
int lis_v1(const std::vector<int> &sequence) {
    if (sequence.empty()) { return 0; }

    // Let 'lis[i]' be the LIS ending at index 'i'.
    std::vector<int> lis(sequence.size(), 1);

    int max_subsequence = 1;
    for (int i = 1; i < sequence.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (sequence[j] < sequence[i] && lis[j] + 1 > lis[i]) {
                lis[i] = lis[j] + 1;
            }
        }
        max_subsequence = std::max(max_subsequence, lis[i]);
    }

    return max_subsequence;
}

// Returns the Longest Increasing Subsequence (LIS) on 'sequence' in O(n^2).
// In this variant we make the search to all 'j' from 'i' (for every j > i),
// instead of from all j to i (for every j < i), like in v1 version.
int lis_v2(const std::vector<int> &sequence) {
    if (sequence.empty()) { return 0; }

    // Let 'lis[i]' be the LIS ending at index 'i'.
    std::vector<int> lis(sequence.size(), 1);

    int max_subsequence = 1;
    for (int i = 0; i < sequence.size(); ++i) {
        for (int j = i + 1; j < sequence.size(); ++j) {
            if (sequence[i] < sequence[j] && lis[i] + 1 > lis[j]) {
                lis[j] = lis[i] + 1;
                max_subsequence = std::max(max_subsequence, lis[j]);
            }
        }
    }

    return max_subsequence;
}

// Returns the Longest Increasing Subsequence (LIS) on 'sequence' in O(nlog(n)),
// using a patient sort approach. This variant is not the most suitable to construct solutions.
int lis_patient_sort(const std::vector<int> &sequence) {
    // Set to apply patience sorting algorithm: <sequence value>.
    std::set<int> lis;

    for (const int value: sequence) {
        const auto it = lis.lower_bound(value);
        if (it != lis.end()) {
            lis.erase(it);
        }
        lis.insert(value);
    }

    return static_cast<int>(lis.size());
}

void test_algorithms(const std::vector<int> &sequence) {
    const std::set<int> lis_set = {
            lis_v1(sequence),
            lis_v2(sequence),
            lis_patient_sort(sequence),
    };
    assert(lis_set.size() == 1);  // checking that all algorithms have the same result.
    const int lis = *lis_set.begin();
    std::cout << "LIS: " << lis << (lis == 0 ? " -> No Solution" : "") << std::endl;
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
