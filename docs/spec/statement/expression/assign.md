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
Error: Symbol(b) is not found near the test.kx:8
```
