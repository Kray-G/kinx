# Matching Operator

## Overview

Matching operator is the interface to use Regular Expression.
Note that no escaping characters are required in the regular expression literal.

```javascript
a =~ /[\t ]+[Ss]omething/;
a !~ /[\t ]+[Ss]omething/;
```

The operator `=~` is to find matched strings. If nothing to be matched, returns false.
If matched, matched strings are returned as structured below.

```javascript
[
    {
        string: "whole matched string",
        begin: b0,
        end: e0
    },
    {
        string: "captured string 1",
        begin: b1,
        end: e1
    },
    {
        string: "captured string 2",
        begin: b2,
        end: e2
    },
    ...
]
```

The operator `!~` is used to check if not matched.
If not matched, returns true. Otherwise returns false.

The operator `=~` can be used in the loop condition as example below.

```javascript
while (a =~ /abc/) {
    // loop while matched.
}
```

There is a note when breaking the loop in the half way.
If loop is finished incompletely, the regular expression object may not be reset in the next loop.
It will be reset well in the next loop when the previous loop is completed after condition is false.
The reset will be done when:

*   The first operation.
*   The target string, which is `a` in the above example, was changed.

## Examples

### Example 1. Simple use

#### Code

```javascript
var a = "a-aaabbb,aabb-baaa,b-bbaaaa";

System.println("%{a}:");
while (group = (a =~ /\w+/)) {
    System.println("    found");
    var l = group.length();
    for (var i = 0; i < l; ++i) {
        System.println("        [%2d,%2d) = '%s'"
            % group[i].begin
            % group[i].end
            % group[i].string);
    }
}
```

#### Result

```
a-aaabbb,aabb-baaa,b-bbaaaa:
    found
        [ 0, 1) = 'a'
    found
        [ 2, 8) = 'aaabbb'
    found
        [ 9,13) = 'aabb'
    found
        [14,18) = 'baaa'
    found
        [19,20) = 'b'
    found
        [21,27) = 'bbaaaa'
```

### Example 2. Use `/=.../`

#### Code

```javascript
var a = "a=aaabbb,aabb=baaa,b=bbaaaa";

System.println("%{a}:");
while (group = (a =~ /=\w+/)) {
    System.println("    found");
    var l = group.length();
    for (var i = 0; i < l; ++i) {
        System.println("        [%2d,%2d) = '%s'"
            % group[i].begin
            % group[i].end
            % group[i].string);
    }
}
```

#### Result

```
a=aaabbb,aabb=baaa,b=bbaaaa:
    found
        [ 1, 8) = '=aaabbb'
    found
        [13,18) = '=baaa'
    found
        [20,27) = '=bbaaaa'
```

### Example 3. Use regex literal with `%m(...)`

#### Code

```javascript
var a = "abbb/aabbbaaa/bbbaa/aa";
System.println("%{a}:");
while (group = (a =~ %m(a+/))) {
    System.println("    found");
    var l = group.length();
    for (var i = 0; i < l; ++i) {
        System.println("        [%2d,%2d) = '%s'"
            % group[i].begin
            % group[i].end
            % group[i].string);
    }
}
```

#### Result

```
abbb/aabbbaaa/bbbaa/aa:
    found
        [10,14) = 'aaa/'
    found
        [17,20) = 'aa/'
```
