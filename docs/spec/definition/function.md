# Function

## Overview

### Normal Function

The `function` to share code has long been used.
The `function` receives some arguments, does something, and returns a result.

```javascript
function add(a, b) {
    return a + b;
}
System.println(add(1, 2));  // 3
```

### Rest Operator

The `function` can accept a rest operator only at the last argument like JavaScript.
It is useful for variable arguments.

```javascript
function toArrayWith3(...a) {
    var b = [...a]; // copy
    return b + [3];
}
System.println(toArrayWith3(1, 2).join(', '));  // "1, 2, 3"
```

### Recursive call

Recursive calling is available, but not supported a tail-recursion optimization.

```javascript
function fib(n) {
    if (n < 3) return n;
    return fib(n-2) + fib(n-1);
}

System.println("fib(34) = ", fib(34));  // fib(34) = 9227465
```

### Arguments

You can use a destructuring assignment style in arguments, which is same as declaration statement.
The following three styles are available.

* Array Style ... each item in the array will be assigned to a variable in the order.
* Object Key Style ... the value according to a key name will be assigned to the variable of the same name as the key.
* Object Style ... each value will be assigned to the variable bound to each key.

Here is an example.

```javascript
function func([a, b, , ...c], { x, y }, { x: d, y: { a: e, b: f } }) {
    System.println("a = ", a);
    System.println("b = ", b);
    System.println("c = ", c);
    System.println("d = ", d);
    System.println("e = ", e);
    System.println("f = ", f);
    System.println("x = ", x);
    System.println("y = ", y);
}
func([1, 2, 3, 4, 5, 6], { x: 10, y: 100 }, { x: 20, y: { a: 30, b: 300 } });
```

Here is the result.

```
a = 1
b = 2
c = [4, 5, 6]
d = 20
e = 30
f = 300
x = 10
y = 100
```

#### Pattern Matching

As this is same as assignment and declaration, the pattern matching is available also in an argument.
If a part of variables is a literal, it will be checked if the same value.
And if matching a pattern is failed, the exdeption of `NoMatchingPatternException` will be raised.

Here is an example.

```javascript
function func([a, b, , ...c], { x, y }, { x: d, y: { a: e, b: 300 } }) {
    System.println("a = ", a);
    System.println("b = ", b);
    System.println("c = ", c);
    System.println("d = ", d);
    System.println("e = ", e);
    System.println("x = ", x);
    System.println("y = ", y);
}
func([1, 2, 3, 4, 5, 6], { x: 10, y: 100 }, { x: 20, y: { a: 30, b: 300 } });
func([1, 2, 3, 4, 5, 6], { x: 10, y: 100 }, { x: 20, y: { a: 30, b: 3 } });
```

Here is the result.

```
a = 1
b = 2
c = [4, 5, 6]
d = 20
e = 30
x = 10
y = 100
Uncaught exception: No one catch the exception.
NoMatchingPatternException: Pattern not matched
Stack Trace Information:
        at function func(test.kx:1)
        at <main-block>(test.kx:11)
```

### Anonymous Function

Here is the example of anonymous function.
That can be written directly into an expression, and it can be also an argument of a function.

```javascript
var calc = function(func, a, b) {
    return func(a, b);
};
System.println(calc(function(a, b) { return a + b; }, 2, 3));   // 5
```

## Examples

### Example 1. Fibonacci

#### Code

```javascript
function fib(n) {
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
function fact(a) {
    if (a < 1) return 1;
    return a * fact(a-1);
}
for (var i = 0; i <= 20; ++i) {
    System.println("fact(%{i}) = ", fact(i));
}
System.println("fact(500) = ", fact(500));
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
fact(500) = 1220136825991110068701238785423046926253574342803192842192413588385845373153881997605496447502203281863013616477148203584163378722078177200480785205159329285477907571939330603772960859086270429174547882424912726344305670173270769461062802310452644218878789465754777149863494367781037644274033827365397471386477878495438489595537537990423241061271326984327745715546309977202781014561081188373709531016356324432987029563896628911658974769572087926928871281780070265174507768410719624390394322536422605234945850129918571501248706961568141625359056693423813008856249246891564126775654481886506593847951775360894005745238940335798476363944905313062323749066445048824665075946735862074637925184200459369692981022263971952597190945217823331756934581508552332820762820023402626907898342451712006207714640979456116127629145951237229913340169552363850942885592018727433795173014586357570828355780158735432768888680120399882384702151467605445407663535984174430480128938313896881639487469658817504506926365338175055478128640000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
```

### Example 3. While Loop

#### Code

```javascript
var n = 10000;
function loop_while(n) {
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
function loop_for(n) {
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
function loop_do_while(n) {
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
function test(a:dbl) {
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
function loop_while(n) {
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
function loop_for(n) {
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
function loop_do_while(n) {
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

### Example 10. Try-Catch-Finally

#### Code

```javascript
var b = 100;
var c = 100;
function test() {
    var d = 0;
    return function (n) {
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

### Example 11. Array & Object Style

#### Code

```javascript
function func([a, b, , ...c], { x, y }, { x: d, y: { a: e, b: f } }) {
    System.println("a = ", a);
    System.println("b = ", b);
    System.println("c = ", c);
    System.println("d = ", d);
    System.println("e = ", e);
    System.println("f = ", f);
    System.println("x = ", x);
    System.println("y = ", y);
}
func([1, 2, 3, 4, 5, 6], { x: 10, y: 100 }, { x: 20, y: { a: 30, b: 300 } });
```

#### Result

```
a = 1
b = 2
c = [4, 5, 6]
d = 20
e = 30
f = 300
x = 10
y = 100
```

### Example 12. Pattern Matching

#### Code

```javascript
function func([a, b, , ...c], { x, y }, { x: d, y: { a: e, b: 300 } }) {
    System.println("a = ", a);
    System.println("b = ", b);
    System.println("c = ", c);
    System.println("d = ", d);
    System.println("e = ", e);
    System.println("x = ", x);
    System.println("y = ", y);
}
func([1, 2, 3, 4, 5, 6], { x: 10, y: 100 }, { x: 20, y: { a: 30, b: 300 } });
func([1, 2, 3, 4, 5, 6], { x: 10, y: 100 }, { x: 20, y: { a: 30, b: 3 } });
```

#### Result

```
a = 1
b = 2
c = [4, 5, 6]
d = 20
e = 30
x = 10
y = 100
Uncaught exception: No one catch the exception.
NoMatchingPatternException: Pattern not matched
Stack Trace Information:
        at function func(test.kx:1)
        at <main-block>(test.kx:11)
```
