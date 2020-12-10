# Types

## Overview

In Kinx, a variable doesn't have a type but a value has a type.
The types which can be used are below.

|   Type    |        CheckProperty        |            Example            |                                 Meaning                                  |
| --------- | --------------------------- | :---------------------------: | ------------------------------------------------------------------------ |
| Undefined | `isUndefined`               |             null              | The value is not defined. Initial value.                                 |
| Integer   | `isInteger`, `isBigInteger` |           100, 0x02           | Integer value. Converting automatically between integer and big integer. |
| Double    | `isDouble`                  |              1.5              | Double value.                                                            |
| String    | `isString`                  |         "aaa", 'bbb'          | String value. Double quote and single quote is the same meaning.         |
| Binary    | `isBinary`                  |            <1,2,3>            | Byte array. Each value is 0x00-0xFF.                                     |
| Array     | `isArray`, `isObject`       |         [1,a,["aaa"]]         | Array of any data.                                                       |
| Object    | `isObject`                  |        { a: 1, b: x }         | Key-value data structure like JSON.                                      |
| Function  | `isFunction`                | function(){},<br/>&() => expr | Function object like function, lambda, or native function.               |

The CheckProperty for each `Type` shown above will be `true`.

And `isDefined` for the value which is not null/undefined will be `true`.
This means `isUndefined` for that is `false`.

## Examples

### Example 1. Undefined

#### Code

```javascript
function checkType(name, n) {
    System.println(name);
    System.println("    ", name, ".isUndefined  = ", n.isUndefined);
    System.println("    ", name, ".isInteger    = ", n.isInteger);
    System.println("    ", name, ".isBigInteger = ", n.isBigInteger);
    System.println("    ", name, ".isDouble     = ", n.isDouble);
    System.println("    ", name, ".isString     = ", n.isString);
    System.println("    ", name, ".isBinary     = ", n.isBinary);
    System.println("    ", name, ".isArray      = ", n.isArray);
    System.println("    ", name, ".isObject     = ", n.isObject);
    System.println("    ", name, ".isFunction   = ", n.isFunction);
    System.println("    ", name, ".isDefined    = ", n.isDefined);
}

checkType("undefined", undefined);
checkType("null", null);
```

#### Result

```
undefined
    undefined.isUndefined  = 1
    undefined.isInteger    = 0
    undefined.isBigInteger = 0
    undefined.isDouble     = 0
    undefined.isString     = 0
    undefined.isBinary     = 0
    undefined.isArray      = 0
    undefined.isObject     = 0
    undefined.isFunction   = 0
    undefined.isDefined    = 0
null
    null.isUndefined  = 1
    null.isInteger    = 0
    null.isBigInteger = 0
    null.isDouble     = 0
    null.isString     = 0
    null.isBinary     = 0
    null.isArray      = 0
    null.isObject     = 0
    null.isFunction   = 0
    null.isDefined    = 0
```

### Example 2. Integer

#### Code

```javascript
function checkType(n) {
    System.println(n);
    System.println("    ", n, ".isUndefined  = ", n.isUndefined);
    System.println("    ", n, ".isInteger    = ", n.isInteger);
    System.println("    ", n, ".isBigInteger = ", n.isBigInteger);
    System.println("    ", n, ".isDouble     = ", n.isDouble);
    System.println("    ", n, ".isString     = ", n.isString);
    System.println("    ", n, ".isBinary     = ", n.isBinary);
    System.println("    ", n, ".isArray      = ", n.isArray);
    System.println("    ", n, ".isObject     = ", n.isObject);
    System.println("    ", n, ".isFunction   = ", n.isFunction);
    System.println("    ", n, ".isDefined    = ", n.isDefined);
}

checkType(-1);
checkType(0);
checkType(1);
checkType(100_000);
checkType(0xff);
checkType(010);
```

#### Result

