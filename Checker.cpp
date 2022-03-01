#include "testlib-master/testlib.h"
#include <bits/stdc++.h>

#define ll long long
#define all(vec) (vec.begin(), vec.end())
#define sz(s) (int)s.size()
using namespace std;

// inf - stream with the testdata.
// ouf - stream with the contestant output.
// ans - stream with the jury answer.

set < ll > cheat_primes;

bool is_prime(ll n){
    if(n < 2 || (n % 2 == 0 && n != 2)) return false;
    for(int i = 3; i <= sqrt(n); i += 2)
        if(n % i == 0) return false;
    return true;
}

void build_cheats(ll num){
    if(num > 1e9) return;
    if(is_prime(num) || !num){
        cheat_primes.insert(num);
        build_cheats(num * 10 + 2);
        build_cheats(num * 10 + 3);
        build_cheats(num * 10 + 5);
        build_cheats(num * 10 + 7);
        build_cheats(num * 10 + 9);
    }
}

bool Check_answers(string a, string b){
    
    vector < string > va, vb;
    stringstream sa;
    
    sa << a;
    string cur;
    while (sa >> cur)
        va.push_back(cur);

    stringstream sb;
    sb << b;
    while (sb >> cur)
        vb.push_back(cur);

    if(vb == va)
        return true;

    string num = vb[0], Ans = va[0];

    while(num.back() == ' ') num.pop_back();
    while(Ans.back() == ' ') Ans.pop_back();
    
    if(Ans == num) return true;

    if(sz(num) != sz(Ans))
        quitf(_wa, "Your number lenght not equal %d", sz(Ans));

    if(!cheat_primes.count(stoll(num)))
        quitf(_wa, "Your answer isn't valid");

    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    
    string strAnswer;
    int n = 0;

    while (!ans.eof()) {
        
        setTestCase(n + 1);
        
        string j = ans.readString("-1|[0-9]+", "jury");

        if (j == "" && ans.eof())
          break;
        
        string p = ouf.readString("-1|[0-9]+", "contestant");
        strAnswer = p;

        if(p == "" && ouf.eof())
            break;

        n++;

        Check_answers(j, p);
    }
    
    if (n == 1)
        quitf(_ok, "1 line");
    
    quitf(_ok, "%d lines", n);
}
