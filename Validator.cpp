#include "testlib-master/testlib.h"
using namespace std;

// inf - stream with the testdata.

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int testCaseCount = 1;
    // make comment on the next two line if the problem single test case
    testCaseCount = inf.readInt(1, 1000, "TestCase");
    inf.readEoln();
    for (int testCase = 1; testCase <= testCaseCount; testCase++) {
        setTestCase(testCase);
        
    }
    inf.readEof();
    return 0;
}