#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>

void read_lengths(std::uint32_t &len_a, std::uint32_t &len_b, std::uint32_t &len_c);
void read_vec(std::uint32_t values, std::vector<std::uint64_t> &vec);

int main() {
    std::uint32_t len_a, len_b, len_c;
    std::vector<std::uint64_t> a, b, c;

    // Input
    read_lengths(len_a, len_b, len_c);
    read_vec(len_a, a);
    read_vec(len_b, b);
    read_vec(len_c, c);
    // Removing duplicate elements in each vector.
    a.erase(std::unique(a.begin(), a.end()), a.end());
    b.erase(std::unique(b.begin(), b.end()), b.end());
    c.erase(std::unique(c.begin(), c.end()), c.end());
    // Sorting element in each vector.
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::sort(c.begin(), c.end());

    std::uint64_t triplets = 0;
    std::size_t cur_a = 0, cur_c = 0;
    for (std::size_t cur_b = 0; cur_b < b.size(); ++cur_b) {
        while (cur_a < a.size() && a[cur_a] <= b[cur_b]) ++cur_a;
        while (cur_c < c.size() && c[cur_c] <= b[cur_b]) ++cur_c;
        triplets += static_cast<uint64_t>(cur_a) * static_cast<uint64_t>(cur_c);
    }

    std::cout << triplets << std::endl;

    return 0;
}

void read_lengths(std::uint32_t &len_a, std::uint32_t &len_b, std::uint32_t &len_c) {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    iss >> len_a >> len_b >> len_c;
}

void read_vec(std::uint32_t values, std::vector<std::uint64_t> &vec) {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    std::uint64_t value;
    while (values--) {
        iss >> value;
        vec.push_back(value);
    }
}
