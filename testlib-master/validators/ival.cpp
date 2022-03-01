/**
 * Validates that input contains the only integer between 1 and 100, inclusive.
 * Also validates that file ends with EOLN and EOF.
 */

#include "testlib.h"

using namespace std;

int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    inf.readLong(1ll, 1000000000000000000ll, "a");
    inf.readSpace();
    inf.readLong(1ll, 1000000000000000000ll, "b");
    inf.readSpace();
    inf.readLong(1ll, 1000000000000000000ll, "c");
    inf.readSpace();
    inf.readEoln();
    inf.readEof();

    return 0;
}
