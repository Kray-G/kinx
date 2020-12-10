# Unary Operator

## Overview

Unary operator is a prefix operator.
Here is the unary operator's list.

*  `!`, `+`, `-`, `*`, `++`, `--`.
   *  `! expression` ... Operator Not, means it is evaluated as true when expression is false.
   *  `+ expression` ... Operator Plus, do nothing so far.
   *  `- expression` ... Operator Minus, means it makes expression negative when expression is positive.
   *  `* expression` ... Operator Asterisk, means it is converted to other type depending on the expression's type.
   *  `++ expression` ... Operator Plus Plus, means a prefix increment, and the result will be the value after evaluated.
   *  `-- expression` ... Operator Minus Minus, means a prefix decrement, and the result will be the value after evaluated.

Note that the `true` and the `false` is defined just as Integer of 1 and 0 in Kinx.

```javascript
var a = false;  // false is just 0 as an integer.
var b = !a;     // b => true, means 1 as an integer.
```

## Examples

### Example 1. Simple use of `!`

#### Code

```javascript
System.println(!true);
System.println(!false);
System.println(!True);  // True object.
System.println(!False); // False object.
```

#### Result

```
0
1
0
1
```

### Example 2. Simple use of `+`

#### Code

```javascript
System.println(+true);
System.println(+false);
System.println(+True);  // True object.
System.println(+False); // False object.
```

#### Result

```
1
0
true
false
```

### Example 3. Simple use of `-`

#### Code

```javascript
function test(a) {
    System.println(-a);
}
test(true);
test(false);
test(10);
test(2 ** 70 - 1);
```

#### Result

```
-1
0
-10
-1180591620717411303423
```

### Example 4. Simple use of `*`

#### Code

```javascript
function test(a) {
    System.println(*a);
}
test(97);
test([97, 98, 99]);
test(<97, 98, 99>);
test("ABC");
```

#### Result

```
a
abc
abc
[65, 66, 67]
```

### Example 5. Simple use of `++`

#### Code

```javascript
function test(a) {
    var b = a;
    System.println([b, ++a]);
}
test(97);
test(2 ** 70);
test(-(2 ** 70));
```

#### Result

```
[97, 98]
[1180591620717411303424, 1180591620717411303425]
[-1180591620717411303424, -1180591620717411303423]
```

### Example 6. Simple use of `--`

#### Code

```javascript
function test(a) {
    var b = a;
    System.println([b, --a]);
}
test(97);
test(2 ** 70);
test(-(2 ** 70));
```

#### Result

```
[97, 96]
[1180591620717411303424, 1180591620717411303423]
[-1180591620717411303424, -1180591620717411303425]
```
