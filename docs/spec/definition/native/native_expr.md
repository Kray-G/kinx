# Basic Expression in Native

## Overview

Native function can do some expressions like a normal function.
Here are supported operations.

* Addition, subtraction, multiplication, division, and modulo operation for integer.
* Addition, subtraction, multiplication, division, and modulo operation for double.
* Addition, and multiplication by integer for string.

## Examples

### Example 1. For integer (1)

#### Code

```javascript
native add(a, b) { return a + b; }
native sub(a, b) { return a - b; }
native mul(a, b) { return a * b; }
native div(a, b) { return a / b; }
native mod(a, b) { return a % b; }
System.println(add(10, 20));
System.println(sub(10, 20));
System.println(mul(10, 20));
System.println(div(10, 20));
System.println(mod(10, 20));
```

#### Result

```
30
-10
200
0
10
```

### Example 2. For integer (2)

#### Code

```javascript
native add(a, b) { return a + b; }
native sub(a, b) { return a - b; }
native mul(a, b) { return a * b; }
native div(a, b) { return a / b; }
native mod(a, b) { return a % b; }
System.println(add(103, 20));
System.println(sub(103, 20));
System.println(mul(103, 20));
System.println(div(103, 20));
System.println(mod(103, 20));
```

#### Result

```
123
83
2060
5
3
```

### Example 3. For integer (3)

#### Code

```javascript
native add(a, b) { return a + b; }
native sub(a, b) { return a - b; }
native mul(a, b) { return a * b; }
native div(a, b) { return a / b; }
native mod(a, b) { return a % b; }
System.println(add(-103, 20));
System.println(sub(-103, 20));
System.println(mul(-103, 20));
System.println(div(-103, 20));
System.println(mod(-103, 20));
```

#### Result

```
-83
-123
-2060
-5
-3
```

### Example 4. For double (1)

#### Code

```javascript
native:dbl add(a:dbl, b:dbl) { return a + b; }
native:dbl sub(a:dbl, b:dbl) { return a - b; }
native:dbl mul(a:dbl, b:dbl) { return a * b; }
native:dbl div(a:dbl, b:dbl) { return a / b; }
native:dbl mod(a:dbl, b:dbl) { return a % b; }
System.println(add(10, 20));
System.println(sub(10, 20));
System.println(mul(10, 20));
System.println(div(10, 20));
System.println(mod(10, 20));
```

#### Result

```
30
-10
200
0.5
10
```

### Example 5. For double (2)

#### Code

```javascript
native:dbl add(a:dbl, b:dbl) { return a + b; }
native:dbl sub(a:dbl, b:dbl) { return a - b; }
native:dbl mul(a:dbl, b:dbl) { return a * b; }
native:dbl div(a:dbl, b:dbl) { return a / b; }
native:dbl mod(a:dbl, b:dbl) { return a % b; }
System.println(add(103, 20));
System.println(sub(103, 20));
System.println(mul(103, 20));
System.println(div(103, 20));
System.println(mod(103, 20));
```

#### Result

```
123
83
2060
5.15
3
```

### Example 6. For double (3)

#### Code

```javascript
native:dbl add(a:dbl, b:dbl) { return a + b; }
native:dbl sub(a:dbl, b:dbl) { return a - b; }
native:dbl mul(a:dbl, b:dbl) { return a * b; }
native:dbl div(a:dbl, b:dbl) { return a / b; }
native:dbl mod(a:dbl, b:dbl) { return a % b; }
System.println(add(-103, 20));
System.println(sub(-103, 20));
System.println(mul(-103, 20));
System.println(div(-103, 20));
System.println(mod(-103, 20));
```

#### Result

```
-83
-123
-2060
-5.15
-3
```

### Example 7. For string

#### Code

```javascript
native:str add(a:str, b:str) { return a + b; }
native:str mul(a:str, b) { return a * b; }
System.println(add("pre:", "post"));
System.println(mul("abc:", 5));
```

#### Result

```
pre:post
abc:abc:abc:abc:abc:
```
