# Merge Sort

## Overview

Please see the Wikipedia.

*   [Merge sort - Wikipedia](https://en.wikipedia.org/wiki/Merge_sort)

## Examples

### Example 1. Merge Sort Algorithm

#### Code

```javascript
function merge(a, b) {
    var c = [];
    while (a.length() && b.length()) {
        if (a[0] > b[0]) {
            c.push(b.shift());
        } else {
            c.push(a.shift());
        }
    }
    while (a.length()) {
        c.push(a.shift());
    }
    while (b.length()) {
        c.push(b.shift());
    }
    return c;
}

function mergesort(a) {
    var n = a.length();
    return a if (n <= 1);

    var l1 = [];
    var l2 = [];
    var i = 0; n2 = n / 2;
    while (i < n2) {
        l1.push(a[i]);
        ++i;
    }
    while (i < n) {
        l2.push(a[i]);
        ++i;
    }
    l1 = mergesort(l1);
    l2 = mergesort(l2);
    return merge(l1, l2);
}

function show(title, a) {
    System.print(title);
    a.each(&(e) => System.print(" %2d" % e));
    System.print("\n");
}

function demo() {
    var a = [69, 63, 88, 85, 26, 77, 51, 42, 16, 4, 20, 18, 18, 40, 23, 26, 24, 63, 96, 59];

    show("Before:", a);
    a = mergesort(a);
    show("After: ", a);
}

demo();
```

#### Result

```
Before: 69 63 88 85 26 77 51 42 16  4 20 18 18 40 23 26 24 63 96 59
After:   4 16 18 18 20 23 24 26 26 40 42 51 59 63 63 69 77 85 88 96
```
