# Kinx Object Reference

## Binary

`Binary` object is used to operate for a binary object like `<0x01,0x02>`.

|        Method        |             Meaning             |
| -------------------- | ------------------------------- |
| `Binary.length(bin)` | Returns the length of a binary. |

There is a special use case for this object.
The following 2 example means the same work.

```js
Binary.length(bin);
bin.length();
```
