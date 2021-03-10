
# Kinx Specification

## As A Sample Of SpecTest

### Overview

This is Kinx specification, and examples are test code as is.
This is right just a specification document, but this is also test codes at the same time.
I named this system as **SpecTest**, and this documentation is also provided as an example of the **SpecTest**.
Writing a specification means writing a test, and examples will become test codes as is.

As for the detail of **SpecTest**, that will be described in the link below,
but **SpecTest** is designed to not only for Kinx but also for any other systems.
This means you can also use **SpecTest** for your product developed not by Kinx.

*   See **[SpecTest](spec/spectest/README.md)** for detail.

As an example of **SpecTest**, I prepared another [here](spec/../benchmark/README.md).

### How to Run

Execute the command below under `kinx` repository's root to run the **SpecTest** of Kinx,
and **SpecTest** will automatically load a `.spectest` file and run the tests.

```
$ ./kinx --exec:spectest -v
```

## Contents

> Note that writing specifications is incomplete. Some links are still under construction.

Actual specification is described from here.
I divided the section for the description of SpecTest, but actually it do not have to be separated.
SpecTest will recognize the test code by the rule of `.spectest` file regardless of the structure of document.

### Command Line

Here is a command line specification.

*   [arguments](spec/command/arguments.md)

### Statement

Statement is almost near the C or JavaScript syntax.
There are some of special statements that `yield` for Fiber, `mixin` for Module, and so on.

#### Basic Statement

Declaration statement and expression statement is a basic statement of Kinx.
Some of expression rules will be described in `expression` section.
`mixin` is a special declaration to include `Module` component.
This statement will be described also in `Module` section again.

*   [declaration](spec/statement/declaration.md)
*   [enum](spec/statement/enum.md)
*   [expression](spec/statement/expression.md)
*   [mixin](spec/statement/mixin.md)
*   [using](spec/statement/using.md)

By the way, declaration of a Function or a Class, etc,
is described not in this section but in **Definitions** section.

#### Flow Control

Flow control is a branch, a loop, returning from a function, throwing a exception, etc.
But as for function call is described in `expression` because it is a part of expression.
Note that a flow is not changed by `block`, but `block` is included in this section.

##### Block

*   [block](spec/statement/block.md)
*   [namespace](spec/statement/namespace.md)

##### Branch

*   [if-else](spec/statement/if_else.md)
*   [switch-case](spec/statement/switch_case.md)
*   [switch-when](spec/statement/switch_when.md)
*   [try-catch-finally](spec/statement/try_catch_finally.md)

Kinx has supported a `case-when` syntax is an expression but also branch, see [expression](spec/statement/expression.md) for details.

##### Loop

*   [while](spec/statement/while.md)
*   [do-while](spec/statement/do_while.md)
*   [for](spec/statement/for.md)
*   [for-in](spec/statement/for_in.md)

##### Jump

*   [return](spec/statement/return.md)
*   [yield](spec/statement/yield.md)
*   [throw](spec/statement/throw.md)

### Definitions

Definitions are structured as a Function definition, a Class definition, and a Module definition.
As a special object derived from Function, there are Lambda, Closure, and Fiber.

#### Object Definitions

*   [Function](spec/definition/function.md)
*   [Class](spec/definition/class.md)
*   [Module](spec/definition/module.md)
*   [Native](spec/definition/native.md)

#### Special Objects

*   [Lambda](spec/definition/lambda.md)
*   [Closure](spec/definition/closure.md)
*   [Fiber](spec/definition/fiber.md)

### Type Check

The following properties are used to check the type of a variable.

*   [TypeCheck](spec/statement/expression/typecheck.md)

### Library

Kinx has many useful libraries and you can use those once you install this product.
Kinx goal is to become a glue between libraries, and Kinx will include many of useful libraries also in future.

#### Primitives

This is not a library but basic methods for a primitive data type,
but the description is included in this section because its feature is near a library.

*   [Integer](spec/lib/primitive/integer.md)
*   [Double](spec/lib/primitive/double.md)
*   [String](spec/lib/primitive/string.md)
*   [Binary](spec/lib/primitive/binary.md)
*   [Array](spec/lib/primitive/array.md)

#### Functions

*   [eval()](spec/lib/function/eval.md)
*   [DefineException()](spec/lib/function/define_exception.md)

#### Standard Objects

Here are provided objects as a Kinx Standard.

##### Basic Objects

Basic objects are the list of components usually used in many products.
The functionality is very simple but powerful, so a lot of developpers will use those naturally.

*   [System](spec/lib/basic/system.md)
*   [Getopt](spec/lib/basic/getopt.md)
*   [Iconv](spec/lib/basic/iconv.md)
*   [Math](spec/lib/basic/imath.md)
*   [File](spec/lib/basic/file.md)
*   [Directory](spec/lib/basic/directory.md)
*   [Regex](spec/lib/basic/regex.md)
*   [Enumerable](spec/lib/basic/enumerable.md)
*   [Functional](spec/lib/basic/functional.md)
*   [Range](spec/lib/basic/range.md)
*   [DateTime](spec/lib/basic/datetime.md)
*   [Process](spec/lib/basic/process.md)
*   [JSON](spec/lib/basic/json.md)
*   [CSV/TSV](spec/lib/basic/csv_tsv.md)
*   [Xml](spec/lib/basic/xml.md)
*   [Zip](spec/lib/basic/zip.md)
*   [SQLite](spec/lib/basic/sqlite.md)
*   [JIT](spec/lib/basic/jit.md)
*   [Parsek](spec/lib/basic/parsek.md)

##### Network Objects

Network library is now very few, but it will be increased in future
because now the networking library is needed by many developpers.

*   [Http](spec/lib/net/http.md)
*   [SSH](spec/lib/net/ssh.md)

I provide Http library only, but it is based on libcurl.
Therefore adding a library based on the same technology must be easy.
I strongly want **contributers**. How about you?

Note that the above documents do not have any test code because it is hard to test of networking.

##### Exception Objects

*   [Exception](spec/lib/primitive/exception.md)

#### Algorithm and Data Structure

Algorithm and Data structure examples are being described in the page below.

*   [Algorithm](spec/algorithm/README.md)

### Others

Some special specifications.

*   [String#next](spec/others/string_next.md)

### Bug Fixes

*   [Bug Fixes](spec/others/bugfixes.md)
