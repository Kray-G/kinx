# Integer

## Overview

Integer objects are numbers like `1`.
You can write it in decimal, octal, and hexadecimal numbers.

### Methods

There is a special object named as `Integer`.
The methods of `Integer` can be used for integer values directly.

|               Method               |                                                                           Meaning                                                                            |
| ---------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Integer.times(val, callback)       | As the range of i = 0 to (val-1), if `callback` exists, it is the result of `callback(i)`, and if it does not exist, creates an array with i and returns it. |
| Integer.upto(val, max, callback)   | Call `callback(i)` as an argument in the range of i = val to max.                                                                                            |
| Integer.downto(val, min, callback) | Call `callback(i)` as an argument in the range of i = min to val.                                                                                            |
| Integer.toString(val, base)        | Converts `val` into a string. `base` only supports 10 and 16.                                                                                                |
| Integer.toDouble(val)              | Converts `val` into Double.                                                                                                                                  |

The `Integer` object can hold any methods you want to add.
For example, see below.

```javascript
Integer.times100 = function(value) {
    return value * 100;
};
var val = 100.times100();
System.println(val);
```

Let's run it.

```
10000
```

The receiver comes in the first argument.

### Math Object Method

`Integer` objects have the same special methods as Math objects. See below for details.
When written in a concrete example, the following can be written, for example.

```javascript
var a = 2.pow(10); // same as Math.pow(2, 10) => 1024
var b = (-10).abs(); // same as Math.abs(-10) => 10
```

Note that unary minus (`-`) has lower precedence than function calls, so it must be enclosed in parentheses.

### Special operator

#### Unary `*` operator

When the unary `*` operator is applied to an integer value, the character string (1 character) corresponding to the character code is returned.

```javascript
var a = *97; // => "a"
```

By the way, the reverse conversion (`*a`) cannot be restored.
Note that the unary `*` operator for strings is an array, so `*a` in the above example would be an array `[97]`.
To get the character code alone, use `a[0]`.

### BigInteger

Converting between Integer and BigInteger will be automatically done.
Integer will be dealt with between INT64_MIN and INT64_MAX,
and when it is over those range, a value will be converted to BigInteger.

## Examples

### Example 1. Normal case

#### Code

```javascript
System.println(100);
System.println(0xff);
System.println(010);
```

#### Result

```
100
255
8
```

### Example 2. Math

#### Code

```javascript
var a = 2.pow(10);
var b = (-10).abs();
System.println(a);
System.println(b);
```

#### Result

```
1024
10
```

### Example 3. BigInteger (1)

#### Code

```javascript
var a = 0x7fffffffffffffff - 4;
for (var i = 0; i < 8; ++i) {
    var isI = a.isInteger;
    var isB = a.isBigInteger;
    System.println(a++, ": ", isI ? "Integer, " : "         ", isB ? "BigInteger" : "");
}
```

#### Result

```
9223372036854775803: Integer,
9223372036854775804: Integer,
9223372036854775805: Integer,
9223372036854775806: Integer,
9223372036854775807: Integer,
9223372036854775808: Integer, BigInteger
9223372036854775809: Integer, BigInteger
9223372036854775810: Integer, BigInteger
```

### Example 4. BigInteger (2)

#### Code

```javascript
var a = -(0x7fffffffffffffff) - 4;
for (var i = 0; i < 8; ++i) {
    var isI = a.isInteger;
    var isB = a.isBigInteger;
    System.println(a++, ": ", isI ? "Integer, " : "         ", isB ? "BigInteger" : "");
}
```

#### Result

```
-9223372036854775811: Integer, BigInteger
-9223372036854775810: Integer, BigInteger
-9223372036854775809: Integer, BigInteger
-9223372036854775808: Integer,
-9223372036854775807: Integer,
-9223372036854775806: Integer,
-9223372036854775805: Integer,
-9223372036854775804: Integer,
```