```
-1
    -1.isUndefined  = 0
    -1.isInteger    = 1
    -1.isBigInteger = 0
    -1.isDouble     = 0
    -1.isString     = 0
    -1.isBinary     = 0
    -1.isArray      = 0
    -1.isObject     = 0
    -1.isFunction   = 0
    -1.isDefined    = 1
0
    0.isUndefined  = 0
    0.isInteger    = 1
    0.isBigInteger = 0
    0.isDouble     = 0
    0.isString     = 0
    0.isBinary     = 0
    0.isArray      = 0
    0.isObject     = 0
    0.isFunction   = 0
    0.isDefined    = 1
1
    1.isUndefined  = 0
    1.isInteger    = 1
    1.isBigInteger = 0
    1.isDouble     = 0
    1.isString     = 0
    1.isBinary     = 0
    1.isArray      = 0
    1.isObject     = 0
    1.isFunction   = 0
    1.isDefined    = 1
100000
    100000.isUndefined  = 0
    100000.isInteger    = 1
    100000.isBigInteger = 0
    100000.isDouble     = 0
    100000.isString     = 0
    100000.isBinary     = 0
    100000.isArray      = 0
    100000.isObject     = 0
    100000.isFunction   = 0
    100000.isDefined    = 1
255
    255.isUndefined  = 0
    255.isInteger    = 1
    255.isBigInteger = 0
    255.isDouble     = 0
    255.isString     = 0
    255.isBinary     = 0
    255.isArray      = 0
    255.isObject     = 0
    255.isFunction   = 0
    255.isDefined    = 1
8
    8.isUndefined  = 0
    8.isInteger    = 1
    8.isBigInteger = 0
    8.isDouble     = 0
    8.isString     = 0
    8.isBinary     = 0
    8.isArray      = 0
    8.isObject     = 0
    8.isFunction   = 0
    8.isDefined    = 1
```

### Example 3. BigInteger

#### Code

```javascript
function checkType(n) {
    System.println(n);
    System.println("    ", n, ".isUndefined  = ", n.isUndefined);
    System.println("    ", n, ".isInteger    = ", n.isInteger);
    System.println("    ", n, ".isBigInteger = ", n.isBigInteger);
    System.println("    ", n, ".isDouble     = ", n.isDouble);
    System.println("    ", n, ".isString     = ", n.isString);
    System.println("    ", n, ".isBinary     = ", n.isBinary);
    System.println("    ", n, ".isArray      = ", n.isArray);
    System.println("    ", n, ".isObject     = ", n.isObject);
    System.println("    ", n, ".isFunction   = ", n.isFunction);
    System.println("    ", n, ".isDefined    = ", n.isDefined);
}

checkType(0xffffffffffffffff);
checkType((0xffffffffffffffff >> 1) + 1);
checkType(-(0xffffffffffffffff >> 1) - 2);
```

#### Result

```
18446744073709551615
    18446744073709551615.isUndefined  = 0
    18446744073709551615.isInteger    = 1
    18446744073709551615.isBigInteger = 1
    18446744073709551615.isDouble     = 0
    18446744073709551615.isString     = 0
    18446744073709551615.isBinary     = 0
    18446744073709551615.isArray      = 0
    18446744073709551615.isObject     = 0
    18446744073709551615.isFunction   = 0
    18446744073709551615.isDefined    = 1
9223372036854775808
    9223372036854775808.isUndefined  = 0
    9223372036854775808.isInteger    = 1
    9223372036854775808.isBigInteger = 1
    9223372036854775808.isDouble     = 0
    9223372036854775808.isString     = 0
    9223372036854775808.isBinary     = 0
    9223372036854775808.isArray      = 0
    9223372036854775808.isObject     = 0
    9223372036854775808.isFunction   = 0
    9223372036854775808.isDefined    = 1
-9223372036854775809
    -9223372036854775809.isUndefined  = 0
    -9223372036854775809.isInteger    = 1
    -9223372036854775809.isBigInteger = 1
    -9223372036854775809.isDouble     = 0
    -9223372036854775809.isString     = 0
    -9223372036854775809.isBinary     = 0
    -9223372036854775809.isArray      = 0
    -9223372036854775809.isObject     = 0
    -9223372036854775809.isFunction   = 0
    -9223372036854775809.isDefined    = 1
```

