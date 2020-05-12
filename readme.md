# pymm

gitee: <https://gitee.com/searchstar/pymm>

github: <https://github.com/searchstar2017/pymm>

#### description

An interpreted language. You can use it as an advanced calculator.

It relies on nothing but C++ standard library.

#### Fetures

##### data type

1. Four basic data types:

    - big integer
    - double
    - bool
    - fraction

    The basic data types can be converted to each other automatically during calculation.

2. One compound type

    generalized list. The elements in it can be any type including generalized list.

##### grammar

- Do not output the result if the statement is ended with a semicolon.
- C-style Loops: for, while, do-while
- C-style conditional branch: if-else

#### Compile and run

cd to the root directory of the project.

```shell
mkdir build
cd build
cmake ..
make
```

Then the executable ```pymm``` should be in the directory ```build```. Then just run it

```shell
./pymm
```

It will read from ```stdin``` and output to ```stdout```.

There are some examples in ```examples.txt```, and some useful scripts in the directory ```scripts```.

Enjoy!

#### TODO

- Support matrix
- Support function
- Modify the logic of judging whether the input is ended to allow '{' being placed in the next line, like this:

    ```c
    if (condition)
    {
        do something;
    }
    ```

- Use try-catch to handle errors.
- Report the errors instead of terminate the program when some errors detected.
