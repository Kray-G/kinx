# Semantic Version

## Overview

`SemanticVersion` class is the class to use a semantic version.

### Semantic Version

This class is supporting a following spec.

1. The version is following the format of `x.y.z[-prerelease[.n[.m]][+build[.i[.j]]]`.
    * Meaning
        * `x` : Major version.
        * `y` : Minor versoin.
        * `z` : Patch version.
        * `prerelease` : Identifier string of pre-release.
        * `n.m` : Pre-release number.
        * `build` : Identifier string of build.
        * `n.m` : Build number.
    * Example
        * `1.0.0`
        * `1.0.0-alpha.1`
        * `1.0.0-beta.1.0`
        * `1.0.0-beta.1.0+build.1`
        * `1.0.0-beta.1.0+build.2.3.0`
2. Rule of comparing versions for pre-release.
    * Pre-release means an older version.
        * For example, `1.0.0` is newwer than `1.0.0-alpha.1`.
    * Pre-release string is compared by alphabetical.
        * For example, `1.0.0-beta.1` is newwer than `1.0.0-alpha.1`.
    * Pre-release number is compared when the version and the pre-release string is the same.
        * For example, `1.0.0-beta.2` is newwer than `1.0.0-beta.1`.
3. Rule of comparing versions for build.
    * Build string and number is not used in comparison.
        * For example, `1.0.0-beta.1+build.1` is same as `1.0.0-beta.1`.
        * `1.0.0-beta.1+build.1` is also same as `1.0.0-beta.1+build.2`.

### `using`

To use SemanticVersion class, use `using` directive first.

```javascript
using SemanticVersion;
```

### class SemanticVersion

To instantiate it, use `new` operator as well as a normal class.

```javascript
using SemanticVersion;
var version = new SemanticVersion("1.0.0");
```

### Comparing Versions

You can compare between instances of SemanticVersion class.
The following operators are supported.

| Operator |                                   Meaning                                   |
| :------: | --------------------------------------------------------------------------- |
|   `==`   | true if lhs and rhs are the same.                                           |
|   `!=`   | true if lhs and rhs are not the same.                                       |
|   `>`    | true if the version of lhs is greater than the version of rhs.              |
|   `<`    | true if the version of lhs is less than the version of rhs.                 |
|   `>=`   | true if the version of lhs is greater than or equals to the version of rhs. |
|   `<=`   | true if the version of lhs is less than or equals to the version of rhs.    |

Here is the example below.

```javascript
using SemanticVersion;
var version1 = new SemanticVersion("1.4.10");
var version2 = new SemanticVersion("2.1.0");
System.println(version1 == version2);   // => false
System.println(version1 != version2);   // => true
System.println(version1 > version2);    // => false
System.println(version1 < version2);    // => true
System.println(version1 >= version2);   // => false
System.println(version1 <= version2);   // => true
```

### Matching To The Pattern

You can also check if the version is matching to the pattern you specified.
In the pattern, you can use `*` which means any number.
Moreover, you can specify the operator to compare such as `>`.
For example, it is `1.1.*`,  `>1.1.*`, `<=2`, and so on.

`*` can be used from the right side, so you can not use it like `1.*.10`.
And `.*` can be omitted like `1.1` which means `1.1.*`.

Here is the example below.

```javascript
using SemanticVersion;
var version = new SemanticVersion("1.1.10");
System.println(version.match("1.1.10"));    // => true
System.println(version.match("1.1.*"));     // => true
System.println(version.match("1.2.*"));     // => false
System.println(version.match(">1.1"));      // => false
System.println(version.match(">=1.1"));     // => true
System.println(version.match(">1.1.2"));    // => true
```

## Examples

### Example 1. SemanticVersion Test (1)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "1.0.0";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.0 match ("1.0.0") => true : expected => true
```

### Example 2. SemanticVersion Test (2)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "1.0.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.0 match ("1.0.*") => true : expected => true
```

### Example 3. SemanticVersion Test (3)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.0 match ("1.*.*") => true : expected => true
```

### Example 4. SemanticVersion Test (4)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "2.0.0";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.0 match ("2.0.0") => false : expected => false
```

### Example 5. SemanticVersion Test (5)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "2.0.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.0 match ("2.0.*") => false : expected => false
```

### Example 6. SemanticVersion Test (6)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "2.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.0 match ("2.*.*") => false : expected => false
```

