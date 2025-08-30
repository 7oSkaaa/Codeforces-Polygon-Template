#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define Num_of_Digits(n) ((int)log10(n) + 1)
#define all(vec) (vec.begin(), vec.end())
#define sz(x) int(x.size())

const ll INF = 1LL << 60;

template < typename T = ll > using Pair = pair < T, T >;

namespace gen_numbers {
    template < typename T = long long >
    T random (T l, T r) {
        if constexpr (std::is_integral_v<T> && std::is_signed_v<T>)
            return static_cast<T>(rnd.next((long long)l, (long long)r));
        else if constexpr (std::is_integral_v<T> && std::is_unsigned_v<T>)
            return static_cast<T>(rnd.next((unsigned long long)l, (unsigned long long)r));
        else
            return static_cast<T>(rnd.next((double)l, (double)r));
    }

    template < typename T = long long >
    vector < T > random_range (T l, T r, int count) {
        vector < T > v(count);
        for (auto &x : v) x = random<T>(l, r);
        return v;
    }

    template < typename T = long long >
    T random_exclude (T l, T r, const set < T > &exclude) {
        T val;
        do { val = random<T>(l, r); } while (exclude.count(val));
        return val;
    }

    template < typename T = long long >
    vector < T > random_range_exclude (T l, T r, int count, const set < T > &exclude) {
        vector < T > v;
        while ((int)v.size() < count) {
            T val = random<T>(l, r);
            if (!exclude.count(val)) v.push_back(val);
        }
        return v;
    }

    template < typename T = long long >
    T random_weighted (const vector < T > &values, const vector < double > &weights) {
        double sum = 0.0; for (double w : weights) sum += w;
        double r = rnd.next(0.0, sum), acc = 0.0;
        for (size_t i = 0; i < values.size(); ++i) { acc += weights[i]; if (r < acc) return values[i]; }
        return values.back();
    }

    template < typename T = double >
    T random_real (T l, T r) { return static_cast<T>(rnd.next((double)l, (double)r)); }

    template < typename T = double >
    T random_real_exclude (T l, T r, T excl_l, T excl_r) {
        T val; do { val = random_real<T>(l, r); } while (val >= excl_l && val <= excl_r); return val;
    }
}

namespace gen_arrays {
    template < typename T = long long >
    vector < T > random (int len, T l, T r, bool unique = false, bool sorted = false) {
        vector < T > v;
        if (unique) {
            set < T > s;
            while ((int)s.size() < len) s.insert((T)rnd.next((long long)l, (long long)r));
            v.assign(s.begin(), s.end());
        } else {
            v.resize(len);
            for (auto &x : v) x = (T)rnd.next((long long)l, (long long)r);
        }
        if (sorted) sort(v.begin(), v.end());
        return v;
    }

    template < typename T = int >
    vector < T > permutation (int n) {
        vector < T > v(n); iota(v.begin(), v.end(), 1); shuffle(v.begin(), v.end()); return v;
    }

    template < typename T = long long >
    vector < vector < T > > matrix (int rows, int cols, T l, T r, bool unique_rows = false, bool sorted_rows = false) {
        vector < vector < T > > mat(rows);
        for (auto &row : mat) row = random<T>(cols, l, r, unique_rows, sorted_rows);
        return mat;
    }

    template < typename T = long long >
    vector < pair < T, T > > pairs (int len, T l1, T r1, T l2, T r2, bool ordered = false) {
        vector < pair < T, T > > v(len);
        for (auto &p : v) {
            p.first = (T)rnd.next((long long)l1, (long long)r1);
            p.second = (T)rnd.next((long long)l2, (long long)r2);
            if (ordered && p.first > p.second) swap(p.first, p.second);
        }
        return v;
    }

    template < typename T = long long >
    vector < T > subset (T l, T r, int k, bool sorted = false) {
        set < T > s; while ((int)s.size() < k) s.insert((T)rnd.next((long long)l, (long long)r));
        vector < T > v(s.begin(), s.end()); if (!sorted) shuffle(v.begin(), v.end()); return v;
    }

    template < typename T = long long >
    vector < T > partition (T sum, int k, T min_val, T max_val) {
        vector < T > parts(k, min_val); sum -= min_val * k;
        for (int i = 0; i < k && sum > 0; ++i) {
            T add = min(sum, max_val - min_val);
            if (add > 0) { T delta = (T)rnd.next((long long)0, (long long)add); parts[i] += delta; sum -= delta; }
        }
        shuffle(parts.begin(), parts.end()); return parts;
    }

    template < typename T = long long >
    vector < T > arithmetic_progression (int len, T start, T step) {
        vector < T > v(len); for (int i = 0; i < len; ++i) v[i] = start + i * step; return v;
    }

    template < typename T = long long >
    vector < T > geometric_progression (int len, T start, T ratio) {
        vector < T > v(len); T val = start; for (int i = 0; i < len; ++i) { v[i] = val; val *= ratio; } return v;
    }

