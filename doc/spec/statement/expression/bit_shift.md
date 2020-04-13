# Bit Shift Operator

## Overview

Bit Shift operator will shift right or left by specified bit numbers.

```javascript
var a = 0x05;
var b = a << 1;   // 0101 << 1 => 1010
var c = b >> 1;   // 1010 >> 1 => 0101
```

This can be also used with assignment operator as `<<=` or `>>=`.
Those operators will automatically make it promote to Big Integer when it is over 64 bit integer range.

```javascript
var a = 0x05;
a ^= 0x06;          // 0101 | 0110 => 0011
```

Note that Bit OR operator will treat `null` as 0.

## Examples

### Example 1. Shift left

#### Code

```javascript
function test(a, b) {
    return a << b;
}

System.println(test(0x05, 1));
System.println(test(10, 11));
System.println(test(null, 0x05));
System.println(test(0x07, null));
```

#### Result

```
10
20480
0
7
```

### Example 2. Shift right

#### Code

```javascript
function test(a, b) {
    return a >> b;
}

System.println(test(0x0a, 1));
System.println(test(1024, 4));
System.println(test(null, 0x05));
System.println(test(0x07, null));
```

#### Result

```
5
64
0
7
```

### Example 3. Big Integer Shift left

#### Code

```javascript
function test(a, b) {
    return (a << b).toString(16);
}

System.println(test(0x7fffffffffffffff, 2));
System.println(test(0x7fffffffffffffff + 1, 2));
```

#### Result

```
1fffffffffffffffc
20000000000000000
```

### Example 4. Big Integer Shift right

#### Code

```javascript
function test(a, b) {
    return (a >> b).toString(16);
}

System.println(test(0x7fffffffffffffff * 2, 2));
System.println(test((0x7fffffffffffffff + 1) * 2, 2));
System.println(test((0x7fffffffffffffff + 1) * 8, 2));
```

#### Result

```
3fffffffffffffff
4000000000000000
10000000000000000
```
