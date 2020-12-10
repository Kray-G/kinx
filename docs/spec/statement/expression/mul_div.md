# Multiplication/Division Operator

## Overview

`*` operator is showing of multiplication.
`/` and `%` operators are showing of division and reminder operations.
Multiplication will automatically make it promote to Big Integer when it is over 64 bit integer range.
Division and reminder operations are converted to double when it is done by double or the result is not integer.

```javascript
var a = 10;
var b = a * 2;                  // 10 * 2 => 20
var c = 0x7fffffffffffffff * a; // 9223372036854775807 * 10 => 92233720368547758070
```

This can be also used with assignment operator as `*=`, `/=`, or `%=`.

```javascript
var a = 0x05;
a *= 0x06;          // 5 * 6 => 30
```

Note that those operators will treat `null` as 0.

### `%` operator for String.

`%` operator is a special for String object, which is used as a **formatter** operator for String.
Once the `%` operator is applied to String, it will return the formatter object.
The formatter object will work when it is used by output functions like `System.print/println()` or addition to another string object.
Format characters are like C language, which is `%d`, `%s`, and so on.
But if it is not suited to that type, a format character will be automatically changed to be suitable.

```javascript
var name = "John";
var b = "The name is %s." % name;
System.println(b);  // Displaying "The name is John.".
```

The format character can be used with the location number like `%1%`.
This is useful when you want to control the location to apply data.

```javascript
var name = "John";
var age = 19;
var b = "The name is %2%, his age is %1%." % age % name;
System.println(b);  // Displaying "The name is John, his age is 19.".
```

If you want to use a standard format character like `%x` in hex with the location number,
you can use it with `$` like this.

```javascript
var name = "John";
var age = 19;
var b = "The name is %2%, his age is 0x%1$x in hex." % age % name;
System.println(b);  // Displaying "The name is John, his age is 0x13 in hex.".
```

## Examples

### Example 1. Multiplication

#### Code

```javascript
function test(a, b) {
    return a * b;
}

System.println(test(0x05, 100));
System.println(test(10, -2048));
System.println(test(null, 0x05));
System.println(test(0x07, null));
```

#### Result

```
500
-20480
0
0
```

### Example 2. Division

#### Code

```javascript
function test(a, b) {
    return a / b;
}

System.println(test(0x05, 100));
System.println(test(-20480, 10));
System.println(test(null, 0x05));
System.println(test(0x07, null));
```

#### Result

```
0.05
-2048
0
Uncaught exception: No one catch the exception.
SystemException: Divide by zero
Stack Trace Information:
        at function test(test.kx:2)
        at <main-block>(test.kx:8)
```

### Example 3. Reminder

#### Code

```javascript
function test(a, b) {
    return a % b;
}

System.println(test(0x05, 100));
System.println(test(-20481, 10));
System.println(test(null, 0x05));
System.println(test(0x07, null));
```

#### Result

```
5
-1
0
Uncaught exception: No one catch the exception.
SystemException: Divide by zero
Stack Trace Information:
        at function test(test.kx:2)
        at <main-block>(test.kx:8)
```
