
# Declaration statement

## Overview

Declaration statement is the statement to declare variables.

```javascript
var a; // initializing 'a' to null
```

### Declaration with initializer

Declaration of a variable has initializer to initialize it.
If there is no initializer, the variable should be `null` automatically.

```javascript
var a = 10; // initializing 'a' to 10 as integer.
```

### Multiple declaration of variables

Multiple variables can be put in one declaration statement separated by `,`.
Each variable can have its own initializer, or can have no initializer.

```javascript
var a, b;
var x = 10, y;
```

### Constant value

Variable can be constant by declaration with `const`.

```javascript
const a = 10; // initializing 'a' to 10 as integer and it is constant value.
```

Constant value can not be modified and it will be compile error when trying to change that variable's value.

```javascript
const a = 10;
a = 20; // error.
```

### Destructuring assignment

Destructuring assignment is supported and spread/rest operator is also available.
But destructuring assignment for Object is not supported.

```javascript
var [a, ...b] = [10, 20, 30];
// => a == 10
// => b == [20, 30]
```

Of course, assignment is rejected when it declared as `const`.

```javascript
const [a, ...b] = [10, 20, 30];
a = 10; // error.
```

## Examples

### Example 1. Normal case

#### Code

```javascript
var a;
System.println(a.isUndefined ? "null" : "defined");
```

#### Result

```
null
```

### Example 2. With initializer

#### Code

```javascript
var a = 5;
System.println(a);
```

#### Result

```
5
```

### Example 3. With initializer of expression

#### Code

```javascript
function pow8(n) {
    return n ** 8;
}

var a = "2 ** 8 = " + pow8(2);
System.println(a);
```

#### Result

```
2 ** 8 = 256
```

### Example 4. Multiple variable declaration

#### Code

```javascript
var a, b = 10, c, d = "abc";
System.println(a.isUndefined ? "null" : a);
System.println(b.isUndefined ? "null" : b);
System.println(c.isUndefined ? "null" : c);
System.println(d.isUndefined ? "null" : d);
```

#### Result

```
null
10
null
abc
```

### Example 5. Constant value (1)

#### Code

```javascript
const a = 10;
a = 20;
```

#### Result

```
Error: Can not assign a value to the 'const' variable near the test.kx:2
```

### Example 6. Constant value (2)

#### Code

If you did not initialize a constant variable, you can initialize it only one time by assignment.

```javascript
const a;
a = 20;
System.println(a);
```

#### Result

```
20
```

### Example 7. Constant value (3)

#### Code

It should be error when initializing twice.

```javascript
const a;
a = 20;
a = 30; // error.
```

#### Result

```
Error: Can not assign a value to the 'const' variable near the test.kx:3
```

### Example 7. Constant value (4)

#### Code

Even if it is Object, it should be compile error.

```javascript
const a = { x: 10 };
a = { y: 20 };
```

#### Result

```
Error: Can not assign a value to the 'const' variable near the test.kx:2
```

### Example 6. Constant value (5)

#### Code

But the object member can be modified.

```javascript
const a = { x: 10 };
a.x = 20;
System.println(a.x);
```

#### Result

```
20
```

### Example 7. Destructuring assignment (1)

#### Code

```javascript
var [a, ...b] = [10, 20, 30];
System.println(a);
System.println(b[1]);
```

#### Result

```
10
30
```

### Example 7. Destructuring assignment (2)

#### Code

```javascript
const [a, ...b] = [10, 20, 30];
a = 10;
b = 20;
```

#### Result

```
Error: Can not assign a value to the 'const' variable near the test.kx:2
Error: Can not assign a value to the 'const' variable near the test.kx:3
```
