
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

### Scope

`enum` is alive in a scope.
The scope is defined in a Function, in a Class, in a Module, and in a Namespace.
The value for the name is overwritten when the name is redefined in a nested scope,
and when scoped out, the value will be back.

```javascript
enum {
    C_VAL_UNKNOWN, C_VAL_INTEGER, C_VAL_STRING,
}

namespace X {
    // redefined the names.
    enum {
        C_VAL_UNKNOWN = 100, C_VAL_INTEGER, C_VAL_STRING,
    }
}

// C_VAL_UNKNOWN should be 0.
```

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

### Example 4. The scope

#### Code


```javascript
enum {
    C_VAL_UNKNOWN, C_VAL_INTEGER, C_VAL_STRING,
}

namespace X {

    enum {
        C_VAL_UNKNOWN = 100, C_VAL_INTEGER, C_VAL_STRING,
    }

    System.println(C_VAL_UNKNOWN);  // => 100
    System.println(C_VAL_INTEGER);  // => 101
    System.println(C_VAL_STRING);   // => 102

}

System.println(C_VAL_UNKNOWN);  // => 0
System.println(C_VAL_INTEGER);  // => 1
System.println(C_VAL_STRING);   // => 2
```

#### Result

```
100
101
102
0
1
2
```

### Example 5. The scope

#### Code


```javascript
enum {
    C_VAL_UNKNOWN = -100,
    C_VAL_INTEGER,
    C_VAL_STRING,
}

System.println(C_VAL_UNKNOWN);  // => -100
System.println(C_VAL_INTEGER);  // => -99
System.println(C_VAL_STRING);   // => -98
```

#### Result

```
-100
-99
-98
```
