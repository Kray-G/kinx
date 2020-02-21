# Kinx Object Reference

## Integer

`Integer` object is used to operate for an integer like `100`.
And `Math` object's function is available for Integer object like `2.pow(10)`.

|                Method                |                          Meaning                          |
| ------------------------------------ | --------------------------------------------------------- |
| `Integer.parseInt(val)`              | Converts `val` to an integer value.                       |
| `Integer.parseDouble(val)`           | Converts `val` to a double value.                         |
| `Integer.times(val, callback)`       | Loop and callback with the range from `0` to `(val - 1)`. |
| `Integer.upto(val, max, callback)`   | Loop and callback with the range from `val` to `max`.     |
| `Integer.downto(val, min, callback)` | Loop and callback with the range from `val` to `min`.     |

There is a special use case for this object.
The following 2 example means the same work.

```js
Integer.times(100, callback);
100.times(callback);
```
