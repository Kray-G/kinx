# Bit OR Operator

## Overview

Bit OR operator will set 1 when both bits are not 0 for each bit.

```javascript
var a = 0x05;
var b = a | 0x06;   // 0101 | 0110 => 0111
```

This can be also used with assignment operator as `|=`.

```javascript
var a = 0x05;
a |= 0x06;          // 0101 | 0110 => 0111
```

Note that Bit OR operator will treat `null` as 0.

## Examples

### Example 1. Simple use

#### Code

```javascript
function test(a, b) {
    return a | b;
}

System.println(test(0x05, 0x06).toString(16));
System.println(test(10, 1).toString(16));
System.println(test(null, 0x05).toString(16));
System.println(test(0x07, null).toString(16));
```

#### Result

```
7
b
5
7
```

### Example 2. With assignment

#### Code

```javascript
function test(a, b) {
    a |= b;
    return a;
}

System.println(test(0x05, 0x06).toString(16));
System.println(test(10, 1).toString(16));
System.println(test(null, 0x05).toString(16));
System.println(test(0x07, null).toString(16));
```

#### Result

```
7
b
5
7
```

### Example 2. With BigInteger

#### Code

```javascript
function test(a, b) {
    a |= b;
    return a;
}

System.println(test(0x7fffffffffffffff + 2, 0x02).toString(16));
System.println(test(0x02, 0x7fffffffffffffff + 2).toString(16));
System.println(test(0x7fffffffffffffff * 2, 0x7fffffffffffffff + 2).toString(16));
```

#### Result

```
8000000000000003
8000000000000003
ffffffffffffffff
```
