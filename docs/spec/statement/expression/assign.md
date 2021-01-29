# Assignment

## Overview

Assignment is to set a value into a variable.
This expression is evaluated right to left.

```javascript
a = b = 10;
```

You can use a variable without declaration, but the scope depends on the situation.
If there is a declaration in outer scope, compiler will refer it.
Otherwise, compiler will use it as declared there.

### Destructuring assignment

You can use the style of an array or object in assignment.
The following three styles are available.

* Array Style ... each item in the array will be assigned to a variable in the order.
* Object Key Style ... the value according to a key name will be assigned to the variable of the same name as the key.
* Object Style ... each value will be assigned to the variable bound to each key.

Here is an example.

```javascript
[a, b, , ...c] = [1, 2, 3, 4, 5, 6];  // 3rd parameter is skipped.
{ x, y } = { x: 20, y: { a: 30, b: 300 } };
{ x: d, y: { a: e, b: f } } = { x: 20, y: { a: 30, b: 300 } };

System.println("a = ", a);
System.println("b = ", b);
System.println("c = ", c);
System.println("d = ", d);
System.println("e = ", e);
System.println("f = ", f);
System.println("x = ", x);
System.println("y = ", y);
```

Here is the result.

```
a = 1
b = 2
c = [4, 5, 6]
d = 20
e = 30
f = 300
x = 20
y = {"a":30,"b":300}
```

#### Pattern Matching

When it is an assignment expresison, the pattern matching is available.
If a part of variables is a literal, it will be checked if the same value.
And if matching a pattern is failed, the exdeption of `NoMatchingPatternException` will be raised.

Here is an example.

```javascript
[a, b, , ...c] = [1, 2, 3, 4, 5, 6];
{ x, y } = { x: 20, y: { a: 30, b: 300 } };
{ x: d, y: { a: e, b: 300 } } = { x: 20, y: { a: 30, b: 300 } };

System.println("a = ", a);
System.println("b = ", b);
System.println("c = ", c);
System.println("d = ", d);
System.println("e = ", e);
System.println("x = ", x);
System.println("y = ", y);

// => .y.b requires 300, but it is 3 in actual.
{ x: d, y: { a: e, b: 300 } } = { x: 20, y: { a: 30, b: 3 } };
```

Here is the result.

```
a = 1
b = 2
c = [4, 5, 6]
d = 20
e = 30
x = 20
y = {"a":30,"b":300}
Uncaught exception: No one catch the exception.
NoMatchingPatternException: Pattern not matched
Stack Trace Information:
        at <main-block>(test.kx:14)
```

##### Range in Pattern Matching

If you write a Range in a pattern, it will check inside that Range.

Here is an example.

```javascript
[1..10, b] = [1, 100];  // b => 100
[1..10, b] = [2, 100];  // b => 100
[1..10, b] = [9, 100];  // b => 100
[1..10, b] = [11, 100]; // NoMatchingPatternException will occur.
```

## Examples

### Example 1. Scope (1)

#### Code

```javascript
var a = 10;
var b;
{
    var a;
    a = b = 100;
    System.println(a);  // => 100
    System.println(b);  // => 100
}
System.println(a);  // => 10
System.println(b);  // => 100
```

#### Result

```
100
100
10
100
```

### Example 2. Scope (2)

#### Code

```javascript
var a = 10;
{
    a = b = 100;
    System.println(a);  // => 100
    System.println(b);  // => 100
}
System.println(a);  // => 10
System.println(b);  // => ???
```

#### Result

```
Error: Symbol(b) is not found near the <test.kx>:8
```

### Example 3. Array & Object Style

#### Code

```javascript
[a, b, , ...c] = [1, 2, 3, 4, 5, 6];  // 3rd parameter is skipped.
{ x, y } = { x: 20, y: { a: 30, b: 300 } };
{ x: d, y: { a: e, b: f } } = { x: 20, y: { a: 30, b: 300 } };

System.println("a = ", a);
System.println("b = ", b);
System.println("c = ", c);
System.println("d = ", d);
System.println("e = ", e);
System.println("f = ", f);
System.println("x = ", x);
System.println("y = ", y);
```

#### Result

```
a = 1
b = 2
c = [4, 5, 6]
d = 20
e = 30
f = 300
x = 20
y = {"a":30,"b":300}
```

### Example 4. Pattern Matching

#### Code

```javascript
[a, b, , ...c] = [1, 2, 3, 4, 5, 6];
{ x, y } = { x: 20, y: { a: 30, b: 300 } };
{ x: d, y: { a: e, b: 300 } } = { x: 20, y: { a: 30, b: 300 } };

System.println("a = ", a);
System.println("b = ", b);
System.println("c = ", c);
System.println("d = ", d);
System.println("e = ", e);
System.println("x = ", x);
System.println("y = ", y);

// => .y.b requires 300, but it is 3 in actual.
{ x: d, y: { a: e, b: 300 } } = { x: 20, y: { a: 30, b: 3 } };
```

#### Result

```
a = 1
b = 2
c = [4, 5, 6]
d = 20
e = 30
x = 20
y = {"a":30,"b":300}
Uncaught exception: No one catch the exception.
NoMatchingPatternException: Pattern not matched
Stack Trace Information:
        at <main-block>(test.kx:14)
```

### Example 5. Range in Pattern

#### Code

```javascript
[1..10, b] = [1, 100];  // b => 100
[1..10, c] = [2, 100];  // c => 100
[1..10, d] = [9, 100];  // d => 100
System.println("b = ", b);
System.println("c = ", c);
System.println("d = ", d);

[1..10, b] = [11, 100]; // NoMatchingPatternException will occur.
```

#### Result

```
b = 100
c = 100
d = 100
Uncaught exception: No one catch the exception.
NoMatchingPatternException: Pattern not matched
Stack Trace Information:
        at <main-block>(test.kx:8)
```
