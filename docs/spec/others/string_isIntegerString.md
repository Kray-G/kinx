# String#isIntegerString

## Overview

`String#isIntegerString` is used for checking if the string is following integer format.

## Examples

### Example 1. `String#isIntegerString` (radix:10)

#### Code

```javascript
var vals = [
    ["1"],
    ["10"],
    ["100"],
    ["1000"],
    ["1_000"],
    ["1", 10],
    ["10", 10],
    ["100", 10],
    ["1000", 10],
    ["1_000", 10],
    ["1a"],
    ["1a0"],
    ["a100"],
    ["1x000"],
    ["x1_000"],
    ["0x1", 10],
    ["10h", 10],
    ["100m", 10],
    ["1a000", 10],
    ["1_a000", 10],
];
System.println(vals.map { => _1[0].isIntegerString(_1[1]) });
System.println(vals.map { => _1[0].isIntegerString(_1[1]) ? Integer.parseInt(_1[0]) : null });
```

#### Result

```
[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
[1, 10, 100, 1000, 1000, 1, 10, 100, 1000, 1000, null, null, null, null, null, null, null, null, null, null]
```

### Example 2. `String#isIntegerString` (radix:16)/0x

#### Code

```javascript
var vals = [
    ["0x1"],
    ["0x1a0"],
    ["0x10b0"],
    ["0x100c0"],
    ["0x1_00d0"],
    ["1e", 16],
    ["10f", 16],
    ["100a", 16],
    ["1000b", 16],
    ["c1_000", 16],
    ["0x1e", 16],
    ["0x10f", 16],
    ["0x100a", 16],
    ["0x1000b", 16],
    ["0xc1_000", 16],
    ["0x1g"],
    ["0x1h0"],
    ["0xai00"],
    ["0x1x000"],
    ["0xj1_000"],
    ["1m", 16],
    ["10j", 16],
    ["100m", 16],
    ["1a0x00", 16],
    ["1_a0z00", 16],
];
System.println(vals.map { => _1[0].isIntegerString(_1[1]) });
System.println(vals.map { => _1[0].isIntegerString(_1[1]) ? ("%x" % Integer.parseInt(_1[0], 16)).format() : null });
```

#### Result

```
[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
["1", "1a0", "10b0", "100c0", "100d0", "1e", "10f", "100a", "1000b", "c1000", "1e", "10f", "100a", "1000b", "c1000", null, null, null, null, null, null, null, null, null, null]
```

### Example 3. `String#isIntegerString` (radix:16)/h

#### Code

```javascript
var vals = [
    ["1h"],
    ["1a0h"],
    ["10b0h"],
    ["100c0h"],
    ["1_00d0h"],
    ["1e", 16],
    ["10f", 16],
    ["100a", 16],
    ["1000b", 16],
    ["c1_000", 16],
    ["1eh", 16],
    ["10fh", 16],
    ["100ah", 16],
    ["1000bh", 16],
    ["c1_000h", 16],
    ["1gh"],
    ["1h0h"],
    ["ai00h"],
    ["1x000h"],
    ["j1_000h"],
    ["1m", 16],
    ["10j", 16],
    ["100m", 16],
    ["1a0x00", 16],
    ["1_a0z00", 16],
    ["0x1eh", 16],
    ["0x10fh", 16],
    ["0x100ah", 16],
    ["0x1000bh", 16],
    ["0xc1_000h", 16],
];
System.println(vals.map { => _1[0].isIntegerString(_1[1]) });
System.println(vals.map { => _1[0].isIntegerString(_1[1]) ? ("%x" % Integer.parseInt(_1[0], 16)).format() : null });
```

#### Result

```
[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
["1", "1a0", "10b0", "100c0", "100d0", "1e", "10f", "100a", "1000b", "c1000", "1e", "10f", "100a", "1000b", "c1000", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null]
```

### Example 4. `String#isIntegerString` (radix:2)/0b

#### Code

