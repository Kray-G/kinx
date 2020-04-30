# Change Log

## V1.0.0 (Future Planned)

*   Documentation complete.
*   REPL (Read-Eval-Print Loop).
*   Library mode like `libkinx.so`.
*   Some Optimaizations.
*   User selectable installation.

## V0.6.0 (Current Development)

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

*   Planned, or remaining tasks.
    *   Append alias methods like `Array#collect` for `Array#map`.
    *   Support DateTime class.
    *   Replace Bison by Kmyacc.
    *   Support REPL.
    *   Use a register as a stack pointer.
    *   Support kinx as a library.

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
