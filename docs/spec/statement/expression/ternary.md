# Ternary Operator

## Overview

Ternary operator is a simple `if-else`.
`a ? b : c` means, if a is true, then b, otherwise c.

```javascript
var b = a ? 10 : 20;
```

This expression is evaluated right to left.

## Examples

### Example 1. Simple use

#### Code

```javascript
function test(a) {
    return a ? 10 : 20;
}

System.println(test(true));
System.println(test(False));    // False object.
```

#### Result

```
10
20
```

### Example 2. Combination of ternary operator

#### Code

```javascript
function test(b1, b2, b3) {
    return b1 ? b2 ? 1 : 2 : b3 ? 3 : 4;
}

System.println(test(0, 0, 0));
System.println(test(0, 0, 1));
System.println(test(0, 1, 0));
System.println(test(0, 1, 1));
System.println(test(1, 0, 0));
System.println(test(1, 0, 1));
System.println(test(1, 1, 0));
System.println(test(1, 1, 1));
```

#### Result

```
4
3
4
3
2
2
1
1
```
