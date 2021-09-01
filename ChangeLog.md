# Change Log

## V1.2.0 (Future Planned)

* Planned.
    *   Support Cryptography library.
    *   Support GUI library.
    *   Support OpenCV library.
    *   Support HTTP Server library.
    *   Enhancement Plan
        *   Package Maneger
            *   Dependency check between packages.
            *   Scan for the update.
            *   Search packages with pattern matching.

## V1.1.0 (Current Development Version)

*   New Features
    *   #232: Supported a Package Manager named as `Kip`.
        *   1st version with no dependency check and no update check.
    *   #275: Supported SAT solver by picosat.
*   Improvements/Enhancements
    *   #261: Separated binary modules in extlib to another repository & reduced a repository size.
    *   #255: Improved the `operator[]` in `Range`.
    *   #264: Supported to change directory.
    *   #265: Supported `$pwd` for getting a current directory.
    *   #272: Supported a binary mode in HTTP.
    *   #273: Supported `read`/`write` in `File`.
    *   #290: Supported `chmod` in `File`.
    *   #308: Improvement of the stack usage.
    *   #316: Changed a specification of a label to be with 2 colons.
    *   #332: Supported any radix on the `Integer.toString()` method.
    *   Small improvements and enhancements as follows without managing by issues.
        *   Supported SemanticVersion class with `using SemanticVersion;`.
        *   Supported putting a comma at the end of an argument's list for both declaration and calling.
        *   Added operators of `==` and `!=` in Boolean class.
        *   Supported `String#isIntegerString`.
        *   Shared an implementation of conversion for a string, an integer, and a double.
        *   Improved type analysis for the language server.
        *   SpecTest: Made a space wider of Test case number.
        *   Improved Array.keySet() for `Array` itself.
        *   Improved a type check a little in assignment.
*   Bug Fixed
    *   #235: Crash when using `_` outside a function.
    *   #236: Can't specify the class as a return type of function.
    *   #237: Comparing between variables having a string is failed.
    *   #256: Comparison operator will be failed with an integer on LHS and a variable(double) on RHS.
    *   #257: Fails a destructuring assignment when declaration with const.
    *   #258: There is a case that the bytecode is not outputted.
    *   #267: Can't use a variable name using an upper case in debugger.
    *   #269: Object item is removed by flatten().
    *   #274: No error for multiple `const` declaration for the same variable.
    *   #284: Fixed a segmentation fault problem on Linux.
    *   #288: Incorrect message is displayed when `File.open` failed.
    *   #289: `File.setFiledate` does not work correctly.
    *   #293: Fixed a problem of a stack overflow with `=~` or `!~`.
    *   #301: Fixed a prblem of using `ctx` after cleanup.
    *   #302: Fixed a prblem of the string optimization.
    *   #305: Fixed a prblem of no POPC in try.
    *   #314: Fixed a crash when accessing uninitialized object in native.
    *   #331: Fixed an incorrect handling of a big integer literal in lexer.

## V1.0.0 (Official Release) - 2021/03/16
This is 1st official release version.

