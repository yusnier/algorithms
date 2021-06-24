#include <iostream>
#include <vector>

void print_vector(uint32_t permutation_order, const std::vector<int> &vec) {
    std::cout << permutation_order << ":";
    for (auto v: vec) {
        std::cout << " " << v;
    }
    std::cout << std::endl;
}

// Generates all possible permutations of 'vec' elements, using Heap's algorithm.
void generate(std::vector<int> &vec) {
    std::vector<int> indexes(vec.size(), 0);

    //----- Process current permutation. -----
    uint32_t permutation_order = 1;
    print_vector(permutation_order++, vec);
    //----------------------------------------

    uint32_t i = 1;
    while (i < vec.size()) {
        if (indexes[i] < i) {
            if (i % 2 == 0) {
                std::swap(vec[0], vec[i]);
            } else {
                std::swap(vec[indexes[i]], vec[i]);
            }

            //----- Process current permutation. -----
            print_vector(permutation_order++, vec);
            //----------------------------------------

            ++indexes[i];
            i = 1;
        } else {
            indexes[i] = 0;
            ++i;
        }
    }
}

int main() {
    std::vector<int> vec = {1, 2, 3};

    generate(vec);

    return 0;
}
