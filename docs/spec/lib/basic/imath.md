# Math

## Overview

`Math` is a library for mathematics.
The same methods are bound to the special object of Integer and Double,
so you don't have to use `Math` instead of those. For example, you can use;

```javascript
var a = 2.pow(10);     // Math.pow(2, 10)   => 1024
var b = 2.0.pow(10);   // Math.pow(2.0, 10) => 1024
var c = (-10).abs();   // Math.abs(-10)     => 10
```

As an unary minus is lower priority than the function call,
you need parentheses for `-10` above. You can also use `random()` with the receiver of Integer or Double,
but the receiver does not mean anything.

```javascript
var a = 1000.random(); // 1000 is nothing to mean.
var b = 10.0.random(); // 10.0 is nothing to mean.
var c = Math.random(); // Normal.
```

## Math Functions

Here are methods of Math.
By the way, the first argument is `x` and the second argument is `y` below.

|        Method        |                                        Meaning                                        |
| -------------------- | ------------------------------------------------------------------------------------- |
| Math.sin(dbl)        | $$\sin x$$                                                                            |
| Math.cos(dbl)        | $$\cos x$$                                                                            |
| Math.tan(dbl)        | $$\tan x$$                                                                            |
| Math.asin(dbl)       | $$\theta$$ for $$\sin \theta=x$$                                                      |
| Math.acos(dbl)       | $$\theta$$ for $$\cos \theta=x$$                                                      |
| Math.atan(dbl)       | $$\theta$$ for $$\tan \theta=x$$                                                      |
| Math.atan2(dbl, dbl) | the angle between the positive x axis and the ray to the point $$(x, y) \neq (0, 0)$$ |
| Math.sinh(dbl)       | $$\sinh x$$                                                                           |
| Math.cosh(dbl)       | $$\cosh x$$                                                                           |
| Math.tanh(dbl)       | $$\tanh x$$                                                                           |
| Math.exp(dbl)        | $$e^x$$                                                                               |
| Math.ldexp(dbl, int) | $$x \times 2^y$$                                                                      |
| Math.log(dbl)        | $$\log_e x$$                                                                          |
| Math.log10(dbl)      | $$\log_{10} x$$                                                                       |
| Math.pow(dbl, dbl)   | $$x^y$$                                                                               |
| Math.sqrt(dbl)       | $$\sqrt x$$                                                                           |
| Math.ceil(dbl)       | Minimum value of integer over $$x$$ by Double                                         |
| Math.floor(dbl)      | Maximum value of integer under $$x$$ by Double                                        |
| Math.fmod(dbl, dbl)  | Floating point remainder for $$x \div y$$                                             |
| Math.abs(dbl)        | Absolute value of $$x$$ by Double                                                     |
| Math.random()        | Random value between $$0 \leq r < 1$$                                                 |

> Look at above with LaTeX in your brain...

## Examples

### Example 1. acos

#### Code

```javascript
function calc1(n) {
    return Math.acos(n);
}
function calc2(n) {
    return n.acos();
}
function calc3(n) {
    return Math.acos(n);
}
function calc4(n) {
    return n.acos();
}
var r1 = Math.acos(0.8);
var r2 = Math.acos(0);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(0) % r2);
System.println("%g, should be %g" % calc4(0) % r2);
```

#### Result

```
0.643501, should be 0.643501
0.643501, should be 0.643501
1.5708, should be 1.5708
1.5708, should be 1.5708
```

### Example 2. asin

#### Code

```javascript
function calc1(n) {
    return Math.asin(n);
}
function calc2(n) {
    return n.asin();
}
function calc3(n) {
    return Math.asin(n);
}
function calc4(n) {
    return n.asin();
}
var r1 = Math.asin(0.8);
var r2 = Math.asin(1);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(1) % r2);
System.println("%g, should be %g" % calc4(1) % r2);
```

#### Result

```
0.927295, should be 0.927295
0.927295, should be 0.927295
1.5708, should be 1.5708
1.5708, should be 1.5708
```

### Example 3. atan

#### Code

```javascript
function calc1(n) {
    return Math.atan(n);
}
function calc2(n) {
    return n.atan();
}
function calc3(n) {
    return Math.atan(n);
}
function calc4(n) {
    return n.atan();
}
var r1 = Math.atan(0.8);
var r2 = Math.atan(1);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(1) % r2);
System.println("%g, should be %g" % calc4(1) % r2);
```

#### Result

```
0.674741, should be 0.674741
0.674741, should be 0.674741
0.785398, should be 0.785398
0.785398, should be 0.785398
```

### Example 4. atan2

#### Code

```javascript
function calc1(n) {
    return Math.atan2(n, 0.9);
}
function calc2(n) {
    return n.atan2(0.9);
}
function calc3(n) {
    return Math.atan2(n, 1);
}
function calc4(n) {
    return n.atan2(1);
}
var r1 = Math.atan2(0.8, 0.9);
var r2 = Math.atan2(1, 1);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(1) % r2);
System.println("%g, should be %g" % calc4(1) % r2);
```

#### Result

