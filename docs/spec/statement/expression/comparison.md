# Comparison

## Overview

Comparison operators are `<`, `>`, `<=`, and `>=`.

```javascript
var a = 0x05;
var b = a < 0x06;   // 5 < 6 => true means 1
```

## Examples

### Example 1. Simple use of `<`

#### Code

```javascript
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test("<", &(a, b) => a < b, 0x05, 0x06));
System.println(test("<", &(a, b) => a < b, 99, 99));
System.println(test("<", &(a, b) => a < b, 100, 11));
System.println(test("<", &(a, b) => a < b, null, 0x05));
System.println(test("<", &(a, b) => a < b, 0x07, null));
```

#### Result

```
::        5 <        6 => 1
::       99 <       99 => 0
::      100 <       11 => 0
:: ((null)) <        5 => 1
::        7 < ((null)) => 0
```

### Example 2. Simple use of `<=`

#### Code

```javascript
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test("<=", &(a, b) => a <= b, 0x05, 0x06));
System.println(test("<=", &(a, b) => a <= b, 99, 99));
System.println(test("<=", &(a, b) => a <= b, 100, 11));
System.println(test("<=", &(a, b) => a <= b, null, 0x05));
System.println(test("<=", &(a, b) => a <= b, 0x07, null));
```

#### Result

```
::        5 <=        6 => 1
::       99 <=       99 => 1
::      100 <=       11 => 0
:: ((null)) <=        5 => 1
::        7 <= ((null)) => 0
```

### Example 3. Simple use of `>`

#### Code

```javascript
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test(">", &(a, b) => a > b, 0x05, 0x06));
System.println(test(">", &(a, b) => a > b, 99, 99));
System.println(test(">", &(a, b) => a > b, 100, 11));
System.println(test(">", &(a, b) => a > b, null, 0x05));
System.println(test(">", &(a, b) => a > b, 0x07, null));
```

#### Result

```
::        5 >        6 => 0
::       99 >       99 => 0
::      100 >       11 => 1
:: ((null)) >        5 => 0
::        7 > ((null)) => 1
```

### Example 4. Simple use of `<=`

#### Code

```javascript
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test(">=", &(a, b) => a >= b, 0x05, 0x06));
System.println(test(">=", &(a, b) => a >= b, 99, 99));
System.println(test(">=", &(a, b) => a >= b, 100, 11));
System.println(test(">=", &(a, b) => a >= b, null, 0x05));
System.println(test(">=", &(a, b) => a >= b, 0x07, null));
```

#### Result

```
::        5 >=        6 => 0
::       99 >=       99 => 1
::      100 >=       11 => 1
:: ((null)) >=        5 => 0
::        7 >= ((null)) => 1
```

### Example 5. Big Integer of `<`

#### Code

```javascript
const BI = 0x7fffffffffffffff + 2;
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test("<", &(a, b) => a < b, BI, 0x06));
System.println(test("<", &(a, b) => a < b, BI, BI));
System.println(test("<", &(a, b) => a < b, 100, BI));
System.println(test("<", &(a, b) => a < b, null, BI));
System.println(test("<", &(a, b) => a < b, BI, null));
```

#### Result

```
:: 9223372036854775809 <        6 => 0
:: 9223372036854775809 < 9223372036854775809 => 0
::      100 < 9223372036854775809 => 1
:: ((null)) < 9223372036854775809 => 1
:: 9223372036854775809 < ((null)) => 0
```

### Example 6. Big Integer of `<=`

#### Code

```javascript
const BI = 0x7fffffffffffffff + 2;
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test("<=", &(a, b) => a <= b, BI, 0x06));
System.println(test("<=", &(a, b) => a <= b, BI, BI));
System.println(test("<=", &(a, b) => a <= b, 100, BI));
System.println(test("<=", &(a, b) => a <= b, null, BI));
System.println(test("<=", &(a, b) => a <= b, BI, null));
```

#### Result

```
:: 9223372036854775809 <=        6 => 0
:: 9223372036854775809 <= 9223372036854775809 => 1
::      100 <= 9223372036854775809 => 1
:: ((null)) <= 9223372036854775809 => 1
:: 9223372036854775809 <= ((null)) => 0
```

### Example 7. Big Integer of `>`

#### Code

```javascript
const BI = 0x7fffffffffffffff + 2;
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test(">", &(a, b) => a > b, BI, 0x06));
System.println(test(">", &(a, b) => a > b, BI, BI));
System.println(test(">", &(a, b) => a > b, 100, BI));
System.println(test(">", &(a, b) => a > b, null, BI));
System.println(test(">", &(a, b) => a > b, BI, null));
```

#### Result

```
:: 9223372036854775809 >        6 => 1
:: 9223372036854775809 > 9223372036854775809 => 0
::      100 > 9223372036854775809 => 0
:: ((null)) > 9223372036854775809 => 0
:: 9223372036854775809 > ((null)) => 1
```

### Example 8. Big Integer of `>=`

#### Code

```javascript
const BI = 0x7fffffffffffffff + 2;
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test(">=", &(a, b) => a >= b, BI, 0x06));
System.println(test(">=", &(a, b) => a >= b, BI, BI));
System.println(test(">=", &(a, b) => a >= b, 100, BI));
System.println(test(">=", &(a, b) => a >= b, null, BI));
System.println(test(">=", &(a, b) => a >= b, BI, null));
```

#### Result

```
:: 9223372036854775809 >=        6 => 1
:: 9223372036854775809 >= 9223372036854775809 => 1
::      100 >= 9223372036854775809 => 0
:: ((null)) >= 9223372036854775809 => 0
:: 9223372036854775809 >= ((null)) => 1
```
