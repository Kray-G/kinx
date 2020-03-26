# Comparison by Equation

## Overview

Operators for equation are `==` and `!=`.

```javascript
var a = 0x05;
var b = a == 0x06;   // 5 == 6 => false means 0
```

If the type is different, it will be compared after converting by the table below.

|         |    Inteer     | Double |    String     |
| :-----: | :-----------: | :----: | ------------- |
| Integer |    Integer    | Double | String by dec |
| Double  |    Double     | Double | -             |
| String  | String by dec |   -    | String        |

Comparing between Integer and String is done as stringified by decimal numbers.

## Examples

### Example 1. Use `==` for Integers

#### Code

```javascript
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test("==", &(a, b) => a == b, 0x05, 0x06));
System.println(test("==", &(a, b) => a == b, 99, 99));
System.println(test("==", &(a, b) => a == b, 100, 11));
System.println(test("==", &(a, b) => a == b, null, 0x05));
System.println(test("==", &(a, b) => a == b, 0x07, null));
```

#### Result

```
::        5 ==        6 => 0
::       99 ==       99 => 1
::      100 ==       11 => 0
:: ((null)) ==        5 => 0
::        7 == ((null)) => 0
```

### Example 2. Use `==` between Integer and Double

#### Code

```javascript
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test("==", &(a, b) => a == b, 1, 1.0));
```

#### Result

```
::        1 ==        1 => 1
```

### Example 3. Use `==` between Integer and String

#### Code

```javascript
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test("==", &(a, b) => a == b, 0xff, "255"));
System.println(test("==", &(a, b) => a == b, 0xff, "ff"));
```

#### Result

```
::      255 ==      255 => 1
::      255 ==       ff => 0
```

### Example 4. Use `==` between String and Integer

#### Code

```javascript
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test("==", &(a, b) => a == b, "255", 0xff));
System.println(test("==", &(a, b) => a == b, "ff", 0xff));
```

#### Result

```
::      255 ==      255 => 1
::       ff ==      255 => 0
```

### Example 5. Use `!=` for Integers

#### Code

```javascript
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test("!=", &(a, b) => a != b, 0x05, 0x06));
System.println(test("!=", &(a, b) => a != b, 99, 99));
System.println(test("!=", &(a, b) => a != b, 100, 11));
System.println(test("!=", &(a, b) => a != b, null, 0x05));
System.println(test("!=", &(a, b) => a != b, 0x07, null));
```

#### Result

```
::        5 !=        6 => 1
::       99 !=       99 => 0
::      100 !=       11 => 1
:: ((null)) !=        5 => 1
::        7 != ((null)) => 1
```

### Example 6. Use `!=` between Integer and Double

#### Code

```javascript
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test("!=", &(a, b) => a != b, 1, 1.0));
```

#### Result

```
::        1 !=        1 => 0
```

### Example 7. Use `!=` between Integer and String

#### Code

```javascript
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test("!=", &(a, b) => a != b, 0xff, "255"));
System.println(test("!=", &(a, b) => a != b, 0xff, "ff"));
```

#### Result

```
::      255 !=      255 => 0
::      255 !=       ff => 1
```

### Example 8. Use `!=` between String and Integer

#### Code

```javascript
function test(label, func, a, b) {
    return ":: %8d %s %8d => %d" % a % label % b % func(a, b);
}

System.println(test("!=", &(a, b) => a != b, "255", 0xff));
System.println(test("!=", &(a, b) => a != b, "ff", 0xff));
```

#### Result

```
::      255 !=      255 => 0
::       ff !=      255 => 1
```
