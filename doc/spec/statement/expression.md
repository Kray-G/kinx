# Expression statement

## Overview

Expression statement is the expression of assignments, calculations, calling functions, accessing objects, and so on.
This statement would be a main statement of the program.

```javascript
f(10);
a = 2 * getValueOf(holder);
```

### Priority

Expression has a priority about a calculation order.
Here is the order to calculate values.

|   #   |     Type      |                                                   Excample                                                    |  Evaluation   |
| :---: | ------------- | ------------------------------------------------------------------------------------------------------------- | :-----------: |
|   1   | Factor        | Variable, Number, String, ...                                                                                 |       -       |
|   2   | Postfix       | `++`, `--`, `[]`, `.`, `()`                                                                                   | left to right |
|   3   | Prefix        | `!`, `+`, `-`, `*`, `++`, `--`                                                                                | left to right |
|   4   | Matching      | `=~`, `!~`                                                                                                    | left to right |
|   5   | Exponent      | `**`                                                                                                          | right to left |
|   6   | Mul,...       | `*`, `/`, `%`                                                                                                 | left to right |
|   7   | Add,...       | `+`, `-`                                                                                                      | left to right |
|   8   | Shift         | `<<`, `>>`                                                                                                    | left to right |
|   9   | Compare       | `<`, `>`, `>=`, `<=`                                                                                          | left to right |
|  10   | Equals        | `==`, `!=`                                                                                                    | left to right |
|  11   | Bit AND       | `&`                                                                                                           | left to right |
|  12   | Bit XOR       | `^`                                                                                                           | left to right |
|  13   | Bit OR        | <code>&#124;</code>                                                                                           | left to right |
|  14   | Logical AND   | `&&`                                                                                                          | left to right |
|  15   | Logical OR    | <code>&#124;&#124;</code>                                                                                     | left to right |
|  16   | Logical UNDEF | `??`                                                                                                          | left to right |
|  17   | Ternary, ...  | ` ? : `, `function(){}`                                                                                       | left to right |
|  18   | Assignment    | `=`, `+=`, `-=`, `*=`. `/=`. `%=`, `&=`, <code>&#124;=</code>, `^=`, `&&=`, <code>&#124;&#124;=</code>, `??=` | right to left |

In this list, only for exponent operator and assignment operator the evaluation direction is right to left.
Otherwise it is left to right.

## Expressions/Operations

The individual operations are described below.

*   [Assignment](expression/assign.md)
*   [Ternary Expression](expression/ternary.md)
*   [Logical UNDEF Operation](expression/logical_undef.md)
*   [Logical OR Operation](expression/logical_or.md)
*   [Logical AND Operation](expression/logical_and.md)
*   [Bit OR Operation](expression/bitl_or.md)
*   [Bit XOR Operation](expression/bit_xor.md)
*   [Bit AND Operation](expression/bit_and.md)
*   [Comparison](expression/Comparison.md)
*   [Bit Shift Operation](expression/bit_shift.md)
*   [Addition/Subtraction](expression/add_sub.md)
*   [Multiplication/Division](expression/mul_div.md)
*   [Exponentiation](expression/exponent.md)
*   [Matching Operation](expression/matching.md)
*   [Unary Expression](expression/prefix.md)
*   [Postfix Operation](expression/postfix.md)

### Special Description

Almost all operators above may be familiar with programmers, but some of operators will be not.
Here is describing those.

#### Unary `*` - Convert Operator

`*` of unary expression means a convert operator.
This operator works as below.

|       From        |        To        |                                             Example                                             |
| ----------------- | ---------------- | ----------------------------------------------------------------------------------------------- |
| Integer           | String           | `*97` -> `'a'`                                                                                  |
| BigInteger        | String           | `*122013682599111006870123878542304692625357` -> `'122013682599111006870123878542304692625357'` |
| Double            | String           | `*1.2` -> `'1.2'`                                                                               |
| String            | Array            | `*'abc'` -> `[97, 98, 99]`                                                                      |
| Binary            | String           | `*<97, 98, 99>` -> `'abc'`                                                                      |
| Object(Formatter) | Formatted String | `*('abc%s' % 'xyz')` -> `'abcxyz'`                                                              |
| Array(non-Object) | String           | `*[97, 98, 99]` -> `'abc'`                                                                      |
| ... Otherwise     | null             |                                                                                                 |

#### `**` - Exponent Operator

Exponent operator is also provided in Math libarary as `Math.pow`.
This operator is provided for easy to use instead of that function.
Note that the evaluation direction is right to left.
It is based on the mathematical conventions.

Here is the example.

```javascript
a = 2 ** 3 ** 4;    // means 2 ** (3 ** 4), not (2 ** 3) ** 4.
                    //  should be 2417851639229258349412352.
```

#### `??` - Logical Undefined Operator

This operator is like Logical OR operator of `||`.
When using `||` and LHS is `false`, the RHS will be evaluated.
Compared to that, whe using `??` and LHS is `null`, the RHS will be evaluated.

The `false` meaning is wider than undefined,
that is why the `??` is very useful especially when you destingish between 0 and `null`.

Note that undefined and `null` is the same in Kinx.

This operator can be used as assignment by writing `??=` because it is shortcut operator same as `||`.

```javascript
var a;
a ||= 0;    // => 0
a ||= 10;   // => 10
var b;
b ??= 0;    // => 0
b ??= 10;   // => 0
```

## Examples

### Example 1. Assignment

#### Code

```javascript
a = 10 * 20;
System.println(a);
```

#### Result

```
200
```

### Example 2. Exponent Evaluation

#### Code

```javascript
a = 2 ** 3 ** 4;
System.println(a);
```

#### Result

```
2417851639229258349412352
```

### Example 3. Logical Undefined Operator

#### Code

```javascript
var a;
a ||= 0;    // => 0
a ||= 10;   // => 10
System.println(a);
var b;
b ??= 0;    // => 0
b ??= 10;   // => 0
System.println(b);
```

#### Result

```
10
0
```