### Example 7. SemanticVersion Test (7)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "1.0.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.0 match ("1.0.*") => true : expected => true
```

### Example 8. SemanticVersion Test (8)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.1");
var pattern = "1.0.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.1 match ("1.0.*") => true : expected => true
```

### Example 9. SemanticVersion Test (9)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.99");
var pattern = "1.0.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.99 match ("1.0.*") => true : expected => true
```

### Example 10. SemanticVersion Test (10)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.99");
var pattern = "1.0.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.99 match ("1.0.*") => false : expected => false
```

### Example 11. SemanticVersion Test (11)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "1.1.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.0 match ("1.1.*") => false : expected => false
```

### Example 12. SemanticVersion Test (12)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.1");
var pattern = "1.1.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.1 match ("1.1.*") => false : expected => false
```

### Example 13. SemanticVersion Test (13)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.99");
var pattern = "1.1.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.99 match ("1.1.*") => false : expected => false
```

### Example 14. SemanticVersion Test (14)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.99");
var pattern = "1.1.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.99 match ("1.1.*") => true : expected => true
```

### Example 15. SemanticVersion Test (15)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.0 match ("1.*.*") => true : expected => true
```

### Example 16. SemanticVersion Test (16)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.1");
var pattern = "1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.1 match ("1.*.*") => true : expected => true
```

### Example 17. SemanticVersion Test (17)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.99");
var pattern = "1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.99 match ("1.*.*") => true : expected => true
```

### Example 18. SemanticVersion Test (18)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.99");
var pattern = "1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.99 match ("1.*.*") => true : expected => true
```

### Example 19. SemanticVersion Test (19)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("11.1.99");
var pattern = "1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
11.1.99 match ("1.*.*") => false : expected => false
```

### Example 20. SemanticVersion Test (20)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = ">1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.0 match (">1.*.*") => false : expected => false
```

### Example 21. SemanticVersion Test (21)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = ">=1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.0 match (">=1.*.*") => true : expected => true
```

### Example 22. SemanticVersion Test (22)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = ">1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.0 match (">1") => false : expected => false
```

### Example 23. SemanticVersion Test (23)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = ">=1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.0 match (">=1") => true : expected => true
```

### Example 24. SemanticVersion Test (24)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = ">1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.0 match (">1.1") => false : expected => false
```

### Example 25. SemanticVersion Test (25)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = ">=1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.0 match (">=1.1") => false : expected => false
```

### Example 26. SemanticVersion Test (26)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = ">1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.0 match (">1.1") => false : expected => false
```

### Example 27. SemanticVersion Test (27)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = ">=1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.0 match (">=1.1") => true : expected => true
```

### Example 28. SemanticVersion Test (28)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.1");
var pattern = ">1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.1 match (">1.1") => false : expected => false
```

### Example 29. SemanticVersion Test (29)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.1");
var pattern = ">=1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.1 match (">=1.1") => true : expected => true
```

### Example 30. SemanticVersion Test (30)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = ">1.1.2";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.10 match (">1.1.2") => true : expected => true
```

### Example 31. SemanticVersion Test (31)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = ">=1.1.2";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.10 match (">=1.1.2") => true : expected => true
```

### Example 32. SemanticVersion Test (32)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.10.10");
var pattern = ">1.2.99";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.10.10 match (">1.2.99") => true : expected => true
```

### Example 33. SemanticVersion Test (33)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.10.10");
var pattern = ">=1.2.99";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.10.10 match (">=1.2.99") => true : expected => true
```

### Example 34. SemanticVersion Test (34)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "<1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.0 match ("<1.*.*") => false : expected => false
```

### Example 35. SemanticVersion Test (35)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "<=1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.0 match ("<=1.*.*") => true : expected => true
```

### Example 36. SemanticVersion Test (36)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "<1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.0 match ("<1") => false : expected => false
```

### Example 37. SemanticVersion Test (37)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "<=1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.0 match ("<=1") => true : expected => true
```

### Example 38. SemanticVersion Test (38)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "<1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.0 match ("<1.1") => true : expected => true
```

### Example 39. SemanticVersion Test (39)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "<=1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.0 match ("<=1.1") => true : expected => true
```

### Example 40. SemanticVersion Test (40)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "<1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.0 match ("<1.1") => false : expected => false
```

### Example 41. SemanticVersion Test (41)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "<=1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.0 match ("<=1.1") => true : expected => true
```

### Example 42. SemanticVersion Test (42)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.1");
var pattern = "<1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.1 match ("<1.1") => false : expected => false
```

