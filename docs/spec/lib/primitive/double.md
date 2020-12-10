# Double

## Overview

Double objects are floating point numbers like `1.5`.
You can write it in decimal point notation.

### Methods

There is a special object named as `Double`.
The methods of `Double` can be used for integer values directly.

|            Method            |                                                               Meaning                                                                |
| ---------------------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| Double.toString(val, format) | Converts `val` into a string. `format` can be `a`, `A`, `e`, `E`, `f`, `F`, `g`, or `G` following `%`. `%g` will be used if omitted. |
| Double.toInt(val)            | Converts `val` into Integer.                                                                                                         |

The `Double` object can hold any methods you want to add.
For example, see below.

```javascript
Double.times100 = function(value) {
    return value * 100;
};
var val = 100.2.times100();
System.println(val);
```

Let's run it.

```
10020
```

The receiver comes in the first argument.

### Math Object Method

`Double` objects have the same special methods as Math objects. See below for details.
When written in a concrete example, the following can be written, for example.

```javascript
var a = 2.0.pow(10); // same as Math.pow(2.0, 10) => 1024
var b = (-10.0).abs(); // same as Math.abs(-10.0) => 10
```

Note that unary minus (`-`) has lower precedence than function calls, so it must be enclosed in parentheses.

## Examples

### Example 1. Normal case

#### Code

```javascript
System.println(100.1);
```

#### Result

```
100.1
```

### Example 2. Math

#### Code

```javascript
var a = 2.0.pow(10);
var b = (-10.0).abs();
System.println(a);
System.println(b);
```

#### Result

```
1024
10
```
