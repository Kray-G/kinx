
# Functional

## Overview

The `Functional` is a global instance having functional methods which is useful with [a pipeline operator](../../statement/expression/pipeline.md).
For example, when multiple valuse are passed to the next function via pipeline,
a method in `Functional` can fetch a value one by one and pass the value to a next function in order.

Therefore, `Functional` can handle an infinite sequence.
This is an example below.

```javascript
1..
    |> Functional.enumerable
    |> Functional.drop(10)
    |> Functional.filter { => _1 % 3 == 0 }
    |> Functional.take(10)
    |> Functional.toArray
    |> System.println;
```

The `Functional.enumerable` is a magic function to make a sequence change to an item which `Functional` methods can use.
You can write it also like an example below, but the way how to write in the above example is more useful.

```javascript
new Functional.Enumerator(1..)
    |> Functional.drop(10)
    |> Functional.filter { => _1 % 3 == 0 }
    |> Functional.take(10)
    |> Functional.toArray
    |> System.println;
```

### Methods

The methods of `Functional` to pass values in pipeline is currently as follows.

|         Name         |                                                         Outline                                                         |
| -------------------- | ----------------------------------------------------------------------------------------------------------------------- |
| filter(func)         | Filters by the element returned by `func`.                                                                              |
| map(func)            | Maps by the element returned by `func`.                                                                                 |
| flatMap(func)        | Maps by the element returned by `func`, then flatten the all result.                                                    |
| take(n)              | Takes `n` elements from the beginning.                                                                                  |
| takeWhile(func)      | Takes an element while returning true by `func`.                                                                        |
| drop(n)              | Skips `n` elements from the beginning.                                                                                  |
| dropWhile(func)      | Skips an element while returning true by `func`.                                                                        |
| sort(func)           | Sorts elements by comparing with the result of `func`. Note that this method will fetch all at first to sort.           |
| shuffle(func)        | Shuffles elements in an array. Note that this method will fetch all at first to shuffle.                                |
| each(func)           | Applies `func` for each. The value will be passed to the next as it is.                                                 |
| println/println(msg) | Prints the value and pass it to the next. This is used to see inside the pipeline. `msg` can be lead message of output. |

The following methods will aggregate a sequence.
By one of those, the pipeline will be terminated once and a value will be aggregated.

|         Name         |                                                          Outline                                                          |
| -------------------- | ------------------------------------------------------------------------------------------------------------------------- |
| reduce(func, initer) | Reduces by the result of `func`. `initer` is the initial value if necessary.                                              |
| all(func)            | true if the result of `func` is all true for all elements.                                                                |
| any(func)            | true if there is at least one element which is true returned by `func`.                                                   |
| sum                  | Returns a sum of all sequence items.                                                                                      |
| toArray              | Returns gathered elements as Array.                                                                                       |
| partition(func)      | Returns an array of 2 groups of a group which is returning true by `func` and a group which is returning false by `func`. |
| printlnAll           | Apply `System.println` for all elements.                                                                                  |

### Functional.trace

This is not a `functional` method but a method just to trace and display items passed in the pipeline.
This method will display an item and pass it to the next as it is.

Therefore, `Functional.trace` can be used before `Functional.enumerable` as an example below.

```javascript
[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    |> Functional.trace
    |> Functional.enumerable
    |> Functional.each { => Functional.trace(_1) }
    |> Functional.reduce(&(r, e) => r += e, 0)
    |> Functional.trace
    ;

// [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8
// 9
// 10
// 55
```

## Examples

### Example 1. Functional.Enumerator

#### Code

```javascript
var $F = Functional;
var println = System.println;
var printlnArray = $F.toArray +> println;

new $F.Enumerator(1..10)
    |> $F.filter({ => _1 <= 4 })
    |> $F.map({ => _1 * 10 })
    |> printlnArray;
```

#### Result

```
[10, 20, 30, 40]
```

### Example 2. With Function Composition Operator

#### Code

```javascript
var $F = Functional;
var println = System.println;
var printlnArray = $F.toArray +> println;

1..10
    |> $F.enumerable
    |> $F.filter({ => _1 < 7 }) +> $F.map({ => _1 * 100 }) +> printlnArray
    ;
```

#### Result

```
[100, 200, 300, 400, 500, 600]
```

### Example 3. dropWhile

#### Code

```javascript
var $F = Functional;
var println = System.println;
var printlnArray = $F.toArray +> println;

1..20
    |> $F.enumerable
    |> $F.dropWhile { => _1 < 10 || _1 % 2 == 0 }
    |> printlnArray;
```

#### Result

```
[11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
```

### Example 4. flatMap (1)

#### Code

