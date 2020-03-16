# Quicksort

## Overview

Please see the Wikipedia.

*   [Quicksort - Wikipedia](https://en.wikipedia.org/wiki/Quicksort)

## Examples

### Example 1. Quicksort Algorithm

#### Code

```javascript
function quicksort(a, first, last) {
    var i = first;
    var j = last;
    var x = a[(first + last) / 2];
    while (true) {
        while (a[i] < x) i++;
        while (x < a[j]) j--;
        if (i >= j) break;

        [a[i], a[j]] = [a[j], a[i]];
        ++i; --j;
    }
    if (first  < i - 1)
        quicksort(a, first , i - 1);
    if (j + 1 < last)
        quicksort(a, j + 1, last);
}

function show(title, a) {
    System.print(title);
    a.each(&(e) => System.print(" %2d" % e));
    System.print("\n");
}

function demo() {
    var a = [69, 63, 88, 85, 26, 77, 51, 42, 16, 4, 20, 18, 18, 40, 23, 26, 24, 63, 96, 59];

    show("Before:", a);
    quicksort(a, 0, a.length() - 1);
    show("After: ", a);
}

demo();
```

#### Result

```
Before: 69 63 88 85 26 77 51 42 16  4 20 18 18 40 23 26 24 63 96 59
After:   4 16 18 18 20 23 24 26 26 40 42 51 59 63 63 69 77 85 88 96
```
