# class DateTime

### using DateTime

DateTime Library is not an embedded library, so you should load it by `using`.

```javascript
using DateTime;
```

### Instanciate

Basically, use `new` to instanciate a DateTime object.

* `new DateTime()` ... 現在時刻でインスタンス化
* `new DateTime(dateString)` ... 文字列をパースしてインスタンス化
* `new DateTime(Unixtime)` ... UNIXエポックの時刻からインスタンス化
* `new DateTime(year, month, day[, hour, minute, second])` ... 日時情報を個別に指定してインスタンス化

But you can use one of the followings as you like.
Those are the same and it returns a DateTime object created by `new` internally.

* `DateTime.parse(...)`
* `DateTime(...)`

You can use following formats as a `dateString`.

* `"2020-01-01"`, `"2020-1-1"`
* `"2020/01/01"`, `"2020/1/1"`
* `"2020-01-01T10:00:05"`, `"2020-1-01T10:0:5"`
* `"2020/01/01 10:00:05"`, `"2020/1/01 10:0:5"`

### Methods

A DateTime object has following methods.

|     メソッド      |                                       動作概要                                       |
| ----------------- | ------------------------------------------------------------------------------------ |
| `isLeapYear()`    | true if it is a leap year.                                                           |
| `unixtime()`      | Returns a Unix epoch time.                                                           |
| `datetime()`      | Returns a JSON object.                                                               |
| `year()`          | Returns a year.                                                                      |
| `month()`         | Returns a month.                                                                     |
| `day()`           | Returns a day.                                                                       |
| `hour()`          | Returns a hour.                                                                      |
| `minute()`        | Returns a minute.                                                                    |
| `second()`        | Returns a second.                                                                    |
| `weekday()`       | Returns a week. (0: Sunday, 1: Monday, ..., 6: Saturday）                            |
| `isSunday()`      | true if it is a Sunday.                                                              |
| `isMonday()`      | true if it is a Monday.                                                              |
| `isTuesday()`     | true if it is a Tuesday.                                                             |
| `isWednesday()`   | true if it is a Wednesday.                                                           |
| `isThursday()`    | true if it is a Thursday.                                                            |
| `isFriday()`      | true if it is a Friday.                                                              |
| `isSaturday()`    | true if it is a Saturday.                                                            |
| `clone()`         | Returns a clone object.                                                              |
| `addDay(day)`     | Goes forward by the number of days specified by `day`. (destructive)                 |
| `subDay(day)`     | Goes back by the number of days specified by `day`. (destructive)                    |
| `addMonth(month)` | Goes forward by the number of months specified by `month`. (destructive)             |
| `subMonth(month)` | Goes back by the number of months specified by `month`. (destructive)                |
| `next()`          | Returns a DateTime object with a next day.                                           |
| `+(day)`          | Returns a DateTime object gone forward by the number of days specified by `day`.     |
| `-(day)`          | Returns a DateTime object gone back by the number of days specified by `day`.        |
| `>>(month)`       | Returns a DateTime object gone forward by the number of months specified by `month`. |
| `<<(month)`       | Returns a DateTime object gone back by the number of months specified by `month`.    |
| `<=>(dt)`         | 0 if it is a same time, -1 if `dt` is a later date and time, otherwise 1.            |
| `format(fmtString)`| Returns a string formatted by `fmtString`. It supports a format string as follows.<br/>`%YYYY%`: Year of 4 digits, `%YY%`: Year of 2 digits.<br/>`%MM%`:Month of 2 digits, `%M%`: Month of 1 digit.<br/>`%DD%`: Day of 2 digits., `%D%`: Day of 1 digit.<br/>`%hh%`: Hour of 2 digits, `%h%`: Hour of 1 digit.<br/>`%mm%`: Minute of 2 digits, `%m%`: Minute of 1 digit.<br/>`%ss%`: Second of 2 digits, `%s%`: Second of 1 digit.<br/>|

### The End of Month

When you move a month by the operator `<<` or `>>` and there is no same date in the moved month, the date will be an end of the month.

```javascript
using DateTime;
System.println(DateTime("2001-3-28") << 1);  // 2001/02/28 00:00:00
System.println(DateTime("2001-3-31") << 1);  // 2001/02/28 00:00:00
```

This may cause what you don't expected.

```javascript
using DateTime;
System.println(DateTime("2001-1-31") >> 2);        // 2001/03/31 00:00:00
System.println(DateTime("2001-1-31") >> 1 >> 1);   // 2001/03/28 00:00:00
System.println(DateTime("2001-1-31") >> 1 >> -1);  // 2001/01/28 00:00:00
```

### Range

A DateTime object can be used with Range.

```javascript
using DateTime;
(DateTime(2020,1,1)..DateTime(2020,1,10))
    .each(&(d) => System.println(d));
```

This example will show the last date because the range operator is `..`.
If the range operator is `...`, the last date will not be shown.

```
2020/01/01 00:00:00
2020/01/02 00:00:00
2020/01/03 00:00:00
2020/01/04 00:00:00
2020/01/05 00:00:00
2020/01/06 00:00:00
2020/01/07 00:00:00
2020/01/08 00:00:00
2020/01/09 00:00:00
2020/01/10 00:00:00
```

Of course, a Range of a Datetime object can be also used in `for-in`.

```javascript
using DateTime;
for (var d in DateTime(2020,1,1)...DateTime(2020,1,10)) {
    System.println(d);
}
```

This loop do not include the last date.

```
2020/01/01 00:00:00
2020/01/02 00:00:00
2020/01/03 00:00:00
2020/01/04 00:00:00
2020/01/05 00:00:00
2020/01/06 00:00:00
2020/01/07 00:00:00
2020/01/08 00:00:00
2020/01/09 00:00:00
```

## Examples

### Example 1. Normal case

#### Code

```javascript
using DateTime;
function test(dt) {
    System.println(dt);
}
test(new DateTime("2020/01/01"));
test(DateTime("2020/01/01"));
test(DateTime.parse("2020/01/01"));
```

#### Result

```
2020/01/01 00:00:00
2020/01/01 00:00:00
2020/01/01 00:00:00
```

### Example 2. Basic Methods (1)

#### Code

```javascript
using DateTime;
function test(dt) {
    System.println("=> ", dt);
    System.println("    isLeapYear  = ", dt.isLeapYear());
    System.println("    datetime    = ", dt.datetime());
    System.println("    year        = ", dt.year());
    System.println("    month       = ", dt.month());
    System.println("    day         = ", dt.day());
    System.println("    hour        = ", dt.hour());
    System.println("    minute      = ", dt.minute());
    System.println("    second      = ", dt.second());
    System.println("    weekday     = ", dt.weekday());
    System.println("    isSunday    = ", dt.isSunday());
    System.println("    isMonday    = ", dt.isMonday());
    System.println("    isTuesday   = ", dt.isTuesday());
    System.println("    isWednesday = ", dt.isWednesday());
    System.println("    isThursday  = ", dt.isThursday());
    System.println("    isFriday    = ", dt.isFriday());
    System.println("    isSaturday  = ", dt.isSaturday());
}

(DateTime("2020/01/01")..DateTime("2020/01/3")).each { => test(_1) };
```

#### Result

```
=> 2020/01/01 00:00:00
    isLeapYear  = 1
    datetime    = {"day":1,"hour":0,"minute":0,"month":1,"second":0,"weekday":3,"year":2020}
    year        = 2020
    month       = 1
    day         = 1
    hour        = 0
    minute      = 0
    second      = 0
    weekday     = 3
    isSunday    = 0
    isMonday    = 0
    isTuesday   = 0
    isWednesday = 1
    isThursday  = 0
    isFriday    = 0
    isSaturday  = 0
=> 2020/01/02 00:00:00
    isLeapYear  = 1
    datetime    = {"day":2,"hour":0,"minute":0,"month":1,"second":0,"weekday":4,"year":2020}
    year        = 2020
    month       = 1
    day         = 2
    hour        = 0
    minute      = 0
    second      = 0
    weekday     = 4
    isSunday    = 0
    isMonday    = 0
    isTuesday   = 0
    isWednesday = 0
    isThursday  = 1
    isFriday    = 0
    isSaturday  = 0
=> 2020/01/03 00:00:00
    isLeapYear  = 1
    datetime    = {"day":3,"hour":0,"minute":0,"month":1,"second":0,"weekday":5,"year":2020}
    year        = 2020
    month       = 1
    day         = 3
    hour        = 0
    minute      = 0
    second      = 0
    weekday     = 5
    isSunday    = 0
    isMonday    = 0
    isTuesday   = 0
    isWednesday = 0
    isThursday  = 0
    isFriday    = 1
    isSaturday  = 0
```

### Example 3. Basic Methods (2)

#### Code

```javascript
using DateTime;
function test(dt) {
    System.println("=> ", dt);
    System.println("    isLeapYear  = ", dt.isLeapYear());
    System.println("    datetime    = ", dt.datetime());
    System.println("    year        = ", dt.year());
    System.println("    month       = ", dt.month());
    System.println("    day         = ", dt.day());
    System.println("    hour        = ", dt.hour());
    System.println("    minute      = ", dt.minute());
    System.println("    second      = ", dt.second());
    System.println("    weekday     = ", dt.weekday());
    System.println("    isSunday    = ", dt.isSunday());
    System.println("    isMonday    = ", dt.isMonday());
    System.println("    isTuesday   = ", dt.isTuesday());
    System.println("    isWednesday = ", dt.isWednesday());
    System.println("    isThursday  = ", dt.isThursday());
    System.println("    isFriday    = ", dt.isFriday());
    System.println("    isSaturday  = ", dt.isSaturday());
}

(DateTime("2021/01/01")..DateTime("2021/01/3")).each { => test(_1) };
```

#### Result

```
=> 2021/01/01 00:00:00
    isLeapYear  = 0
    datetime    = {"day":1,"hour":0,"minute":0,"month":1,"second":0,"weekday":5,"year":2021}
    year        = 2021
    month       = 1
    day         = 1
    hour        = 0
    minute      = 0
    second      = 0
    weekday     = 5
    isSunday    = 0
    isMonday    = 0
    isTuesday   = 0
    isWednesday = 0
    isThursday  = 0
    isFriday    = 1
    isSaturday  = 0
=> 2021/01/02 00:00:00
    isLeapYear  = 0
    datetime    = {"day":2,"hour":0,"minute":0,"month":1,"second":0,"weekday":6,"year":2021}
    year        = 2021
    month       = 1
    day         = 2
    hour        = 0
    minute      = 0
    second      = 0
    weekday     = 6
    isSunday    = 0
    isMonday    = 0
    isTuesday   = 0
    isWednesday = 0
    isThursday  = 0
    isFriday    = 0
    isSaturday  = 1
=> 2021/01/03 00:00:00
    isLeapYear  = 0
    datetime    = {"day":3,"hour":0,"minute":0,"month":1,"second":0,"weekday":0,"year":2021}
    year        = 2021
    month       = 1
    day         = 3
    hour        = 0
    minute      = 0
    second      = 0
    weekday     = 0
    isSunday    = 1
    isMonday    = 0
    isTuesday   = 0
    isWednesday = 0
    isThursday  = 0
    isFriday    = 0
    isSaturday  = 0
```

### Example 4. The End of Month (1)

#### Code

```javascript
using DateTime;
System.println(DateTime("2001-3-28") << 1);  // 2001/02/28 00:00:00
System.println(DateTime("2001-3-31") << 1);  // 2001/02/28 00:00:00
```

#### Result

```
2001/02/28 00:00:00
2001/02/28 00:00:00
```

### Example 5. The End of Month (2)

#### Code

```javascript
using DateTime;
System.println(DateTime("2001-1-31") >> 2);        // 2001/03/31 00:00:00
System.println(DateTime("2001-1-31") >> 1 >> 1);   // 2001/03/28 00:00:00
System.println(DateTime("2001-1-31") >> 1 >> -1);  // 2001/01/28 00:00:00
```

#### Result

```
2001/03/31 00:00:00
2001/03/28 00:00:00
2001/01/28 00:00:00
```

### Example 6. for-in

#### Code

```javascript
using DateTime;
for (var d in DateTime(2020,1,1)...DateTime(2020,1,10)) {
    System.println(d);
}
```

#### Result

```
2020/01/01 00:00:00
2020/01/02 00:00:00
2020/01/03 00:00:00
2020/01/04 00:00:00
2020/01/05 00:00:00
2020/01/06 00:00:00
2020/01/07 00:00:00
2020/01/08 00:00:00
2020/01/09 00:00:00
```