### Example 43. SemanticVersion Test (43)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.1");
var pattern = "<=1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.1 match ("<=1.1") => true : expected => true
```

### Example 44. SemanticVersion Test (44)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.2");
var pattern = "<1.1.10";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.2 match ("<1.1.10") => true : expected => true
```

### Example 45. SemanticVersion Test (45)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.2");
var pattern = "<=1.1.10";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.2 match ("<=1.1.10") => true : expected => true
```

### Example 46. SemanticVersion Test (46)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.2.99");
var pattern = "<1.10.10";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.2.99 match ("<1.10.10") => true : expected => true
```

### Example 47. SemanticVersion Test (47)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.2.99");
var pattern = "<=1.10.20";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.2.99 match ("<=1.10.20") => true : expected => true
```

### Example 48. SemanticVersion Test (48)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "==1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.0 match ("==1.*.*") => true : expected => true
```

### Example 49. SemanticVersion Test (49)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "==1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.0.0 match ("==1") => true : expected => true
```

### Example 50. SemanticVersion Test (50)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "==1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.0 match ("==1.*.*") => true : expected => true
```

### Example 51. SemanticVersion Test (51)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "==1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.0 match ("==1") => true : expected => true
```

### Example 52. SemanticVersion Test (52)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "==1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.0 match ("==1.*.*") => true : expected => true
```

### Example 53. SemanticVersion Test (53)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "==1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.0 match ("==1.1") => true : expected => true
```

### Example 54. SemanticVersion Test (54)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "==1.1.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.0 match ("==1.1.*") => true : expected => true
```

### Example 55. SemanticVersion Test (55)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "==1.1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.0 match ("==1.1.1") => false : expected => false
```

### Example 56. SemanticVersion Test (56)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "==1.1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.10 match ("==1.1.1") => false : expected => false
```

### Example 57. SemanticVersion Test (57)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "==1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.10 match ("==1") => true : expected => true
```

### Example 58. SemanticVersion Test (58)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "==1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.10 match ("==1.*.*") => true : expected => true
```

### Example 59. SemanticVersion Test (59)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "==1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.10 match ("==1.1") => true : expected => true
```

### Example 60. SemanticVersion Test (60)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "==1.1.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.10 match ("==1.1.*") => true : expected => true
```

### Example 61. SemanticVersion Test (61)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "==1.1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.10 match ("==1.1.1") => false : expected => false
```

### Example 62. SemanticVersion Test (62)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "==1.1.10";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.10 match ("==1.1.10") => true : expected => true
```

### Example 63. SemanticVersion Test (63)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "!=1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.0 match ("!=1.*.*") => false : expected => false
```

### Example 64. SemanticVersion Test (64)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var pattern = "!=1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.0.0 match ("!=1") => false : expected => false
```

### Example 65. SemanticVersion Test (65)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "!=1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.0 match ("!=1.*.*") => false : expected => false
```

### Example 66. SemanticVersion Test (66)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "!=1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.0 match ("!=1") => false : expected => false
```

### Example 67. SemanticVersion Test (67)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "!=1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.0 match ("!=1.*.*") => false : expected => false
```

### Example 68. SemanticVersion Test (68)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "!=1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.0 match ("!=1.1") => false : expected => false
```

### Example 69. SemanticVersion Test (69)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "!=1.1.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.0 match ("!=1.1.*") => false : expected => false
```

### Example 70. SemanticVersion Test (70)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var pattern = "!=1.1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.0 match ("!=1.1.1") => true : expected => true
```

### Example 71. SemanticVersion Test (71)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "!=1.1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.10 match ("!=1.1.1") => true : expected => true
```

### Example 72. SemanticVersion Test (72)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "!=1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.10 match ("!=1") => false : expected => false
```

### Example 73. SemanticVersion Test (73)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "!=1.*.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.10 match ("!=1.*.*") => false : expected => false
```

### Example 74. SemanticVersion Test (74)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "!=1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.10 match ("!=1.1") => false : expected => false
```

### Example 75. SemanticVersion Test (75)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "!=1.1.*";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.10 match ("!=1.1.*") => false : expected => false
```

### Example 76. SemanticVersion Test (76)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "!=1.1.1";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.10 match ("!=1.1.1") => true : expected => true
```

