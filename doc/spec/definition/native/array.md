# Array in Native

## Overview

Native function can use an array of Integer or Double.
For that, the type will be `int[]` for an array of integer, and `dbl[]` for an array of double.

You can also use a multidimensional array like `int[][]`.

## Examples

### Example 1. Simple an array of integer in native

#### Code

```javascript
native<int[]> makeArray(a:int[]) {
    for (var i = 0; i < 10; ++i) {
        a[i] = i;
    }
    return a;
}
System.println(makeArray([]));
```

#### Result

```
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
```

### Example 2. Simple an array of double in native

#### Code

```javascript
native<dbl[]> makeArray(a:dbl[]) {
    for (var i = 0; i < 10; ++i) {
        a[i] = i * 0.1;
    }
    return a;
}
System.println(makeArray([]));
```

#### Result

```
[0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]
```

### Example 3. Multidimensional array in native

#### Code

```javascript
native<dbl[]> makeArray(a:dbl[][]) {
    var d:dbl[] = a[0];
    for (var i = 0; i < 10; ++i) {
        d[i] = i * 0.1;
    }
    return a;
}
System.println(makeArray([[]]));
```

#### Result

```
[[0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]]
```

### Example 4. Array map in native

#### Code

```javascript
native<dbl[]> mapArray(a:dbl[]) {
    for (var i = 0, n = a.length(); i < n; ++i) {
        a[i] = a[i] * a[i];
    }
    return a;
}
System.println(mapArray([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]));
```

#### Result

```
[1, 4, 9, 16, 25, 36, 49, 64, 81, 100]
```