    template < typename T = long long >
    vector < T > constant_array (int len, T value) { return vector < T > (len, value); }

    template < typename T = int >
    vector < T > bit_array (int len, double prob_one) {
        vector < T > v(len); for (int i = 0; i < len; ++i) v[i] = (rnd.next(0.0, 1.0) < prob_one); return v;
    }

    template < typename T >
    vector < T > shuffled (vector < T > v) { shuffle(v.begin(), v.end()); return v; }

    template < typename T = long long >
    vector < T > strictly_increasing (int len, T start, T step_min, T step_max) {
        vector < T > v(len); T cur = start; for (int i = 0; i < len; ++i) { v[i] = cur; if (i + 1 < len) cur += (T)rnd.next((long long)step_min, (long long)step_max); } return v;
    }

    template < typename T = long long >
    vector < T > strictly_decreasing (int len, T start, T step_min, T step_max) {
        vector < T > v(len); T cur = start; for (int i = 0; i < len; ++i) { v[i] = cur; if (i + 1 < len) cur -= (T)rnd.next((long long)step_min, (long long)step_max); } return v;
    }

    template < typename T = long long >
    vector < T > random_with_sum (int len, T sum, T min_val, T max_val) {
        vector < T > v(len, min_val); sum -= min_val * len;
        for (int i = 0; i < len && sum > 0; ++i) { T add = min(sum, max_val - min_val); if (add > 0) { T delta = (T)rnd.next((long long)0, (long long)add); v[i] += delta; sum -= delta; } }
        shuffle(v.begin(), v.end()); return v;
    }
}

namespace gen_strings {
    enum class CaseType { Lower, Upper, Mixed };
    inline char random_char (CaseType caseType, char l = 'a', char r = 'z') {
        char base = (caseType == CaseType::Upper) ? 'A' : 'a';
        char ch = base + (char)rnd.next((int)(l - base), (int)(r - base));
        if (caseType == CaseType::Mixed && rnd.next(0, 1)) ch = std::islower(ch) ? std::toupper(ch) : std::tolower(ch);
        return ch;
    }
    inline string random (int len, CaseType caseType, char l = 'a', char r = 'z') {
        string s(len, 'a'); for (auto &ch : s) ch = random_char(caseType, l, r); return s;
    }
    inline string palindrome (int len, CaseType caseType, char l = 'a', char r = 'z') {
        string s(len, 'a'); for (int i = 0, j = len - 1; i <= j; ++i, --j) { char ch = random_char(caseType, l, r); s[i] = s[j] = ch; } return s;
    }
    inline string random_alphanum (int len, bool letters, bool digits, CaseType caseType) {
        string s; s.reserve(len);
        for (int i = 0; i < len; ++i) {
            if (letters && digits) { if (rnd.next(0, 1)) s += random_char(caseType); else s += (char)('0' + rnd.next(0, 9)); }
            else if (letters) s += random_char(caseType);
            else s += (char)('0' + rnd.next(0, 9));
        }
        return s;
    }
    inline string random_custom (int len, const string &alphabet) {
        string s(len, ' '); for (auto &ch : s) ch = alphabet[rnd.next(0, (int)alphabet.size() - 1)]; return s;
    }
    inline vector < string > random_strings (int count, int len, CaseType caseType) {
        vector < string > v(count); for (auto &s : v) s = random(len, caseType); return v;
    }
    inline vector < string > palindromes (int count, int len, CaseType caseType) {
        vector < string > v(count); for (auto &s : v) s = palindrome(len, caseType); return v;
    }
}

