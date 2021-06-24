#include <algorithm>
#include <iostream>
#include <vector>

// Rearranges the elements of 'vec' into the previous lexicographically-ordered permutation
// using Narayana Panditha’s algorithm.
bool prev_permutation(std::vector<int> &vec) {
    // Find the largest index i such that vec[i] > vec[i + 1].
    int i = static_cast<int>(vec.size()) - 2;
    while (i >= 0 && vec[i] <= vec[i + 1]) {
        --i;
    }
    // If no such index exists, the permutation is the last permutation.
    if (i < 0) {
        return false;
    }
    // Find the largest index j greater than i such that a[i] > a[j].
    int j = static_cast<int>(vec.size()) - 1;
    while (vec[i] <= vec[j]) {
        --j;
    }
    // Swap vec[i] and vec[j].
    std::swap(vec[i], vec[j]);
    // Reverse the elements from vec[i + 1] to the last element.
    std::reverse(vec.begin() + i + 1, vec.end());

    return true;
}

void print_vector(int permutation_order, const std::vector<int> &vec) {
    std::cout << permutation_order << ":";
    for (auto v: vec) {
        std::cout << " " << v;
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec = {3, 2, 1};

    int permutation_order = 1;
    do {
        print_vector(permutation_order++, vec);
    } while (prev_permutation(vec));
    // We could instead use 'std::prev_permutation(vec.begin(), vec.end())' from STL.

    return 0;
}
