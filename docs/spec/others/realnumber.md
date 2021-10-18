# Real Number

## Overview

As for a real number, a normal real number representation and an exponent representation are supported.

## Examples

### Example 1. Normal Cases

#### Code

```javascript
var a = [
    [ 12.345, 12345e-3 ],
    [ 12345.1, 1.23451e+4 ],
    [ 12345.2, 1.23452e4 ],
];
a.each {
    if (_1[0] > _1[1] || _1[0] < _1[1]) {
        System.println("Value mismatched: ", _1);
    } else {
        System.println("Good: ", _1[0]);
    }
};
```

#### Result

```
Good: 12.345
Good: 12345.1
Good: 12345.2
```

### Example 2. Exponents in Decimal

#### Code

```javascript
var a = [
    [ 12.345e19, 1.2345e20 ],
    [ -0.1e+9, -1e+8 ],
    [ 0.125, 125e-3 ],
    [ 1e20, 10e19 ],
    [ 0e-19, 0 ],
    [ 5.9e-76, 59e-77 ],
];
a.each {
    if (_1[0] > _1[1] || _1[0] < _1[1]) {
        System.println("Value mismatched: ", _1);
    } else {
        System.println("Good: ", _1[0]);
    }
};
```

#### Result

```
Good: 1.2345e+20
Good: -1e+08
Good: 0.125
Good: 1e+20
Good: 0
Good: 5.9e-76
```

### Example 3. Exponents in Hexadecimal (1)

#### Code

```javascript
var a = [
    [ 0x1.4p+3, 10.0 ],
    [ 0xAp0, 10.0 ],
    [ 0x0Ap0, 10.0 ],
    [ 0x0A, 10.0 ],
];
a.each {
    if (_1[0] > _1[1] || _1[0] < _1[1]) {
        System.println("Value mismatched: ", _1);
    } else {
        System.println("Good: ", _1[0]);
    }
};
```

#### Result

```
Good: 10
Good: 10
Good: 10
Good: 10
```

### Example 4. Exponents in Hexadecimal (2)

#### Code

```javascript
var a = [
    [ 0xA0, 160.0 ],
    [ 0x0.A0p8, 160.0 ],
    [ 0x0.50p9, 160.0 ],
    [ 0x0.28p10, 160.0 ],
    [ 0x0.14p11, 160.0 ],
    [ 0x0.0A0p12, 160.0 ],
    [ 0x0.050p13, 160.0 ],
    [ 0x0.028p14, 160.0 ],
    [ 0x0.014p15, 160.0 ],
    [ 0x00.00A0p16, 160.0 ],
    [ 0x00.0050p17, 160.0 ],
    [ 0x00.0028p18, 160.0 ],
    [ 0x00.0014p19, 160.0 ],
];
a.each {
    if (_1[0] > _1[1] || _1[0] < _1[1]) {
        System.println("Value mismatched: ", _1);
    } else {
        System.println("Good: ", _1[0]);
    }
};
```

#### Result

```
Good: 160
Good: 160
Good: 160
Good: 160
Good: 160
Good: 160
Good: 160
Good: 160
Good: 160
Good: 160
Good: 160
Good: 160
Good: 160
```

### Example 5. Exponents in Hexadecimal (3)

#### Code

```javascript
var a = [
    [ 0x1p-1023, 1.11253692925360069154511635866620203210960799023116591527666e-308 ],
    [ 0x0.8p-1022, 1.11253692925360069154511635866620203210960799023116591527666e-308 ],
    [ 0x80000Ap-23, 0x80000Ap-23 ],
    [ 1e-324, 0 ],
    [ 0x100000000000008p0, 0x1p56 ],
    [ 0x100000000000008.p0, 0x1p56 ],
    [ 0x100000000000008.00p0, 0x1p56 ],
    [ 0x10000000000000800p0, 0x1p64 ],
    [ 0x10000000000000801p0, 0x1.0000000000001p64 ],
];
a.each {
    if (_1[0] > _1[1] || _1[0] < _1[1]) {
        System.println("Value mismatched: ", _1);
    } else {
        System.println("Good: ", _1[0]);
    }
};
```

#### Result

```
Good: 1.11254e-308
Good: 1.11254e-308
Good: 1
Good: 0
Good: 7.20576e+16
Good: 7.20576e+16
Good: 7.20576e+16
Good: 1.84467e+19
Good: 1.84467e+19
```
