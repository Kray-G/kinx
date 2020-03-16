# Heapsort

## Overview

Please see the Wikipedia.

*   [Heapsort - Wikipedia](https://en.wikipedia.org/wiki/Heapsort)

## Examples

### Example 1. Heapsort Algorithm

#### Code

```javascript
function heapsort(n, a) {
    var i, j, k, x;
    for (k = n / 2; k >= 1; k--) {
        i = k;  x = a[i];
        while ((j = 2 * i) <= n) {
            if (j < n && a[j] < a[j + 1]) j++;
            if (x >= a[j]) break;
            a[i] = a[j];  i = j;
        }
        a[i] = x;
    }
    while (n > 1) {
        x = a[n];  a[n] = a[1];  n--;
        i = 1;
        while ((j = 2 * i) <= n) {
            if (j < n && a[j] < a[j + 1]) j++;
            if (x >= a[j]) break;
            a[i] = a[j];  i = j;
        }
        a[i] = x;
    }
}

function show(title, a) {
    System.print(title);
    a.each(&(e, i) => {
        System.print(" %2d" % e) if (i >= 1);
    });
    System.print("\n");
}

function demo() {
    var a = [0, 69, 63, 88, 85, 26, 77, 51, 42, 16, 4, 20, 18, 18, 40, 23, 26, 24, 63, 96, 59];

    show("Before:", a);
    heapsort(a.length() - 1, a);
    show("After: ", a);
}

demo();
```

#### Result

```
Before: 69 63 88 85 26 77 51 42 16  4 20 18 18 40 23 26 24 63 96 59
After:   4 16 18 18 20 23 24 26 26 40 42 51 59 63 63 69 77 85 88 96
```
