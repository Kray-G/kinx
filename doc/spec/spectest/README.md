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

#### Setup The File

Write `.spectest` file first.
This is written in Json style.
SpecTest will expect there is a `.spectest` file to load in the current directory.

#### Markdown Template

SpecTest will work the rule from `.spectest`.
That rule is based on **Markdown** by default and you can write some differences.

> Note that currently there is no template but for Markdown.
> In future some templates will be added for other document styles.

#### The Sample of `.spectest` File

See the example below.
This is the actual `.spectest` file of Kinx itself.

```json
{
    "root": "doc/spec",

    "testfile": "test.kx",
    "resultfile": "result.txt",
    "interpreter": "kinx",

    "ignoreFiles": [
        "doc/spec/../benchmark/README.md",
        "doc/spec/spectest/README.md"
    ]
}
```

#### Rules

The items of `.spectest` file is below.

|         Key         |                    Default                     |                                          Meaning                                           |
| ------------------- | ---------------------------------------------- | ------------------------------------------------------------------------------------------ |
| topLevelFilePattern | <code>"(README&#124;CONTENTS)\\\\.md"</code>   | Root document for SpecTest.                                                                |
| linkPattern         | `"\\[([^\\]]+)\\]\\s*\\(([^\\)]+\\.md)\\)"`    | Link pattern to traverse document tree.                                                    |
| targetNamePattern   | `"^#\\s+(.+)"`                                 | The line of TestSuite name.                                                                |
| startTestPattern    | `"^##+\\s+Examples"`                           | The line to recognize to start a test code area.                                           |
| endTestPattern      | `""`                                           | The line to recognize to end a test code area.                                             |
| testNamePattern     | `"^##+\\s+Example\\s+[0-9]+[\\.\\)]?\\s+(.+)"` | The line of TestCase name.                                                                 |
| startCodePattern    | `"^##+\\s+Code(?:\\s+\\(([^\\)]+)\\))?.*"`     | The line to recognize to start a test code section.                                        |
| startResultPattern  | `"^##+\\s+Result.*"`                           | The line to recognize to start a test result section.                                      |
| codeBlockStart      | `"^```"`                                       | The line to recognize to start a test code.                                                |
| codeBlockEnd        | `"^```"`                                       | The line to recognize to end a test code.                                                  |
| testfile            | `"test.kx"`                                    | Temporary test code file name.                                                             |
| resultfile          | `"result.txt"`                                 | Temporary test result file name.                                                           |
| compiler            | `""`                                           | *Currently Not supported*. This will be supported when supporting to use compiler.         |
| interpreter         | `"kinx"`                                       | Interpreter command name. It is necessary to set the environment variable PATH in advance. |

Note that **testfile** and **resultfile** will be removed after testing.

## Example

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