### Example 77. SemanticVersion Test (77)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10");
var pattern = "!=1.1.10";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.10 match ("!=1.1.10") => false : expected => false
```

### Example 78. SemanticVersion Test (78)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10-alpha.1");
var pattern = ">1.1.10";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.10-alpha.1 match (">1.1.10") => false : expected => false
```

### Example 79. SemanticVersion Test (79)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10-alpha.1");
var pattern = ">=1.1.10";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, False);
```

#### Result

```
1.1.10-alpha.1 match (">=1.1.10") => false : expected => false
```

### Example 80. SemanticVersion Test (80)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10-alpha.1");
var pattern = "<1.1.10";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.10-alpha.1 match ("<1.1.10") => true : expected => true
```

### Example 81. SemanticVersion Test (81)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.10-alpha.1");
var pattern = "<=1.1.10";
SemanticVersionTest("match", lhs.version(), '("%{pattern}")', { => lhs.match(pattern) }, True);
```

#### Result

```
1.1.10-alpha.1 match ("<=1.1.10") => true : expected => true
```

### Example 82. SemanticVersion Test (82)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.0.0");
SemanticVersionTest("==", lhs.version(), rhs.version(), { => lhs == rhs }, True);
```

#### Result

```
1.0.0 == 1.0.0 => true : expected => true
```

### Example 83. SemanticVersion Test (83)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest("==", lhs.version(), rhs.version(), { => lhs == rhs }, False);
```

#### Result

```
1.0.0 == 2.0.0 => false : expected => false
```

### Example 84. SemanticVersion Test (84)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest("==", lhs.version(), rhs.version(), { => lhs == rhs }, False);
```

#### Result

```
1.1.0 == 2.0.0 => false : expected => false
```

### Example 85. SemanticVersion Test (85)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.1.0");
SemanticVersionTest("==", lhs.version(), rhs.version(), { => lhs == rhs }, False);
```

#### Result

```
1.0.0 == 1.1.0 => false : expected => false
```

### Example 86. SemanticVersion Test (86)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.0.1");
SemanticVersionTest("==", lhs.version(), rhs.version(), { => lhs == rhs }, False);
```

#### Result

```
1.0.0 == 1.0.1 => false : expected => false
```

### Example 87. SemanticVersion Test (87)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.0.0");
SemanticVersionTest("!=", lhs.version(), rhs.version(), { => lhs != rhs }, False);
```

#### Result

```
1.0.0 != 1.0.0 => false : expected => false
```

### Example 88. SemanticVersion Test (88)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest("!=", lhs.version(), rhs.version(), { => lhs != rhs }, True);
```

#### Result

```
1.0.0 != 2.0.0 => true : expected => true
```

### Example 89. SemanticVersion Test (89)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest("!=", lhs.version(), rhs.version(), { => lhs != rhs }, True);
```

#### Result

```
1.1.0 != 2.0.0 => true : expected => true
```

### Example 90. SemanticVersion Test (90)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.1");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest("!=", lhs.version(), rhs.version(), { => lhs != rhs }, True);
```

#### Result

```
1.0.1 != 2.0.0 => true : expected => true
```

### Example 91. SemanticVersion Test (91)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.1.0");
SemanticVersionTest("!=", lhs.version(), rhs.version(), { => lhs != rhs }, True);
```

#### Result

```
1.0.0 != 1.1.0 => true : expected => true
```

### Example 92. SemanticVersion Test (92)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.0.1");
SemanticVersionTest("!=", lhs.version(), rhs.version(), { => lhs != rhs }, True);
```

#### Result

```
1.0.0 != 1.0.1 => true : expected => true
```

### Example 93. SemanticVersion Test (93)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("2.0.0");
var rhs = new SemanticVersion("1.0.0");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, True);
```

#### Result

```
2.0.0 > 1.0.0 => true : expected => true
```

### Example 94. SemanticVersion Test (94)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, False);
```

#### Result

```
1.1.0 > 2.0.0 => false : expected => false
```

### Example 95. SemanticVersion Test (95)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.1");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, False);
```

#### Result

```
1.0.1 > 2.0.0 => false : expected => false
```

### Example 96. SemanticVersion Test (96)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var rhs = new SemanticVersion("1.0.0");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, True);
```

#### Result

```
1.1.0 > 1.0.0 => true : expected => true
```

