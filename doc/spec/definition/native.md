# Native

## Overview

Keyword `native` is a style of function definition used when you want to compile it to the native machine code.
You can just write a `native` instead of `function` keyword for that.

```javascript
native fib(n) {
    if (n < 3) return n;
    return fib(n-2) + fib(n-1);
}
```

### Supports and Limitations

It is very fast but there are some limitations.

*   All variables are defined as a type. Available type is `int`, `dbl`, `str`, `bin`, `obj`, `ary`, or `native`.
    *   If type information is omitted, the type would be followings.
        *   On argument, it become automatically `int`.
        *   Without initializer on declaration, it become automatically `int`.
        *   With initializer on declaration, it is decided by the result of right hand side.
            *   When it can not be decided, a compile error will occur.
    *   For `int`
        *   Integer value is **NOT** automatically promoted to a big integer, it will just overflow instead.
        *   Math functions like `Math.pow(2, 10)` or `2.pow(10)` are supported.
    *   For `dbl`
        *   Math functions like `Math.pow(2.0, 10.0)` or `2.0.pow(10.0)` are supported.
    *   For `str`
        *   `str` is only supported for adding 2 strings and multiplying string by integer.
    *   For `bin`
        *   It is supported as an array of byte.
    *   For `int[]` and `dbl[]`
        *   It is currently just supported as an array of integer or double.
    *   For `native`.
        *   `native` function's return type is shown like `native<int>`.
        *   Even in this case, you can omit `<int>` like just `native` and automatically make it `int`.
*   For function call.
    *   Can not call a script function. Only can call a native function.
*   For statement and expression.
    *   Exceptions with `try-catch-finally` is supported, but a stack trace is not available.
    *   Switch-Case is supported, but the case label should be an integer value or expression.
    *   The lexical scope and variables are available, but the type must be clarified.
        *   If you omit the type, it will assume the integer.
        *   If the type is mismatched, runtime exception will occur.
*   Supported platform.
    *   Supporting 64bit only.
    *   Libraries are supporting x64, ARM, MIPS, but it is not tested except x64 Windows or Linux.

### Math Functions

Especially, see below for examples of `Math` functions.

* [Math functions](native/math.md)

### Supported Switch-Case

Switch-Case is now supported in native function.
But the case label should be an integer type.
See below for examples of Switch-Case in native.

* [Switch-Case in Native](native/switch_case.md)

## Examples

### Example 1. Fibonacci

#### Code

```javascript
native fib(n) {
    if (n < 3) return n;
    return fib(n-2) + fib(n-1);
}
System.println(fib(34));  // => 9227465
```

#### Result

```
9227465
```

### Example 2. Factorial

#### Code

```javascript
native fact(a) {
    if (a < 1) return 1;
    return a * fact(a-1);
}
for (var i = 0; i <= 20; ++i) {
    System.println("fact(%{i}) = ", fact(i));
}
```

#### Result

```
fact(0) = 1
fact(1) = 1
fact(2) = 2
fact(3) = 6
fact(4) = 24
fact(5) = 120
fact(6) = 720
fact(7) = 5040
fact(8) = 40320
fact(9) = 362880
fact(10) = 3628800
fact(11) = 39916800
fact(12) = 479001600
fact(13) = 6227020800
fact(14) = 87178291200
fact(15) = 1307674368000
fact(16) = 20922789888000
fact(17) = 355687428096000
fact(18) = 6402373705728000
fact(19) = 121645100408832000
fact(20) = 2432902008176640000
```

### Example 3. While Loop

#### Code

```javascript
var n = 10000;
native loop_while(n) {
    var v = 0, i = 0;
    while (i <= n) {
        v += i++;
    }
    return v;
}
System.println("while(%{n}) = ", loop_while(n));
```

#### Result

```
while(10000) = 50005000
```

### Example 4. For Loop

#### Code

```javascript
var n = 10000;
native loop_for(n) {
    var v = 0;
    for (var i = 0; i <= n; ++i) {
        v += i;
    }
    return v;
}
System.println("for(%{n}) = ", loop_for(n));
```

#### Result

```
for(10000) = 50005000
```

### Example 5. Do-While Loop

#### Code

```javascript
var n = 10000;
native loop_do_while(n) {
    var v = 0, i = 0;
    do {
        v += i++;
    } while (i <= n);
    return v;
}
System.println("do_while(%{n}) = ", loop_do_while(n));
```

