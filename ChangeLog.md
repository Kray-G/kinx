# Change Log

## V1.0.0 (Future Planned)

*   Planned, or remaining tasks.
    *   Support Environment Variable.
    *   Support OpenCV library.
    *   Support PDF library with libHaru.
    *   Support HTTP Server library with libhttp.
    *   Support REPL (Read-Eval-Print Loop).
    *   User selectable installation.
    *   Documentation & SpecTest complete.
    *   Library mode like `libkinx.so`.
    *   The followings are planned but priority is low.
        *   Improvement with `KX_FASTENTER`.
            *   `KX_FASTENTER` is entering function without frame.
        *   Improvement with some specialized instructions.
            *   `KXOPT_LENGTH` ... for `Array`, `Binary`, `String`
            *   `KXOPT_PARSEINT` ... `Integer.parseInt`

## V0.8.0 (Current Development)

*   Updated
    *   Updated some of native code output.
    *   Supported a dot style of string literal like `.abc` means `"abc"`.
    *   Supported Process library.
    *   Supported `System.gtopt()`.
    *   Supported Escape Sequence with `\e`.
    *   Some bug fixes and improvement.

## V0.7.1 (7th Preview Release)

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
    *   Some bug fixes and improvement.

## V0.6.0 (6th Preview Release)

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
    *   Some bug fixes and improvement.

## V0.5.2 (5th Preview Release)

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
    *   Some bug fixes and improvement.

## V0.4.1 (4th Preview Release)

Updates from v0.3.1.

*   Updated
    *   Supported Enumerable module.
    *   Supported Range object and the syntax of `n..m` and `n...m`.
    *   Supported `for-in` statement.
    *   Updated a spread operator to use with any expressions.
    *   Supported some operators like `==` as a property name.
    *   Supported a spread operator with declaration statement.
    *   Some bug fixes.

## V0.3.1 (3rd Preview Release)

Updates from v0.2.0.

*   Updated
    *   Combining ternary expressions.
    *   Updated Fiber.
    *   Supported Signal.
    *   Some bug fixes.

## V0.2.0 (2nd Preview Release)

Updates from v0.1.0.

*   Updated
    *   Supported Standard I/O.
        *   `$stdin`, `$stdout`, `$stderr` has same methods as `File`.
        *   There are constant variables as `STDIN`, `STDOUT`, `STDERR` 
            corresponding to `$stdin`, `$stdout`, `$stderr`.
    *   Added or modified `File` instance methods.
        *   Supported `getch`, `putch`, `peek`.

## V0.1.0 (1st Preview Release)

*   Initial Release.
