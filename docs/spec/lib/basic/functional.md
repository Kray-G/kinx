
# Functional

## Overview

### `Functional`

The `Functional` is a global instance to deal with functional methods.
In general, when you use a method of some object in pipeline, you should do it as a following example.

```javascript
obj |> { &(obj) => obj.map({ => _1 * 2 }) }
    |> { &(obj) => obj.method() }
    |> // ... and so on.
```

The `Functional` instance will wrap the actual function object and pass it into the pipeline.
For example, you can write it as follows against the example above.

```javascript
obj |> Functional.map { => _1 * 2 }
    |> Functional.method()  // Note that it needs a `()` to use an actual function object
                            // which receives an object at a first argument.
    |> // ... and so on.
```

### `Enumerable`

The `Enumerable` is not only as a `module` but also a global instance having functional enumerable methods
which is useful in [a pipeline](../../statement/expression/pipeline.md).
For example, when multiple values are passed to the next function via pipeline,
a method in `Enumerable` can fetch a value one by one and pass the value to a next function in order.

Therefore, `Enumerable` can handle an infinite sequence.
This is an example below.

```javascript
1..
    |> Functional.enumerable
    |> Enumerable.drop(10)
    |> Enumerable.filter { => _1 % 3 == 0 }
    |> Enumerable.take(10)
    |> Enumerable.toArray
    |> System.println;
```

The `Functional.enumerable` is a magic function to make a sequence change to an item which `Enumerable` methods can use.
You can write it also like an example below, but the way how to write in the above example is more useful.

```javascript
new Functional.Enumerator(1..)
    |> Enumerable.drop(10)
    |> Enumerable.filter { => _1 % 3 == 0 }
    |> Enumerable.take(10)
    |> Enumerable.toArray
    |> System.println;
```

### Methods

The methods of `Enumerable` to pass values in pipeline is currently as follows.

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

### Enumerable.trace

This is not a `functional` method but a method just to trace and display items passed in the pipeline.
This method will display an item and pass it to the next as it is.

Therefore, `Enumerable.trace` can be used before `Functional.enumerable` as an example below.

```javascript
[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    |> Enumerable.trace
    |> Functional.enumerable
    |> Enumerable.each { => Enumerable.trace(_1) }
    |> Enumerable.reduce(&(r, e) => r += e, 0)
    |> Enumerable.trace
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
var $E = Enumerable;
var println = System.println;
var printlnArray = $E.toArray +> println;

new Functional.Enumerator(1..10)
    |> $E.filter({ => _1 <= 4 })
    |> $E.map({ => _1 * 10 })
    |> printlnArray;
```

#### Result

```
[10, 20, 30, 40]
```

### Example 2. With Function Composition Operator

#### Code

```javascript
var $E = Enumerable;
var println = System.println;
var printlnArray = $E.toArray +> println;

1..10
    |> Functional.enumerable
    |> $E.filter({ => _1 < 7 }) +> $E.map({ => _1 * 100 }) +> printlnArray
    ;
```

#### Result

```
[100, 200, 300, 400, 500, 600]
```

### Example 3. dropWhile

#### Code

```javascript
var $E = Enumerable;
var println = System.println;
var printlnArray = $E.toArray +> println;

1..20
    |> Functional.enumerable
    |> $E.dropWhile { => _1 < 10 || _1 % 2 == 0 }
    |> printlnArray;
```

#### Result

```
[11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
```

### Example 4. flatMap (1)

#### Code

```javascript
var $E = Enumerable;
var println = System.println;
var printlnArray = $E.toArray +> println;

[[1, 2], [3, 4]]
    |> Functional.enumerable
    |> $E.flatMap { => _1.map { => _1 * 2 } }
    |> printlnArray;
```

#### Result

```
[2, 4, 6, 8]
```

### Example 5. flatMap (2)

#### Code

```javascript
var $E = Enumerable;
var println = System.println;
var printlnArray = $E.toArray +> println;

[10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0]
    |> Functional.enumerable
    |> $E.flatMap { => [_1, _1 * 2] }
    |> printlnArray;
```

#### Result

```
[10, 20, 9, 18, 8, 16, 7, 14, 6, 12, 5, 10, 4, 8, 3, 6, 2, 4, 1, 2, 0, 0]
```

### Example 6. sort

#### Code