### Example 4. Double

#### Code

```javascript
function checkType(n) {
    System.println(n);
    System.println("    ", n, ".isUndefined  = ", n.isUndefined);
    System.println("    ", n, ".isInteger    = ", n.isInteger);
    System.println("    ", n, ".isBigInteger = ", n.isBigInteger);
    System.println("    ", n, ".isDouble     = ", n.isDouble);
    System.println("    ", n, ".isString     = ", n.isString);
    System.println("    ", n, ".isBinary     = ", n.isBinary);
    System.println("    ", n, ".isArray      = ", n.isArray);
    System.println("    ", n, ".isObject     = ", n.isObject);
    System.println("    ", n, ".isFunction   = ", n.isFunction);
    System.println("    ", n, ".isDefined    = ", n.isDefined);
}

checkType(-1 / 2);
checkType(0.0);
checkType(1 / 2);
checkType(100_000 / 3);
checkType(0xff / 2);
checkType(010 / 9);
```

#### Result

```
-0.5
    -0.5.isUndefined  = 0
    -0.5.isInteger    = 0
    -0.5.isBigInteger = 0
    -0.5.isDouble     = 1
    -0.5.isString     = 0
    -0.5.isBinary     = 0
    -0.5.isArray      = 0
    -0.5.isObject     = 0
    -0.5.isFunction   = 0
    -0.5.isDefined    = 1
0
    0.isUndefined  = 0
    0.isInteger    = 0
    0.isBigInteger = 0
    0.isDouble     = 1
    0.isString     = 0
    0.isBinary     = 0
    0.isArray      = 0
    0.isObject     = 0
    0.isFunction   = 0
    0.isDefined    = 1
0.5
    0.5.isUndefined  = 0
    0.5.isInteger    = 0
    0.5.isBigInteger = 0
    0.5.isDouble     = 1
    0.5.isString     = 0
    0.5.isBinary     = 0
    0.5.isArray      = 0
    0.5.isObject     = 0
    0.5.isFunction   = 0
    0.5.isDefined    = 1
33333.3
    33333.3.isUndefined  = 0
    33333.3.isInteger    = 0
    33333.3.isBigInteger = 0
    33333.3.isDouble     = 1
    33333.3.isString     = 0
    33333.3.isBinary     = 0
    33333.3.isArray      = 0
    33333.3.isObject     = 0
    33333.3.isFunction   = 0
    33333.3.isDefined    = 1
127.5
    127.5.isUndefined  = 0
    127.5.isInteger    = 0
    127.5.isBigInteger = 0
    127.5.isDouble     = 1
    127.5.isString     = 0
    127.5.isBinary     = 0
    127.5.isArray      = 0
    127.5.isObject     = 0
    127.5.isFunction   = 0
    127.5.isDefined    = 1
0.888889
    0.888889.isUndefined  = 0
    0.888889.isInteger    = 0
    0.888889.isBigInteger = 0
    0.888889.isDouble     = 1
    0.888889.isString     = 0
    0.888889.isBinary     = 0
    0.888889.isArray      = 0
    0.888889.isObject     = 0
    0.888889.isFunction   = 0
    0.888889.isDefined    = 1
```

### Example 5. String

#### Code

```javascript
function checkType(n) {
    System.println(n);
    System.println("    ", n, ".isUndefined  = ", n.isUndefined);
    System.println("    ", n, ".isInteger    = ", n.isInteger);
    System.println("    ", n, ".isBigInteger = ", n.isBigInteger);
    System.println("    ", n, ".isDouble     = ", n.isDouble);
    System.println("    ", n, ".isString     = ", n.isString);
    System.println("    ", n, ".isBinary     = ", n.isBinary);
    System.println("    ", n, ".isArray      = ", n.isArray);
    System.println("    ", n, ".isObject     = ", n.isObject);
    System.println("    ", n, ".isFunction   = ", n.isFunction);
    System.println("    ", n, ".isDefined    = ", n.isDefined);
}

checkType("aaa");
checkType('bbb');
checkType(*[97,98,99]);
checkType("xxxYYYzzz".replace(/YYY/, ""));
checkType("abcdefghijklmnop".subString(2));
```