### Example 97. SemanticVersion Test (97)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.1");
var rhs = new SemanticVersion("1.0.0");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, True);
```

#### Result

```
1.0.1 > 1.0.0 => true : expected => true
```

### Example 98. SemanticVersion Test (98)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("0.9.101");
var rhs = new SemanticVersion("0.9.100");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, True);
```

#### Result

```
0.9.101 > 0.9.100 => true : expected => true
```

### Example 99. SemanticVersion Test (99)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("10.0.2");
var rhs = new SemanticVersion("10.0.1");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, True);
```

#### Result

```
10.0.2 > 10.0.1 => true : expected => true
```

### Example 100. SemanticVersion Test (100)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.0.1");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, False);
```

#### Result

```
1.0.0 > 1.0.1 => false : expected => false
```

### Example 101. SemanticVersion Test (101)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.0.0");
SemanticVersionTest(">=", lhs.version(), rhs.version(), { => lhs >= rhs }, True);
```

#### Result

```
1.0.0 >= 1.0.0 => true : expected => true
```

### Example 102. SemanticVersion Test (102)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.1");
var rhs = new SemanticVersion("1.0.0");
SemanticVersionTest(">=", lhs.version(), rhs.version(), { => lhs >= rhs }, True);
```

#### Result

```
1.0.1 >= 1.0.0 => true : expected => true
```

### Example 103. SemanticVersion Test (103)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.0.1");
SemanticVersionTest(">=", lhs.version(), rhs.version(), { => lhs >= rhs }, False);
```

#### Result

```
1.0.0 >= 1.0.1 => false : expected => false
```

### Example 104. SemanticVersion Test (104)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest(">=", lhs.version(), rhs.version(), { => lhs >= rhs }, False);
```

#### Result

```
1.1.0 >= 2.0.0 => false : expected => false
```

### Example 105. SemanticVersion Test (105)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.1");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest(">=", lhs.version(), rhs.version(), { => lhs >= rhs }, False);
```

#### Result

```
1.0.1 >= 2.0.0 => false : expected => false
```

### Example 106. SemanticVersion Test (106)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0 < 2.0.0 => true : expected => true
```

### Example 107. SemanticVersion Test (107)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.1.0 < 2.0.0 => true : expected => true
```

### Example 108. SemanticVersion Test (108)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.1");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.1 < 2.0.0 => true : expected => true
```

### Example 109. SemanticVersion Test (109)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.1.0");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0 < 1.1.0 => true : expected => true
```

### Example 110. SemanticVersion Test (110)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.0.1");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0 < 1.0.1 => true : expected => true
```

### Example 111. SemanticVersion Test (111)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("0.9.100");
var rhs = new SemanticVersion("0.9.101");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
0.9.100 < 0.9.101 => true : expected => true
```

### Example 112. SemanticVersion Test (112)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("10.0.1");
var rhs = new SemanticVersion("10.0.2");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
10.0.1 < 10.0.2 => true : expected => true
```

### Example 113. SemanticVersion Test (113)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.1");
var rhs = new SemanticVersion("1.0.0");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, False);
```

#### Result

```
1.0.1 < 1.0.0 => false : expected => false
```

### Example 114. SemanticVersion Test (114)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.0.0");
SemanticVersionTest("<=", lhs.version(), rhs.version(), { => lhs <= rhs }, True);
```

#### Result

```
1.0.0 <= 1.0.0 => true : expected => true
```

### Example 115. SemanticVersion Test (115)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.0.1");
SemanticVersionTest("<=", lhs.version(), rhs.version(), { => lhs <= rhs }, True);
```

#### Result

```
1.0.0 <= 1.0.1 => true : expected => true
```

### Example 116. SemanticVersion Test (116)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.1");
var rhs = new SemanticVersion("1.0.0");
SemanticVersionTest("<=", lhs.version(), rhs.version(), { => lhs <= rhs }, False);
```

#### Result

```
1.0.1 <= 1.0.0 => false : expected => false
```

### Example 117. SemanticVersion Test (117)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.1.0");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest("<=", lhs.version(), rhs.version(), { => lhs <= rhs }, True);
```

#### Result

```
1.1.0 <= 2.0.0 => true : expected => true
```

### Example 118. SemanticVersion Test (118)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.1");
var rhs = new SemanticVersion("2.0.0");
SemanticVersionTest("<=", lhs.version(), rhs.version(), { => lhs <= rhs }, True);
```

#### Result

```
1.0.1 <= 2.0.0 => true : expected => true
```

