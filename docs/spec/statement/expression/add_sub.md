# Addition/Subtraction Operator

## Overview

`+` and `-` operators are showing of addition and subtraction operations.
Those operators will automatically make it promote to Big Integer when it is over 64 bit integer range.

```javascript
var a = 10;
var b = a + 1;                  // 10 + 1 => 11
var c = 0x7fffffffffffffff + a; // 0x7fffffffffffffff + 10 => 0x8000000000000009
```

This can be also used with assignment operator as `+=` or `-=`.

```javascript
var a = 0x05;
a += 0x06;          // 5 + 6 => 11
```

Note that those operators will treat `null` as 0.

## Examples

### Example 1. Addition

#### Code

```javascript
function test(a, b) {
    return a + b;
}

System.println(test(0x05, 1));
System.println(test(10, -2048));
System.println(test(null, 0x05));
System.println(test(0x07, null));
```

#### Result

```
6
-2038
5
7
```

### Example 2. Subtraction

#### Code

```javascript
function test(a, b) {
    return a - b;
}

System.println(test(0x05, 1));
System.println(test(10, -2048));
System.println(test(null, 0x05));
System.println(test(0x07, null));
```

#### Result

```
4
2058
-5
7
```

### Example 3. Big Integer Addition

#### Code

```javascript
function test(a, b) {
    return (a + b).toString(16);
}

System.println(test(0x7fffffffffffffff, 2));
System.println(test(0x7fffffffffffffff + 1, -2));
```

#### Result

```
8000000000000001
7ffffffffffffffe
```

### Example 4. Big Integer Subtraction

#### Code

```javascript
function test(a, b) {
    return (a - b).toString(16);
}

System.println(test(0x7fffffffffffffff, -2));
System.println(test(0x7fffffffffffffff + 1, 2));
```

#### Result

```
8000000000000001
7ffffffffffffffe
```