#### Result

```
aaa
    aaa.isUndefined  = 0
    aaa.isInteger    = 0
    aaa.isBigInteger = 0
    aaa.isDouble     = 0
    aaa.isString     = 1
    aaa.isBinary     = 0
    aaa.isArray      = 0
    aaa.isObject     = 0
    aaa.isFunction   = 0
    aaa.isDefined    = 1
bbb
    bbb.isUndefined  = 0
    bbb.isInteger    = 0
    bbb.isBigInteger = 0
    bbb.isDouble     = 0
    bbb.isString     = 1
    bbb.isBinary     = 0
    bbb.isArray      = 0
    bbb.isObject     = 0
    bbb.isFunction   = 0
    bbb.isDefined    = 1
abc
    abc.isUndefined  = 0
    abc.isInteger    = 0
    abc.isBigInteger = 0
    abc.isDouble     = 0
    abc.isString     = 1
    abc.isBinary     = 0
    abc.isArray      = 0
    abc.isObject     = 0
    abc.isFunction   = 0
    abc.isDefined    = 1
xxxzzz
    xxxzzz.isUndefined  = 0
    xxxzzz.isInteger    = 0
    xxxzzz.isBigInteger = 0
    xxxzzz.isDouble     = 0
    xxxzzz.isString     = 1
    xxxzzz.isBinary     = 0
    xxxzzz.isArray      = 0
    xxxzzz.isObject     = 0
    xxxzzz.isFunction   = 0
    xxxzzz.isDefined    = 1
cdefghijklmnop
    cdefghijklmnop.isUndefined  = 0
    cdefghijklmnop.isInteger    = 0
    cdefghijklmnop.isBigInteger = 0
    cdefghijklmnop.isDouble     = 0
    cdefghijklmnop.isString     = 1
    cdefghijklmnop.isBinary     = 0
    cdefghijklmnop.isArray      = 0
    cdefghijklmnop.isObject     = 0
    cdefghijklmnop.isFunction   = 0
    cdefghijklmnop.isDefined    = 1
```

### Example 6. Binary

#### Code

```javascript
function checkType(n) {
    System.println(n);
    System.println("    ", n, ".isUndefined  = ", n.isUndefined);
    System.println("    ", n, ".isInteger    = ", n.isInteger);
    System.println("    ", n, ".isBigInteger = ", n.isBigInteger);
    System.println("    ", n, ".isDouble     = ", n.isDouble);
    System.println("    ", n, ".isString     = ", n.isString);
    System.println("    ", n, ".isBinary     = ", n.isBinary);
    System.println("    ", n, ".isArray      = ", n.isArray);
    System.println("    ", n, ".isObject     = ", n.isObject);
    System.println("    ", n, ".isFunction   = ", n.isFunction);
    System.println("    ", n, ".isDefined    = ", n.isDefined);
}

checkType(<1,2,3>);
checkType(<1,...[2,3,4]>);
```

#### Result

```
<0x01, 0x02, 0x03>
    <0x01, 0x02, 0x03>.isUndefined  = 0
    <0x01, 0x02, 0x03>.isInteger    = 0
    <0x01, 0x02, 0x03>.isBigInteger = 0
    <0x01, 0x02, 0x03>.isDouble     = 0
    <0x01, 0x02, 0x03>.isString     = 0
    <0x01, 0x02, 0x03>.isBinary     = 1
    <0x01, 0x02, 0x03>.isArray      = 0
    <0x01, 0x02, 0x03>.isObject     = 0
    <0x01, 0x02, 0x03>.isFunction   = 0
    <0x01, 0x02, 0x03>.isDefined    = 1
<0x01, 0x02, 0x03, 0x04>
    <0x01, 0x02, 0x03, 0x04>.isUndefined  = 0
    <0x01, 0x02, 0x03, 0x04>.isInteger    = 0
    <0x01, 0x02, 0x03, 0x04>.isBigInteger = 0
    <0x01, 0x02, 0x03, 0x04>.isDouble     = 0
    <0x01, 0x02, 0x03, 0x04>.isString     = 0
    <0x01, 0x02, 0x03, 0x04>.isBinary     = 1
    <0x01, 0x02, 0x03, 0x04>.isArray      = 0
    <0x01, 0x02, 0x03, 0x04>.isObject     = 0
    <0x01, 0x02, 0x03, 0x04>.isFunction   = 0
    <0x01, 0x02, 0x03, 0x04>.isDefined    = 1
```

