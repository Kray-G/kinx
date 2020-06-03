
# for-in statement

## Overview

`for-in` is the statement for loop with collection. Basic syntax is as below.
`var` for declaration of a variable is not required when you want to use the variable which is already declared at the outside scope.

```javascript
for (var e in collection) {
    ...
}
```

The following objects can be used at the `collection` part.

* Range object.
* Array object.
* Key-Value object.

See examples below about how to work with each object above.

## Examples

### Example 1. Range

#### Code

```javascript
for (var e in 2..10) {
    System.println(e);
}
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

### Example 2. Range with excluding end

#### Code

```javascript
for (var e in 2...10) {
    System.println(e);
}
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
```

### Example 3. Array

#### Code

```javascript
for (var e in [2,3,4,5,6,7,8,9,10]) {
    System.println(e);
}
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

### Example 4. Array variation (1)

#### Code

```javascript
for ([i, j] in [[1,2], [3,4], [5,6]]) {
    System.println("[%{i}, %{j}]");
}
```

#### Result

```
[1, 2]
[3, 4]
[5, 6]
```

### Example 5. Array variation (2)

#### Code

```javascript
for ([i, j] in [1, 2, 3]) {
    System.println([i, j]);
}
```

#### Result

Note that the result is **NOT** `[1, 2]` and `[3, null]`, against your expected.

```
[1, null]
[2, null]
[3, null]
```

### Example 6. Key-Value object

#### Code

```javascript
var obj = { a: 10, b: 100 };
for ([key, value] in obj) {
    System.println("key: %{key} => value: %{value}");
}
```

#### Result

```
key: a => value: 10
key: b => value: 100
```

