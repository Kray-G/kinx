# Script Kinx [![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)

Small scripting language with C like style syntax.

## Overview

### Motivation

#### Motivation 1

The script language is a platform as a glue between libraries.
This means a language itself is not a main purpose,
it should be just a backend or supporter due to use a library you want to use.

Kinx can be the best platform for any libraries which you want to use or your own library.

#### Motivation 2

I guess almost all programmers wants a lightweight scripting language with C style syntax
because it is simple, easy, and familier to them.

Any other languages are also all good solution, but for me...

*   Python is greate. But it is too far from C style. Indentend style is a little cramped.
*   Ruby is also greate. But is is too far from C style. Too many typing for `end`.
*   JavaScript is very good for me, and it is a C like style. But nodejs is too heavyweight.

##### What is C Style Syntax?

Sharing the definition of **C Style Syntax**, it is below.

*   **Block** is a scope between `{` and `}`
*   Mostly **freedom** style of indent.
*   **Fall through** in switch case.
*   etc.

For example that is C, C++, Java, JavaScript, C#, and so on.

### Features

* Extendable. Contributers are able to extend features easily for your own use.
* Lightweight. You can start using this without a lot of work.
* Small. Using C instead of C++. I love C++ but runtime is big in some cases.
* Object-Oriented. Of cource you can do the object-oriented programming.
* C style syntax... no it is JavaScript style syntax rather than C, but it is also good.

## Getting Started

### Building This Program

#### Windows

On Windows, tested with Visual Studio 2017 Express Edition with x64.
To build, see below.

```
$ make.cmd
```

#### Linux

On Linux, tested with gcc 7.4.0 with x64.
To build, see below.

```
$ make
```

### How to Execute

#### Usage

```
$ kinx.exe [options] [<script-file>]
```

#### Options

Here is current available options.

| Option |          Description          |
| ------ | ----------------------------- |
| `-h`   | Display help.                 |
| `-v`   | Display version number.       |
| `-d`   | Dump compiled code.           |
| `-i`   | Input source code from stdin. |

#### Examples

You will think it is like JavaScript.

##### Fibonacci

```js
function fib(n) {
    if (n < 3) return n;
    return fib(n-2) + fib(n-1);
}

System.println("fib(34) = ", fib(34));
```

##### Factorial

```js
function fact(n) {
    if (n < 1) return 1;
    return n * fact(n-1);
}

System.println(fact(5000));
```

##### Class

```coffee
class Example(i) {
    public get() { return i; }
}

System.println(new Example(100).get());
```

### Extending Functionalities

You can add the functionalities easily.
Basic strategy is to add the dll following by some rules.

First, you use `import` directive like this.

```js
import YourLibrary;
```

The import library name is `kx` plus your specified name with lower-case.
For example in the above case, the name will be `"kxyourlibrary"`.
`import` directive will do the followings.

*   Loading the dll of `kxyourlibrary.dll` dynamically and making an object with a dll rule.
*   About a dll rule is like below.
    *   See [`kxstring.c`](src/extlib/kxstring.c) for single object. It will be very simple example.
    *   See [`kxregex.c`](src/extlib/kxregex.c) for class definition. Just defines a `create` method for `new` operator.
*   Assigning the object to the variable of the name you specified.
    For example, the variable name is `YourLibrary` in the above case.

For `new` operator, `new A` is just alias of `A.create`.
See [Class Design](doc/ClassDesign.md) for how class works.

### Support Objects

Currently many functionalities are too lack, I would like to add objects and methods as soon as possible.
Many functionalities added in the future will be created by above strategy.

|  Object  |           Method           |                                                    Work                                                    |
| -------- | -------------------------- | ---------------------------------------------------------------------------------------------------------- |
| `System` | `System.print(arg, ...)`   | Printing to stdout without newline at the end.                                                             |
|          | `System.println(arg, ...)` | Printing to stdout with newline at the end.                                                                |
|          | `System.abort()`           | Aborting the program.                                                                                      |
|          | `System.exec(cmdline)`     | Executing the command with shell.                                                                          |
|          |                            |                                                                                                            |
| `String` | `String.length(str)`       | Counting the length of string.                                                                             |
|          |                            |                                                                                                            |
| `Array`  | `Array.length(obj)`        | Counting the length of array object.                                                                       |
|          |                            |                                                                                                            |
| `Regex`  | `re = new Regex(pattern)`  | Creating Regex object. (`re` is example)                                                                   |
|          | `re.reset(str)`            | Reset the search target string.                                                                            |
|          | `re.find()`                | `true` if found. This can be used continuously until it has been not found.                                |
|          | `re.matches()`             | `true` if matches. This can be used only one time because this is checking if the target is fully matched. |
|          |                            |                                                                                                            |

`String` & `Array` objects will do the special work for the object.
For example  `String.length(str)` is the same as `str.length()`.
`Array` object is also same work like `Array.length(ary)` is the same as `ary.length()`.

### TODO

Now development is very early stage, I need to add many functionalities.
Here is a plan to add.

* [ ] Adding many methods to `String` and `Array`.
* [ ] Binary data access.
* [ ] `switch-case` statement.
* [ ] `using` directive to include another source code.
* [ ] `namespace` block.
* [ ] `class` mechanism fully support.
  * [ ] `instanceOf()`
  * [ ] `initialize()`
* [ ] `module` to add function easily to object.
* [ ] `Math` object to support some calculations.
* [ ] `File` object to support standard File I/O.
* [ ] `XmlDom` object to support Xml.
* [ ] `Network` object to support Network protocal access.
* [ ] `SQLite` object to support SQLite database access.
* [ ] Inner expression of string like `"...%{expr}..."`.
* [ ] Inner regular expression like `/pattern/`, and operations of `=~` & `!~`.
* [ ] `eval` to run the script on the fly.
* [ ] Here document.
* [ ] Object identifier property.
