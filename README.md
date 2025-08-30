# Codeforces Polygon Template

Template for creating Codeforces Polygon problems with a ready-to-use single-file generator, validator, and checker based on testlib.

## Repository layout

- Generator.cpp — single-file generator with inlined helpers (numbers/arrays/strings/graphs/utils) using testlib’s rnd
- Validator.cpp — place your input validation here (uses testlib)
- Checker.cpp — place your custom checker here (uses testlib)
- Solution.cpp — reference/author solution (optional)
- input.txt, output.txt — optional local I/O for Solution.cpp
- testlib/ — bundled testlib sources (headers, examples).

## testlib

Polygon provides testlib.h on the server side automatically. For local builds, use the header from this repo:

- Include with: #include "testlib.h"
- Build with: add -I testlib to your compiler flags
- More docs in this repo: [testlib/README.md](testlib/README.md)

## Build locally (macOS/Linux)

Example compile commands:

```
g++ -std=gnu++17 -O2 -Wall -Wextra -I testlib -o gen Generator.cpp
g++ -std=gnu++17 -O2 -Wall -Wextra -I testlib -o validator Validator.cpp
g++ -std=gnu++17 -O2 -Wall -Wextra -I testlib -o checker Checker.cpp
```

## Generator: inlined helpers you can call

Namespaces available inside `Generator.cpp`:

- gen_numbers: random(l, r), random_range, random_real, random_exclude, random_weighted
- gen_arrays: random(len, l, r, unique, sorted), permutation(n), matrix, pairs, subset, partition, progressions, bit_array, shuffled, strictly_increasing/decreasing, random_with_sum
- gen_strings: CaseType, random, palindrome, random_alphanum, random_custom, random_strings, palindromes
- gen_graphs: tree, simple_graph, weighted_graph, directed_graph, dag, bipartite, star, cycle, complete, regular, tree_with_diameter, chain_tree
- gen_utils: print overloads for vectors, pairs, tuples

Skeleton to fill in inside `Generate_tests()`:

```
int T = opt<int>("T", 1);           // number of testcases per file
long long sumNCap = opt<long long>("sumN", 200000LL); // optional cap for sum of n
if (T > 1) std::cout << T << '\n';
for (int tc = 1; tc <= T; ++tc) {
  // write your per-test generation here
  // e.g., int n = gen_numbers::random<int>(1, 10);
  // auto a = gen_arrays::random<int>(n, -100, 100);
  // std::cout << n << '\n';
  // gen_utils::print(a);
}
```

## Using generator in Polygon

Upload `Generator.cpp` as the generator. Use a FreeMarker loop in “Generate tests” to produce multiple files. Pass the loop index as a seed (last arg is used by testlib’s registerGen for seeding), and add your optional CLI flags (like T, n, ranges):

```
<#list begin..end as s>
  ./gen --T=1 ${s} > $
</#list>
```

Examples:

```
<#list 1..20 as s>
  ./gen --T=1 --n=1000 --l=-1000000000 --r=1000000000 ${s} > $
</#list>
```

If your input format requires multiple testcases in a single file, print T first and generate T tests per run (set --T accordingly) and keep one output file per run.

## Learning resources

- [Validators tutorial](https://codeforces.com/blog/entry/18426)
- [Checker tutorial](https://codeforces.com/blog/entry/18431)
- [Generators tutorial](https://codeforces.com/blog/entry/18291)
- [Interactors tutorial](https://codeforces.com/blog/entry/18455)
- [testlib.h information](https://codeforces.com/blog/entry/18289)
- [Polygon statements manual](https://polygon.codeforces.com/docs/statements-tex-manual)
- [Polygon usage tutorial](https://quangloc99.github.io/2022/03/08/polygon-codeforces-tutorial.html)

### Videos

- Polygon walkthrough (part 1): https://drive.google.com/file/d/198dWogj2xSGWZxVMNtCRMqVnawgVRXLX/view?usp=sharing
- Polygon updates (part 2): https://drive.google.com/file/d/1t5aJPvVRx-D_cuaQuQJ8WV3vh6qnbPDw/view?usp=sharing
