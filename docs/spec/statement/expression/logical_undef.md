# Logical UNDEF Operator

## Overview

Logical Undef operator is a shortcut operator and this operator is like Logical OR operator of `||`.
When using `||` and LHS is `false`, the RHS will be evaluated.
Compared to that, whe using `??` and LHS is `null`, the RHS will be evaluated.

The `false` meaning is wider than undefined/null,
that is why the `??` is very useful especially when you destingish between 0 and `null`.

```javascript
var b = a ?? 0; // initializing 0 when a is uninitialized.
```

This can be also used with assignment operator as `??=`.

```javascript
a ??= new A();  // creating an instance only when a is uninitialized.
```

## Examples

### Example 1. Simple use

#### Code

```javascript
function test(a) {
    return a ?? 10;
}

System.println(test(0));
System.println(test(1));
System.println(test(null));
```

#### Result

```
0
1
10
```

### Example 2. With assignment

#### Code

```javascript
var id;
class A() { @id = id++; }

function test(a) {
    a ??= new A();
    return a;
}

var a;
id = 10;
System.println((a = test(a)).id);
System.println((a = test(a)).id);
System.println((a = test(a)).id);
```

#### Result

```
10
10
10
```
