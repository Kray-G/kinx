# Array

## Overview

An array object is a set of sequential objects like `[1,2,3]`.
An array itself can be inside an array, and it can be nested like `[[1,2,3],3,[2,[3,4]]]`.

### Methods

There is a special object named as `Array`.
The methods of `Array` can be used for array directly.

|                Method                 |                                   Meaning                                    |
| ------------------------------------- | ---------------------------------------------------------------------------- |
| `Array.length(ary)`                   | Returns the length of an array.                                              |
| `Array.join(ary, delim)`              | Returns the string of joining array items by `delim`.                        |
| `Array.keySet(obj)`                   | Returns the array of keys.                                                   |
| `Array.push(ary, val)`                | Appends the value to the tail of an array.                                   |
| `Array.pop(ary)`                      | Takes the value from the tail of an array.                                   |
| `Array.unshift(ary, val)`             | Appends the value to the head of an array.                                   |
| `Array.shift(ary)`                    | Takes the value from the head of an array.                                   |
| `Array.reverse(ary)`                  | Returns the array of items to reverse the order.                             |
| `Array.flatten(ary, level)`           | Flattens an array until specified level.                                     |
| `Array.toString(ary)`                 | Same as `"[" + ary.join(', ') + "]"`.                                        |
| `Array.each(ary, callback)`           | Loop and call `callback`.                                                    |
| `Array.map(ary, callback)`            | Returns an array having items mapped by `callback`.                          |
| `Array.filter(ary, callback)`         | Returns an array having items filtered by `callback`.                        |
| `Array.reduce(ary, callback, initer)` | Returns an array having items applied by `callback(r, initer)` to each item. |
| `Array.sort(ary, cmpfunc)`            | Sorted array by `cmpfunc`. **Not implemented yet**                           |

For example, the following 2 examples mean the same.

```javascript
Array.length(ary);
ary.length();
```

### Assignment

#### Normal case

Array can be lvalue like the following.

```javascript
[a, b] = [1, 2, 3];
```

#### Declaration

This style can be used also in a declaration.

```javascript
var [a, b] = [1, 2, 3];
```

#### Swap values

You can swap the values of variables by this mechanism like this.

```javascript
[a, b] = [b, a]; // swap
```

#### Ignore value

If you don't have to use a part of element, you can skip the parameter of lvalue.

```javascript
[a, , b] = [1, 2, 3];   // a == 1, b == 3
```

You can also skip the first parameter.

```javascript
[, a, b] = [1, 2, 3];   // a == 2, b == 3
```

### Function arguments

If you put an array style in the argument list,
an array of function call argument is separated and set the value to each variable in array list.
To understand it easily, see example below.

```javascript
function func([a, b], c) {
    return a + b + c;
}
func([1, 2], 3);    // => 6
```

## Examples

### Example 1. Normal case

#### Code

```javascript
System.println([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
```

#### Result

```
[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
```

### Example 2. Assignment

#### Code

```javascript
[a, b] = [1, 2, 3];
System.println([a, b]);
```

#### Result

```
[1, 2]
```

### Example 3. Declration

#### Code

```javascript
var [a, b] = [1, 2, 3];
System.println([a, b]);
```

#### Result

```
[1, 2]
```

### Example 4. Swap

#### Code

```javascript
var a = 1, b = 2;
[a, b] = [b, a];
System.println([a, b]);
```

#### Result

```
[2, 1]
```

### Example 5. Ignore

#### Code

```javascript
[a, , b] = [1, 2, 3];   // a == 1, b == 3
System.println([a, b]);
[, a, b] = [1, 2, 3];   // a == 2, b == 3
System.println([a, b]);
```

#### Result

```
[1, 3]
[2, 3]
```

### Example 6. Function argument (1)

#### Code

```javascript
function func([a, b], c) {
    return a + b + c;
}
System.println(func([1, 2], 3));
```

#### Result

```
6
```

### Example 7. Function argument (2)

#### Code

```javascript
function func([, a, , b], c) {
    return a + b + c;
}
System.println(func([1, 2, 3, 4], 3));
```

#### Result

```
9
```
