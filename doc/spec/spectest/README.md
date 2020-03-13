<p align="center"><img src="../../spectest.png" height="84px" /></p>
<p align="center">Writing documentation means writing tests, and examples are becoming test codes as is.</p>

## Overview

Do you write a test code?
You know it is very important to make a test code, but it is one of tough work these days.
**SpecTest** will help you a little smaller work of that.

### Waht is SpecTest?

**SpecTest** is a testing system based on **Specification By Example**.
That is one of thought in **Behavior Driven Development**.
You only write a document, it will be tested automatically.

If you want to see a kind of examples soon, see [here](#example).

## How to Use

### `.spectest` File

#### Markdown Template


### Example

This an example of a **SpecTest** working for [Kinx Specification](../README.md).
SpecTest will automatically recognize a test code in your markdown document,
and run it and compare to the expected result.

> Note that some parts of Kinx Specification documentations are still under construction.
> 
```
$ ./kinx --exec:spectest
Test Cout = 54
[<>[<*********>][<****>][<***>][<*>][<*>][<***>][<****>][<**>][<**>][<***>][<*>][<*>][W]
[W][W][W][W][W][W][W][W][W][W][W][W][W][W][W][W][W][W][W]]

<Test Result Detail>

Entry: doc/spec/README.md
    Kinx Specification with SpecTest (0.00s)
    Entry: doc/spec/statement/declaration.md
        Declaration statement (0.52s)
            Case[0] (Normal case) ........................... successful (  0.08s)
            Case[1] (With initializer) ...................... successful (  0.06s)
            Case[2] (With initializer of expression) ........ successful (  0.06s)
            Case[3] (Multiple variable declaration) ......... successful (  0.06s)
            Case[4] (Constant value (1)) .................... successful (  0.03s)
            Case[5] (Constant value (2)) .................... successful (  0.06s)
            Case[6] (Constant value (3)) .................... successful (  0.04s)
            Case[7] (Constant value (4)) .................... successful (  0.03s)
            Case[8] (Constant value (5)) .................... successful (  0.06s)
    Entry: doc/spec/statement/enum.md
        Enum statement (0.25s)
            Case[0] (Normal case) ........................... successful (  0.06s)
            Case[1] (With initializer (1)) .................. successful (  0.06s)
            Case[2] (With initializer (2)) .................. successful (  0.05s)
            Case[3] (The scope) ............................. successful (  0.07s)
    Entry: doc/spec/statement/expression.md
        Expression statement (0.19s)
            Case[0] (Assignment) ............................ successful (  0.06s)
            Case[1] (Exponent Evaluation) ................... successful (  0.06s)
            Case[2] (Logical Undefined Operator) ............ successful (  0.06s)
    Entry: doc/spec/statement/mixin.md
        Mixin statement (0.07s)
            Case[0] (Normal case) ........................... successful (  0.07s)
    Entry: doc/spec/statement/block.md
        Block statement (0.07s)
            Case[0] (Scope) ................................. successful (  0.07s)
    Entry: doc/spec/statement/if_else.md
        If-Else statement (0.20s)
            Case[0] (Normal case) ........................... successful (  0.06s)
            Case[1] (No else clause) ........................ successful (  0.06s)
            Case[2] (If-else combination) ................... successful (  0.06s)
    Entry: doc/spec/statement/switch_case.md
        Switch-Case statement (0.33s)
            Case[0] (Normal case) ........................... successful (  0.07s)
            Case[1] (With do-while) ......................... successful (  0.08s)
            Case[2] (Non-integer value) ..................... successful (  0.09s)
            Case[3] (Complex switch-case pattern) ........... successful (  0.06s)
    Entry: doc/spec/statement/while.md
        While statement (0.12s)
            Case[0] (Normal case) ........................... successful (  0.06s)
            Case[1] (Infinaite loop) ........................ successful (  0.06s)
    Entry: doc/spec/statement/do_while.md
        Do-While statement (0.12s)
            Case[0] (Normal case) ........................... successful (  0.06s)
            Case[1] (Infinaite loop) ........................ successful (  0.06s)
    Entry: doc/spec/statement/for.md
        For statement (0.20s)
            Case[0] (Normal case) ........................... successful (  0.06s)
            Case[1] (Infinaite loop) ........................ successful (  0.06s)
            Case[2] (Declation variable in scope) ........... successful (  0.07s)
    Entry: doc/spec/algorithm/qsort.md
        Quicksort (0.06s)
            Case[0] (Quicksort Algorithm) ................... successful (  0.06s)
    Entry: doc/spec/algorithm/mergesort.md
        Merge Sort (0.06s)
            Case[0] (Merge Sort Algorithm) .................. successful (  0.06s)
    Entry(nolink): doc/spec/statement/try_catch_finally.md
    Entry(nolink): doc/spec/statement/return.md
    Entry(nolink): doc/spec/statement/yield.md
    Entry(nolink): doc/spec/statement/throw.md
    Entry(nolink): doc/spec/statement/function.md
    Entry(nolink): doc/spec/statement/class.md
    Entry(nolink): doc/spec/statement/module.md
    Entry(nolink): doc/spec/statement/lambda.md
    Entry(nolink): doc/spec/statement/closure.md
    Entry(nolink): doc/spec/statement/module.md
    Entry(nolink): doc/spec/lib/primitive/integer.md
    Entry(nolink): doc/spec/lib/primitive/double.md
    Entry(nolink): doc/spec/lib/primitive/string.md
    Entry(nolink): doc/spec/lib/primitive/array.md
    Entry(nolink): doc/spec/lib/basic/file.md
    Entry(nolink): doc/spec/lib/basic/directory.md
    Entry(nolink): doc/spec/lib/basic/regex.md
    Entry(nolink): doc/spec/lib/basic/xml.md
    Entry(nolink): doc/spec/lib/basic/zip.md
    Entry(nolink): doc/spec/lib/net/http.md

<Test Result>
    Total Test Cases:       54
        Successful  :       34
        Failed      :        0
        Warning     :       20

```
