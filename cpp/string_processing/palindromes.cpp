#include <bits/stdc++.h>

using namespace std;

// Counts all palindromes substrings in 's'. Time complexity O(n^2), Space complexity O(1).
long count_all_palindromes(int n, string s) {
    int count = n;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (s[i] == s[j]) {
                int p = i, q = j;
                while (p < q && s[p] == s[q]) {
                    ++p;
                    --q;
                }
                if (p >= q) {  // if p > q (strictly), then the palindrome sequence has an even length.
                    std::cout << "(" << i << ", " << j << ")" << std::endl;
                    ++count;
                }
            }
        }
    }

    return count;
}

