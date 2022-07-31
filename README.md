# Codeforces-Polygon-Template

### Template for codeforces contest preperation on [polygon](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwiU3cXDq6b2AhWQ-6QKHY7YAX0QFnoECAoQAQ&url=https%3A%2F%2Fpolygon.codeforces.com%2F&usg=AOvVaw3i2v31m8II47sBuBT85c8t)

---

There are 4 files to use

- Validator.cpp
  - to make validator for the problem to check the validation of the test case

- Checker.cpp
  - to make special checker for your problem when there a lot of valid solutions

- Solution.cpp
  - to put your solution in it and upload it

- Generator.cpp
  - to generate the test cases that you need in your problem

`input.txt` and `output.txt` we use them with `Solution.cpp` file but you can ignore them and use your terminal instead of files

---

There is folder `testlib-master` in it there are a lot of examples of checkers, generators, validators, and there is the header file that we include it in validator.cpp and checker.cpp `testlib.h`

**Linux**:

- **You should copy to `testlib.h` and `testlib.h.gch` from `testlib-master` to `/usr/local/include`**

**Windows**:

- **You should copy to `testlib.h` and `testlib.h.gch` from `testlib-master` to `include` folder in your compiler folder**

---

You can read information about `testlib.h` from [here](https://github.com/7oSkaaa/Codeforces-Polygon-Template/blob/main/testlib-master/README.md).

You can see these tutorial, they will help you to write a good problem

- [Writing Statements tutorial](https://polygon.codeforces.com/docs/statements-tex-manual?ccid=f5bddf71bb1644157d570cc2043d9df7&session=68e51869dd74479dbd85d7d89b67012852f5a418)

- [Validators tutorial](https://codeforces.com/blog/entry/18426)

- [Checker tutorial](https://codeforces.com/blog/entry/18431)

- [Generators tutorial](https://codeforces.com/blog/entry/18291)

- [Interactors tutorial](https://codeforces.com/blog/entry/18455)

- [testlib.h information](https://codeforces.com/blog/entry/18289)

---

There are generator builtin-functions you can use from `testlib.h`, and you can use `Generator.cpp` file.

If you will use `Generator.cpp` file, these information will help you to use it.

- Choose number of file you want to print in line `134`
- Choose number of test cases in each file from line `131`
- If your problem has a single test case uncomment line `130`

there are many functions to help you to generate test like:

- gen_string
  - generate a string `Upper Case` or `Lower Case` and in any range you want with your length

- gen_string_u_and_l
  - generate a string `Upper Case` and `Lower Case` and in any range you want with your length
 
- gen_int
  - generate a integer number in the range you want from `L` to `R`

- gen_palindrome
  - generate a palindrome string with your length in the range that you want

- gen_array
  - generate an array with your size and in range you want, you can make the array `normal` or `increasing` or `decreasing`

- gen_array_2D
  - generate an array_2D with your size and in range you want.

- gen_permutation
  - generate an array with a permutation of `N`

- gen_bit_int
  - generate a string with your length consit of digit in the range that you want

- gen_array_of_pairs
  - generate an array of pairs with your length in the range that you want, you can choose if the pair is interval or not.

- gen_char
  - gen character in range that you want 

- gen_tree
  - generate a tree or `bamboo` like tree or `star` like tree

- gen_graph
  - generate a simple graph

The test cases files will exported in `Tests` folder in the same directory of the `Generator.cpp` file

---

### You can see tutorial video for polygon site, how to use it and write a problem live from [](https://drive.google.com/file/d/198dWogj2xSGWZxVMNtCRMqVnawgVRXLX/view?usp=sharing)

---

#### This a tutorial for polygon and how to use it [Ali Ibrahim Site](https://ali-ibrahim137.github.io/competitive/programming/2020/09/27/polygon-codeforces.html)
