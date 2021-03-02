
# module Enumerable

## Overview

The module `Enumerable` is used by `mixin` into the class object. Now the class `Range` is used `Enumerable` by `mixin`.

### Interfaces

The interfaces of `Enumerable` can be used by the class which doing `mixin` the `Enumerable` module.
For example, the `Range` can also use the following interfaces.

`Lazy` field means the lazy operation will be performed after you call `lazy()` and use the `Enumerator` object returned by `lazy()`.

|         Name         |                                   Outline                                    | Lazy  |
| -------------------- | ---------------------------------------------------------------------------- | :---: |
| filter(func)         | Filters by the element returned by `func`.                                   |   O   |
| map(func)            | Maps by the element returned by `func`.                                      |   O   |
| flatMap(func)        | Maps by the element returned by `func`, then flatten the all result.         |   O   |
| take(n)              | Takes `n` elements from the beginning.                                       |   O   |
| takeWhile(func)      | Takes an element while returning true by `func`.                             |   O   |
| drop(n)              | Skips `n` elements from the beginning.                                       |   O   |
| dropWhile(func)      | Skips an element while returning true by `func`.                             |   O   |
| each(func)           | Applies `func` for each.                                                     |   O   |
| reduce(func, initer) | Reduces by the result of `func`. `initer` is the initial value if necessary. |       |
| sort(func)           | Sorts elements by comparing with the result of `func`                        |       |
| all(func)            | true if the result of `func` is all true for all elements.                   |       |
| any(func)            | true if there is at least one element which is true returned by `func`.      |       |
| toArray()            | Returns elements as Array.                                                   |       |
| println()            | Applies `System.println` for all elements.                                   |       |
| lazy()               | Returns `Enumerator` for lazy operation.                                     |       |

## Examples

### Example 1. filter

#### Code

```javascript
System.println((2..10).filter(&(e) => e % 2));
```

#### Result

```
[3, 5, 7, 9]
```

### Example 2. map

#### Code

```javascript
(2..10).map(&(e) => e**e).each(&(e) => System.println(e));
```

#### Result

```
4
27
256
3125
46656
823543
16777216
387420489
10000000000
```

### Example 3. flatMap

#### Code

```javascript
(2..10).flatMap(&(e) => [e, e**2]).each(&(e) => System.println(e));
```

#### Result

```
2
4
3
9
4
16
5
25
6
36
7
49
8
64
9
81
10
100
```

### Example 4. take

#### Code

```javascript
(2..10).take(5).each(&(e) => System.println(e));
```

#### Result

```
2
3
4
5
6
```

### Example 5. takeWhile

#### Code

```javascript
(2..10).takeWhile(&(e) => e < 4).each(&(e) => System.println(e));
```

#### Result

```
2
3
```
### Example 6. drop

#### Code

```javascript
(2..10).drop(5).each(&(e) => System.println(e));
```

#### Result

```
7
8
9
10
```

### Example 7. dropWhile

#### Code

```javascript
(2..10).dropWhile(&(e) => e < 4).each(&(e) => System.println(e));
```

#### Result

```
4
5
6
7
8
9
10
```

### Example 8. each

#### Code

```javascript
(2..10).each(&(e) => System.println(e));
```

#### Result

```
2
3
4
5
6
7
8
9
10
```

### Example 9 reduce

#### Code

```javascript
System.println((2..10).reduce(&(r, e) => r + e));
System.println((2..10).reduce(&(r, e) => r + e, 1));
```

#### Result

```
54
55
```

### Example 10. sort

#### Code

```javascript
System.println((2..10).sort(&(e1, e2) => e1 <=> e2));
System.println((2..10).sort(&(e1, e2) => e2 <=> e1));
```

#### Result

```
[2, 3, 4, 5, 6, 7, 8, 9, 10]
[10, 9, 8, 7, 6, 5, 4, 3, 2]
```

### Example 11. all

#### Code

```javascript
System.println((2..10).all(&(e) => e < 3));
System.println((2..10).all(&(e) => e <= 10));
```

#### Result

```
0
1
```

### Example 12. any

#### Code

```javascript
System.println((2..10).any(&(e) => e == 3));
System.println((2..10).any(&(e) => e == 13));
```

#### Result

```
1
0
```

### Example 13. toArray

#### Code

```javascript
System.println((2..10).toArray());
```

#### Result

```
[2, 3, 4, 5, 6, 7, 8, 9, 10]
```

### Example 14. println

#### Code

```javascript
(2..10)
    .takeWhile(&(e) => e < 4)
    .println();
```

#### Result

```
2
3
```

### Example 15. lazy

#### Code

```javascript
(2..10).lazy()
    .filter(&(e) => e % 2)
    .take(3)
    .println();
```

#### Result

```
3
5
7
```
