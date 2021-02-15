# Function

## Overview

### Lambda

Lambda is a simple style of an anonymous function.
`&` is used instead of `function`, and `=> expression` is used instead of block.

```javascript
var calc = &(func, a, b) => func(a, b);
System.println(calc(&(a, b) => a + b, 2, 3));   // 5
```

Note that `=> { /* block */ }` is also available, so you can not use `&(args) => { /* object */ }`.
If you want to use an object, you have to write it with `&(args) => ({ /* object */ })`.

### Block object

If the function has no arguments, a lambda can be written like `&{...}` style.

```javascript
var a = 10;
var doit = &(block) => block();
System.println(doit(&{
    return a + 100;
}));
```

## Function block syntax

### Block style

This is not same as a block object above. A lambda can be wrapped with `{` and `}`, and it is the base of some simple syntax.
For example, the above `doit` function can be written as below.

```javascript
var doit = { &(block) => block() };
```

#### Omit the argument list

As combining with the block style and a numbered parameter, you can remove an argument list itself.
For example, you can write the `doit` function as below.

```javascript
var doit = { => _1() };
```

#### No arrow style

When the block style without an arrow of `=>` operator, it can be just like a block statement with argument list inside block.

```javascript
var add = { &(a, b)
    return a + b;
};
System.println(add(1, 2));  // => 3
```

If you want to omit an argument list in the normal statement, you have to use it as a block object.

```javascript
var add = &{
    return _1 + _2;
};
System.println(add(1, 2));  // => 3
```

### The last argument in function call

If the last argument in function call is a function object, that can be placed outside the argument list with a block style.
For example, the 4 styles below are absolutely same.

```javascript
callFunction(&(a, b) => a + b);

callFunction(&(a, b) => {
    return a + b;
});

callFunction() { &(a, b) => a + b };

callFunction() { &(a, b)
    return a + b;
};
```

In this case, you can omit an argument list itself without a block object style.
It means you do not have to use `&` before a block when it is the argument written outside the argument list.

```javascript
function callFunction(f) {
    System.println(f(1, 2));    // => 3
}
callFunction() {
    return _1 + _2;
};
```

And you can also omit the parenthesis of function call when there is no argument list except the outside argument.

```javascript
function callFunction(f) {
    System.println(f(1, 2));    // => 3
}
callFunction {
    return _1 + _2;
};
```

## Examples

### Example 1. Fibonacci

#### Code

```javascript
var fib = &(n) => {
    if (n < 3) return n;
    return fib(n-2) + fib(n-1);
};
System.println(fib(34));  // => 9227465
```

#### Result

```
9227465
```

### Example 2. Factorial

#### Code

```javascript
var fact = &(a) => {
    if (a < 1) return 1;
    return a * fact(a-1);
};
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
var loop_while = &(n) => {
    var v = 0, i = 0;
    while (i <= n) {
        v += i++;
    }
    return v;
};
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
var loop_for = &(n) => {
    var v = 0;
    for (var i = 0; i <= n; ++i) {
        v += i;
    }
    return v;
};
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
var loop_do_while = &(n) => {
    var v = 0, i = 0;
    do {
        v += i++;
    } while (i <= n);
    return v;
};
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
var test = &(a:dbl) => {
    return a + b;
};
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
var loop_while = &(n) => {
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
};
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
var loop_for = &(n) => {
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
};
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
var loop_do_while = &(n) => {
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
};
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
};

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

### Example 11. Block style (1)

#### Code

```javascript
function calc(x, y, func) {
    return func(x, y);
}

// The callback function can be put outside an arugument list.
System.println("add = " + calc(10, 2) { &(a, b) => a + b });
System.println("sub = " + calc(10, 2) { &(a, b) => a - b });
System.println("mul = " + calc(10, 2) { &(a, b) => a * b });
System.println("div = " + calc(10, 2) { &(a, b) => a / b });
System.println("add = " + calc(10, 2) { &() => _1 + _2 });
System.println("sub = " + calc(10, 2) { &() => _1 - _2 });
System.println("mul = " + calc(10, 2) { &() => _1 * _2 });
System.println("div = " + calc(10, 2) { &() => _1 / _2 });

System.println("add = " + calc(10, 2) { => _1 + _2 });
System.println("sub = " + calc(10, 2) { => _1 - _2 });
System.println("mul = " + calc(10, 2) { => _1 * _2 });
System.println("div = " + calc(10, 2) { => _1 / _2 });
```

#### Result

```
add = 12
sub = 8
mul = 20
div = 5
add = 12
sub = 8
mul = 20
div = 5
add = 12
sub = 8
mul = 20
div = 5
```

### Example 12. Block style (2)

#### Code

```javascript
var r = [1, 2, 3].map() {
    return _1 * 2;
};
System.println(r);  // => [2, 4, 6]
```

#### Result

```
[2, 4, 6]
```

### Example 13. Block style (3)

#### Code

```javascript
var r = [1, 2, 3].map {
    return _1 * 2;
};
System.println(r);  // => [2, 4, 6]
```

#### Result

```
[2, 4, 6]
```

### Example 14. Block style (4)

#### Code

```javascript
r = (1..10).sort { => _2 <=> _1 };
System.println(r);  // => [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
```

#### Result

```
[10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
```
