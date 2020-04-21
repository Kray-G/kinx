# String#next

## Overview

`String#next` is used in Range object.

*   [String#next](https://docs.ruby-lang.org/en/master/String.html#method-i-next)

## Examples

### Example 1. CRC32 Algorithm

#### Code

```javascript
System.println("aa".next());
System.println("88".next().next());
System.println("99".next());
System.println("ZZ".next());
System.println("a9".next());
System.println("-9".next());
System.println("1.9.9".next());
System.println(".".next());
System.println("a".next());
System.println("z".next());
System.println("Ad".next());
System.println("Az".next());
System.println("zz".next());
System.println("4".next());
System.println("9".next());
System.println("a9".next());
System.println("9z".next());
System.println("4:5:9".next());
System.println("-5".next());
System.println(":9".next());
```

#### Result

```
ab
90
100
AAA
b0
-10
2.0.0
/
b
aa
Ae
Ba
aaa
5
10
b0
10a
4:6:0
-6
:10
```
