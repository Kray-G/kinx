# CRC32

## Overview

Please see the Wikipedia.

*   [CRC - Wikipedia](https://en.wikipedia.org/wiki/Cyclic_redundancy_check)

## Examples

### Example 1. CRC32 Algorithm

#### Code

```javascript
const CRCPOLY1 = 0x04C11DB7;
const CRCPOLY2 = 0xEDB88320;
const CHAR_BIT = 8;

function crc1(c) {
    var r = 0xFFFFFFFF;
    var n = c.length();

    for (var i = 0; i < n; i++) {
        r ^= c[i] << (32 - CHAR_BIT);
        for (var j = 0; j < CHAR_BIT; j++)
            if (r & 0x80000000) r = (r << 1) ^ CRCPOLY1;
            else                r <<= 1;
    }

    return ~r & 0xFFFFFFFF;
}

function crc2(c) {
    var r = 0xFFFFFFFF;
    var n = c.length();

    for (var i = 0; i < n; i++) {
        r ^= c[i];
        for (var j = 0; j < CHAR_BIT; j++)
            if (r & 1) r = (r >> 1) ^ CRCPOLY2;
            else       r >>= 1;
    }

    return r ^ 0xFFFFFFFF;
}

var s = "Hello, world!";
System.println("crc1(%s) = %08lX" % s % crc1(s));
System.println("crc2(%s) = %08lX" % s % crc2(s));
```

#### Result

```
crc1(Hello, world!) = 8E9A7706
crc2(Hello, world!) = EBE6C6E6
```
