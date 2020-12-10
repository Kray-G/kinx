# N Queens

## Overview

Please see the Wikipedia.

*   [Eight queens puzzle - Wikipedia](https://en.wikipedia.org/wiki/Eight_queens_puzzle)

## Examples

### Example 1. 8 Queens Algorithm

Here is 8 Queens puzzle algorithm.

#### Code

```javascript
var a = [], b = [], c = [], x = [];
var solution = 0;
const SOLUTIONMAX = 92;

function found(n) {
    if (++solution < SOLUTIONMAX) return;
    System.print("\nSolution %d\n" % solution);
    for (var i = 0; i < n; i++) {
        for (var j = 0; j < n; j++)
            if (x[i] == j) System.print(" Q");
            else           System.print(" .");
        System.print("\n");
    }
}

function test(i, n) {
    for (var j = 0; j < n; j++)
        if (a[j] && b[i + j] && c[i - j + n - 1]) {
            x[i] = j;
            if (i < n - 1) {
                a[j] = b[i + j] = c[i - j + n - 1] = 0;
                test(i + 1, n);
                a[j] = b[i + j] = c[i - j + n - 1] = 1;
            } else found(n);
        }
}

function nqueen(n) {    
    for (var i = 0; i < n; i++)         a[i] = 1;
    for (var i = 0; i < 2 * n - 1; i++) b[i] = 1;
    for (var i = 0; i < 2 * n - 1; i++) c[i] = 1;
    test(0, n);
}

nqueen(8);
```

#### Result

```
Solution 92
 . . . . . . . Q
 . . . Q . . . .
 Q . . . . . . .
 . . Q . . . . .
 . . . . . Q . .
 . Q . . . . . .
 . . . . . . Q .
 . . . . Q . . .
```
