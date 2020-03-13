
# Enum statement

## Overview

`enum` statement is used as declaration for naming an integer value.
Usually, the direct integer value is what everybody wants to avoid
because it shows nothing about a meaning.

`enum` can provide a meaning to an integer number.

```javascript
enum {
    A,      // Starting from 0 if not specified the number.
    B,
    C = 10, // Changing the value to be 10.
    D       // Next value should be 11.
}
```

The actual number is started from 0, but you can change the number with initializer.
Initializer can be put to any enum names.

## Examples

### Example 1. Normal case

#### Code

```javascript
enum { A, B, C, D }
System.println(A);
System.println(B);
System.println(C);
System.println(D);
```

#### Result

```
0
1
2
3
```

### Example 2. With initializer (1)

#### Code

```javascript
enum { A=100, B, C, D }
System.println(A);
System.println(B);
System.println(C);
System.println(D);
```

#### Result

```
100
101
102
103
```

### Example 3. With initializer (2)

#### Code

```javascript
enum { A=1000, B, C=2000, D }
System.println(A);
System.println(B);
System.println(C);
System.println(D);
```

#### Result

```
1000
1001
2000
2001
```