### Example 119. SemanticVersion Test (119)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.0.0-alpha");
SemanticVersionTest("==", lhs.version(), rhs.version(), { => lhs == rhs }, False);
```

#### Result

```
1.0.0 == 1.0.0-alpha => false : expected => false
```

### Example 120. SemanticVersion Test (120)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest("==", lhs.version(), rhs.version(), { => lhs == rhs }, False);
```

#### Result

```
1.0.0-alpha == 1.0.0-alpha.1 => false : expected => false
```

### Example 121. SemanticVersion Test (121)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest("==", lhs.version(), rhs.version(), { => lhs == rhs }, True);
```

#### Result

```
1.0.0-alpha.1 == 1.0.0-alpha.1 => true : expected => true
```

### Example 122. SemanticVersion Test (122)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1");
var rhs = new SemanticVersion("1.0.0-alpha.1+build.1");
SemanticVersionTest("==", lhs.version(), rhs.version(), { => lhs == rhs }, True);
```

#### Result

```
1.0.0-alpha.1 == 1.0.0-alpha.1+build.1 => true : expected => true
```

### Example 123. SemanticVersion Test (123)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.0.0-alpha");
SemanticVersionTest("!=", lhs.version(), rhs.version(), { => lhs != rhs }, True);
```

#### Result

```
1.0.0 != 1.0.0-alpha => true : expected => true
```

### Example 124. SemanticVersion Test (124)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest("!=", lhs.version(), rhs.version(), { => lhs != rhs }, True);
```

#### Result

```
1.0.0-alpha != 1.0.0-alpha.1 => true : expected => true
```

### Example 125. SemanticVersion Test (125)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest("!=", lhs.version(), rhs.version(), { => lhs != rhs }, False);
```

#### Result

```
1.0.0-alpha.1 != 1.0.0-alpha.1 => false : expected => false
```

### Example 126. SemanticVersion Test (126)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1");
var rhs = new SemanticVersion("1.0.0-alpha.1+build.1");
SemanticVersionTest("!=", lhs.version(), rhs.version(), { => lhs != rhs }, False);
```

#### Result

```
1.0.0-alpha.1 != 1.0.0-alpha.1+build.1 => false : expected => false
```

### Example 127. SemanticVersion Test (127)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-beta.1");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, True);
```

#### Result

```
1.0.0-beta.1 > 1.0.0-alpha.1 => true : expected => true
```

### Example 128. SemanticVersion Test (128)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0");
var rhs = new SemanticVersion("1.0.0-alpha");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, True);
```

#### Result

```
1.0.0 > 1.0.0-alpha => true : expected => true
```

### Example 129. SemanticVersion Test (129)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1");
var rhs = new SemanticVersion("1.0.0-alpha");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, True);
```

#### Result

```
1.0.0-alpha.1 > 1.0.0-alpha => true : expected => true
```

### Example 130. SemanticVersion Test (130)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.2");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, True);
```

#### Result

```
1.0.0-alpha.2 > 1.0.0-alpha.1 => true : expected => true
```

### Example 131. SemanticVersion Test (131)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.beta");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, True);
```

#### Result

```
1.0.0-alpha.beta > 1.0.0-alpha.1 => true : expected => true
```

### Example 132. SemanticVersion Test (132)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.2");
var rhs = new SemanticVersion("1.0.0-alpha.1+build.1");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, True);
```

#### Result

```
1.0.0-alpha.2 > 1.0.0-alpha.1+build.1 => true : expected => true
```

### Example 133. SemanticVersion Test (133)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest(">", lhs.version(), rhs.version(), { => lhs > rhs }, False);
```

#### Result

```
1.0.0-alpha.1 > 1.0.0-alpha.1 => false : expected => false
```

### Example 134. SemanticVersion Test (134)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1");
var rhs = new SemanticVersion("1.0.0-alpha.2");
SemanticVersionTest(">=", lhs.version(), rhs.version(), { => lhs >= rhs }, False);
```

#### Result

```
1.0.0-alpha.1 >= 1.0.0-alpha.2 => false : expected => false
```

### Example 135. SemanticVersion Test (135)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest(">=", lhs.version(), rhs.version(), { => lhs >= rhs }, True);
```

#### Result

```
1.0.0-alpha.1 >= 1.0.0-alpha.1 => true : expected => true
```

### Example 136. SemanticVersion Test (136)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.2");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest(">=", lhs.version(), rhs.version(), { => lhs >= rhs }, True);
```

