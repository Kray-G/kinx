
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
