# SAT Solver

## Overview

Please see the Wikipedia.

*   [SAT Solver - Wikipedia](https://en.wikipedia.org/wiki/Boolean_satisfiability_problem)

## Examples

### Example 1. 8 Queens

#### Code

```javascript
using SatisfiablitySolver;

const N = 8;
var cnf = [];
var solution = 0;

function display(e) {
    var board = [];
    for (var ijQ = 0, l = e.length(); ijQ < l; ++ijQ) {
        var i = ijQ % N;
        var j = Integer.parseInt(ijQ / N);
        board[i][j] = e[ijQ] > 0;
    }
    for (var jx = 0; jx < N; ++jx) {
        System.print("|");
        for (var ix = 0; ix < N; ++ix) {
            System.print(board[ix][jx] ? " Q" : " .");
        }
        System.println(" |");
    }
}

function getVarNum(i, j) {
    return (i + j * N) + 1;
}

function addClauses(s, i, j) {
    const ijQ = getVarNum(i, j);

    /* right */
    for (var ix = i + 1; ix < N; ++ix) {
        s.addClause([-ijQ, -getVarNum(ix, j)]);
    }

    /* down */
    for (var jx = j + 1; jx < N; ++jx) {
        s.addClause([-ijQ, -getVarNum(i, jx)]);
    }

    /* right-down */
    for (var ix = i + 1, jx = j + 1; ix < N && jx < N; ++ix, ++jx) {
        s.addClause([-ijQ, -getVarNum(ix, jx)]);
    }

    /* left-down */
    for (var ix = i - 1, jx = j + 1; ix >= 0 && jx < N; --ix, ++jx) {
        s.addClause([-ijQ, -getVarNum(ix, jx)]);
    }
}

var s = new Satisfiablity();

/* Possible answers */
for (var jx = 0; jx < N; ++jx) {
    s.addClause(N.times().map { => getVarNum(_1, jx) });
}
/* Restrictions */
for (var ix = 0; ix < N; ++ix) {
    for (var jx = 0; jx < N; ++jx) {
        addClauses(s, ix, jx);
    }
}
display(s.solve());
```

#### Result

```
| . . . . . . . Q |
| . Q . . . . . . |
| . . . . Q . . . |
| . . Q . . . . . |
| Q . . . . . . . |
| . . . . . . Q . |
| . . . Q . . . . |
| . . . . . Q . . |
```


### Example 2. Number Place

#### Code

```javascript
using SatisfiablitySolver;

const N = Integer.parseInt($$[1] || 3);
const P = Integer.parseInt($$[2] || 0);
const R = N * N;
var solution = 0;

function display(test, e) {
    var board = e ? [] : test.clone();
    if (e) {
        for (var ijv = 0, l = e.length(); ijv < l; ++ijv) {
            if (e[ijv] > 0) {
                var value = e[ijv];
                var v = value % R;
                var ij = Integer.parseInt((value-1) / R);
                var i = ij % R;
                var j = Integer.parseInt(ij / R);
                board[j][i] = v == 0 ? R : v;
            }
        }
    }
    for (var jx = 0; jx < R; ++jx) {
        if (jx % N == 0) System.println((("+" + ("-" * (3 * N + 1))) * N) + "+");
        for (var ix = 0; ix < R; ++ix) {
            if (ix % N == 0) System.print(ix == 0 ? "|" : " |");
            if (board[jx][ix]) {
                System.print(" " + ("%2d" % board[jx][ix]).format());
            } else {
                System.print("  .");
            }
        }
        System.println(" |");
    }
    System.println((("+" + ("-" * (3 * N + 1))) * N) + "+");
}

function getVarNum(i, j, v) {
    return ((i + j * R) * R) + v;
}

function addClauses(s, i, j, v) {
    const ijv = getVarNum(i, j, v);

    // There is at most one number in each cell. (Cell - uniqueness)
    for (var vi = 1; vi <= R; ++vi) {
        if (v != vi) {
            s.addClause([-ijv, -getVarNum(i, j, vi)]);
        }
    }

    // Each number appears at most once in each row. (Row - uniqueness)
    for (var ix = i + 1; ix < R; ++ix) {
        s.addClause([-ijv, -getVarNum(ix, j, v)]);
    }

    // Each number appears at most once in each column. (Column - uniqueness)
    for (var jx = j + 1; jx < R; ++jx) {
        s.addClause([-ijv, -getVarNum(i, jx, v)]);
    }

    var si = Integer.parseInt(i / N) * N;
    var sj = Integer.parseInt(j / N) * N;
    var ei = si + N;
    var ej = sj + N;
    // Each number appears at most once in each block. (Block - uniqueness)
    for (var ix = si; ix < ei; ++ix) {
        for (var jx = sj; jx < ej; ++jx) {
            const ijv2 = getVarNum(ix, jx, v);
            if (ijv2 > ijv) {
                s.addClause([-ijv, -ijv2]);
            }
        }
    }
}

function setup(test) {
    var s = new Satisfiablity();

    // Adding this restrictions makes a performance increase.
    for (var v = 1; v <= R; ++v) {
        // Each number appears at least once in each row. (Row - definedness)
        for (var j = 0; j < R; ++j) {
            s.addClause(R.times().map { => getVarNum(_1, j, v) });
        }
        // Each number appears at least once in each column. (Column - definedness)
        for (var i = 0; i < R; ++i) {
            s.addClause(R.times().map { => getVarNum(i, _1, v) });
        }
    }
    for (var j = 0; j < R; ++j) {
        for (var i = 0; i < R; ++i) {
            const ijv = ((i + j * R) * R);
            var v = test[j][i];
            if (v == 0) {
                // There is at least one number in each cell. (Cell - definedness)
                s.addClause(R.times().map { => ijv + (_1 + 1) });
            } else {
                s.addClause([ ijv + v ]);
            }
            R.times().each { => addClauses(s, i, j, (_1 + 1)) };
        }
    }

    return s;
}

const _ = 0;
var test = [
    [ _, _, _, _, _, _, _, 7, _],
    [ 1, _, 5, _, 3, 6, 4, _, 9],
    [ _, 7, 4, 9, _, _, 5, _, _],
    [ _, _, _, _, _, 5, 8, _, _],
    [ _, 1, _, 3, _, _, _, _, 5],
    [ 7, _, _, _, _, 8, 1, _, _],
    [ 6, 4, _, _, _, _, _, _, 7],
    [ _, 3, _, 6, 2, _, _, 8, 4],
    [ _, _, _, 5, 9, _, _, _, 3],
];

System.println("* %dx%d Number Place" % R % R);
display(test);
var s = setup(test);
display(test, s.solve());
```

#### Result

```
* 9x9 Number Place
+----------+----------+----------+
|  .  .  . |  .  .  . |  .  7  . |
|  1  .  5 |  .  3  6 |  4  .  9 |
|  .  7  4 |  9  .  . |  5  .  . |
+----------+----------+----------+
|  .  .  . |  .  .  5 |  8  .  . |
|  .  1  . |  3  .  . |  .  .  5 |
|  7  .  . |  .  .  8 |  1  .  . |
+----------+----------+----------+
|  6  4  . |  .  .  . |  .  .  7 |
|  .  3  . |  6  2  . |  .  8  4 |
|  .  .  . |  5  9  . |  .  .  3 |
+----------+----------+----------+
+----------+----------+----------+
|  9  6  2 |  4  5  1 |  3  7  8 |
|  1  8  5 |  7  3  6 |  4  2  9 |
|  3  7  4 |  9  8  2 |  5  6  1 |
+----------+----------+----------+
|  4  9  6 |  1  7  5 |  8  3  2 |
|  2  1  8 |  3  6  9 |  7  4  5 |
|  7  5  3 |  2  4  8 |  1  9  6 |
+----------+----------+----------+
|  6  4  9 |  8  1  3 |  2  5  7 |
|  5  3  1 |  6  2  7 |  9  8  4 |
|  8  2  7 |  5  9  4 |  6  1  3 |
+----------+----------+----------+
```
