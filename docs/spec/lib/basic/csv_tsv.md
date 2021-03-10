# CSV

## Overview

Kinx has a CSV Parser Library to parse CSV text or file easily.

### using CSV

CSV Library is not an embedded library, so you should load it by `using`.

```javascript
using CSV;
```

### Parsing All

If you want to read a file and to parse it all at once, use `CSV.parse()`.

```javascript
using CSV;
var r = CSV.parse("filename.csv");
```

Here is data structure of the result parsed from CSV.
All lines are returned as an item of an array.
And there is a `data` field in each item, and it has an array of strings of each column.
But `data` field is empty when it is a comment line starting with `#`, and there is a `comment` field instead.
The `comment` field has a comment string which has `#` itself at the head.

```json
[{
    "data": ["aaa", "bbb", "ccc"]
}, ..., {
    "data": {},
    "comment": "# comment"
}]
```

### Callback Each Line

If there are a lot of lines, so much memory size may be required.
That is why you can use a callback for each line such as a following.
The argument of a callback is an item of a line.

```javascript
using CSV;
CSV.parse("filename.csv", &(row) => {
    System.println(row);  // like `{ data: ["aaa", "bbb", "ccc"] }`
});
```

By the way, `CSV.parse()` will return nothing, which means to return null.

### Parsing String

When you want to parse a string of CSV style, use `CSV.parseString()`.
It also has a callback version.

```javascript
using CSV;
var r = CSV.parseString(csvString);
CSV.parseString(csvString, &(row) => {
    ...
});
```

## CSV Specification

Here is a specification of CSV parsed by this library.

* Starting with `#` will be recognized as a comment line.
* A double-quotation is not necessary.
* But a double-quotation is required when the item has `,`, `"`, or new line character.
* A specification of inside a double-quotation is below.
    * `,` can be directly written.
    * `"` should be written as `""`.
    * You can write a new line character directly as a new line.
* It is okay not to put a new line at the bottom line.

## TSV

TSV is like CSV but the separator is <kbd>TAB</kbd> instead of `,`.
The library is the same so you should do `using CSV` first.
Replace `CSV` by `TSV`, and you can use TSV format.

```javascript
using CSV;
var r = TSV.parse(tsvFilename);
TSV.parseString(tsvString, &(row) => {
    ...
});
```

## Examples

### Example 1. Parsing CSV File

#### Code

```javascript
using CSV;

var csv = %{# comment in CSV.
abcde,efgh,non-quoted string
"abcde","efgh","quoted string"
"abcde",efgh,"quoted & non-quoted string in the same row"
"abcde",efgh,"can use , or "" in csv"
"abcde",efgh,"can use newlines

in the row"
# another comment in CSV.
abcde,efgh,not necessary \n the end of csv};

File.open("test.csv", File.WRITE) { => _1.print(csv) };
System.println(CSV.parse("test.csv").toJsonString(true));
```

#### Result

```json
[{
    "comment": "# comment in CSV.",
    "data": {}
}, {
    "data": ["abcde", "efgh", "non-quoted string"]
}, {
    "data": ["abcde", "efgh", "quoted string"]
}, {
    "data": ["abcde", "efgh", "quoted & non-quoted string in the same row"]
}, {
    "data": ["abcde", "efgh", "can use , or \" in csv"]
}, {
    "data": ["abcde", "efgh", "can use newlines\n\nin the row"]
}, {
    "comment": "# another comment in CSV.",
    "data": {}
}, {
    "data": ["abcde", "efgh", "not necessary \\n the end of csv"]
}]
```

### Example 2. Parsing CSV String

#### Code

```javascript
using CSV;

var csv = %{# comment in CSV.
abcde,efgh,non-quoted string
"abcde","efgh","quoted string"
"abcde",efgh,"quoted & non-quoted string in the same row"
"abcde",efgh,"can use , or "" in csv"
"abcde",efgh,"can use newlines

in the row"
# another comment in CSV.
abcde,efgh,not necessary \n the end of csv
};

System.println(CSV.parseString(csv).toJsonString(true));
```

#### Result

```json
[{
    "comment": "# comment in CSV.",
    "data": {}
}, {
    "data": ["abcde", "efgh", "non-quoted string"]
}, {
    "data": ["abcde", "efgh", "quoted string"]
}, {
    "data": ["abcde", "efgh", "quoted & non-quoted string in the same row"]
}, {
    "data": ["abcde", "efgh", "can use , or \" in csv"]
}, {
    "data": ["abcde", "efgh", "can use newlines\n\nin the row"]
}, {
    "comment": "# another comment in CSV.",
    "data": {}
}, {
    "data": ["abcde", "efgh", "not necessary \\n the end of csv"]
}]
```

### Example 3. Parsing TSV File

#### Code

```javascript
using CSV;

var tsv = 
    '# comment in TSV.\n'
    'abcde\tefgh\tnon-quoted string\n'
    '"abcde"\t"efgh"\t"quoted string"\n'
    '"abcde"\tefgh\t"quoted & non-quoted string in the same row"\n'
    '"abcde"\tefgh\t"can use , or "" in tsv"\n'
    '"abcde"\tefgh\t"can use newlines\n\nin the row"\n'
    '# another comment in TSV.\n'
    'abcde\tefgh\tnot necessary \\n the end of tsv\n'
;

File.open("test.tsv", File.WRITE) { => _1.print(tsv) };
System.println(TSV.parse("test.tsv").toJsonString(true));
```

#### Result

```json
[{
    "comment": "# comment in TSV.",
    "data": {}
}, {
    "data": ["abcde", "efgh", "non-quoted string"]
}, {
    "data": ["abcde", "efgh", "quoted string"]
}, {
    "data": ["abcde", "efgh", "quoted & non-quoted string in the same row"]
}, {
    "data": ["abcde", "efgh", "can use , or \" in tsv"]
}, {
    "data": ["abcde", "efgh", "can use newlines\n\nin the row"]
}, {
    "comment": "# another comment in TSV.",
    "data": {}
}, {
    "data": ["abcde", "efgh", "not necessary \\n the end of tsv"]
}]
```

### Example 4. Parsing TSV String

#### Code

```javascript
using CSV;

var tsv = 
    '# comment in TSV.\n'
    'abcde\tefgh\tnon-quoted string\n'
    '"abcde"\t"efgh"\t"quoted string"\n'
    '"abcde"\tefgh\t"quoted & non-quoted string in the same row"\n'
    '"abcde"\tefgh\t"can use , or "" in tsv"\n'
    '"abcde"\tefgh\t"can use newlines\n\nin the row"\n'
    '# another comment in TSV.\n'
    'abcde\tefgh\tnot necessary \\n the end of tsv\n'
;

System.println(TSV.parseString(tsv).toJsonString(true));
```

#### Result

```json
[{
    "comment": "# comment in TSV.",
    "data": {}
}, {
    "data": ["abcde", "efgh", "non-quoted string"]
}, {
    "data": ["abcde", "efgh", "quoted string"]
}, {
    "data": ["abcde", "efgh", "quoted & non-quoted string in the same row"]
}, {
    "data": ["abcde", "efgh", "can use , or \" in tsv"]
}, {
    "data": ["abcde", "efgh", "can use newlines\n\nin the row"]
}, {
    "comment": "# another comment in TSV.",
    "data": {}
}, {
    "data": ["abcde", "efgh", "not necessary \\n the end of tsv"]
}]
```

### Example 5. Finalize

#### Code

```javascript
File.remove("test.csv");
File.remove("test.tsv");
System.println("Succeeded.");
```

#### Result

```
Succeeded.
```
