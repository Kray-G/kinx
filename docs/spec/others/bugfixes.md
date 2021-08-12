# Bug Fixes

## Overview

This section describes a testing for bug fixes.

## Examples

### Example 1. isPrime in native

This bug's was caused by an invalid mod operation.

* Issue: [#17](https://github.com/Kray-G/kinx/issues/17)
* Fixed: [84458603b333c6a678082ab2c17a4d730fd8c6dc](https://github.com/Kray-G/kinx/commit/84458603b333c6a678082ab2c17a4d730fd8c6dc)

See also an additional test code in [Basic Expressions in native](../definition/native/native_expr.md).

#### Code

```javascript
native isPrime(n: int) {
    for (var i = 2; i <= Math.sqrt(n); ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

System.println(isPrime(15) ? 'true' : 'false'); // false
System.println(isPrime(17) ? 'true' : 'false'); // true
```

#### Result

```
false
true
```

### Example 2. Integer multiply by -1

This was found internally, so there is no issue id.

* Fixed: [877b9a5e9e5ce8e1da2224126381dd960a43258d..7411e7aef32307ecb539ce1512b85dbd9ed48a4f](https://github.com/Kray-G/kinx/compare/877b9a5e9e5ce8e1da2224126381dd960a43258d..7411e7aef32307ecb539ce1512b85dbd9ed48a4f)

#### Code

```javascript
for (ypix in 0...24) {
    System.print(":");
    var y = ypix / 12 - 1;
    for (xpix in 1...79) {
        var x = xpix / 30 - 2;
        var x0 = x;
        var y0 = y;
        var iter = 0;
        while (iter < 11 && x0 * x0 + y0 * y0 <= 4) {
            var x1 = (x0 * x0) - (y0 * y0) + x;
            var y1 = 2 * x0 * y0 + y;
            x0 = x1;
            y0 = y1;
            iter = iter + 1;
        }
        System.print(*(" .-:;+=xX$& "[iter]));
    }
    System.println("");
}
```

#### Result

```
:        .......------------------------:::::::::;;;;+=X X & ;:::::::------....
:      ......------------------------::::::::::;;;;+==x&  &x=+;;;::::::-------.
:     ....------------------------::::::::::;;;;++=X         X=;;;;;:::::------
:    ...-----------------------::::::::::;;+++++==xX         Xx=+++;;;;;:::----
:   ..----------------------::::::::;;;;+x   &XX               & $x===x +;::---
:  ..--------------------::::;;;;;;;;+++=x&                             $+;::--
: ..----------------::::;;;;;;;;;;++++=x$                              $=+;;::-
: .-----------:::::;;= x+++++++++====xx&                               &xx+;:::
:.-----:::::::::;;;++=$  &$X$ &XXXxxXX&                                   x+;::
:---:::::::::;;;;;;+==X$            &                                    &=;;::
:-::::::::;;;;;;+=xxX$                                                   x+;;::
:::;;:::++++++==xX&                                                     =+;;;::
:                                                                     Xx=+;;;::
:::;;:::++++++==xX&                                                     =+;;;::
:-::::::::;;;;;;+=xxX$                                                   x+;;::
:---:::::::::;;;;;;+==X$            &                                    &=;;::
:.-----:::::::::;;;++=$  &$X$ &XXXxxXX&                                   x+;::
: .-----------:::::;;= x+++++++++====xx&                               &xx+;:::
: ..----------------::::;;;;;;;;;;++++=x$                              $=+;;::-
:  ..--------------------::::;;;;;;;;+++=x&                             $+;::--
:   ..----------------------::::::::;;;;+x   &XX               & $x===x +;::---
:    ...-----------------------::::::::::;;+++++==xX         Xx=+++;;;;;:::----
:     ....------------------------::::::::::;;;;++=X         X=;;;;;:::::------
:      ......------------------------::::::::::;;;;+==x&  &x=+;;;::::::-------.
```

### Example 3. Comparing between variables of a string

This bug's was caused by missing implementation.

* Issue: [#237](https://github.com/Kray-G/kinx/issues/237)
* Fixed: [94c49bae803a0131c138d28a5a65b2a4e1426612](https://github.com/Kray-G/kinx/commit/94c49bae803a0131c138d28a5a65b2a4e1426612)

#### Code

```javascript
function gt(a, b)  { return a > b; }
function lt(a, b)  { return a < b; }
function ge(a, b)  { return a >= b; }
function le(a, b)  { return a <= b; }
function lge(a, b) { return a <=> b; }
try { gt("a", "b");  System.println("Successful"); } catch (e) { System.println(e.what()); }
try { lt("a", "b");  System.println("Successful"); } catch (e) { System.println(e.what()); }
try { ge("a", "b");  System.println("Successful"); } catch (e) { System.println(e.what()); }
try { le("a", "b");  System.println("Successful"); } catch (e) { System.println(e.what()); }
try { lge("a", "b"); System.println("Successful"); } catch (e) { System.println(e.what()); }
```

#### Result

```
Successful
Successful
Successful
Successful
Successful
```

### Example 4. Can't specify a return type of function

This bug's was caused by lack of consideration of a part of type propagation.

* Issue: [#236](https://github.com/Kray-G/kinx/issues/236)
* Fixed: [3fa599b7153bdcecaf506aeca753c2047f328aa2](https://github.com/Kray-G/kinx/commit/3fa599b7153bdcecaf506aeca753c2047f328aa2)
* Fixed: [00319887f851d960a7e0523f5ef4735b2d37531c](https://github.com/Kray-G/kinx/commit/00319887f851d960a7e0523f5ef4735b2d37531c)

#### Code

```javascript
class A() {
    public xxx() {
        System.println("Successful");
    }
}

function f(): A {
    return new A(); // => Error: Expect return type (object) but (... unknown)
}
f().xxx();
```

#### Result

```
Successful
```

### Example 5. Comparison Failure & Crash

This bug's was caused by lack of the code which moves to the next opcode.

* Issue: [#256](https://github.com/Kray-G/kinx/issues/256)
* Fixed: [bf1b5ba926db08a69a5c6786d7557f9f6d7e420f](https://github.com/Kray-G/kinx/commit/bf1b5ba926db08a69a5c6786d7557f9f6d7e420f)

#### Code

```javascript
function test1(a) { return 10 >= a; }
function test2(a) { return -1 <= a; }
function test3(a) { return 100 < a; }

System.println(test1(10.5));
System.println(test2(10.5));
System.println(test3(10.5));
```

#### Result

```
0
1
0
```

### Example 6. Fails a Destructuring Assignment in Const

This bug's was caused by an incorrect bytecode.

* Issue: [#257](https://github.com/Kray-G/kinx/issues/257)
* Fixed: [43d82765b577221c820575b7f5e7323cc0171be1](https://github.com/Kray-G/kinx/commit/43d82765b577221c820575b7f5e7323cc0171be1)

#### Code

```javascript
function test1(data) {
    var [a, b, ...c] = data.split(',');
}
function test2(data) {
    [a, b, ...c] = data.split(',');
}
function test3(data) {
    const [a, b, ...c] = data.split(',');
}
test1("1,2,3,4,5,6,7,8,9");
test2("1,2,3,4,5,6,7,8,9");
test3("1,2,3,4,5,6,7,8,9");

System.println("Successful");
```

#### Result

```
Successful
```

### Example 7. Fixed toJsonString() for Object

This bug's was caused by incorrect extracting an object.

* Issue: [#271](https://github.com/Kray-G/kinx/issues/271)
* Fixed: [e7c9b9527b9a21b298df1d1a166311cfd8f97774](https://github.com/Kray-G/kinx/commit/e7c9b9527b9a21b298df1d1a166311cfd8f97774)

#### Code

```javascript
class A {
    public toString() { return "A"; }
}
class B {
    public toString() { return "\\\"B\""; }
}

System.println({ a: new A() });  // => {"a":"A"}
System.println({ b: new B() });  // => {"a":"A"}
```

#### Result

```
{"a":"A"}
{"b":"\\\"B\""}
```

### Example 8. Detects error for multi decl of 'const'

This bug's was caused by missing to check the condition.

* Issue: [#274](https://github.com/Kray-G/kinx/issues/274)
* Fixed: [c6f7f926f1790686fcb059605bc89ac24352663f](https://github.com/Kray-G/kinx/commit/c6f7f926f1790686fcb059605bc89ac24352663f)

#### Code

```javascript
const A = 1;
const A = 2;
A = 3;
System.println(A);
```

#### Result

```
Error: Symbol(A) has been already declared as 'const' near the <test.kx>:2
Error: Can not assign a value to the 'const' variable near the <test.kx>:3
```

### Example 9. Pin operator in declaration.

This bug's was caused by handling with `pinned` as a `const`.

* Issue: [#277](https://github.com/Kray-G/kinx/issues/277)
* Fixed: [554854f5c2afd0b459526dfd9ace74047d89c6e6](https://github.com/Kray-G/kinx/commit/554854f5c2afd0b459526dfd9ace74047d89c6e6)

#### Code

```javascript
var a = 10;
var { x: ^a, y } = { x: 10, y: 100 };
System.println(y);
var { x: ^a, y } = { x: 100, y: 100 };
System.println(y);
```

#### Result

```
100
Uncaught exception: No one catch the exception.
NoMatchingPatternException: Pattern not matched
Stack Trace Information:
        at <main-block>(test.kx:4)
```

### Example 10. Pin operator in function arguments.

This bug's was caused by the incorrect scope for a variable with pin operator in function arguments.

* Issue: [#277](https://github.com/Kray-G/kinx/issues/277)
* Fixed: [554854f5c2afd0b459526dfd9ace74047d89c6e6](https://github.com/Kray-G/kinx/commit/554854f5c2afd0b459526dfd9ace74047d89c6e6)

#### Code

```javascript
var a = 10;
function test({ x: ^a, y }) {   // The variable `a` should be handled
                                //  as an outside variable by a lexical scope.
    return y;
}
System.println(test({ x: 10, y: 100 }));
System.println(test({ x: 100, y: 100 }));
```

#### Result

```
100
Uncaught exception: No one catch the exception.
NoMatchingPatternException: Pattern not matched
Stack Trace Information:
        at function test(test.kx:2)
        at <main-block>(test.kx:7)
```

### Example 11. Fixed SegFault on Linux

This bug's was caused by NULL dereference only with a Linux code.

* Issue: [#284](https://github.com/Kray-G/kinx/issues/284)
* Fixed: [3e79cc61e9a57a74b0dbb2163d68f5669535e127](https://github.com/Kray-G/kinx/commit/3e79cc61e9a57a74b0dbb2163d68f5669535e127)

#### Code

```javascript
var t = $env.NO_ENVVAR;
System.println("t = ", t);
```

#### Result

```
t =
```

### Example 12. Stack overflow with `=~` or `!~`

This bug's was caused by missing a pop operation.

* Issue: [#293](https://github.com/Kray-G/kinx/issues/293)
* Fixed: [6e7d0115aef380fd92a1ff9799a3b4ce00f86890](https://github.com/Kray-G/kinx/commit/6e7d0115aef380fd92a1ff9799a3b4ce00f86890)

#### Code

```javascript
var l = "aaaaaaa";
for (var i = 0; i < 1000; ++i) {
    if (g = (l =~ /([b-z]+)/)) {
        System.println(g[1].string);
    } else if (g = (l =~ /([0-9]+)/)) {
        System.println(g[1].string);
    }
}
System.println("Successful");
```

#### Result

```
Successful
```

### Example 13. Crash in native.

This bug's was caused by dereferencing uninitialized variable pointer.

* Issue: [#314](https://github.com/Kray-G/kinx/issues/314)
* Fixed: [1852462fb54d49de723e3c08df5619b7751b2689](https://github.com/Kray-G/kinx/commit/1852462fb54d49de723e3c08df5619b7751b2689)

#### Code

```javascript
var mem = [];
for (var i = 0; i < 10; ++i) {
    mem[i] = i;
}

native func0(n:int):obj {
    var r:int[];
    for (var i = 0; i < n; ++i) {
        r[i] = mem[i];
    }
    return r;
}
var res = func0(10);
System.println(res);

native func1(n:int):bin {
    var r:bin;
    for (var i = 0; i < n; ++i) {
        r[i] = mem[i];
    }
    return r;
}
var res = func1(10);
System.println(res);
```

#### Result

```
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
<0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09>
```
