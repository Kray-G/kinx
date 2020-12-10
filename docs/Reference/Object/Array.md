# Kinx Object Reference

## Array

`Array` object is used to operate for an array object like `[1,2,3]`.

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

There is a special use case for this object.
The following 2 example means the same work.

```js
Array.length(ary);
ary.length();
```
