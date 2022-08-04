#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define Num_of_Digits(n) ((int)log10(n) + 1)
#define all(vec) (vec.begin(), vec.end())
#define sz(x) (int) x.size()

const int N = 1e6 + 4;
const ll INF = 1LL << 60;

template < typename T = ll > using Pair = pair < T, T >;

namespace generator {

	ll gen_int(ll l = -INF, ll r = INF){
        return rnd.next(l, r);
	}

    string gen_string(int len = 0, bool upperCase = false, ll l = 1, ll r = 26) {
        assert(len >= 0 && len <= 5e6);
        string str(len, (upperCase ? 'A' : 'a'));
        for (char &ch: str)
            ch += gen_int(l, r) - 1;
        return str;
    }

    string gen_string_u_and_l(int len = 0, char l = 'a', char r = 'z'){
        assert(len >= 0 && len <= 5e6);
        string str(len, 'A');
        for(auto& ch : str){
            bool is_upper = gen_int(0, 1);
            if(is_upper)
                ch = 'A' + gen_int(l - 'A', r - 'A');
            else
                ch = 'a' + gen_int(l - 'a', r - 'A');
        }
        return str;
    }

    string gen_palindrome(int len = 0, bool upperCase = false, char l = 'a', char r = 'z'){
        assert(len >= 0 && len <= 5e6);
        string str(len, (upperCase ? 'A' : 'a'));
        for (int left = 0, right = len - 1; left <= right; left++, right--)
            str[left] = str[right] = str[left] + gen_int(l - (upperCase ? 'A' : 'a'), r - (upperCase ? 'A' : 'a'));
        return str;
    }

    vector < ll > gen_array(int len = 0, ll minRange = -INF, ll maxRange = INF, bool Increasing = false, bool Decreasing = false){
        assert(len >= 0 and len <= 5e6);
        vector < ll > vec(len);
        ll Delta = max(maxRange / len, 1ll);
        for (auto &x: vec) x = gen_int(minRange, maxRange);
        if(Increasing){
            for(int i = 0; i < len; i++)
                vec[i] = (i == 0 ? 0 : vec[i - 1]) + Delta;
        }
        if(Decreasing){
            for(int i = len - 1; i >= 0; i--)
                vec[i] = (i == len - 1 ? 0 : vec[i + 1]) + Delta;
        }
        return vec;
    }

    vector < ll > gen_unique_array(int len = 0, ll minRange = -INF, ll maxRange = INF, bool Increasing = false, bool Decreasing = false){
        assert(len >= 0 and len <= 5e6);
        vector < ll > vec;
        set < ll > st;
        while(sz(st) != len)
            st.insert(gen_int(minRange, maxRange));
        for(auto& i : st)
            vec.push_back(i);
        if(Increasing) 
            return vec;
        if(Decreasing) {
            reverse(vec.begin(), vec.end());
            return vec;
        }
        shuffle(vec.begin(), vec.end());
        return vec;
    }

    vector < vector < ll > > gen_array_2D(int row = 0, int col = 0, ll minRange = -INF, ll maxRange = INF){
		assert(row >= 0 and row <= 5e6 && col >= 0 && col <= 5e6 && row * col <= 1e8);
		vector < vector < ll > > vec(row);
		for(int i = 0; i < row; i++)
			vec[i] = gen_array(col, minRange, maxRange);
		return vec;
	}

    vector < ll > gen_permutation(int len = 0){
        assert(len >= 0 && len <= 5e6);
        vector < ll > vec(len);
        iota(vec.begin(), vec.end(), 1);
        shuffle(vec.begin(), vec.end());
        return vec;
    }

    string gen_big_int(int len = 0, char l = '0', char r = '9'){
		assert(len >= 0 && len <= 5e6);
		string str(len, '0');
		for (char &ch: str) 
			ch += gen_int(l - '0', r - '0');
		if(str.front() == '0') str.front() += gen_int(l - '0' + 1, r - '0');
		return str;
  	}

    vector < Pair < > > gen_array_of_pairs(int len = 0, ll minRange = -INF, ll maxRange = INF, bool Interval = false){
        assert(len >= 0 and len <= 5e6);
        vector < Pair < > > vec(len);
        for (auto &[l, r]: vec) 
            l = gen_int(minRange, maxRange), r = gen_int((Interval ? l : minRange), maxRange);
        return vec;
    }

    char gen_char(bool upperCase = false, bool Digit = false, char l = 'a', char r = 'z'){
		if(upperCase)
			return 'A' + gen_int(l - 'A', r - 'A');
		if(Digit)
			return '0' + gen_int(l - '0', r - '0');
		return 'a' + gen_int(l - 'a', r - 'a');
	}

    vector < Pair < > > gen_tree(ll n = 0){
        assert(n >= 0);
        vector < Pair < > > res(n ? n - 1 : 0);
        // if you like to have bamboo like tree or star like tree uncomment below 8 lines
        /*if (rng() % 5 == 0) { // bamboo like tree
            for (int i = 1; i < n; ++i) res[i-1] = {i, i + 1};
            return res;
        }
        if (rng() % 7 == 0) { // star tree
            for (int i = 2; i <= n; ++i) res[i-2] = {1, i};
            return res;
        }*/
        vector < ll > permutation(n + 1);
        iota(permutation.begin() + 1, permutation.begin() +  n + 1, 0);
        shuffle(permutation.begin() + 1, permutation.begin() + n + 1);
        for(int i = 2; i <= n; ++i){
            ll u = i, v = gen_int(1 , i - 1);
            u = permutation[u], v = permutation[v];
            res[i - 2] = minmax(u, v); // u < v, just for convenience while debugging
        }
        shuffle(res.begin(), res.end());
        return res;
    }
  
    vector < Pair < > > simple_graph(ll n = 0, ll m = 0) {
        assert(n > 0 && m >= n);
        ll max_edges = n * (n - 1) / 2;
        assert(m <= max_edges);
        vector < Pair < > > res = gen_tree(n);
        set < Pair < > > edge(res.begin(), res.end());
        for (int i = n; i <= m; ++i) {
            while (true) {
                ll u = gen_int(1, n), v = gen_int(1, n);
                if (u == v) continue;
                auto it = edge.insert(minmax(u, v));
                if (it.second) break;
            }
        }
        res.assign(edge.begin(), edge.end());
        return res;
    }

}

using namespace generator;

template < typename T = int > ostream& operator << (ostream &other, const vector < pair < T, T > > &v) {
    for (const auto &x : v) 
        other << x.first << ' ' << x.second << '\n';
    return other;
}

// comment the just below line if test cases required
#define SINGLE_TEST
constexpr int tests_count = 100, sum_of_n = 2e5;

// complete this function according to the requirements
void Generate_tests() {
    
}

// make name of text file
// freopen(made_txt(f).c_str(), "w", stdout);
string made_txt(int t){
    string testcase = "Tests/test";
    testcase += to_string(t);
    testcase += ".txt";
    return testcase;
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