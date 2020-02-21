# Kinx Object Reference

## Double

`Double` object is used to operate for a double like `1.5`.
And `Math` object's function is available for Integer object like `2.0.pow(10.0)`.

|          Method           |               Meaning               |
| ------------------------- | ----------------------------------- |
| `Double.parseInt(val)`    | Converts `val` to an integer value. |
| `Double.parseDouble(val)` | Converts `val` to a double value.   |

There is a special use case for this object.
The following 2 example means the same work.

```js
Double.parseInt(1.5);
1.5.parseInt();
```
