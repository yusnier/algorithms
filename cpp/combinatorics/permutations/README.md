# Permutations algorithms
A permutation of a set is a rearrangement of its elements. A set which consists of **n** elements has **n!**
permutations. Two of the best known related algorithms are the **Narayana Panditha's** algorithm and the **Heap's**
algorithm. The first one, less efficient, is used when we want to generate the next permutation with a higher or
lower lexicographic order, ignoring the permutations with repeated elements. The second one is very efficient when
you want to generate all possible n! permutations, regardless of the order. This algorithm doesn't ignore permutations
with repeated elements, as it generates them based on index position swaps rather than a lexicographic analysis.
Also, unlike Narayana Panditha's algorithm, this one needs the states of the previous iterations to generate each
permutation. The following table shows a comparison of the two algorithms:

| Algorithm         | Lexicographical ordered | Skip permutations with repeated elements | Space complexity | Time complexity for all permutation generation | Time complexity for each permutation |
|:---               |:----:   |:----:   |:----:    |:----: |:----:    |
| Narayana Panditha | **YES** | **YES** | **O(1)** | O(n!) | O(n)     |
| Heap              | NO      | NO      | O(n)     | O(n!) | **O(n)** |

## Implemented algorithms (C++14)
- Narayana Panditha’s algorithm
    - [Next permutation](https://github.com/yusnier/algorithms/blob/main/cpp/combinatorics/permutations/next_permutation.cpp) in lexicographical order.
    - [Previous permutation](https://github.com/yusnier/algorithms/blob/main/cpp/combinatorics/permutations/prev_permutation.cpp) in lexicographical order.
- [Heap's algorithm (iterative version)](https://github.com/yusnier/algorithms/blob/main/cpp/combinatorics/permutations/heap_generator.cpp) generates all possible permutations.
