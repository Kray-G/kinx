# Missionaries and Cannibals Problem

## Overview

Please see the Wikipedia.

*   [Missionaries and cannibals problem - Wikipedia](https://en.wikipedia.org/wiki/Missionaries_and_cannibals_problem)

## Examples

### Example 1. Missionaries and cannibals problem algorithm

#### Code

```javascript
const M = 3;
const C = 3;
const B = 2;

var np, solution;
var mb = [], cb = [],
    mh = [], ch = [], flag = [];
var i = 0;
var mmm = "MMMMMMMMMM", ccc = "CCCCCCCCCC";

function found(n) { /* Display a solution */
    var i;

    System.println("Solution %d" % ++solution);
    for (i = 0; i <= n; i++) {
        var m1 = mmm.subString(0, mh[i]);
        var m2 = mmm.subString(0, M-mh[i]);
        var c1 = ccc.subString(0, ch[i]);
        var c2 = ccc.subString(0, C-ch[i]);
        System.println(("%4d  %-%{M}s %-%{C}s  /  %-%{M}s %-s") % i % m1 % c1 % m2 % c2);
    }
}

function tryit() { /* Try it recursve */
    var j, m, c;

    i++;
    for (j = 1; j < np; j++) {
        if (i & 1) {  /* Go there in odd number. */
            m = mh[i - 1] - mb[j];  c = ch[i - 1] - cb[j];
        } else {      /* Come here in even number. */
            m = mh[i - 1] + mb[j];  c = ch[i - 1] + cb[j];
        }
        if (m < 0 || c < 0 || m > M || c > C ||
                (flag[m][c] & (1 << (i & 1)))) continue;
        mh[i] = m;  ch[i] = c;
        if (m == 0 && c == 0) found(i);
        else {
            flag[m][c] |= 1 << (i & 1);  tryit();
            flag[m][c] ^= 1 << (i & 1);
        }
    }
    i--;
}

var m, c;

np = 0;
for (m = 0; m <= B; m++) for (c = 0; c <= B - m; c++)
    if (m == 0 || m >= c) {
        mb[np] = m;  cb[np] = c;  np++;
    }
for (m = 0; m <= M; m++) for (c = 0; c <= C; c++)
    if ((m > 0 && m < c) || (m < M && M - m < C - c))
        flag[m][c] |= 1 | 2;
mh[0] = M;  ch[0] = C;  flag[M][C] |= 1;
solution = 0;  tryit();
if (solution == 0) System.println("No solutions.");
```

#### Result

```
Solution 1
   0  MMM CCC  /
   1  MMM C    /      CC
   2  MMM CC   /      C
   3  MMM      /      CCC
   4  MMM C    /      CC
   5  M   C    /  MM  CC
   6  MM  CC   /  M   C
   7      CC   /  MMM C
   8      CCC  /  MMM
   9      C    /  MMM CC
  10      CC   /  MMM C
  11           /  MMM CCC
Solution 2
   0  MMM CCC  /
   1  MMM C    /      CC
   2  MMM CC   /      C
   3  MMM      /      CCC
   4  MMM C    /      CC
   5  M   C    /  MM  CC
   6  MM  CC   /  M   C
   7      CC   /  MMM C
   8      CCC  /  MMM
   9      C    /  MMM CC
  10  M   C    /  MM  CC
  11           /  MMM CCC
Solution 3
   0  MMM CCC  /
   1  MM  CC   /  M   C
   2  MMM CC   /      C
   3  MMM      /      CCC
   4  MMM C    /      CC
   5  M   C    /  MM  CC
   6  MM  CC   /  M   C
   7      CC   /  MMM C
   8      CCC  /  MMM
   9      C    /  MMM CC
  10      CC   /  MMM C
  11           /  MMM CCC
Solution 4
   0  MMM CCC  /
   1  MM  CC   /  M   C
   2  MMM CC   /      C
   3  MMM      /      CCC
   4  MMM C    /      CC
   5  M   C    /  MM  CC
   6  MM  CC   /  M   C
   7      CC   /  MMM C
   8      CCC  /  MMM
   9      C    /  MMM CC
  10  M   C    /  MM  CC
  11           /  MMM CCC
```