```javascript
var vals = [
    ["0b1"],
    ["0b110"],
    ["0b1010"],
    ["0b10010"],
    ["0b1_0010"],
    ["10", 2],
    ["101", 2],
    ["1000", 2],
    ["10001", 2],
    ["11_000", 2],
    ["0b11", 2],
    ["0b100", 2],
    ["0b1001", 2],
    ["0b10101", 2],
    ["0b01_000", 2],
    ["0ba1"],
    ["0b11a"],
    ["0b1140"],
    ["0b10200"],
    ["0b12_000"],
    ["1m", 2],
    ["10j", 2],
    ["100m", 2],
    ["1a0b00", 2],
    ["1_a0z00", 2],
];
System.println(vals.map { => _1[0].isIntegerString(_1[1]) });
System.println(vals.map { => _1[0].isIntegerString(_1[1]) ? ("0x%x" % Integer.parseInt(_1[0], 2)).format() : null });
```

#### Result

```
[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
["0x1", "0x6", "0xa", "0x12", "0x12", "0x2", "0x5", "0x8", "0x11", "0x18", "0x3", "0x4", "0x9", "0x15", "0x8", null, null, null, null, null, null, null, null, null, null]
```

### Example 3. `String#isIntegerString` (radix:2)/b

#### Code

```javascript
var vals = [
    ["1b"],
    ["110b"],
    ["1010b"],
    ["10010b"],
    ["1_0010b"],
    ["10", 2],
    ["101", 2],
    ["1000", 2],
    ["10001", 2],
    ["11_000", 2],
    ["11b", 2],
    ["100b", 2],
    ["1001b", 2],
    ["10101b", 2],
    ["01_000b", 2],
    ["a0b"],
    ["120b"],
    ["1130b"],
    ["10090b"],
    ["11_x00b"],
    ["1m", 2],
    ["10j", 2],
    ["100m", 2],
    ["1a0b00", 2],
    ["1_a0z00", 2],
    ["0b11b", 2],
    ["0b100b", 2],
    ["0b1001b", 2],
    ["0b10101b", 2],
    ["0b01_000b", 2],
    ["1111111111111111111111111111111", 2],
    ["11111111111111111111111000011111", 2],
    ["1111111111111111111111100001111111111111111111111111111000011111", 2],
    ["11111111111111111111111000011111111111111111111111111110000111111111111111111111111111100001111111111111111111111111111000011111", 2],
    ["1111111111111111111111100001111111111111111111111111111000011111111111111111111111111110000111111111111111111111111111100001111111111111111111111111111000011111111111111111111111111110000111111111111111111111111111100001111111111111111111111111111000011111", 2],
];
System.println(vals.map { => _1[0].isIntegerString(_1[1]) });
System.println(vals.map { => _1[0].isIntegerString(_1[1]) ? ("0x%x" % Integer.parseInt(_1[0], 2)).format() : null });
```

#### Result

```
[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
["0x1", "0x6", "0xa", "0x12", "0x12", "0x2", "0x5", "0x8", "0x11", "0x18", "0x3", "0x4", "0x9", "0x15", "0x8", null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, "0x7fffffff", "0xfffffe1f", "0xfffffe1ffffffe1f", "0xfffffe1ffffffe1ffffffe1ffffffe1f", "0xfffffe1ffffffe1ffffffe1ffffffe1ffffffe1ffffffe1ffffffe1ffffffe1f"]
```

### Example 5. `String#isIntegerString` (radix:8)/0

#### Code

```javascript
var vals = [
    ["01"],
    ["0170"],
    ["01530"],
    ["076541"],
    ["01_6610"],
    ["1", 8],
    ["170", 8],
    ["1530", 8],
    ["76541", 8],
    ["1_6610", 8],
    ["01", 8],
    ["0170", 8],
    ["01530", 8],
    ["076541", 8],
    ["01_6610", 8],
    ["0a1"],
    ["011a"],
    ["01178"],
    ["010209"],
    ["017_0a0"],
    ["1m", 8],
    ["10j", 8],
    ["100m", 8],
    ["1a0b00", 8],
    ["1_a0z00", 8],
];
System.println(vals.map { => _1[0].isIntegerString(_1[1]) });
System.println(vals.map { => _1[0].isIntegerString(_1[1]) ? ("%x" % Integer.parseInt(_1[0], 8)).format() : null });
```

#### Result

```
[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
["1", "78", "358", "7d61", "1d88", "1", "78", "358", "7d61", "1d88", "1", "78", "358", "7d61", "1d88", null, null, null, null, null, null, null, null, null, null]
```
