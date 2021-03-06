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