```javascript
var $E = Enumerable;
var println = System.println;
var printlnArray = $E.toArray +> println;

[10, 21, 92, 22, 37, 23, 98, 76, 56 , 48, 88, 76, 109, 2, 54]
    |> $E.trace
    |> Functional.enumerable
    |> $E.shuffle
    |> printlnArray <+ $E.sort
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
var $E = Enumerable;
var println = System.println;
var printlnArray = $E.toArray +> println;

100..
    |> Functional.enumerable
    |> $E.println("==> ")
    |> $E.filter { => _1 % 2 == 0 }
    |> $E.println("filterred: ")
    |> $E.take(10)
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
var $E = Enumerable;
var println = System.println;

1..20
    |> Functional.enumerable
    |> $E.all({ => _1 > 0 })
    |> println;
```

#### Result

```
1
```

### Example 9. all (2)

#### Code

```javascript
var $E = Enumerable;
var println = System.println;

0..20
    |> Functional.enumerable
    |> $E.all({ => _1 < 20 })
    |> println;
```

#### Result

```
0
```

### Example 10. all (3)

#### Code

```javascript
var $E = Enumerable;
var println = System.println;

0...20
    |> Functional.enumerable
    |> $E.all({ => _1 < 20 })
    |> println;
```

#### Result

```
1
```

### Example 11. any (1)

#### Code

```javascript
var $E = Enumerable;
var println = System.println;

0..20
    |> Functional.enumerable
    |> $E.any({ => _1 >= 20 })
    |> println;
```

#### Result

```
1
```

### Example 12. any (2)

#### Code

```javascript
var $E = Enumerable;
var println = System.println;

0...20
    |> Functional.enumerable
    |> $E.any({ => _1 >= 20 })
    |> println;
```

#### Result

```
0
```

### Example 13. sum

#### Code

```javascript
var $E = Enumerable;
var println = System.println;
var printlnArray = $E.toArray +> println;

1..100
    |> Functional.enumerable
    |> $E.sum
    |> println;
```

#### Result

```
5050
```

### Example 14. partition

#### Code

```javascript
var $E = Enumerable;
var println = System.println;
var printlnArray = $E.toArray +> println;

[10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0]
    |> Functional.enumerable
    |> $E.partition { => _1 % 3 == 0 }
    |> Functional.enumerable
    |> $E.printlnAll;
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
    |> Enumerable.drop(10)
    |> Enumerable.filter { => _1 % 3 == 0 }
    |> Enumerable.take(10)
    |> Enumerable.toArray
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
    |> Enumerable.trace
    |> Functional.enumerable
    |> Enumerable.each { => Enumerable.trace(_1) }
    |> Enumerable.reduce(&(r, e) => r += e, 0)
    |> Enumerable.trace
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

### Example 17. Functional (1)

#### Code

```javascript
class Object(list_) {
    public map(func) {
        list_ = list_.map { => func(_) };
        return this;
    }
    public hoge() {
        list_ = list_ + list_;
        return this;
    }
    public value() {
        return list_;
    }
}

var r = new Object([1, 2, 3])
    |> Functional.map { => _ + 1 }
    |> Functional.map { => _ * 2 }
    |> Functional.hoge()    // to call methodMissing and register it, and use it.
    |> Functional.map { => _ * 2 }
    |> Functional.value()   // to call methodMissing and register it, and use it.
    ;
System.println(r); // [8, 12, 16, 8, 12, 16]
```

#### Result

```
[8, 12, 16, 8, 12, 16]
```

### Example 18. Functional (2)

#### Code

```javascript
var test = (1..10).toArray();
var r = test
    |> { => Array.map(_) { => _1 + ":" + _1 } }
    |> { => Array.map(_) { => String.split(_1, ":") } }
    |> Array.flatten
    ;
System.println(r);
var r = test
    |> Functional.map { => _1 + ":" + _1 }
    |> Functional.map { => String.split(_1, ":") }
    |> Array.flatten
    ;
System.println(r);
```

#### Result

```
["1", "1", "2", "2", "3", "3", "4", "4", "5", "5", "6", "6", "7", "7", "8", "8", "9", "9", "10", "10"]
["1", "1", "2", "2", "3", "3", "4", "4", "5", "5", "6", "6", "7", "7", "8", "8", "9", "9", "10", "10"]
```
