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

### Example 4. Can't specify a return type of function. 

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