```javascript
var $F = Functional;
var println = System.println;
var printlnArray = $F.toArray +> println;

[[1, 2], [3, 4]]
    |> $F.enumerable
    |> $F.flatMap { => _1.map { => _1 * 2 } }
    |> printlnArray;
```

#### Result

```
[2, 4, 6, 8]
```

### Example 5. flatMap (2)

#### Code

```javascript
var $F = Functional;
var println = System.println;
var printlnArray = $F.toArray +> println;

[10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0]
    |> $F.enumerable
    |> $F.flatMap { => [_1, _1 * 2] }
    |> printlnArray;
```

#### Result

```
[10, 20, 9, 18, 8, 16, 7, 14, 6, 12, 5, 10, 4, 8, 3, 6, 2, 4, 1, 2, 0, 0]
```

### Example 6. sort

#### Code

```javascript
var $F = Functional;
var println = System.println;
var printlnArray = $F.toArray +> println;

[10, 21, 92, 22, 37, 23, 98, 76, 56 , 48, 88, 76, 109, 2, 54]
    |> $F.trace
    |> $F.enumerable
    |> $F.shuffle
    |> printlnArray <+ $F.sort
    ;
```

#### Result

```
[10, 21, 92, 22, 37, 23, 98, 76, 56, 48, 88, 76, 109, 2, 54]
[2, 10, 21, 22, 23, 37, 48, 54, 56, 76, 76, 88, 92, 98, 109]
```

### Example 7. Infinite Sequence

#### Code

```javascript
var $F = Functional;
var println = System.println;
var printlnArray = $F.toArray +> println;

100..
    |> $F.enumerable
    |> $F.println("==> ")
    |> $F.filter { => _1 % 2 == 0 }
    |> $F.println("filterred: ")
    |> $F.take(10)
    |> printlnArray;
```

#### Result

```
==> 100
filterred: 100
==> 101
==> 102
filterred: 102
==> 103
==> 104
filterred: 104
==> 105
==> 106
filterred: 106
==> 107
==> 108
filterred: 108
==> 109
==> 110
filterred: 110
==> 111
==> 112
filterred: 112
==> 113
==> 114
filterred: 114
==> 115
==> 116
filterred: 116
==> 117
==> 118
filterred: 118
[100, 102, 104, 106, 108, 110, 112, 114, 116, 118]
```

### Example 8. all (1)

#### Code

```javascript
var $F = Functional;
var println = System.println;

1..20
    |> $F.enumerable
    |> $F.all({ => _1 > 0 })
    |> println;
```

#### Result

```
1
```

### Example 9. all (2)

#### Code

```javascript
var $F = Functional;
var println = System.println;

0..20
    |> $F.enumerable
    |> $F.all({ => _1 < 20 })
    |> println;
```

#### Result

```
0
```

### Example 10. all (3)

#### Code

```javascript
var $F = Functional;
var println = System.println;

0...20
    |> $F.enumerable
    |> $F.all({ => _1 < 20 })
    |> println;
```

#### Result

```
1
```

### Example 11. any (1)

#### Code

```javascript
var $F = Functional;
var println = System.println;

0..20
    |> $F.enumerable
    |> $F.any({ => _1 >= 20 })
    |> println;
```

#### Result

```
1
```

### Example 12. any (2)

#### Code

```javascript
var $F = Functional;
var println = System.println;

0...20
    |> $F.enumerable
    |> $F.any({ => _1 >= 20 })
    |> println;
```

#### Result

```
0
```

### Example 13. sum

#### Code

```javascript
var $F = Functional;
var println = System.println;
var printlnArray = $F.toArray +> println;

1..100
    |> $F.enumerable
    |> $F.sum
    |> println;
```

#### Result

```
5050
```

### Example 14. partition

#### Code

```javascript
var $F = Functional;
var println = System.println;
var printlnArray = $F.toArray +> println;

[10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0]
    |> $F.enumerable
    |> $F.partition { => _1 % 3 == 0 }
    |> $F.enumerable
    |> $F.printlnAll;
```

#### Result

```
[9, 6, 3, 0]
[10, 8, 7, 5, 4, 2, 1]
```

### Example 15. Example (1)

#### Code

```javascript
1..
    |> Functional.enumerable
    |> Functional.drop(10)
    |> Functional.filter { => _1 % 3 == 0 }
    |> Functional.take(10)
    |> Functional.toArray
    |> System.println;
```

#### Result

```
[12, 15, 18, 21, 24, 27, 30, 33, 36, 39]
```

### Example 16. Example (2)

#### Code

```javascript
[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    |> Functional.trace
    |> Functional.enumerable
    |> Functional.each { => Functional.trace(_1) }
    |> Functional.reduce(&(r, e) => r += e, 0)
    |> Functional.trace
    ;
```

#### Result

```
[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
1
2
3
4
5
6
7
8
9
10
55
```
