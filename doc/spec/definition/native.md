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

*   Currently you can use the type of integer and double only.
*   All variables are defined as a type. Available type is `int`, `dbl`, `str`, or `native`.
    *   If type information is omitted, the type would be followings.
        *   On argument, it become automatically `int`.
        *   Without initializer on declaration, it become automatically `int`.
        *   With initializer on declaration, it is decided by the result of right hand side.
            *   When it can not be decided, it occurs a compile error.
    *   `native` function's return type is shown like `native<int>`.
    *   Even in this case, you can omit `<int>` like just `native` and automatically make it `int`.
    *   `str` is only supported for adding 2 strings and multiplying string by integer.
*   Integer value is not automatically promoted to big integer, it will just overflow instead.
*   Math functions like `Math.pow(2, 10)` or `2.pow(10)` are supported.
*   Can not call a script function. Only can call a native function.
*   `switch-case` is not supported.
*   Can access to the lexical scope and variables, but only for an integer value, a double value, and a native function.
*   Exceptions with `try-catch-finally` is supported, but a stack trace is not available.
*   Support 64bit only. Libraries are supporting x64, ARM, MIPS, but sorry I can not test it except x64 Windows or Linux.

### Math Functions

Especially, see below for examples of `Math` functions.

* [Math functions](native/math.md)

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
