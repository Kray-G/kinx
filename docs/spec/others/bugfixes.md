# Bug Fixes

## Overview

This section describes a testing for bug fixes.

## Examples

### Example 1. isPrime in native

This bug's was caused by an invalid mod operation.

* Issue: #17
* Fixed: 84458603b333c6a678082ab2c17a4d730fd8c6dc
* Release: **NOT Released Yet**

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
