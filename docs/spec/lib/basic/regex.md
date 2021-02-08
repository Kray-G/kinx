# class Regex

## Overview

class Regex is for **Regular expression**.

### Supported Regular Expression

Supported all features of [Oniguruma](https://github.com/kkos/oniguruma).
See below for details.

* https://github.com/kkos/oniguruma/blob/master/doc/RE

### Regular Expression Literal

You can use a regular expression as literal with surrounded by `/`.
Between `/` and `/`, you do not have to escape characters like `\n`.

```javascript
/ab+[\t\n]/
```

The above example is the same as below.

```javascript
new Regex("ab+[\\t\\n]");  // same as /ab+[\t\n]/
new Regex(%|ab+[\t\n]|);   // same as /ab+[\t\n]/
```

If you want to change the character of `/` for a literal, any character used with the prefix of `%m` is available.
In that case, you do not have to escape a character except the character used with the prefix of `%m`.

If you use a bracket character, you can use a close character corresponding to the open character which you used.

```javascript
%m<ab+[\t\n]>  // same as /ab+[\t\n]/
%m(ab+[\t\n])  // same as /ab+[\t\n]/
```

### `=~` Operator and `=~` Operator

These operators are described at the document below.
Please see the document below for details.

*   [Matching Operation](../../statement/expression/matching.md)

### Methods for `String`

A regular expression object can be directly used for the following methods of a string.

#### replace

* `replace` ... Use as specifying a condition string.

```javascript
var s = "xabbbbbcabbc".replace(/ab+/, ",");
System.println(s);
```

Here is the result.

```
x,c,c
```

#### split

* `split` ... Use as a separator condition.

```javascript
var s = "xabbbbbcabbc".split(/ab+/);
s.each(&(e) => System.println(e));
```

Here is the result.

```
x
c
c
```

### Notes

There is a note when it is used in a condition expression of loop like `while`.

For example, you can loop until not matched with the string of `str`.
But if the loop has ended by such as `break`, there is a situation that the regular expression object has not correctly been reset in the start of the next loop.

```javascript
while (group = (str =~ /ab+/)) {
    /* block */
}
```

A regular expression object will be reset with the following 2 situations.

*   The first evaluation. It includes th situation where the last same loop has been completed correctly.
*   A content of `str` has been changed.

This is currently a restriction.

## Examples

### Example 1. `=~` Operator

#### Code

```javascript
var a = "111/aaa/bbb/ccc/ddd";
while (group = (a =~ /\w+\//)) {
    for (var i = 0, len = group.length(); i < len; ++i) {
        System.println("found[%2d,%2d) = %s"
            % group[i].begin
            % group[i].end
            % group[i].string);
    }
}
```

#### Result

```
found[ 0, 4) = 111/
found[ 4, 8) = aaa/
found[ 8,12) = bbb/
found[12,16) = ccc/
```

### Example 2. `=!` Operator

#### Code

```javascript
var s = "XYZXYZ";
if (s !~ /ABC/) {
    System.println("ABC is not included.");
}
```

#### Result

```
ABC is not included.
```

### Example 3. `String#replace()`

#### Code

```javascript
var s = "xabbbbbcabbc".replace(/ab+/, ",");
System.println(s);
```

#### Result

```
x,c,c
```

### Example 4. `String#split()`

#### Code

```javascript
var s = "xabbbbbcabbc".split(/ab+/);
s.each(&(e) => System.println(e));
```

#### Result

```
x
c
c
```

### Example 5. `%m` Prefix (1)

#### Code

```javascript
var a = "111/aaa/bbb/ccc/ddd";
while (group = (a =~ %m(\w+/))) {
    for (var i = 0, len = group.length(); i < len; ++i) {
        System.println("found[%2d,%2d) = %s"
            % group[i].begin
            % group[i].end
            % group[i].string);
    }
}
```

#### Result

```
found[ 0, 4) = 111/
found[ 4, 8) = aaa/
found[ 8,12) = bbb/
found[12,16) = ccc/
```

### Example 6. `%m` Prefix (2)

#### Code

```javascript
var a = "111/aaa/bbb/ccc/ddd";
while (group = (a =~ %m<\w+/>)) {
    for (var i = 0, len = group.length(); i < len; ++i) {
        System.println("found[%2d,%2d) = %s"
            % group[i].begin
            % group[i].end
            % group[i].string);
    }
}
```

#### Result

```
found[ 0, 4) = 111/
found[ 4, 8) = aaa/
found[ 8,12) = bbb/
found[12,16) = ccc/
```

### Example 7. `%m` Prefix (3)

#### Code

```javascript
var a = "111/aaa/bbb/ccc/ddd";
while (group = (a =~ %m1\w+/1)) {
    for (var i = 0, len = group.length(); i < len; ++i) {
        System.println("found[%2d,%2d) = %s"
            % group[i].begin
            % group[i].end
            % group[i].string);
    }
}
```

#### Result

```
found[ 0, 4) = 111/
found[ 4, 8) = aaa/
found[ 8,12) = bbb/
found[12,16) = ccc/
```
