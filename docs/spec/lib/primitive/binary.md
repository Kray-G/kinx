# Binary

## Overview

A binary object is a set of sequential objects like `<1,2,3>`.

### Methods

There is a special object named as `Binary`.
The methods of `Binary` can be used for array directly.

|                 Method                 |                                         Meaning                                         |
| -------------------------------------- | --------------------------------------------------------------------------------------- |
| `Binary.length(bin)`                   | Returns the length of a binary.                                                         |
| `Binary.join(bin, delim, fmt)`         | Returns the string of joining array items by `delim`. `fmt` will be `0x02x` if omitted. |
| `Binary.keySet(obj)`                   | Returns the array of keys.                                                              |
| `Binary.push(bin, val)`                | Appends the value to the tail of a binary.                                              |
| `Binary.pop(bin)`                      | Takes the value from the tail of a binary.                                              |
| `Binary.unshift(bin, val)`             | Appends the value to the head of a binary.                                              |
| `Binary.shift(bin)`                    | Takes the value from the head of a binary.                                              |
| `Binary.reverse(bin)`                  | Returns the array of items to reverse the order.                                        |
| `Binary.toString(bin)`                 | Same as `"<" + bin.join(', ') + ">"`.                                                   |
| `Binary.each(bin, callback)`           | Loop and call `callback`.                                                               |
| `Binary.map(bin, callback)`            | Returns a binary having items mapped by `callback`.                                     |
| `Binary.filter(bin, callback)`         | Returns a binary having items filtered by `callback`.                                   |
| `Binary.rejct(bin, callback, initer)`  | Returns a binary having items set returned false by `callback(r, initer)` to each item. |
| `Binary.reduce(bin, callback, initer)` | Returns a binary having items applied by `callback(r, initer)` to each item.            |
| `Binary.sort(bin, cmpfunc)`            | Sorted array by `cmpfunc`. **Not implemented yet**                                      |

For example, the following 2 examples mean the same.

```javascript
Binary.length(bin);
bin.length();
```

### Assignment

#### Normal case

Binary can be lvalue like the following.

```javascript
var a = <1, 2, 3>;
```

### Special operator

#### Postfix `[]` operator

You can use `[]` operator to access a value in a binary by index.
The value will be an integer number between 0 and 255.
And it can be used as an l-value.

```javascript
var bin = <1,2,3,4,5>;
bin[2] = 255;
System.println(bin);  // => <0x01, 0x02, 0xff, 0x04, 0x05>
```

#### Unary `*` operator

Unary `*` operator for a binary will convert it to a string of character codes.

```javascript
var a = *<97, 98, 99>;  // => "abc"
```

#### Binary `+` operator

Binary `+` operator for a binary will connect 2 binaries.

```javascript
var a = <97, 98>;
var b = a + <99>;
System.println(*b); // => "abc"
```

#### Spread/Rest operator

You can convert between a binary and an array by a spread/rest operator.
Please see example of **Example 4** below.

## Examples

### Example 1. Normal case

#### Code

```javascript
System.println(<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>);
```

#### Result

```
<0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a>
```

### Example 2. Assignment

#### Code

```javascript
var a = <1, 2, 3>;
a[1] = 4;
System.println(a);
```

#### Result

```
<0x01, 0x04, 0x03>
```

### Example 3. Operator `+` for binary

#### Code

```javascript
var a = <97, 98>;
var b = a + <99>;
System.println(*b); // => "abc"
```

#### Result

```
abc
```

### Example 4. Conversion between a binary and an array

#### Code

```javascript
var a = <97, 98, 99>;
var b = [...a];
var c = <...b>;
b[1] = 100;
System.println(b);
System.println(c);
```

#### Result

```
[97, 100, 99]
<0x61, 0x62, 0x63>
```