#### Result

```
do_while(10000) = 50005000
```

### Example 6. Evaluation with double

#### Code

```javascript
var b = 1.7;
native<dbl> test(a:dbl) {
    return a + b;
}
System.println(test(1.5));
```

#### Result

```
3.2
```

### Example 7. Label to While

#### Code

```javascript
var n = 10000;
native loop_while(n) {
    var v = 0, i = 0;
    LABEL:
    while (1) {
        while (i <= n) {
            if (i == 9) {
                ++i;
                continue;
            }
            v += i++;
            if (i > 10) break LABEL;
        }
    }
    return v;
}
System.println("while(%{n}) = ", loop_while(n));
```

#### Result

```
while(10000) = 46
```

### Example 8. Label to For

#### Code

```javascript
var n = 10000;
native loop_for(n) {
    var v = 0;
    LABEL:
    while (1) {
        for (var i = 0; i <= n; ++i) {
            if (i == 9) continue;
            v += i;
            if (i == 10) break LABEL;
        }
    }
    return v;
}
System.println("for(%{n}) = ", loop_for(n));
```

#### Result

```
for(10000) = 46
```

### Example 9. Label to Do-While

#### Code

```javascript
var n = 10000;
native loop_do_while(n) {
    var v = 0, i = 0;
    LABEL:
    while (1) {
        do {
            if (i == 9) {
                ++i;
                continue;
            }
            v += i++;
            if (i > 10) break LABEL;
        } while (i <= n);
    }
    return v;
}
System.println("do_while(%{n}) = ", loop_do_while(n));
```

#### Result

```
do_while(10000) = 46
```

### Example 10. Too deep to call a native

#### Code

```javascript
native tooDeep(n) {
    return tooDeep(n-1);    # infinite loop!
}
tooDeep(100);
```

#### Result

```
Uncaught exception: No one catch the exception.
NativeFunctionException: Too deep to call function
Stack Trace Information:
        at <main-block>(test.kx:4)
```

### Example 11. Try-Catch-Finally

#### Code

```javascript
var b = 100;
var c = 100;
function test() {
    var d = 0;
    return native (n) {
        var a = 100;
        try {
            try {
                a /= d;
            } finally {
                ++b;
            }
            b %= 9;
        } catch (e) {
            c = 999;
            throw;
        } finally {
            ++b;
        }
        return a;
    };
}

var try_catch = test();
try {
    System.println("b = ", b);
    System.println(try_catch(10));
} catch (e) {
    System.println(e.what());
    e.printStackTrace();
} finally {
    System.println("b = ", b);
    System.println("c = ", c);
}
```

#### Result

```
b = 100
Divide by zero
Stack Trace Information:
        at <main-block>(test.kx:27)
b = 102
c = 999
```

### Example 12. Finally with return

#### Code

```javascript
var a, b, c, d;

function check(name, test) {
    a = b = c = d = 0;
    System.println("%{name}:");
    System.println("    a = %{a}, b = %{b}, c = %{c}, d = %{d}");

    try {
        test();
        System.println("    a = %{a}, b = %{b}, c = %{c}, d = %{d}");
    } catch (e) {
        System.println("Exception: ", e.what());
    }
}

native test1_native() {
    try {
        try {
            return 1;
        } finally {
            a = 100;
        }
    } finally {
        b = 1000;
    }
}

native test_native(f:native) {
    try {
        try {
            return f();
        } finally {
            c = 10000;
        }
    } finally {
        d = 100000;
    }
}

function test1_function() {
    try {
        try {
            return 1;
        } finally {
            a = 100;
        }
    } finally {
        b = 1000;
    }
}

function test_function(f) {
    try {
        try {
            return f();
        } finally {
            c = 10000;
        }
    } finally {
        d = 100000;
    }
}

check("native -> native", &() => test_native(test1_native));
check("function -> native", &() => test_function(test1_native));
check("function -> function", &() => test_function(test1_function));
```

#### Result

```
native -> native:
    a = 0, b = 0, c = 0, d = 0
    a = 100, b = 1000, c = 10000, d = 100000
function -> native:
    a = 0, b = 0, c = 0, d = 0
    a = 100, b = 1000, c = 10000, d = 100000
function -> function:
    a = 0, b = 0, c = 0, d = 0
    a = 100, b = 1000, c = 10000, d = 100000
```

