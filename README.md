# Script Kinx [![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)

Small scripting language with C like style syntax.

## Introduction

The script language is a platform as a glue between libraries.
This means a language itself is not a main purpose,
it should be just a backend or supporter due to use a library you want to use.

The design goal for this language is to be extendable, lightweight,
and easy to use for user's own purpose.
Kinx can be the best platform for any libraries which you want to use or your own library.

### Motivation

I guess almost all programmers want a lightweight scripting language with C style syntax
because it is simple, easy, and familier to them.

Any other languages are also all good solution, but for me...

*   Python is greate. But it is too far from C style. Indentend style is a little cramped.
*   Ruby is also greate. But it is too far from C style. Too many typing for `end`.
*   JavaScript is very good for me, and it is a C like style. But node.js is too heavyweight.

#### What is C Style Syntax?

Sharing the definition of **C Style Syntax**, it is below.

*   **Block** is a scope between `{` and `}`
*   Mostly **freedom** style of indent.
*   **Fall through** in switch case.
*   etc.

For example that is C, C++, Java, JavaScript, C#, and so on.
If you agree, push the star.

## Features

* **Extendable**. Contributers are able to extend features easily for your own use.
* **Lightweight**. You can start using this without a lot of work.
* **Small**. Using C instead of C++. I love C++ but runtime is big in some cases.
* **Object-Oriented**. Of cource you can do the object-oriented programming.
* C style syntax... no it is **JavaScript style syntax** rather than C, but it is also good.
* **Native function** by AOT/JIT compiling supported with some limitations.

## Getting Started

### How to Build

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

## Examples

You will think it is like JavaScript.

### Fibonacci

```js
function fib(n) {
    if (n < 3) return n;
    return fib(n-2) + fib(n-1);
}

System.println("fib(34) = ", fib(34));
```

### Factorial

```js
function fact(n) {
    if (n < 1) return 1;
    return n * fact(n-1);
}

System.println(fact(5000));
```

### Class

```coffee
class Example(i) {
    public get() { return i; }
}

System.println(new Example(100).get());
```

### Native

#### What is Native function?

Remember the fibonacci function above.
That is a simple fibonacci function and execute it with time measurement like below.

```
$ time ./kinx examples/fib.kx
fib(34) = 9227465

real    0m0.578s
user    0m0.516s
sys     0m0.016s
```

Replace `function` to `native`.
That's all.

```js
native fib(n) {
    if (n < 3) return n;
    return fib(n-2) + fib(n-1);
}

System.println("fib(34) = ", fib(34));
```

Let's execute it and measure it!

```
$ time ./kinx examples/native_fib.kx
fib(34) = 9227465

real    0m0.092s
user    0m0.031s
sys     0m0.000s
```

How nice it is 10x or more faster.

But you have to know the limitations below with native function.
I am now considering how to remove those.

*   Currently you can use the type of integer only.
*   Integer value is not automatically promoted to big integer, just overfow it.
*   Can not call a script function. Only can call a native function.
*   Forward declaration of a native function is not supported.
*   Can access to the lexical scope and variables, but only for an integer value.
*   Exceptions with `try-catch-finally` is supported, but a stack trace is not available.
*   Support 64bit only. Libraries are supporting x64, ARM, MIPS, but sorry I can not test it except x64 Windows or Linux.

### Extending Functionalities

You can add the functionalities easily.
Basic strategy is to add the dll following by some rules.

First, you use `import` directive like this.

```js
import YourLibrary;
```

This is same as follows.

```js
var YourLibrary = _import("kxyourlibrary");
using? kxyourlibrary;
```

The import library name is `kx` plus your specified name with lower-case.
For example in the above case, the name will be `"kxyourlibrary"`.
`import` directive will do the followings.

*   Loading the dll of `kxyourlibrary.dll` dynamically and making an object with a dll rule.
    *   The dll is searched by the following order.
        *   The same directory as executable of `kinx`.
        *   Following the system search path.
*   About a dll rule is like below.
    *   See [`kxstring.c`](src/extlib/kxstring.c) for single object. It will be very simple example.
    *   See [`kxregex.c`](src/extlib/kxregex.c) for class definition. Just defines a `create` method for `new` operator.
