#include <algorithm>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> vector2d_int;

int lcs(const std::string &a, const std::string &b) {
    vector2d_int table(a.length() + 1, std::vector<int>(b.length() + 1, 0));

    for (int i = 0; i <= a.length(); ++i) {
        for (int j = 0; j <= b.length(); ++j) {
            if (i == 0 || j == 0) {
                table[i][j] = 0;
            } else if (a[i - 1] == b[j - 1]) {
                table[i][j] = table[i - 1][j - 1] + 1;
            } else {
                table[i][j] = std::max(table[i - 1][j], table[i][j - 1]);
            }
        }
    }

    return table[a.length()][b.length()];
}

std::string lcs_solution(const std::string &a, const std::string &b) {
    vector2d_int table(a.length() + 1, std::vector<int>(b.length() + 1, 0));

    for (int i = 0; i <= a.length(); ++i) {
        for (int j = 0; j <= b.length(); ++j) {
            if (i == 0 || j == 0) {
                table[i][j] = 0;
            } else if (a[i - 1] == b[j - 1]) {
                table[i][j] = table[i - 1][j - 1] + 1;
            } else {
                table[i][j] = std::max(table[i - 1][j], table[i][j - 1]);
            }
        }
    }

    std::string solution;
    int i = static_cast<int>(a.length());
    int j = static_cast<int>(b.length());
    while (i > 0 && j > 0) {
        if (table[i][j] == table[i - 1][j]) {
            --i;
        } else if (table[i][j] == table[i][j - 1]) {
            --j;
        } else {
            // If table[i][j] came form the table[i - 1][j - 1] (diagonal),
            // then 'a[i - 1]' (could be also 'b[j - 1]') is part of the solution.
            solution.push_back(a[i - 1]);
            --i;
            --j;
        }
    }
    std::reverse(solution.begin(), solution.end());

    return solution;
}

int main() {
    // Reference: Competitive Programming 3, P. 247, Steven & Felix Halim.
    {
        //    |     A  G  C  A  T  G  C
        //  ---------------------------
        //    |  0  0  0  0  0  0  0  0
        //  A |  0  1  1  1  1  1  1  1
        //  C |  0  1  1  2  2  2  2  2
        //  A |  0  1  1  2  3  3  3  3
        //  A |  0  1  1  2  3  3  3  3
        //  T |  0  1  1  2  3  4  4  4
        //  C |  0  1  1  2  3  4  4  5
        //  C |  0  1  1  2  3  4  4  5
        const int max = lcs("ACAATCC", "AGCATGC");  // 5
        const std::string solution = lcs_solution("ACAATCC", "AGCATGC");  // ACATC
        std::cout << max << std::endl;
        std::cout << solution << std::endl;
    }
    std::cout << std::endl;
    // https://www.youtube.com/watch?v=HgUOWB0StNE
    {
        //    |     G  X  T  X  A  Y  B
        //  ---------------------------
        //    |  0  0  0  0  0  0  0  0
        //  A |  0  0  0  0  0  1  1  1
        //  G |  0  1  1  1  1  1  1  1
        //  G |  0  1  1  1  1  1  1  1
        //  T |  0  1  1  2  2  2  2  2
        //  A |  0  1  1  2  2  3  3  3
        //  B |  0  1  1  2  2  3  3  4
        const int max = lcs("AGGTAB", "GXTXAYB");  // 4
        const std::string solution = lcs_solution("AGGTAB", "GXTXAYB");  // GTAB
        std::cout << max << std::endl;
        std::cout << solution << std::endl;
    }
    std::cout << std::endl;
    // https://www.youtube.com/watch?v=NnD96abizww
    {
        //    |     A  B  C  D  A  F
        //  ------------------------
        //    |  0  0  0  0  0  0  0
        //  A |  0  1  1  1  1  1  1
        //  C |  0  1  1  2  2  2  2
        //  B |  0  1  2  2  2  2  2
        //  C |  0  1  2  3  3  3  3
        //  F |  0  1  2  3  3  3  4
        const int max = lcs("ACBCF", "ABCDAF");  // 4
        const std::string solution = lcs_solution("ACBCF", "ABCDAF");  // ABCF
        std::cout << max << std::endl;
        std::cout << solution << std::endl;
    }
    return 0;
}

