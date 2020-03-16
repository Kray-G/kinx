
# Return statement

## Overview

`yield` statement is near `return` statement,
but a function will be continued from the next statement of `yield` when calling again after returning back from a function by `yield`.
This mechanism is provided as [Fiber](statement/fiber.md).

```javascript
var fiber = new Fiber(&{
    System.println(1);
    yield;
    System.println(2);
    yield;
    System.println(3);
});
System.println(10);
fiber.resume();
System.println(20);
fiber.resume();
System.println(30);
fiber.resume();
System.println(40);
// 10
// 1
// 20
// 2
// 30
// 3
// 40
```

### Expession

`yield` statement can have any expression and returning the evaluated value to caller function.
If there is no expression, `null` will be returned Implicitly.

```javascript
var fiber = new Fiber(&{
    yield 10;   // returns 10.
    yield;      // returns null.
});
System.println((a = fiber.resume()).isUndefined ? "null" : a);  // 10
System.println((a = fiber.resume()).isUndefined ? "null" : a);  // null
```

### Evaluated `yield`

The method `resume()` of Fiber can have arguments, and give those as function arguments or a return value of `yield` statement.
When it is a return value of `yield`, it will be an array.

```javascript
var fiber = new Fiber(&(a, ...b) => {
    [a] = yield;            // a = 10.
    [a, ...b] = yield;      // a = 10, b = [20, 30].
});
fiber.resume(10, 20, 30); // first call
fiber.resume(10, 20, 30);
fiber.resume(10, 20, 30);
```

### if-modifier

`yield` statement can have `if-modifier`.
See the example below.


```javascript
yield 10 if (a < 10);   // return 10 if `a` is less than 10.
c = yield if (b < 10);  // return null if `b` is less than 10.
```

## Examples

### Example 1. Normal case

#### Code

```javascript
var fiber = new Fiber(&{
    System.println(1);
    yield;
    System.println(2);
    yield;
    System.println(3);
});
System.println(10);
fiber.resume();
System.println(20);
fiber.resume();
System.println(30);
fiber.resume();
System.println(40);
```

#### Result

```
10
1
20
2
30
3
40
```

### Example 2. Without expression

#### Code

```javascript
var fiber = new Fiber(&{
    yield 10;   // returns 10.
    yield;      // returns null.
});
System.println((a = fiber.resume()).isUndefined ? "null" : a);  // 10
System.println((a = fiber.resume()).isUndefined ? "null" : a);  // null
```

#### Result

```
10
null
```

### Example 3. if-modifier (1)

#### Code

```javascript
var fiber = new Fiber(&(a) => {
    yield if (a < 10);
    [a] = yield a * 20; // 8 * 20
    return a * 30;  // 10 * 30
});
System.println((a = fiber.resume( 8)).isUndefined ? "null" : a);
System.println((a = fiber.resume( 9)).isUndefined ? "null" : a);
System.println((a = fiber.resume(10)).isUndefined ? "null" : a);
```

#### Result

```
null
160
300
```

### Example 4. if-modifier (2)

#### Code

```javascript
var fiber = new Fiber(&(a) => {
    yield if (a < 10);
    yield a * 20;       // 12 * 20
    [a] = yield a * 30; // 12 * 30
    return a * 40;      // 10 * 40
});
System.println((a = fiber.resume(12)).isUndefined ? "null" : a);
System.println((a = fiber.resume( 9)).isUndefined ? "null" : a);
System.println((a = fiber.resume(10)).isUndefined ? "null" : a);
```

#### Result

```
240
360
400
```

### Example 5. `yield` returns array.

#### Code

```javascript
var fiber = new Fiber(&{
    [a, b, ...c] = yield;
    System.println(a);
    System.println(b);
    System.println(c[0]);
    System.println(c[1]);
    System.println(c[2]);
});
fiber.resume(); // first call
fiber.resume(1, 2, 3, 4, 5);
```

#### Result

```
1
2
3
4
5
```