*   Assigning the object to the variable of the name you specified.
    For example, the variable name is `YourLibrary` in the above case.
*   After that, if there is `kxyourlibrary.kx` is found in the library path, automatically loading it.
    *   The library is searched by the order which is same as `using`.

For `new` operator, `new A` is just alias of `A.create`.
See [Class Design](doc/ClassDesign.md) for how class works.

## Support Objects

Currently many functionalities are too lack, I would like to add objects and methods as soon as possible.
Many functionalities added in the future will be created by above strategy.

For current supported objects, see [here](doc/Object.md).

## TODO

Now development is very early stage, I need to add many functionalities.
Here is a plan to add.

* [ ] Adding many methods to `String` and `Array`.
* [ ] `switch-case` statement.
* [ ] `namespace` block.
* [ ] `module` to add function easily to object.
* [ ] `File` object to support standard File I/O.
* [ ] `XmlDom` object to support Xml.
* [ ] `Network` object to support Network protocal access.
* [ ] `SQLite` object to support SQLite database access.
* [ ] Regular expression literal like `/pattern/`, and operations of `=~` & `!~`.
* [ ] `const` for constant value.
* [ ] Some Optimizations.

## Undocumented Memo

Now there is no document about following items, but I will write it as soon as possible.

### Command Line Arguments

The variable named `$$` is an array of command line arguments.
Here is an example.

```coffee
for (var i = 0, len = $$.length(); i < len; ++i) {
    System.println("arg[%{i}] = ", $$[i]);
}
```

### Inner Expression

Here is the sample of **inner expression**.

```coffee
var a = 100;
var str = "You can put expression like %{a * (a + 2)} as inner expression in the string.";
System.println(str);
```

The result is here.

```
You can put expression like 10200 as inner expression in the string.
```

### Type Property

You can use the type property to check the object type.
See example of [`idprop.kx`](examples/idprop.kx) for that.

### eval

`eval()` is now supported.
You can run the code of string on the fly.
The eval's arguments are assigned to `$$` like command line arguments as an array.

### using directive

You can use `using` to include another source file.

```coffee
using dir.to.path.file1;
using? dir.to.path.file2;
```

When you use `using` and the file is not found, it will make it error.
When you use `using?` instead, it will be ignored without errors even if the file is not found.

The library is searched by the following order.

*   Current directory.
*   The same directory as executable of `kinx`.
*   The child `lib` directory of a directory of `kinx` executable.
*   The child `lib` directory of a parent directory of `kinx` executable.

### Alternative Function Call Value

When you call `someMethod` but `methodMissing` occurs for an object,
searching a `_someMethod` property and use the value of it if found.
It is sometimes reasonable because you do not have to define the function.

```coffee
var obj = { _msg: "message" };
System.println(obj.msg()); # => print out "message".
```

### String literal like Here Document

String literal like Here document is supported like below.

```coffee
var a = 100;
var b = 10;
var str = %{
This is a string without escaping control characters.
New line is available in this area.
};
System.println(str);
var str = %-{
This is a string without escaping control characters.
New line is available in this area.
But newlines at the beginning and the end are removed when starting with '%-'.
};
System.println(str);
```

Use `%-` instead of `%` at start point and youn can remove newlines if you need,
because there are newlines at the beginning and the end.

You can use the following character for here document instead of `{` and `}`.
Escaping by `\` is available only for the start or the end character.

| Start |  End  |
| :---: | :---: |
|  `(`  |  `)`  |
|  `[`  |  `]`  |
|  `<`  |  `>`  |

You can also use the followings for this purpose.
These are different from above that the start and the end character is the same.
For example, it is like `%| ... |`.
Anyway the first character is always `%`.

*   `|`, `!`, `^`, `~`, `_`, `.`, `,`, `+`, `*`, `@`, `&`, `$`, `:`, `;`, `?`, `'`, `"`.

## License

This project is licensed under the **MIT License**.
See the [LICENSE](LICENSE) file for details.
About the licenses of internal used libraries, follow the licenses of each library.
See [doc/licenses](doc/licenses) folder for details.
