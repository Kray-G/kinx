# Clipboard

## Overview

This library is to read a text from clipboard and to write a text to clipboard.
The basic usage is below.

```javascript
var cb = new Clipboard();
cb.write(str);
var r = cb.read();
```

## Some Examples

> Disabled a spec test because it will be failed on Github Action with the message of `Can't open display: (null)`.

### Example 1. Write to Clipboard

#### Code

```javascript
var cb = new Clipboard();
cb.write("This is a first message.");
var r = cb.read();
System.println("write done - ", r);
cb.write("This message was written by other process.");
```

#### Result

```
write done - This is a first message.
```

### Example 2. Read from Clipboard

#### Code

```javascript
var cb = new Clipboard();
var r = cb.read();
System.println("read - ", r);
```

#### Result

```
read - This message was written by other process.
```