```
0.726642, should be 0.726642
0.726642, should be 0.726642
0.785398, should be 0.785398
0.785398, should be 0.785398
```

### Example 5. cos

#### Code

```javascript
function calc1(n) {
    return Math.cos(n);
}
function calc2(n) {
    return n.cos();
}
function calc3(n) {
    return Math.cos(n);
}
function calc4(n) {
    return n.cos();
}
var r1 = Math.cos(0.8);
var r2 = Math.cos(1);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(1) % r2);
System.println("%g, should be %g" % calc4(1) % r2);
```

#### Result

```
0.696707, should be 0.696707
0.696707, should be 0.696707
0.540302, should be 0.540302
0.540302, should be 0.540302
```

### Example 6. sin

#### Code

```javascript
function calc1(n) {
    return Math.sin(n);
}
function calc2(n) {
    return n.sin();
}
function calc3(n) {
    return Math.sin(n);
}
function calc4(n) {
    return n.sin();
}
var r1 = Math.sin(0.8);
var r2 = Math.sin(1);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(1) % r2);
System.println("%g, should be %g" % calc4(1) % r2);
```

#### Result

```
0.717356, should be 0.717356
0.717356, should be 0.717356
0.841471, should be 0.841471
0.841471, should be 0.841471
```

### Example 7. tan

#### Code

```javascript
function calc1(n) {
    return Math.tan(n);
}
function calc2(n) {
    return n.tan();
}
function calc3(n) {
    return Math.tan(n);
}
function calc4(n) {
    return n.tan();
}
var r1 = Math.tan(0.8);
var r2 = Math.tan(1);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(1) % r2);
System.println("%g, should be %g" % calc4(1) % r2);
```

#### Result

```
1.02964, should be 1.02964
1.02964, should be 1.02964
1.55741, should be 1.55741
1.55741, should be 1.55741
```

### Example 8. cosh

#### Code

```javascript
function calc1(n) {
    return Math.cosh(n);
}
function calc2(n) {
    return n.cosh();
}
function calc3(n) {
    return Math.cosh(n);
}
function calc4(n) {
    return n.cosh();
}
var r1 = Math.cosh(0.8);
var r2 = Math.cosh(1);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(1) % r2);
System.println("%g, should be %g" % calc4(1) % r2);
```

#### Result

```
1.33743, should be 1.33743
1.33743, should be 1.33743
1.54308, should be 1.54308
1.54308, should be 1.54308
```

### Example 9. sinh

#### Code

```javascript
function calc1(n) {
    return Math.sinh(n);
}
function calc2(n) {
    return n.sinh();
}
function calc3(n) {
    return Math.sinh(n);
}
function calc4(n) {
    return n.sinh();
}
var r1 = Math.sinh(0.8);
var r2 = Math.sinh(1);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(1) % r2);
System.println("%g, should be %g" % calc4(1) % r2);
```

#### Result

```
0.888106, should be 0.888106
0.888106, should be 0.888106
1.1752, should be 1.1752
1.1752, should be 1.1752
```

### Example 10. tanh

#### Code

```javascript
function calc1(n) {
    return Math.tanh(n);
}
function calc2(n) {
    return n.tanh();
}
function calc3(n) {
    return Math.tanh(n);
}
function calc4(n) {
    return n.tanh();
}
var r1 = Math.tanh(0.8);
var r2 = Math.tanh(1);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(1) % r2);
System.println("%g, should be %g" % calc4(1) % r2);
```

#### Result

```
0.664037, should be 0.664037
0.664037, should be 0.664037
0.761594, should be 0.761594
0.761594, should be 0.761594
```

### Example 11. exp

#### Code

```javascript
function calc1(n) {
    return Math.exp(n);
}
function calc2(n) {
    return n.exp();
}
function calc3(n) {
    return Math.exp(n);
}
function calc4(n) {
    return n.exp();
}
var r1 = Math.exp(0.8);
var r2 = Math.exp(1);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(1) % r2);
System.println("%g, should be %g" % calc4(1) % r2);
```

#### Result

```
2.22554, should be 2.22554
2.22554, should be 2.22554
2.71828, should be 2.71828
2.71828, should be 2.71828
```

### Example 12. ldexp

#### Code

```javascript
function calc1(n) {
    return Math.ldexp(n, 10.0);
}
function calc2(n) {
    return n.ldexp(10.0);
}
function calc3(n) {
    return Math.ldexp(n, 10);
}
function calc4(n) {
    return n.ldexp(10);
}
var r1 = Math.ldexp(2.1, 10.0);
var r2 = Math.ldexp(2, 10);
System.println("%g, should be %g" % calc1(2.1) % r1);
System.println("%g, should be %g" % calc2(2.1) % r1);
System.println("%g, should be %g" % calc3(2) % r2);
System.println("%g, should be %g" % calc4(2) % r2);
```

#### Result

```
2150.4, should be 2150.4
2150.4, should be 2150.4
2048, should be 2048
2048, should be 2048
```

### Example 12. log

#### Code

