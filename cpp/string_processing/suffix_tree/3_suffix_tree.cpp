#include <algorithm>
#include <map>
#include <vector>
#include <iostream>

class suffix_tree {
private:
    const char chr;
    int p_counter;  // prefix_counter
    std::map<char, suffix_tree> nodes;

    explicit suffix_tree(char chr) : chr(chr), p_counter(0) {}

    bool is_root() const { return chr == 0; };

    bool is_word() const { return p_counter > 0; };

    bool is_leaf() const { return nodes.empty(); };

    void digest(const std::string &str, int pos) {
        if (pos == str.length()) {
            ++p_counter;
            return;
        }
        auto it = nodes.emplace_hint(nodes.end(), str[pos], suffix_tree(str[pos]));
        it->second.digest(str, pos + 1);
    }

    suffix_tree get_suffix_tree(const std::string &prefix, int pos) const {
        suffix_tree root;
        if (pos == prefix.length()) {
            root.nodes = nodes;
            return root;
        }
        auto it = nodes.find(prefix[pos]);
        if (it == nodes.end()) { return suffix_tree(); }
        return it->second.get_suffix_tree(prefix, pos + 1);
    }

    int occurrences(const std::string &word, int pos) const {
        if (pos == word.length()) {
            return p_counter;
        }
        auto it = nodes.find(word[pos]);
        if (it == nodes.end()) { return 0; }
        return it->second.occurrences(word, pos + 1);
    }

public:
    suffix_tree() : suffix_tree(0) {}

    void digest(const std::string &str) { digest(str, 0); }

    std::vector<std::string> words() const {
        std::vector<std::string> all_str;
        if (is_word()) {
            for (int i = 0; i < p_counter; ++i) {
                all_str.push_back({chr});
            }
        }
        for (const auto &node: nodes) {
            for (auto &str: node.second.words()) {
                if (is_root()) {
                    std::reverse(str.begin(), str.end());
                } else {
                    str.push_back(chr);
                }
                all_str.emplace_back(str);
            }
        }
        return all_str;
    }

    std::vector<std::string> suffixes(const std::string &prefix) const {
        return get_suffix_tree(prefix, 0).words();
    }

    int occurrences(const std::string &word) const {
        return occurrences(word, 0);
    }

    // String Matching in
    std::vector<std::string> match(const std::string &prefix) const {
        const int prefix_occurrences = occurrences(prefix);
        std::vector<std::string> matches(prefix_occurrences, prefix);
        for (const auto &suffix: suffixes(prefix)) {
            matches.push_back(prefix + suffix);
        }
        return matches;
    }
    // Longest Repeated Substring
    // Longest Common Substring
};

int main() {

//
//    std::string st = "";
//    std::string c = st.substr(0, st.length() - 100);
//    st.pop_back();
//    std::cout << "<" << c << ">: " << c.size() << std::endl;

    suffix_tree stA;
    stA.digest("mobile");
    stA.digest("mouse");
    stA.digest("moneypot");
    stA.digest("monitor");
    stA.digest("mousepad");

    std::string query = "mouse";

    for (int i=2; i<=query.size(); ++i) {
        std::string st = query.substr(0, i);
        std::vector<std::string> suggestions = stA.match(st);
        std::cout << st << " : ";
        for (const auto &suggestion: suggestions) {
            std::cout << suggestion << ", ";
        }
        std::cout << std::endl;
    }

//    suffix_tree st;
//    st.digest("A");
//    st.digest("ACA");
//    st.digest("AGACA");
//    st.digest("ATAGACA");
//    st.digest("CA");
//    st.digest("GACA");
//    st.digest("GATAGACA");
//    st.digest("TAGACA");
//
//    int c = st.occurrences("");
//
//    std::vector<std::string> suggestions = st.match("A");
//    for (const auto &suggestion: suggestions) {
//        std::cout << suggestion << ", ";
//    }

//    suffix_tree st0;
//    st0.digest("aa");
//    st0.digest("abd");
//    st0.digest("abd");
//    st0.digest("abde");
//
//    st0.digest("bc");
//    st0.digest("bc");
//    st0.digest("bxz");
//    st0.digest("bxz");
//    st0.digest("bxz");
//
//    st0.digest("cp");
//    st0.digest("cqrs");
//    st0.digest("cqrs");
//    st0.digest("cqrtu");
//
//    auto qq = st0.get_all_str();
//    auto qw = st0.get_all_str("bx");
//
//    suffix_tree st;
//    st.digest("he");
//    st.digest("ha");
//    st.digest("hi");
//    st.digest("hello");
//
////    auto st = st.get_all_str();
//    auto st = st.get_suffix_tree("he");
//    auto p = st.get_all_str();
//    auto n = suffix_tree().get_all_str();

    return 0;
}
