# Bit AND Operator

## Overview

Bit AND operator will set 1 when both bits are 1 for each bit.

```javascript
var a = 0x05;
var b = a | 0x06;   // 0101 | 0110 => 0100
```

This can be also used with assignment operator as `&=`.

```javascript
var a = 0x05;
a &= 0x06;          // 0101 | 0110 => 0100
```

Note that Bit OR operator will treat `null` as 0.

## Examples

### Example 1. Simple use

#### Code

```javascript
function test(a, b) {
    return a & b;
}

System.println(test(0x05, 0x06).toString(16));
System.println(test(11, 1).toString(16));
System.println(test(null, 0x05).toString(16));
System.println(test(0x07, null).toString(16));
```

#### Result

```
4
1
0
0
```

### Example 2. With assignment

#### Code

```javascript
function test(a, b) {
    a &= b;
    return a;
}

System.println(test(0x05, 0x06).toString(16));
System.println(test(11, 1).toString(16));
System.println(test(null, 0x05).toString(16));
System.println(test(0x07, null).toString(16));
```

#### Result

```
4
1
0
0
```

### Example 2. With BigInteger

#### Code

```javascript
function test(a, b) {
    a &= b;
    return a;
}

System.println(test(0x7fffffffffffffff + 4, 0x02).toString(16));
System.println(test(0x02, 0x7fffffffffffffff + 4).toString(16));
System.println(test(0x7fffffffffffffff * 2, 0x7fffffffffffffff * 4).toString(16));
```

#### Result

```
2
2
fffffffffffffffc
```
