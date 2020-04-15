# Exponent Operator

## Overview

Exponent operator is `**`.

```javascript
var a = 0x05;
var b = a ** 2;   // 5 * 5 => 25
```

The differences between `Math.pow` and `**` operation are the type of result.
When it is `Math.pow`, the type of result is always double.
However when it is `**` operation, the type of result depends on the source value's type.
For example, the result will be integer when doing `integer ** integer`.

Operator `**` is evaluated from right to left.
For example see below.

```javascript
a = 2 ** 3 ** 4;    // means 2 ** (3 ** 4), not (2 ** 3) ** 4.
                    //  should be 2417851639229258349412352.
```

## Examples

### Example 1. Normal Use for Integer

#### Code

```javascript
var a = 5;
System.println(2 ** a);
System.println(a ** a);
System.println((2 ** a).isInteger ? "Integer" : "NOT Integer");
System.println((2 ** a).isBigInteger ? "BigInteger" : "NOT BigInteger");
```

#### Result

```
32
3125
Integer
NOT BigInteger
```

### Example 2. Normal Use for Double

#### Code

```javascript
var a = 5.0;
System.println(2 ** a);
System.println(a ** a);
System.println((2 ** a).isInteger ? "Integer" : "NOT Integer");
System.println((a ** 2).isInteger ? "Integer" : "NOT Integer");
```

#### Result

```
32
3125
NOT Integer
NOT Integer
```

### Example 3. Normal Use for Big Integer

#### Code

```javascript
var a = 2 ** 84;
System.println(a);
System.println(a.toString(16));
System.println(a.isInteger ? "Integer" : "NOT Integer");
System.println(a.isBigInteger ? "BigInteger" : "NOT BigInteger");
```

#### Result

```
19342813113834066795298816
1000000000000000000000
Integer
BigInteger
```

### Example 4. Operator Priority

Operator `**` is evaluated from right to left.

#### Code

```javascript
var a = 2 ** 3 ** 4;
System.println(a);
```

#### Result

```
2417851639229258349412352
```
