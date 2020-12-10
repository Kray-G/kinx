# Merge Sort

## Overview

Please see the Wikipedia.

*   [Merge sort - Wikipedia](https://en.wikipedia.org/wiki/Merge_sort)

## Examples

### Example 1. Merge Sort Algorithm

#### Code

```javascript
function mergesort(a) {
    function m(first, last) {
        var middle, work = [];
        var i, j, k, p;

        if (first < last) {
            middle = Integer.parseInt((first + last) / 2);
            m(first, middle);
            m(middle + 1, last);
            p = 0;
            for (i = first; i <= middle; i++) {
                work[p++] = a[i];
            }
            i = middle + 1;
            j = 0;
            k = first;
            while (i <= last && j < p) {
                if (work[j] <= a[i]) {
                    a[k++] = work[j++];
                } else {
                    a[k++] = a[i++];
                }
            }
            while (j < p) {
                a[k++] = work[j++];
            }
        }
    }
    return m(0, a.length() - 1);
}

function show(title, a) {
    System.print(title);
    a.each(&(e) => System.print(" %2d" % e));
    System.print("\n");
}

function demo() {
    var a = [69, 63, 88, 85, 26, 77, 51, 42, 16, 4, 20, 18, 18, 40, 23, 26, 24, 63, 96, 59];

    show("Before:", a);
    mergesort(a);
    show("After: ", a);
}

demo();
```

#### Result

```
Before: 69 63 88 85 26 77 51 42 16  4 20 18 18 40 23 26 24 63 96 59
After:   4 16 18 18 20 23 24 26 26 40 42 51 59 63 63 69 77 85 88 96
```
