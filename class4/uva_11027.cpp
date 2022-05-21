#include <iostream>
#include <ostream>
#include <vector>
#include <numeric>
#include <bitset>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define MAX_CHAR 26

vector<string> string_tokenizer(const string &sentence) {
    vector<string> words;
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

vector<ll> int_tokenizer(const string &sentence) {
    vector<ll> words;
    stringstream ss(sentence);
    ll word;
    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

namespace multinomial {
    typedef std::vector<size_t> SVI;
    typedef SVI::iterator SVII;
    typedef SVI::const_iterator SVICI;

    void view(std::ostream &ost, SVI const &v) {
        ost << "(";
        if (v.size() > 0)
            ost << v.at(0);

        for (size_t i = 1; i < v.size(); ++i) {
            size_t const vai(v.at(i));
            if (vai == 0) break;
            ost << ", " << vai;
        }
        ost << ")";
    }

    // class index calculates subscripts for class combo

    class index {
        static SVI pair;
        static SVI sole;

        static size_t pair_ind(size_t const, size_t const);

        static void layer(size_t const);

        static bool compare(size_t const, size_t const);

    public:
        static size_t get(size_t const, size_t const);

        static size_t get(size_t const);

        static size_t get(SVI const &);
    };

    SVI index::pair(1, 1);
    SVI index::sole(1, 0);

    size_t index::pair_ind(size_t const rem, size_t const top) {
        return ((rem * (rem + 1)) / 2 + ((top > rem) ? rem : top));
    }

    void index::layer(size_t const rem) {
        if (pair.size() < pair_ind(rem, 0)) layer(rem - 1);
        pair.push_back(0);
        pair.push_back(1);
        for (size_t top = 2; top <= rem; ++top) {
            pair.push_back(pair.at(pair_ind(rem - top, top)));
            if (rem >= top)
                pair.back() += pair.at(pair_ind(rem, top - 1));
        }
        size_t const y(sole.back());
        sole.push_back(pair.at(pair_ind(rem - 1, rem - 1)));
        sole.back() += y;
    }

    bool index::compare(size_t const a, size_t const b) { return a > b; }

    size_t index::get(size_t const rem, size_t const top) {
        size_t const ind(pair_ind(rem, top));
        if (ind < pair.size()) return pair.at(ind);
        layer(rem);
        return pair.at(ind);
    }

    size_t index::get(size_t const rem) {
        if (rem < sole.size()) return sole.at(rem);
        layer(rem);
        return sole.at(rem);
    }

    size_t index::get(SVI const &part) {
        SVI temp(part);
        std::sort(temp.begin(), temp.end(), &compare);
        size_t minuend(std::accumulate(temp.begin(), temp.end(), 0));
        size_t ans(get(minuend));
        for (SVICI i = temp.begin(); i != temp.end(); ++i) {
            if (*i == 0) break;
            ans += get(minuend, *i - 1);
            minuend -= *i;
        }
        return ans;
    }

    // the calc_multinomial values are stored in class combo

    template<typename result_type>
    class combo {
        static std::vector<result_type> guts;
        static size_t tier;

        static void layer(SVI const &);

        static void layer(size_t const, size_t const,
                          size_t const, SVI &);

        static void layer();

    public:
        static result_type get(SVI const &);
    };

    template<typename result_type>
    std::vector<result_type> combo<result_type>::guts(1, 1);

    template<typename result_type>
    size_t combo<result_type>::tier(0);

    template<typename result_type>
    void combo<result_type>::layer(SVI const &part) {
        result_type total(0);
        SVI temp(part);
        for (SVII n = temp.begin(); n != temp.end(); ++n) {
            size_t &tan(*n);
            if (tan == 0) break;
            tan--;
            total += get(temp);
            tan++;
        }
        guts.push_back(total);
    }

    template<typename result_type>
    void combo<result_type>::layer(size_t const rem, size_t const top,
                                   size_t const pos, SVI &part) {
        if (rem == 0) {
            layer(part);
            return;
        }

        for (size_t n = 1;; ++n) {
            if (n > rem) break;
            if (n > top) break;
            part.at(pos) = n;
            if (top > n)
                layer(rem - n, n, pos + 1, part);
            else
                layer(rem - n, top, pos + 1, part);
            part.at(pos) = 0;
        }
    }

    template<typename result_type>
    void combo<result_type>::layer() {
        ++tier;
        SVI part(tier);
        layer(tier, tier, 0, part);
    }

    template<typename result_type>
    result_type combo<result_type>::get(SVI const &part) {
        size_t const ind(index::get(part));
        while (guts.size() <= ind) layer();
        return guts.at(ind);
    }

    // the next two functions are probably all that you really need

    template<typename result_type>
    result_type multi(SVI const &part) { return combo<result_type>::get(part); }

    size_t parti(size_t const rem, size_t const top) {
        return index::get(rem, (top > rem) ? rem : top);
    }
}

ll calc_multinomial(const vector<size_t> &hist) {
    vector<size_t> new_hist = vector<size_t>(MAX_CHAR, 0);
    for (ll i = 0; i < MAX_CHAR; i++) {
        new_hist[i] = hist[i] / 2;
    }
    return multinomial::multi<ll>(new_hist);
}

bool can_be_palin(const string &word, vector<size_t> hist) {
    ll odd_char = 0;
    for (ll i = 0; i < MAX_CHAR; i++)
        if (hist[i] % 2 == 1)
            odd_char++;

    if ((word.size() % 2 == 1 && odd_char == 1) ||
        (word.size() % 2 == 0 && odd_char == 0))
        return true;
    return false;
}

string palindromic_permutation(const string &word, ll n) {
    // make hist
    vector<size_t> hist = vector<size_t>(MAX_CHAR, 0);
    for (char c: word)
        hist[c - 'a']++;

    // check
    if (!can_be_palin(word, hist))
        return "XXX";

    if (calc_multinomial(hist) < n)
        return "XXX";

    if (word.size() <= 1) {
        return word;
    }

    if (n <= 0) {
        return "XXX";
    }

    string first_half;
    // narrowing dimention
    for (int i = 0; i < word.size() / 2; ++i) {
        bool changed = false;
        int first_char = -1;
        for (int j = 0; j < MAX_CHAR; ++j) {
            if (hist[j] == 0)
                continue;

            if (first_char == -1)
                first_char = j;

            hist[j] -= 2;
            ll mult = calc_multinomial(hist);
            if (n <= mult) {
                first_half += string(1, j + 'a');
                changed = true;
                break;
            }
            hist[j] += 2;
            n -= mult;
        }

        if (!changed) {
            first_half += string(1, first_char + 'a');
            hist[first_char] -= 2;
        }
    }

//    assert(!first_half.empty());

    // create first half
    char odd_char;
    for (ll i = 0; i < MAX_CHAR; i++) {
        if (hist[i] % 2 == 1)
            odd_char = i + 'a';
        first_half += string(hist[i] / 2, i + 'a');
    }

    // find palindrome
    ll count = 0;
    do {
        ++count;
        if (count < n)
            continue;

        string palindrome = first_half;
        if (word.size() % 2 == 1)
            palindrome += odd_char;
        string rev_half = first_half;
        reverse(rev_half.begin(), rev_half.end());
        palindrome += rev_half;

        return palindrome;
    } while (next_permutation(first_half.begin(), first_half.end()));
}

// Function to print all permutations of string word using next_permutation
string palindromic_permutation2(string &word, ll n) {
    // make hist
    vector<size_t> hist = vector<size_t>(MAX_CHAR, 0);
    for (char c: word)
        hist[c - 'a']++;

    // check
    if (!can_be_palin(word, hist))
        return "XXX";

    // create first half
    string half = "";
    char odd_char;
    for (ll i = 0; i < MAX_CHAR; i++) {
        if (hist[i] % 2 == 1)
            odd_char = i + 'a';
        half += string(hist[i] / 2, i + 'a');
    }

    // find palindrome
    ll count = 0;
    do {
        ++count;
        if (count < n)
            continue;

        string palindrome = half;
        if (word.length() % 2 == 1)
            palindrome += odd_char;
        string rev_half = half;
        reverse(rev_half.begin(), rev_half.end());
        palindrome += rev_half;

        return palindrome;
    } while (next_permutation(half.begin(), half.end()));

    return "XXX";
}


int main() {
    string sentence;

    getline(cin, sentence);
    ll N = stoi(sentence);

    for (ll i = 0; i < N; ++i) {
        getline(cin, sentence);
        vector<string> line = string_tokenizer(sentence);

        string word = line[0];
        ll n = stoi(line[1]);

        string palindrome = palindromic_permutation(word, n);
        cout << "Case " << i + 1 << ": " << palindrome << endl;
    }
    return 0;
}

/*
3
abba 1
abba 2
abba 3

10
a 1
ab 1
aa 1
aa 2
abc 1
aba 1
aab 1
aaa 1
aaa 2
abcd 1

*/

