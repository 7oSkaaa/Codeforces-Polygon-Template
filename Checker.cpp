#include "testlib-master/testlib.h"
#include <bits/stdc++.h>

#define ll long long
#define all(vec) (vec.begin(), vec.end())
#define sz(s) (int)s.size()
using namespace std;

// inf - stream with the testdata.
// ouf - stream with the contestant output.
// ans - stream with the jury answer.

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


    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    
    string strAnswer;
    int TestCases = 0;

    while (!ans.eof()) {
        TestCases++;
        setTestCase(TestCases);
        
        string j = ans.readString("-1|[0-9]+", "jury");

        if (j == "" && ans.eof())
          break;
        
        string p = ouf.readString("-1|[0-9]+", "contestant");
        strAnswer = p;

        if(p == "" && ouf.eof())
            break;

        Check_answers(j, p);
    }
    
    if (TestCases == 1)
        quitf(_ok, "1 line");
    
    quitf(_ok, "%d lines", TestCases);
}