#### Result

```
1.0.0-alpha.2 >= 1.0.0-alpha.1 => true : expected => true
```

### Example 137. SemanticVersion Test (137)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.2");
var rhs = new SemanticVersion("1.0.0-alpha.1+build.1");
SemanticVersionTest(">=", lhs.version(), rhs.version(), { => lhs >= rhs }, True);
```

#### Result

```
1.0.0-alpha.2 >= 1.0.0-alpha.1+build.1 => true : expected => true
```

### Example 138. SemanticVersion Test (138)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, False);
```

#### Result

```
1.0.0-alpha.1 < 1.0.0-alpha.1 => false : expected => false
```

### Example 139. SemanticVersion Test (139)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.2");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, False);
```

#### Result

```
1.0.0-alpha.2 < 1.0.0-alpha.1 => false : expected => false
```

### Example 140. SemanticVersion Test (140)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha");
var rhs = new SemanticVersion("1.0.0");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0-alpha < 1.0.0 => true : expected => true
```

### Example 141. SemanticVersion Test (141)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0-alpha < 1.0.0-alpha.1 => true : expected => true
```

### Example 142. SemanticVersion Test (142)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1");
var rhs = new SemanticVersion("1.0.0-alpha.2");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0-alpha.1 < 1.0.0-alpha.2 => true : expected => true
```

### Example 143. SemanticVersion Test (143)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1+build.1");
var rhs = new SemanticVersion("1.0.0-alpha.2");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0-alpha.1+build.1 < 1.0.0-alpha.2 => true : expected => true
```

### Example 144. SemanticVersion Test (144)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.2");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest("<=", lhs.version(), rhs.version(), { => lhs <= rhs }, False);
```

#### Result

```
1.0.0-alpha.2 <= 1.0.0-alpha.1 => false : expected => false
```

### Example 145. SemanticVersion Test (145)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest("<=", lhs.version(), rhs.version(), { => lhs <= rhs }, True);
```

#### Result

```
1.0.0-alpha.1 <= 1.0.0-alpha.1 => true : expected => true
```

### Example 146. SemanticVersion Test (146)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1");
var rhs = new SemanticVersion("1.0.0-alpha.2");
SemanticVersionTest("<=", lhs.version(), rhs.version(), { => lhs <= rhs }, True);
```

#### Result

```
1.0.0-alpha.1 <= 1.0.0-alpha.2 => true : expected => true
```

### Example 147. SemanticVersion Test (147)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1+build.1");
var rhs = new SemanticVersion("1.0.0-alpha.2");
SemanticVersionTest("<=", lhs.version(), rhs.version(), { => lhs <= rhs }, True);
```

#### Result

```
1.0.0-alpha.1+build.1 <= 1.0.0-alpha.2 => true : expected => true
```

### Example 148. SemanticVersion Test (148)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha");
var rhs = new SemanticVersion("1.0.0-alpha.1");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0-alpha < 1.0.0-alpha.1 => true : expected => true
```

### Example 149. SemanticVersion Test (149)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.1");
var rhs = new SemanticVersion("1.0.0-alpha.beta");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0-alpha.1 < 1.0.0-alpha.beta => true : expected => true
```

### Example 150. SemanticVersion Test (150)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-alpha.beta");
var rhs = new SemanticVersion("1.0.0-beta");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0-alpha.beta < 1.0.0-beta => true : expected => true
```

### Example 151. SemanticVersion Test (151)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-beta");
var rhs = new SemanticVersion("1.0.0-beta.2");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0-beta < 1.0.0-beta.2 => true : expected => true
```

### Example 152. SemanticVersion Test (152)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-beta.2");
var rhs = new SemanticVersion("1.0.0-beta.11");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0-beta.2 < 1.0.0-beta.11 => true : expected => true
```

### Example 153. SemanticVersion Test (153)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-beta.11");
var rhs = new SemanticVersion("1.0.0-rc.1");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0-beta.11 < 1.0.0-rc.1 => true : expected => true
```

### Example 154. SemanticVersion Test (154)

#### Code

```javascript
using SemanticVersion;

var lhs = new SemanticVersion("1.0.0-rc.1");
var rhs = new SemanticVersion("1.0.0");
SemanticVersionTest("<", lhs.version(), rhs.version(), { => lhs < rhs }, True);
```

#### Result

```
1.0.0-rc.1 < 1.0.0 => true : expected => true
```