* See [Kinx Specification](https://github.com/Kray-G/kinx/blob/master/docs/index.md) for a specification.

> Small updates from v0.22.0
> 
> *   Updated
>     *   Updated `Functional`.
>         *   See [Functional][] for details.
>     *   Supported String Color methods with Escape Sequence.
>         *   See [String](docs/spec/lib/primitive/string.md) for details.
>     *   Updated Documentation & SpecTest.
>     *   Some bug fixes and improvements.

## V0.22.0 (22th Preview Release) - 2021/03/05

*   Updated
    *   Supported a pipeline and a function compoition operator.
        See [a pipeline][pline], [a function composition][fcomp], and a library of [Functional][] for details.
        *   Supported a pipeline operator of `a |> b` which is just same as `b(a)`.
        *   Supported a pipeline operator of `a <| b` which is just same as `a(b)`.
        *   Supported a function composition operator of `a +> b` which is like `{ => b(a(_1)) }`.
        *   Supported a function composition operator of `a <+ b` which is like `{ => a(b(_1)) }`.
    *   Supported to read/write from/to Clipboard.
        *   By `var cb = new Clipboard();`, then you can:
            *   Use `cb.write(str)` to write `str` to clipboard, or
            *   Use `cb.read()` to read a text from clipboard.
    *   Documentation & SpecTest complete.
        *   The documents which was planned was prepared at least, although the quality should be increased.
    *   Some bug fixes and improvements.

[pline]: docs/spec/statement/expression/pipeline.md
[fcomp]: docs/spec/statement/expression/function_composition.md
[Functional]: docs/spec/lib/basic/functional.md

## V0.21.0 (21th Preview Release) - 2021/02/16

*   Updated
    *   Obsoleted a dot style of string literal like `.abc` which means `"abc"`.
        *   This is changed to another feature.
        *   Newly `.abc` is a function object which means `{ => _1.abc.isFunction ? _1.abc() : _1.abc }`.
        *   And also `.is***` like `.isFunction` to check a type is a function object which means `{ => _1.is*** }`.
        *   This feature will care for the purpose below.
            *   As a call back method for methods of Array such as `Array#map`, `Array#filter`, and so on.
            *   As a function object placed at a `when` clause in `case-when`.
    *   Updated `case-when` features.
        *   Supported `^` as a pin operator.
        *   Supported an lvalue of array with index at `when` condition.
        *   Supported `|` operator for multiple conditions called as alternative pattern at `when` condition.
        *   Supported putting a function object to check the result by function call at `when` condition.
        *   Changed to make it error when the length of array is mismatched.
        *   `_` means to ignore binding a value at `when` condition.
    *   Introduced a `when` label in `switch` statement.
        *   This can be used a substitute of a `case` label, and it will do `break` automatically by default.
        *   When specifying `fallthrough;` at the last statement of a `when` clause, it will be fallthrough.
        *   The label instead of `default:` is `else:` which will do `break` automatically at the end of statements.
        *   The `fallthrough` keyword in a `case` is meaningless and it will be ignored.
        *   You can mix a `case` label and a `when` label, but it is not recommended.
        *   `switch-when` is a statement and it is same as `switch-case` except a behavior of `break` and `fallthrough`.
    *   Updated some type system.
        *   For type check in a language server.
        *   Making a compile error when it is unknown type or type mismatch in assignment.
    *   I am very sorry but, after a reconsideration I desided to change a syntax for a return type of native again.
        Instead, It was possible to add a syntax that you can specify a return type also for a normal function.
        However note that a return type for a normal function is currently just an information to the language server.
        *   OLD
            *   `native:int`
        *   NEW/ADD
            *   `native funcname(args):int`
            *   `function funcname(args):int`
            *   `public funcname(args):int`
            *   `private funcname(args):int`
    *   Some bug fixes and improvements.

## V0.20.1 (20th Preview Release) - 2021/01/29

*   Updated
    *   Added the same directory as a current parsing file to a search path for `using`.
    *   Introduced `File#getUtf8Char()` to get directly UTF8 character from a File object including `$stdin`.
    *   Introduced newly `case-when` expression for trial.
        *   See [case-when](docs/spec/statement/expression/case_when.md) for details.
    *   Supported a different variable name from an object key in assignment, declaration, and function arguments.
        *   `var { x: a, y: b } = { x: 10, y: 100 }` means `a = 10, b = 100`.
    *   Supported a pattern matching syntax in assignment, declaration, and function arguments.
        *   `var { x: a, y: 100 } = { x: 10, y: m }` means `a = 10` if `m == 100`, otherwise an exception occurs.
    *   Supported an object key style also with an assignment.
        *   `{ x, y } = { x: 10, y: 100 }` means `x = 10, y = 100`.
    *   Relocation of build environment.
        *   Created a `build` directory and moved files needed at building to the `build` directory.
    *   Some bug fixes and improvements.

## V0.19.3 (19th Preview Release) - 2021/01/19

*   Updated
    *   Added some features to use a language server.
    *   Added a debugger mode for debugging.
        *   Please see the [debugger document](docs/utility/debugger.md) to know how to use it.
    *   Removed KiTyy files to reduce a repository size.
        *   KiTTy needs a lot of big files like a font.
        *   KiTTy was moved to https://github.com/Kray-G/kinx-tiny-typesetting.
    *   Updated Copyright.
    *   Some bug fixes and improvements.

## V0.18.0 (18th Preview Release) - 2020/12/28

*   Updated
    *   Introduced `$kinxpath` for Kinx installation path.
    *   Instead, `$exepath` means an actual executable's path.
    *   Added some features for a language server.
        *   Added some options for the source input from STDIN.
        *   Added displaying variable definition and reference location.
    *   Some bug fixes and improvements.

## V0.17.1 (17th-1 Preview Release) - 2020/12/17

*   Updated
    *   Windows Installer will automatically add the path to the Kinx executable
        to the `Path` environment variable after installation.
    *   Added the bucket for Scoop, and it is easy to install Kinx into Windows through the Scoop manager.
    *   Some bug fixes and improvements.

## V0.17.0 (17th Preview Release) - 2020/12/15

<img align="right" src="https://github.com/Kray-G/kinx/raw/master/docs/InstallerWelcome.png" width="360px">

*   Updated
    *   Support an installer for Linux, such as `kinx_0.17.0-0_amd64.deb`.
    *   Support an installer for Windows, such as `Kinx_installer_x64.0.17.0.exe`.
    *   Support `catch` without specifying an exception object.
        *   This is like `try { ... } catch { ... }`.
    *   Support a cast syntax in native with an `as` keyword.
        *   Use `as` after a variable such as `var x = 10 as big`, and cast it.
    *   Support Big Integer in native.
    *   Support Multidimensional Array in native.
    *   Changed a syntax for a return type of native. It becomes same as a syntax for an argument.
        *   [OLD] `native<int>`
        *   [NEW] `native:int`
    *   Some bug fixes and improvements.

## V0.16.1 (16th Preview Release) - 2020/12/08

*   Updated
    *   Support Array of Double in native.
    *   Updated some SpecTest pages.
    *   Some bug fixes and improvements.

## V0.15.3 (15th-3 Preview Release) - 2020/11/27

*   Updated
    *   Updated some SpecTest pages.
    *   Some bug fixes and improvements.

## V0.15.2 (15th-2 Preview Release) - 2020/10/14

* Updated
    * Some bug fixes for Typesetting Library.
    * Updated examples for Typesetting.
    * Added `kxkitty` and `kxkitty.exe` command.
    * Added KiTTy's User Guide generated by KiTTy.
        * User Guide in English ... ([PDF](https://github.com/Kray-G/kinx/raw/master/examples/typesetting/KiTTy_en.pdf))
        * User Guide in Japanese ... ([PDF](https://github.com/Kray-G/kinx/raw/master/examples/typesetting/KiTTy_jp.pdf))

### V0.15.1 (15th-1 Preview Release) - 2020/10/07

*   Updated
    *   Supported `Tiny Typesetting` library.
        *   Not documented yet, wait for the next release.
    *   Added duktape library to execute JavaScript internally.
    *   Added phantomjs for a typesetting library.
    *   Added a small Markdown Parser.
    *   Integrated `kc-json` to this project.
    *   Supported loading multiple libraries by `using`.
    *   Some bug fixes and improvements.

## V0.14.0 (14th Preview Release) - 2020/08/24

*   Updated
    *   Supported SSH & libssh2 library.
    *   Supported an iconv library.
    *   Supported `"\uXXXX"` and `"\u{CodePoint}"` as Unicode Code Point in a string literal.
    *   Supported a TCP/UDP socket library.
    *   Support PDF library with libHaru.
    *   Some bug fixes and improvements.

## V0.13.1 (13th Preview Release) - 2020/07/19

*   Updated
    *   Improved `String#split` to support UTF-8.
    *   Supported `Parsek#noneOf`.
    *   Added a script name into an argument list with `--exec` option.
    *   Supported a `$env` variable without a property to get all environment variables.
    *   Improved `String#each` to iterate a character according to UTF-8.
    *   Supported `String.escapeHtml`.
    *   Supported utf8 in `Parsek#oneOf`.
    *   Added a CLI support of kinx content.
    *   Some bug fixes and improvements.

## V0.12.0 (12th Preview Release) - 2020/07/10

*   Updated
    *   Supported a numbered parameter of a function argument.
        *   It is available from `_1` to `_9`, and `_1` is the first argument.
        *   `_` is also available and it is assigned the variable according to the order of appearance.
            *   `(&() => _ + _)` is same as `(&() => _1 + _2)`
    *   Supported a callback block syntax when a callback function is the last argument parameter.
        *   For example, `f(2, 10) { &(a, b) return a + b; }` means `f(2, 10, &(a, b) => { return a + b; })`.
        *   For another example, you can pass a block to `.map` like `[4, 5, 6].map { => _1 * 2 }`.
        *   See [this example](example/../examples/blockfunc.kx) to check the supported syntax.
    *   Supported the syntax to skip a parameter to ignore assignment like `[a,,c] = [1,2,3]`.
    *   Supported the syntax of array assignement with a function argument.
        *   A function argument example is `function func([a, b]) { /* ... */ }`.
    *   Supported the syntax to get the value of an object property like `var {xxx} = { xxx: 100 }`.
        *   In this case it assigns `100` to the variable of `xxx` which is same name as a property name.
        *   This syntax can be used only as a declaration or a function argument.
        *   A function argument example is `function func({ xxx, yyy }) { /* ... */ }`.
    *   Improved `.each` for Object. The callback will receive `[key, value]` pair as array.
        ```
        { x: 100, y: 200, z: 300 }.each { &([key, value])
            System.println([key, value]);
        };
        ```
    *   Some bug fixes and improvements.

## V0.11.0 (11th Preview Release) - 2020/07/03

*   Updated
    *   Supported a Parser Combinator Library named as `Parsek`.
    *   Some bug fixes and improvements.

## V0.10.0 (10th Preview Release) - 2020/06/26

*   Updated
    *   Changed disassembler for x64.
    *   In formatting like `"%-20s" % v` it is correctly worked with UTF8 string with correct width.
    *   Supported some of `Math` functions in native.
    *   Supported some of string operations in native.
    *   Supported some of binary operations in native.
    *   Supported some of array operations in native.
    *   Supported switch-case only with integer label in native.
    *   Kinx As A Library, see `examples/c/runkinx.c` for example.
    *   Supported underline by escape sequence.
    *   Supported `__FILE__`, `__LINE__`, `__FUNC__`.
    *   Supported Environment Variable via `$env` variable.
    *   Supported a JIT library for 64-bit integer and 64-bit floating point.
    *   Supported `libkinx.h` and a library file of `kx.lib` on Windows or `libkx.a` on Linux.
    *   Supported the option of `--version` to show the detail of the version.
    *   Supported the option of `-c` for compiling only to check the syntax.
    *   Supported the option of `-q` for quiet mode.
    *   Some bug fixes and improvements.

## V0.9.2 (9th Preview Release) - 2020/06/03

*   Updated
    *   Supported a long option by `System.getopt()`.
    *   Supported UTF8 utilities.
        *   `String.utf8Length()` to get a length of a utf8 string.
        *   `String.splitUtf8String()` to split a string as an array of a utf8 string.
        *   `String.splitUtf8Object()` to split a string as an array of a utf8 information object.
        *   `String.eastAsianWidth()` to get a width of a utf8 character.
        *   `String.eastAsianWidthType()` to get a type character of width of a utf8 character.
    *   Supported REPL (Read-Eval-Print Loop) with updated below.
        *   Auto-complete by `[TAB]` key.
        *   Moving by word with Ctrl + arrow left/right.
    *   Some bug fixes and improvements.

## V0.8.1 (8th Preview Release) - 2020/05/26

*   Updated
    *   Updated some of native code output.
    *   ~~Supported a dot style of string literal like `.abc` which means `"abc"`~~.
        *   Obsoleted this feature at 0.21.0.
    *   Supported Process library.
    *   Supported `System.getopt()`.
    *   Supported Escape Sequence with `\e`, `\033`, or `\x1b` even with Windows.
    *   Supported a part of REPL (Read-Eval-Print Loop), but it is not a full version.
    *   Some bug fixes and improvements.

## V0.7.1 (7th Preview Release) - 2020/05/15

*   Updated
    *   Bug fixes for operator override.
        *   `<<`, `>>` ... Making it parse correctly.
    *   Added `toString()` method to the class Boolean.
    *   Some runtime optimaizations for function call.
    *   Replaced Bison of a parser generator by Kmyacc.
    *   Supported a DateTime class.
    *   Supported a CSV/TSV class.
    *   Supported some optimizations.
    *   Supported `System.gc()` to perform GC forcely.
    *   Supported a Database class for easier to use than a SQLite class.
    *   Some bug fixes and improvements.

## V0.6.0 (6th Preview Release) - 2020/05/01

Updates from v0.5.2.

*   Updated
    *   Fixed a bug of `String#next`.
    *   Supported Net.Http class.
    *   Supported the operator '~' for bitwise not.
    *   Supported operator override for class instance as below.
        *   `==`, `!=`, `>`, `>=`, `<`, `<=`, `<=>`, `<<`, `>>`, `+`, `-`, `*`, `/`, `%`, `[]`, `()`.
    *   Supported multi-threading as `Isolate` with `Mutex` and `Condition`.
    *   Supported `Enumerable#sum` & `Range#sum`.
    *   Fixed to parse a big integer from hex.
    *   Function Object is always evaluated as `false`. Only `.isFunction` property returns `true`.
    *   Append alias methods for Array/Enumerable below.
        *   `Array#collect` for `Array#map`.
        *   `Array#collectConcat` for `Array#flatMap`.
        *   `Array#inject` for `Array#reduce`.
        *   `Array#select`, `Array#findAll` for `Array#filter`.
    *   Some bug fixes and improvements.

## V0.5.2 (5th Preview Release) - 2020/04/20

Updates from v0.4.1.

*   Updated
    *   Updated OpenSSL library path.
    *   Changed a function name to be treated as a constant.
    *   Supported some binary special methods.
    *   Applying a `toString` method automatically when applying an object to
        `System.print/println`, `Array#join`, and `Array#toString`.
    *   Supported a spread operator for String like `<..."abc">` or `[..."abc"]`.
    *   Supported the option of `binary` with true/false for `Zip#extract`.
    *   Supported applying a Range object to the index for String, Binary, and Array.
    *   Some bug fixes and improvements.

## V0.4.1 (4th Preview Release) - 2020/04/13

Updates from v0.3.1.

*   Updated
    *   Supported Enumerable module.
    *   Supported Range object and the syntax of `n..m` and `n...m`.
    *   Supported `for-in` statement.
    *   Updated a spread operator to use with any expressions.
    *   Supported some operators like `==` as a property name.
    *   Supported a spread operator with declaration statement.
    *   Some bug fixes.

## V0.3.1 (3rd Preview Release) - 2020/04/03

Updates from v0.2.0.

*   Updated
    *   Combining ternary expressions.
    *   Updated Fiber.
    *   Supported Signal.
    *   Some bug fixes.

## V0.2.0 (2nd Preview Release) - 2020/03/19

Updates from v0.1.0.

*   Updated
    *   Supported Standard I/O.
        *   `$stdin`, `$stdout`, `$stderr` has same methods as `File`.
        *   There are constant variables as `STDIN`, `STDOUT`, `STDERR` 
            corresponding to `$stdin`, `$stdout`, `$stderr`.
    *   Added or modified `File` instance methods.
        *   Supported `getch`, `putch`, `peek`.

## V0.1.0 (1st Preview Release) - 2020/03/18

This is a first preview release.

* For Windows, extract `package_win64.zip` and put it where you want.
    * Setup the PATH for executable.
* For Linux, extract a source file and do `make` and `sudo make install`.
    * The executable named as `kinx` is installed to `/usr/bin`.
    * Some libraries are installed under `/usr/bin/kinxlib`
    * Setup the PATH for executable if you need.
    * If you want to uninstall, remove above files by hand.

### Please try `hello, world.`

You can write the program on the top level of source. Prepare the following file named as `hello.kx`.

```javascript:hello.kx
System.println("hello, world.");
```

Execute it as follows, and you will do it well if the PATH is correctly set.

```
$ kinx hello.kx
hello, world.
```
