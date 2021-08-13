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

*   All variables are defined as a type. Available type is `int`, `big`, `dbl`, `str`, `bin`, `obj`, `int[]`, `dbl[]`, or `native`.
    *   If type information is omitted, the type would be followings.
        *   On argument, it become automatically `int`.
        *   Without initializer on declaration, it become automatically `int`.
        *   With initializer on declaration, it is decided by the result of right hand side.
            *   When it can not be decided, a compile error will occur.
    *   For `int`
        *   Integer value is **NOT** automatically promoted to a big integer, it will just overflow instead.
        *   Math functions like `Math.pow(2, 10)` or `2.pow(10)` are supported.
    *   For `big`
        *   It is supported as a big integer, but there is a little note. Please be careful when you use it.
            *   This type will use all values as a big integer value even if it is a small integer like 1.
                Therefore the performance may be quit slower than doing it with a VM execution in some cases.
            *   The native code will generate so many Big Integer objects in calculating with a big integer.
                In a current design, those objects are not collected by GC during a native execution.
                All objects of a big integer will be collected after returning to the VM execution.
                This means so many memory may be used and a performance may be quit slow.
            *   For example, you should **NOT** use a big integer in a native function like a recursive fibonacci calculation.
    *   For `dbl`
        *   Math functions like `Math.pow(2.0, 10.0)` or `2.0.pow(10.0)` are supported.
    *   For `str`
        *   `str` is only supported for adding 2 strings and multiplying string by integer.
    *   For `bin`
        *   It is supported as an array of byte.
    *   For `int[]` and `dbl[]`
        *   It is currently just supported as an array of integer or double.
    *   For `native`.
        *   `native` function's return type is shown like `native funcname(arg):int`.
        *   Even in this case, you can omit `:int` as the type of a return value and automatically make it `int`.
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

### Basic Expressions

See below for examples of basic expressions in native.

* [Basic Expressions](native/native_expr.md)

### Math Functions

Especially, see below for examples of `Math` functions.

* [Math functions](native/math.md)

### Supported Switch-Case/When

Switch-Case/When is now supported in native function.
But the case label should be an integer type.
See below for examples of Switch-Case/When in native.

* [Switch-Case in Native](native/switch_case.md)
* [Switch-When in Native](native/switch_when.md)

### Supported Array

In native function it can use an array of integer and double.
See below for examples of how to use an array in native.

* [Array in Native](native/array.md)

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
native test(a:dbl):dbl {
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
    LABEL::
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
    LABEL::
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
    LABEL::
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

### Example 13. Finally with throw.

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

### Example 14. Quicksort with Integer

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

### Example 15. Quicksort with Double

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

### Example 16. Big Integer

#### Code

```javascript
function fact(n) {
    if (n <= 1) {
        return 1;
    }
    return n * fact(n - 1);
}

native factb(n:big):big {
    if (n <= 1) {
        return 1;
    }
    return n * factb(n - 1);
}

var f1 = fact(1000);
var f2 = factb(1000);
System.println(("fact(1000)  = %d") % f1);
System.println(("factb(1000) = %d") % f2);
System.println("The result is ", f1 == f2 ? "same." : "different.");
```

#### Result

```
fact(1000)  = 402387260077093773543702433923003985719374864210714632543799910429938512398629020592044208486969404800479988610197196058631666872994808558901323829669944590997424504087073759918823627727188732519779505950995276120874975462497043601418278094646496291056393887437886487337119181045825783647849977012476632889835955735432513185323958463075557409114262417474349347553428646576611667797396668820291207379143853719588249808126867838374559731746136085379534524221586593201928090878297308431392844403281231558611036976801357304216168747609675871348312025478589320767169132448426236131412508780208000261683151027341827977704784635868170164365024153691398281264810213092761244896359928705114964975419909342221566832572080821333186116811553615836546984046708975602900950537616475847728421889679646244945160765353408198901385442487984959953319101723355556602139450399736280750137837615307127761926849034352625200015888535147331611702103968175921510907788019393178114194545257223865541461062892187960223838971476088506276862967146674697562911234082439208160153780889893964518263243671616762179168909779911903754031274622289988005195444414282012187361745992642956581746628302955570299024324153181617210465832036786906117260158783520751516284225540265170483304226143974286933061690897968482590125458327168226458066526769958652682272807075781391858178889652208164348344825993266043367660176999612831860788386150279465955131156552036093988180612138558600301435694527224206344631797460594682573103790084024432438465657245014402821885252470935190620929023136493273497565513958720559654228749774011413346962715422845862377387538230483865688976461927383814900140767310446640259899490222221765904339901886018566526485061799702356193897017860040811889729918311021171229845901641921068884387121855646124960798722908519296819372388642614839657382291123125024186649353143970137428531926649875337218940694281434118520158014123344828015051399694290153483077644569099073152433278288269864602789864321139083506217095002597389863554277196742822248757586765752344220207573630569498825087968928162753848863396909959826280956121450994871701244516461260379029309120889086942028510640182154399457156805941872748998094254742173582401063677404595741785160829230135358081840096996372524230560855903700624271243416909004153690105933983835777939410970027753472000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
factb(1000) = 402387260077093773543702433923003985719374864210714632543799910429938512398629020592044208486969404800479988610197196058631666872994808558901323829669944590997424504087073759918823627727188732519779505950995276120874975462497043601418278094646496291056393887437886487337119181045825783647849977012476632889835955735432513185323958463075557409114262417474349347553428646576611667797396668820291207379143853719588249808126867838374559731746136085379534524221586593201928090878297308431392844403281231558611036976801357304216168747609675871348312025478589320767169132448426236131412508780208000261683151027341827977704784635868170164365024153691398281264810213092761244896359928705114964975419909342221566832572080821333186116811553615836546984046708975602900950537616475847728421889679646244945160765353408198901385442487984959953319101723355556602139450399736280750137837615307127761926849034352625200015888535147331611702103968175921510907788019393178114194545257223865541461062892187960223838971476088506276862967146674697562911234082439208160153780889893964518263243671616762179168909779911903754031274622289988005195444414282012187361745992642956581746628302955570299024324153181617210465832036786906117260158783520751516284225540265170483304226143974286933061690897968482590125458327168226458066526769958652682272807075781391858178889652208164348344825993266043367660176999612831860788386150279465955131156552036093988180612138558600301435694527224206344631797460594682573103790084024432438465657245014402821885252470935190620929023136493273497565513958720559654228749774011413346962715422845862377387538230483865688976461927383814900140767310446640259899490222221765904339901886018566526485061799702356193897017860040811889729918311021171229845901641921068884387121855646124960798722908519296819372388642614839657382291123125024186649353143970137428531926649875337218940694281434118520158014123344828015051399694290153483077644569099073152433278288269864602789864321139083506217095002597389863554277196742822248757586765752344220207573630569498825087968928162753848863396909959826280956121450994871701244516461260379029309120889086942028510640182154399457156805941872748998094254742173582401063677404595741785160829230135358081840096996372524230560855903700624271243416909004153690105933983835777939410970027753472000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
The result is same.
```