### Example 7. Array

#### Code

```javascript
function checkType(n) {
    System.println(n);
    System.println("    ", n, ".isUndefined  = ", n.isUndefined);
    System.println("    ", n, ".isInteger    = ", n.isInteger);
    System.println("    ", n, ".isBigInteger = ", n.isBigInteger);
    System.println("    ", n, ".isDouble     = ", n.isDouble);
    System.println("    ", n, ".isString     = ", n.isString);
    System.println("    ", n, ".isBinary     = ", n.isBinary);
    System.println("    ", n, ".isArray      = ", n.isArray);
    System.println("    ", n, ".isObject     = ", n.isObject);
    System.println("    ", n, ".isFunction   = ", n.isFunction);
    System.println("    ", n, ".isDefined    = ", n.isDefined);
}

checkType([1,2,3]);
checkType([1,...<2,3,4>]);
```

#### Result

```
[1, 2, 3]
    [1, 2, 3].isUndefined  = 0
    [1, 2, 3].isInteger    = 0
    [1, 2, 3].isBigInteger = 0
    [1, 2, 3].isDouble     = 0
    [1, 2, 3].isString     = 0
    [1, 2, 3].isBinary     = 0
    [1, 2, 3].isArray      = 1
    [1, 2, 3].isObject     = 1
    [1, 2, 3].isFunction   = 0
    [1, 2, 3].isDefined    = 1
[1, 2, 3, 4]
    [1, 2, 3, 4].isUndefined  = 0
    [1, 2, 3, 4].isInteger    = 0
    [1, 2, 3, 4].isBigInteger = 0
    [1, 2, 3, 4].isDouble     = 0
    [1, 2, 3, 4].isString     = 0
    [1, 2, 3, 4].isBinary     = 0
    [1, 2, 3, 4].isArray      = 1
    [1, 2, 3, 4].isObject     = 1
    [1, 2, 3, 4].isFunction   = 0
    [1, 2, 3, 4].isDefined    = 1
```

### Example 8. Object

#### Code

```javascript
function checkType(n) {
    System.println(n);
    System.println("    ", n, ".isUndefined  = ", n.isUndefined);
    System.println("    ", n, ".isInteger    = ", n.isInteger);
    System.println("    ", n, ".isBigInteger = ", n.isBigInteger);
    System.println("    ", n, ".isDouble     = ", n.isDouble);
    System.println("    ", n, ".isString     = ", n.isString);
    System.println("    ", n, ".isBinary     = ", n.isBinary);
    System.println("    ", n, ".isArray      = ", n.isArray);
    System.println("    ", n, ".isObject     = ", n.isObject);
    System.println("    ", n, ".isFunction   = ", n.isFunction);
    System.println("    ", n, ".isDefined    = ", n.isDefined);
}

checkType({ a: 1, b: 2, c: 3 });
```

#### Result

```
{"a":1,"b":2,"c":3}
    {"a":1,"b":2,"c":3}.isUndefined  = 0
    {"a":1,"b":2,"c":3}.isInteger    = 0
    {"a":1,"b":2,"c":3}.isBigInteger = 0
    {"a":1,"b":2,"c":3}.isDouble     = 0
    {"a":1,"b":2,"c":3}.isString     = 0
    {"a":1,"b":2,"c":3}.isBinary     = 0
    {"a":1,"b":2,"c":3}.isArray      = 0
    {"a":1,"b":2,"c":3}.isObject     = 1
    {"a":1,"b":2,"c":3}.isFunction   = 0
    {"a":1,"b":2,"c":3}.isDefined    = 1
```