### Example 12. Finally with throw.

#### Code

```javascript
var a, b, c, d;

function check(name, test) {
    a = b = c = d = 0;
    System.println("%{name}:");
    System.println("    a = %{a}, b = %{b}, c = %{c}, d = %{d}");

    try {
        test();
    } catch (e) {
        ;
    }
    System.println("    a = %{a}, b = %{b}, c = %{c}, d = %{d}");
}

native test1_native() {
    try {
        try {
            throw 1;
        } finally {
            a = 100;
        }
    } finally {
        b = 1000;
    }
}

native test_native(f:native) {
    try {
        try {
            return f();
        } finally {
            c = 10000;
        }
    } finally {
        d = 100000;
    }
}

function test1_function() {
    try {
        try {
            throw 1;
        } finally {
            a = 100;
        }
    } finally {
        b = 1000;
    }
}

function test_function(f) {
    try {
        try {
            return f();
        } finally {
            c = 10000;
        }
    } finally {
        d = 100000;
    }
}

check("native -> native", &() => test_native(test1_native));
check("function -> native", &() => test_function(test1_native));
check("function -> function", &() => test_function(test1_function));
```

#### Result

```
native -> native:
    a = 0, b = 0, c = 0, d = 0
    a = 100, b = 1000, c = 10000, d = 100000
function -> native:
    a = 0, b = 0, c = 0, d = 0
    a = 100, b = 1000, c = 10000, d = 100000
function -> function:
    a = 0, b = 0, c = 0, d = 0
    a = 100, b = 1000, c = 10000, d = 100000
```

### Example 13. Quicksort with Integer

#### Code

```javascript
native quicksort(a:int[], first, last) {
    var i = first;
    var j = last;
    var x = a[(first + last) / 2];
    while (true) {
        while (a[i] < x) i++;
        while (x < a[j]) j--;
        if (i >= j) break;

        [a[i], a[j]] = [a[j], a[i]];
        ++i; --j;
    }
    if (first  < i - 1)
        quicksort(a, first , i - 1);
    if (j + 1 < last)
        quicksort(a, j + 1, last);
}

function show(title, a) {
    System.print(title);
    a.each(&(e) => System.print(" %2d" % e));
    System.print("\n");
}

function demo() {
    var a = [69, 63, 88, 85, 26, 77, 51, 42, 16, 4, 20, 18, 18, 40, 23, 26, 24, 63, 96, 59];

    show("Before:", a);
    quicksort(a, 0, a.length() - 1);
    show("After: ", a);
}

demo();
```

#### Result

```
Before: 69 63 88 85 26 77 51 42 16  4 20 18 18 40 23 26 24 63 96 59
After:   4 16 18 18 20 23 24 26 26 40 42 51 59 63 63 69 77 85 88 96
```

### Example 14. Quicksort with Double

#### Code

```javascript
native quicksort(a:dbl[], first, last) {
    var i = first;
    var j = last;
    var x = a[(first + last) / 2];
    while (true) {
        while (a[i] < x) i++;
        while (x < a[j]) j--;
        if (i >= j) break;

        [a[i], a[j]] = [a[j], a[i]];
        ++i; --j;
    }
    if (first  < i - 1)
        quicksort(a, first , i - 1);
    if (j + 1 < last)
        quicksort(a, j + 1, last);
}

function show(title, a) {
    System.print(title);
    a.each(&(e) => System.print(" %3.1f" % e));
    System.print("\n");
}

function demo() {
    var a = [69, 63, 88, 85, 26, 77, 51, 42, 16, 4, 20, 18, 18, 40, 23, 26, 24, 63, 96, 59].map { => Double.parseDouble(_1 / 10) };

    show("Before:", a);
    quicksort(a, 0, a.length() - 1);
    show("After: ", a);
}

demo();
```

#### Result

```
Before: 6.9 6.3 8.8 8.5 2.6 7.7 5.1 4.2 1.6 0.4 2.0 1.8 1.8 4.0 2.3 2.6 2.4 6.3 9.6 5.9
After:  0.4 1.6 1.8 1.8 2.0 2.3 2.4 2.6 2.6 4.0 4.2 5.1 5.9 6.3 6.3 6.9 7.7 8.5 8.8 9.6
```
