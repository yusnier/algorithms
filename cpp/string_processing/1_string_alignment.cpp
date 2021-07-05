#include <algorithm>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> vector2d_int;

int minimum_edit_distance(const std::string &a, const std::string &b) {
    vector2d_int table(a.length() + 1, std::vector<int>(b.length() + 1, 0));

    for (int i = 0; i <= a.length(); ++i) {
        for (int j = 0; j <= b.length(); ++j) {
            if (i == 0) {
                table[i][j] = j;
            } else if (j == 0) {
                table[i][j] = i;
            } else if (a[i - 1] == b[j - 1]) {
                table[i][j] = table[i - 1][j - 1];
            } else {
                table[i][j] = std::min(table[i - 1][j - 1], std::min(table[i][j - 1], table[i - 1][j])) + 1;
            }
        }
    }

    return table[a.length()][b.length()];
}

enum operation {
    OK = 0, CHANGED = 1, INSERTED = 2, DELETED = 3
};

std::vector<std::pair<char, operation>> minimum_edit_distance_solution(const std::string &a, const std::string &b) {
    vector2d_int table(a.length() + 1, std::vector<int>(b.length() + 1, 0));

    for (int i = 0; i <= a.length(); ++i) {
        for (int j = 0; j <= b.length(); ++j) {
            if (i == 0) {
                table[i][j] = j;
            } else if (j == 0) {
                table[i][j] = i;
            } else if (a[i - 1] == b[j - 1]) {
                table[i][j] = table[i - 1][j - 1];
            } else {
                table[i][j] = std::min(table[i - 1][j - 1], std::min(table[i][j - 1], table[i - 1][j])) + 1;
            }
        }
    }

    std::vector<std::pair<char, operation>> solution;
    int i = static_cast<int>(a.length());
    int j = static_cast<int>(b.length());
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {  // no change
            solution.emplace_back(a[i - 1], OK);
            --i;
            --j;
        } else if (table[i][j] - 1 == table[i - 1][j]) {
            solution.emplace_back(a[i - 1], DELETED);
            --i;
        } else if (table[i][j] - 1 == table[i][j - 1]) {
            solution.emplace_back(b[j - 1], INSERTED);
            --j;
        } else {
            solution.emplace_back(a[i - 1], CHANGED);
            --i;
            --j;
        }
    }
    std::reverse(solution.begin(), solution.end());

    return solution;
}

void test_algorithms(const std::string &a, const std::string &b) {
    const std::string ops[] = {"OK", "changed", "inserted", "deleted"};
    const int min = minimum_edit_distance(a, b);
    std::cout << "Minimum operations: " << min << std::endl;
    const std::vector<std::pair<char, operation>> solution = minimum_edit_distance_solution(a, b);
    for (const auto &op: solution) {
        std::cout << op.first << " -> " << ops[op.second] << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    // https://www.youtube.com/watch?v=We3YDTzNXEk
    {
        //    |     A  B  C  D  E  F
        //  ------------------------
        //    |  0  1  2  3  4  5  6
        //  A |  1  0  1  2  3  4  5
        //  Z |  2  1  1  2  3  4  5
        //  C |  3  2  2  1  2  3  4
        //  E |  4  3  3  2  2  2  3
        //  D |  5  4  4  3  2  3  3
        test_algorithms( "AZCED", "ABCDEF");
    }
    // https://www.youtube.com/watch?v=bQ7kRW6zo9Y
    {
        //    |     T  C  G  A  C  G  T  C  A
        //  ----------------------------------
        //    |  0  1  2  3  4  5  6  7  8  9
        //  T |  1  0  1  2  3  4  5  6  7  8
        //  G |  2  1  1  1  2  3  4  5  6  7
        //  A |  3  2  2  2  1  2  3  4  5  6
        //  C |  4  3  2  3  2  1  2  3  4  5
        //  G |  5  4  3  2  3  2  1  2  3  4
        //  T |  6  5  4  3  3  3  2  1  2  3
        //  G |  7  6  5  4  4  4  3  2  2  3
        //  C |  8  7  6  5  5  4  4  3  2  3
        test_algorithms( "TGACGTGC", "TCGACGTCA");
    }
    return 0;
}