### Example 9. Function

#### Code

```javascript
function checkType(code, n) {
    System.println(code);
    System.println("    (", code, ").isUndefined  = ", n.isUndefined);
    System.println("    (", code, ").isInteger    = ", n.isInteger);
    System.println("    (", code, ").isBigInteger = ", n.isBigInteger);
    System.println("    (", code, ").isDouble     = ", n.isDouble);
    System.println("    (", code, ").isString     = ", n.isString);
    System.println("    (", code, ").isBinary     = ", n.isBinary);
    System.println("    (", code, ").isArray      = ", n.isArray);
    System.println("    (", code, ").isObject     = ", n.isObject);
    System.println("    (", code, ").isFunction   = ", n.isFunction);
    System.println("    (", code, ").isDefined    = ", n.isDefined);
}

function abc() {}

checkType("abc", abc);
checkType("function(){}", function(){});
checkType("&() => {}", &() => {});
checkType("{ => 0 }", { => 0 });
checkType("{ => _1 }", { => _1 });
checkType("{ &() return _1; }", { &() return _1; });
```

#### Result

```
abc
    (abc).isUndefined  = 0
    (abc).isInteger    = 0
    (abc).isBigInteger = 0
    (abc).isDouble     = 0
    (abc).isString     = 0
    (abc).isBinary     = 0
    (abc).isArray      = 0
    (abc).isObject     = 0
    (abc).isFunction   = 1
    (abc).isDefined    = 1
function(){}
    (function(){}).isUndefined  = 0
    (function(){}).isInteger    = 0
    (function(){}).isBigInteger = 0
    (function(){}).isDouble     = 0
    (function(){}).isString     = 0
    (function(){}).isBinary     = 0
    (function(){}).isArray      = 0
    (function(){}).isObject     = 0
    (function(){}).isFunction   = 1
    (function(){}).isDefined    = 1
&() => {}
    (&() => {}).isUndefined  = 0
    (&() => {}).isInteger    = 0
    (&() => {}).isBigInteger = 0
    (&() => {}).isDouble     = 0
    (&() => {}).isString     = 0
    (&() => {}).isBinary     = 0
    (&() => {}).isArray      = 0
    (&() => {}).isObject     = 0
    (&() => {}).isFunction   = 1
    (&() => {}).isDefined    = 1
{ => 0 }
    ({ => 0 }).isUndefined  = 0
    ({ => 0 }).isInteger    = 0
    ({ => 0 }).isBigInteger = 0
    ({ => 0 }).isDouble     = 0
    ({ => 0 }).isString     = 0
    ({ => 0 }).isBinary     = 0
    ({ => 0 }).isArray      = 0
    ({ => 0 }).isObject     = 0
    ({ => 0 }).isFunction   = 1
    ({ => 0 }).isDefined    = 1
{ => _1 }
    ({ => _1 }).isUndefined  = 0
    ({ => _1 }).isInteger    = 0
    ({ => _1 }).isBigInteger = 0
    ({ => _1 }).isDouble     = 0
    ({ => _1 }).isString     = 0
    ({ => _1 }).isBinary     = 0
    ({ => _1 }).isArray      = 0
    ({ => _1 }).isObject     = 0
    ({ => _1 }).isFunction   = 1
    ({ => _1 }).isDefined    = 1
{ &() return _1; }
    ({ &() return _1; }).isUndefined  = 0
    ({ &() return _1; }).isInteger    = 0
    ({ &() return _1; }).isBigInteger = 0
    ({ &() return _1; }).isDouble     = 0
    ({ &() return _1; }).isString     = 0
    ({ &() return _1; }).isBinary     = 0
    ({ &() return _1; }).isArray      = 0
    ({ &() return _1; }).isObject     = 0
    ({ &() return _1; }).isFunction   = 1
    ({ &() return _1; }).isDefined    = 1
```
