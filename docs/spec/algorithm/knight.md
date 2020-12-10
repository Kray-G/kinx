# Knight Tour

## Overview

Please see the Wikipedia.

*   [Knight tour - Wikipedia](https://en.wikipedia.org/wiki/Knight's_tour)

## Examples

### Example 1. Knight Tour Algorithm

#### Code

```javascript
const N = 5;    // N x N
const SOLUTIONMAX = 304;

var board = [],
    dx = [ 2, 1,-1,-2,-2,-1, 1, 2 ],
    dy = [ 1, 2, 2, 1,-1,-2,-2,-1 ];
var count = 0;
var solution = 0;

function printboard() {
    if (++solution < SOLUTIONMAX) return;
    System.print("\nSolution %d\n" % solution);
    for (var i = 2; i <= N + 1; i++) {
        for (var j = 2; j <= N + 1; j++) System.print("%4d" % board[i][j]);
        System.print("\n");
    }
}

function test(x, y) {
    if (board[x][y] != 0) return;
    board[x][y] = ++count;
    if (count == N * N) printboard();
    else for (var i = 0; i < 8; i++) test(x + dx[i], y + dy[i]);
    board[x][y] = 0;  count--;
}

function knight() {
    for (var i = 0; i <= N + 3; i++)
        for (var j = 0; j <= N + 3; j++) board[i][j] = 1;
    for (var i = 2; i <= N + 1; i++)
        for (var j = 2; j <= N + 1; j++) board[i][j] = 0;
    test(2, 2);
}

knight();
```

#### Result

```
Solution 304
   1  10   5  16  25
   4  17   2  11   6
   9  20  13  24  15
  18   3  22   7  12
  21   8  19  14  23
```
