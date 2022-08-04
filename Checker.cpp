#include "testlib.h"
#include <bits/stdc++.h>

#define ll long long
#define all(vec) (vec.begin(), vec.end())
#define sz(s) (int)s.size()
using namespace std;

// inf - stream with the testdata.
// ouf - stream with the contestant output.
// ans - stream with the jury answer.

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int TestCases = 0;
    while (!ans.eof()) {
        setTestCase(++TestCases);

    }
    if (TestCases == 1)
        quitf(_ok, "1 line");
    quitf(_ok, "%d lines", TestCases);
}