```javascript
function calc1(n) {
    return Math.log(n);
}
function calc2(n) {
    return n.log();
}
function calc3(n) {
    return Math.log(n);
}
function calc4(n) {
    return n.log();
}
var r1 = Math.log(0.8);
var r2 = Math.log(10);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(10) % r2);
System.println("%g, should be %g" % calc4(10) % r2);
```

#### Result

```
-0.223144, should be -0.223144
-0.223144, should be -0.223144
2.30259, should be 2.30259
2.30259, should be 2.30259
```

### Example 13. log10

#### Code

```javascript
function calc1(n) {
    return Math.log10(n);
}
function calc2(n) {
    return n.log10();
}
function calc3(n) {
    return Math.log10(n);
}
function calc4(n) {
    return n.log10();
}
var r1 = Math.log10(0.8);
var r2 = Math.log10(100);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(100) % r2);
System.println("%g, should be %g" % calc4(100) % r2);
```

#### Result

```
-0.09691, should be -0.09691
-0.09691, should be -0.09691
2, should be 2
2, should be 2
```

### Example 14. pow

#### Code

```javascript
function calc1(n) {
    return Math.pow(n, 10.0);
}
function calc2(n) {
    return n.pow(10.0);
}
function calc3(n) {
    return Math.pow(n, 10);
}
function calc4(n) {
    return n.pow(10);
}
var r1 = Math.pow(2.1, 10.0);
var r2 = Math.pow(2, 10);
System.println("%g, should be %g" % calc1(2.1) % r1);
System.println("%g, should be %g" % calc2(2.1) % r1);
System.println("%g, should be %g" % calc3(2) % r2);
System.println("%g, should be %g" % calc4(2) % r2);
```

#### Result

```
1667.99, should be 1667.99
1667.99, should be 1667.99
1024, should be 1024
1024, should be 1024
```

### Example 15. sqrt

#### Code

```javascript
function calc1(n) {
    return Math.sqrt(n);
}
function calc2(n) {
    return n.sqrt();
}
function calc3(n) {
    return Math.sqrt(n);
}
function calc4(n) {
    return n.sqrt();
}
var r1 = Math.sqrt(0.8);
var r2 = Math.sqrt(100);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(100) % r2);
System.println("%g, should be %g" % calc4(100) % r2);
```

#### Result

```
0.894427, should be 0.894427
0.894427, should be 0.894427
10, should be 10
10, should be 10
```

### Example 16. abs

#### Code

```javascript
function calc1(n) {
    return Math.abs(n);
}
function calc2(n) {
    return n.abs();
}
function calc3(n) {
    return Math.abs(n);
}
function calc4(n) {
    return n.abs();
}
var r1 = Math.abs(-0.8);
var r2 = Math.abs(100);
System.println("%g, should be %g" % calc1(-0.8) % r1);
System.println("%g, should be %g" % calc2(-0.8) % r1);
System.println("%g, should be %g" % calc3(100) % r2);
System.println("%g, should be %g" % calc4(100) % r2);
```

#### Result

```
0.8, should be 0.8
0.8, should be 0.8
100, should be 100
100, should be 100
```

### Example 17. ceil

#### Code

```javascript
function calc1(n) {
    return Math.ceil(n);
}
function calc2(n) {
    return n.ceil();
}
function calc3(n) {
    return Math.ceil(n);
}
function calc4(n) {
    return n.ceil();
}
var r1 = Math.ceil(0.8);
var r2 = Math.ceil(100);
System.println("%g, should be %g" % calc1(0.8) % r1);
System.println("%g, should be %g" % calc2(0.8) % r1);
System.println("%g, should be %g" % calc3(100) % r2);
System.println("%g, should be %g" % calc4(100) % r2);
```

#### Result

```
1, should be 1
1, should be 1
100, should be 100
100, should be 100
```

### Example 18. floor

#### Code

```javascript
function calc1(n) {
    return Math.floor(n);
}
function calc2(n) {
    return n.floor();
}
function calc3(n) {
    return Math.floor(n);
}
function calc4(n) {
    return n.floor();
}
var r1 = Math.floor(2.8);
var r2 = Math.floor(100);
System.println("%g, should be %g" % calc1(2.8) % r1);
System.println("%g, should be %g" % calc2(2.8) % r1);
System.println("%g, should be %g" % calc3(100) % r2);
System.println("%g, should be %g" % calc4(100) % r2);
```

#### Result

```
2, should be 2
2, should be 2
100, should be 100
100, should be 100
```

### Example 19. fmod

#### Code

```javascript
function calc1(n) {
    return Math.fmod(n, 10.0);
}
function calc2(n) {
    return n.fmod(10.0);
}
function calc3(n) {
    return Math.fmod(n, 10);
}
function calc4(n) {
    return n.fmod(10);
}
var r1 = Math.fmod(202.1, 10.0);
var r2 = Math.fmod(202, 10);
System.println("%g, should be %g" % calc1(202.1) % r1);
System.println("%g, should be %g" % calc2(202.1) % r1);
System.println("%g, should be %g" % calc3(202) % r2);
System.println("%g, should be %g" % calc4(202) % r2);
```

#### Result

```
2.1, should be 2.1
2.1, should be 2.1
2, should be 2
2, should be 2
```
