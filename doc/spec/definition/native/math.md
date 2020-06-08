# Native `Math` functions

## Overview

In the native function, following `Math` function are supported.
Integer value can be also put instead of `dbl`, it will be automatically casted to double value.

|          Name          |     altanative     |            C prototype             |
| ---------------------- | ------------------ | ---------------------------------- |
| `Math.acos(dbl)`       | `(dbl).acos()`     | `double acos(double x)`            |
| `Math.asin(dbl)`       | `(dbl).asin()`     | `double asin(double x)`            |
| `Math.atan(dbl)`       | `(dbl).atan()`     | `double atan(double x)`            |
| `Math.atan2(dbl, dbl)` | `(dbl).atan2(dbl)` | `double atan2(double y, double x)` |
| `Math.cos(dbl)`        | `(dbl).cos()`      | `double cos(double x)`             |
| `Math.sin(dbl)`        | `(dbl).sin()`      | `double sin(double x)`             |
| `Math.tan(dbl)`        | `(dbl).tan()`      | `double tan(double x)`             |
| `Math.cosh(dbl)`       | `(dbl).cosh()`     | `double cosh(double x)`            |
| `Math.sinh(dbl)`       | `(dbl).sinh()`     | `double sinh(double x)`            |
| `Math.tanh(dbl)`       | `(dbl).tanh()`     | `double tanh(double x)`            |
| `Math.exp(dbl)`        | `(dbl).exp()`      | `double exp(double x)`             |
| `Math.ldexp(dbl, int)` | `(dbl).ldexp(int)` | `double ldexp(double x, int exp)`  |
| `Math.log(dbl)`        | `(dbl).log()`      | `double log(double x)`             |
| `Math.log10(dbl)`      | `(dbl).log10()`    | `double log10(double x)`           |
| `Math.pow(dbl, dbl)`   | `(dbl).pow(dbl)`   | `double pow(double x, double y)`   |
| `Math.sqrt(dbl)`       | `(dbl).sqrt()`     | `double sqrt(double x)`            |
| `Math.ceil(dbl)`       | `(dbl).ceil()`     | `double ceil(double x)`            |
| `Math.abs(dbl)`        | `(dbl).abs()`      | `double fabs(double x)`            |
| `Math.floor(dbl)`      | `(dbl).floor()`    | `double floor(double x)`           |
| `Math.fmod(dbl, dbl)`  | `(dbl).fmod(dbl)`  | `double fmod(double x, double y)`  |

## Examples

### Example 1. acos

#### Code

```javascript
native<dbl> calc1(n:dbl) {
    return Math.acos(n);
}
native<dbl> calc2(n:dbl) {
    return n.acos();
}
native<dbl> calc3(n) {
    return Math.acos(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.asin(n);
}
native<dbl> calc2(n:dbl) {
    return n.asin();
}
native<dbl> calc3(n) {
    return Math.asin(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.atan(n);
}
native<dbl> calc2(n:dbl) {
    return n.atan();
}
native<dbl> calc3(n) {
    return Math.atan(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.atan2(n, 0.9);
}
native<dbl> calc2(n:dbl) {
    return n.atan2(0.9);
}
native<dbl> calc3(n) {
    return Math.atan2(n, 1);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.cos(n);
}
native<dbl> calc2(n:dbl) {
    return n.cos();
}
native<dbl> calc3(n) {
    return Math.cos(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.sin(n);
}
native<dbl> calc2(n:dbl) {
    return n.sin();
}
native<dbl> calc3(n) {
    return Math.sin(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.tan(n);
}
native<dbl> calc2(n:dbl) {
    return n.tan();
}
native<dbl> calc3(n) {
    return Math.tan(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.cosh(n);
}
native<dbl> calc2(n:dbl) {
    return n.cosh();
}
native<dbl> calc3(n) {
    return Math.cosh(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.sinh(n);
}
native<dbl> calc2(n:dbl) {
    return n.sinh();
}
native<dbl> calc3(n) {
    return Math.sinh(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.tanh(n);
}
native<dbl> calc2(n:dbl) {
    return n.tanh();
}
native<dbl> calc3(n) {
    return Math.tanh(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.exp(n);
}
native<dbl> calc2(n:dbl) {
    return n.exp();
}
native<dbl> calc3(n) {
    return Math.exp(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.ldexp(n, 10.0);
}
native<dbl> calc2(n:dbl) {
    return n.ldexp(10.0);
}
native<dbl> calc3(n) {
    return Math.ldexp(n, 10);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.log(n);
}
native<dbl> calc2(n:dbl) {
    return n.log();
}
native<dbl> calc3(n) {
    return Math.log(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.log10(n);
}
native<dbl> calc2(n:dbl) {
    return n.log10();
}
native<dbl> calc3(n) {
    return Math.log10(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.pow(n, 10.0);
}
native<dbl> calc2(n:dbl) {
    return n.pow(10.0);
}
native<dbl> calc3(n) {
    return Math.pow(n, 10);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.sqrt(n);
}
native<dbl> calc2(n:dbl) {
    return n.sqrt();
}
native<dbl> calc3(n) {
    return Math.sqrt(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.abs(n);
}
native<dbl> calc2(n:dbl) {
    return n.abs();
}
native<dbl> calc3(n) {
    return Math.abs(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.ceil(n);
}
native<dbl> calc2(n:dbl) {
    return n.ceil();
}
native<dbl> calc3(n) {
    return Math.ceil(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.floor(n);
}
native<dbl> calc2(n:dbl) {
    return n.floor();
}
native<dbl> calc3(n) {
    return Math.floor(n);
}
native<dbl> calc4(n) {
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
native<dbl> calc1(n:dbl) {
    return Math.fmod(n, 10.0);
}
native<dbl> calc2(n:dbl) {
    return n.fmod(10.0);
}
native<dbl> calc3(n) {
    return Math.fmod(n, 10);
}
native<dbl> calc4(n) {
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
