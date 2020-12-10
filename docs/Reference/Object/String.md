# Kinx Object Reference

## String

`String` object is used to operate for a text.

|               Method                |               Meaning                |
| ----------------------------------- | ------------------------------------ |
| `String.length(str)`                | Returns the length of a string.      |
| `String.trim(str)`                  | Trims whitespaces from a string.     |
| `String.startsWith(str, chk)`       | Returns true if str starts with chk. |
| `String.endsWith(str, chk)`         | Returns true if str ends with chk.   |
| `String.subString(str, start, len)` | Returns a sub string from a string.  |
| `String.parseInt(str)`              | Converts `val` to an integer value.  |
| `String.parseDouble(str)`           | Converts `val` to a double value.    |
| `String.toInt(str)`                 | Same as `parseInt`.                  |
| `String.toDouble(str)`              | Same as `parseDouble`.               |

There is a special use case for this object.
The following 2 example means the same work.

```js
String.length(str);
str.length();
```
