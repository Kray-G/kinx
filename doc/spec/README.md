
# Kinx Specification

## As A Sample Of SpecTest

### Overview

This is Kinx specification, and examples are test code as is.
This is right just a specification document, but this is also test codes at the same time.
I named this system as **SpecTest**, and this documentation is also provided as an example of the **SpecTest**.
Writing a specification means writing a test, and examples are becoming test codes as is.

As for the detail of **SpecTest**, that will be described in the link below,
but **SpecTest** is designed to not only for Kinx but also for any other systems.
This means you can also use **SpecTest** for your product developed not by Kinx.

*   See **[SpecTest](spectest/README.md)** for detail.

As an example of **SpecTest**, I prepared another [here](../benchmark/README.md).

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

*   [arguments](command/arguments.md)

### Statement

Statement is almost near the C or JavaScript syntax.
There are some of special statements that `yield` for Fiber, `mixin` for Module, and so on.

#### Basic Statement

Declaration statement and expression statement is a basic statement of Kinx.
Some of expression rules will be described in `expression` section.
`mixin` is a special declaration to include `Module` component.
This statement will be described also in `Module` section again.

*   [declaration](statement/declaration.md)
*   [enum](statement/enum.md)
*   [expression](statement/expression.md)
*   [mixin](statement/mixin.md)
*   [using](statement/using.md)

By the way, declaration of a Function or a Class, etc,
is described not in this section but in **Definitions** section.

#### Flow Control

Flow control is a branch, a loop, returning from a function, throwing a exception, etc.
But as for function call is described in `expression` because it is a part of expression.
Note that a flow is not changed by `block`, but `block` is included in this section.

##### Block

*   [block](statement/block.md)
*   [namespace](statement/namespace.md)

##### Branch

*   [if-else](statement/if_else.md)
*   [switch-case](statement/switch_case.md)
*   [try-catch-finally](statement/try_catch_finally.md)

##### Loop

*   [while](statement/while.md)
*   [do-while](statement/do_while.md)
*   [for](statement/for.md)
*   [for-in](statement/for_in.md)

##### Jump

*   [return](statement/return.md)
*   [yield](statement/yield.md)
*   [throw](statement/throw.md)

### Definitions

Definitions are structured as a Function definition, a Class definition, and a Module definition.
As a special object derived from Function, there are Lambda, Closure, and Fiber.

#### Object Definitions

*   [Function](definition/function.md)
*   [Class](definition/class.md)
*   [Module](definition/module.md)
*   [Native](definition/native.md)

#### Special Objects

*   [Lambda](definition/lambda.md)
*   [Closure](definition/closure.md)
*   [Fiber](definition/fiber.md)

### Type Check

The following properties are used to check the type of a variable.

*   [isUndefined](typecheck/is_undefined.md)
*   [isDefined](typecheck/is_defined.md)
*   [isInteger](typecheck/is_integer.md)
*   [isDouble](typecheck/is_double.md)
*   [isString](typecheck/is_string.md)
*   [isArray](typecheck/is_array.md)
*   [isObject](typecheck/is_object.md)
*   [isFunction](typecheck/is_function.md)

### Others

Some special specifications.

*   [String#next](others/string_next.md)

### Library

Kinx has many useful libraries and you can use those once you install this product.
Kinx goal is to become a glue between libraries, and Kinx will include many of useful libraries also in future.

#### Primitives

This is not a library but basic methods for a primitive data type,
but the description is included in this section because its feature is near a library.

*   [Integer](lib/primitive/integer.md)
*   [Double](lib/primitive/double.md)
*   [String](lib/primitive/string.md)
*   [Binary](lib/primitive/binary.md)
*   [Array](lib/primitive/array.md)

#### Functions

*   [eval()](lib/function/eval.md)
*   [DefineException()](lib/function/define_exception.md)

#### Standard Objects

Here are provided objects as a Kinx Standard.

##### Basic Objects

Basic objects are the list of components usually used in many products.
The functionality is very simple but powerful, so a lot of developpers will use those naturally.

*   [System](lib/basic/system.md)
*   [Math](lib/primitive/math.md)
*   [File](lib/basic/file.md)
*   [Directory](lib/basic/directory.md)
*   [Regex](lib/basic/regex.md)
*   [Range](lib/basic/range.md)
*   [DateTime](lib/basic/datetime.md)
*   [Process](lib/basic/process.md)
*   [JSON](lib/basic/json.md)
*   [Xml](lib/basic/xml.md)
*   [Zip](lib/basic/zip.md)
*   [SQLite](lib/basic/sqlite.md)

##### Network Objects

Network library is now very few, but it will be increased in future
because now the networking library is needed by many developpers.

*   [Http](lib/net/http.md)

I provide Http library only, but it is based on libcurl.
Therefore adding a library based on the same technology must be easy.
I strongly want **contributers**. How about you?

##### Exception Objects

*   [SystemException](lib/exception/system.md)
*   [FileException](lib/exception/file.md)
*   [RegexException](lib/exception/regex.md)
*   [XmlException](lib/exception/xml.md)
*   [RuntimeException](lib/exception/runtime.md)

#### Algorithm and Data Structure

Algorithm and Data structure examples are being described in the page below.

*   [Algorithm](algorithm/README.md)
