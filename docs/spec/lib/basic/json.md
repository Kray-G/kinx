# JSON

## Overview

**JSON** means **JavaScript Object Notation**.
Kinx Object is just a JSON object and you can use it easily.

### Parsing JSON

Kinx provides a utility function of `JSON.parse()`.
You can use it to parse a JSON string and construct an actual Kinx Object.

Here is an example.

```javascript
var x = JSON.parse(%{
    {
        "aaa": 10,
        "bbb": 20
    }
});
System.println(x);  // => {"aaa":10,"bbb":20}
```

`JSON.parse()` can also handle the key without quotation.

```javascript
var x = JSON.parse(%{
    {
        aaa: 10,
        bbb: 20
    }
});
System.println(x);  // => {"aaa":10,"bbb":20}
```

### Stringify

You can use `JSON.stringify()` to make it stringify from a JSON object,
and also you can apply `toJsonString()` to an object directly.

```javascript
var x = {
    aaa: 10,
    bbb: 20
};
System.println(JSON.stringify(x)); // => {"aaa":10,"bbb":20}
```

The second parameter of `JSON.stringify()` is a flag and it is true if using indentation.

```javascript
var x = {
    aaa: 10,
    bbb: 20
};
System.println(JSON.stringify(x, true));
// {
//     "aaa": 10,
//     "bbb": 20
// }
```

Here is the `toJsonString` version.

```javascript
var x = {
    aaa: 10,
    bbb: 20
};
System.println(x.toJsonString(true));
// {
//     "aaa": 10,
//     "bbb": 20
// }
```

## Examples

### Example 1. Parsing JSON

#### Code

```javascript
var x = JSON.parse(%{
    {
        aaa: 10,
        bbb: 20
    }
});
System.println(x);
```

#### Result

```
{"aaa":10,"bbb":20}
```

### Example 2. JSON.stringify

#### Code

```javascript
var x = {
    aaa: 10,
    bbb: 20
};
System.println(JSON.stringify(x));
```

#### Result

```
{"aaa":10,"bbb":20}
```

### Example 1. toJsonString

#### Code

```javascript
var x = {
    aaa: 10,
    bbb: 20
};
System.println(x.toJsonString(true));
```

#### Result

```
{
    "aaa": 10,
    "bbb": 20
}
```