namespace gen_graphs {
    inline vector < pair < int, int > > tree (int n) {
        vector < int > nodes(n); iota(nodes.begin(), nodes.end(), 1); shuffle(nodes.begin(), nodes.end());
        vector < pair < int, int > > edges; edges.reserve(max(0, n - 1));
        for (int i = 1; i < n; ++i) { int u = nodes[i], v = nodes[rnd.next(0, i - 1)]; edges.emplace_back(u, v); }
        shuffle(edges.begin(), edges.end()); return edges;
    }
    inline vector < pair < int, int > > simple_graph (int n, int m) {
        auto edges = tree(n); set < pair < int, int > > edge_set(edges.begin(), edges.end());
        while ((int)edge_set.size() < m) { int u = rnd.next(1, n); int v = rnd.next(1, n); if (u != v) edge_set.insert(minmax(u, v)); }
        return vector < pair < int, int > > (edge_set.begin(), edge_set.end());
    }
    inline vector < tuple < int, int, int > > weighted_graph (int n, int m, int min_w, int max_w) {
        auto edges = simple_graph(n, m); vector < tuple < int, int, int > > w; w.reserve(edges.size());
        for (auto &e : edges) { int wt = rnd.next(min_w, max_w); w.emplace_back(e.first, e.second, wt); } return w;
    }
    inline vector < pair < int, int > > directed_graph (int n, int m) {
        set < pair < int, int > > edge_set; while ((int)edge_set.size() < m) { int u = rnd.next(1, n); int v = rnd.next(1, n); if (u != v) edge_set.emplace(u, v); } return vector < pair < int, int > > (edge_set.begin(), edge_set.end());
    }
    inline vector < pair < int, int > > dag (int n, int m) {
        vector < int > nodes(n); iota(nodes.begin(), nodes.end(), 1); shuffle(nodes.begin(), nodes.end()); set < pair < int, int > > es;
        while ((int)es.size() < m) { int u = rnd.next(0, n - 2); int v = rnd.next(u + 1, n - 1); es.emplace(nodes[u], nodes[v]); } return vector < pair < int, int > > (es.begin(), es.end());
    }
    inline vector < pair < int, int > > bipartite (int n1, int n2, int m) {
        set < pair < int, int > > es; while ((int)es.size() < m) { int u = rnd.next(1, n1); int v = rnd.next(1, n2) + n1; es.emplace(u, v); } return vector < pair < int, int > > (es.begin(), es.end());
    }
    inline vector < pair < int, int > > star (int n, int center = 1) {
        vector < pair < int, int > > es; for (int i = 1; i <= n; ++i) if (i != center) es.emplace_back(center, i); shuffle(es.begin(), es.end()); return es;
    }
    inline vector < pair < int, int > > cycle (int n) {
        vector < int > nodes(n); iota(nodes.begin(), nodes.end(), 1); shuffle(nodes.begin(), nodes.end()); vector < pair < int, int > > es; for (int i = 0; i < n; ++i) es.emplace_back(nodes[i], nodes[(i + 1) % n]); return es;
    }
    inline vector < pair < int, int > > complete (int n) {
        vector < pair < int, int > > es; for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) es.emplace_back(i, j); return es;
    }
    inline vector < pair < int, int > > regular (int n, int d) {
        if (n * d % 2 != 0 || d >= n) return {}; vector < int > nodes; nodes.reserve(n * d);
        for (int i = 1; i <= n; ++i) for (int j = 0; j < d; ++j) nodes.push_back(i); shuffle(nodes.begin(), nodes.end());
        vector < pair < int, int > > es; for (size_t i = 0; i + 1 < nodes.size(); i += 2) { if (nodes[i] == nodes[i + 1]) return {}; es.emplace_back(nodes[i], nodes[i + 1]); } return es;
    }
    inline vector < pair < int, int > > tree_with_diameter (int n, int diameter) {
        if (diameter >= n) diameter = n - 1; vector < int > path(diameter + 1); iota(path.begin(), path.end(), 1); shuffle(path.begin(), path.end());
        vector < pair < int, int > > es; for (int i = 0; i < diameter; ++i) es.emplace_back(path[i], path[i + 1]); int nxt = diameter + 2;
        while ((int)es.size() < n - 1) { int attach = rnd.next(0, diameter); es.emplace_back(path[attach], nxt++); } shuffle(es.begin(), es.end()); return es;
    }
    inline vector < pair < int, int > > chain_tree (int n) { vector < pair < int, int > > es; for (int i = 2; i <= n; ++i) es.emplace_back(i - 1, i); return es; }
}

namespace gen_utils {
    template < typename T >
    void print (const vector < T > &v) { for (size_t i = 0; i < v.size(); ++i) cout << v[i] << (i + 1 < v.size() ? ' ' : '\n'); }
    template < typename T, typename U >
    void print (const vector < pair < T, U > > &v) { for (const auto &p : v) cout << p.first << ' ' << p.second << '\n'; }
    template < typename T >
    void print (const vector < vector < T > > &mat) { for (const auto &row : mat) print(row); }
    template < typename... Args >
    void print (const vector < tuple < Args... > > &v) {
        for (const auto &t : v) {
            apply([&](const auto &... elems) { size_t n = 0; ((cout << elems << (++n < sizeof...(elems) ? ' ' : '\n')), ...); }, t);
        }
    }
    template < typename T >
    void print (const T &val) { cout << val << '\n'; }
    inline void print (const vector < string > &v) { for (const auto &s : v) cout << s << '\n'; }
}

template < typename T = int > ostream& operator << (ostream &other, const vector < pair < T, T > > &v) {
    for (const auto &x : v)
        other << x.first << ' ' << x.second << '\n';
    return other;
}

template < typename T = int > ostream& operator << (ostream &other, const vector < T > &v) {
    for(int i = 0; i < (int)v.size(); i++)
        other << v[i] << " \n"[i == sz(v) - 1];
    return other;
}

using namespace gen_numbers;
using namespace gen_arrays;
using namespace gen_strings;
using namespace gen_graphs;
using namespace gen_utils;

void Generate_tests() {
    int T = opt<int> ("T", 1);
    long long sumNCap = opt < long long > ("sumN", 200000LL);
    if (T > 1) cout << T << '\n';
    
    for (int tc = 1; tc <= T; ++tc) {
        
    }
}

// use generator in Codeforces Polygon
/*
    <#list begin..end as s>
        Name_of_Generator_file ${s} > $
    </#list>
*/

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    Generate_tests();
}