# KC-JSON [![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)

Simple JSON Parser in C.

## Features

`kc-json` is the simple JSON parser with some extended functionality.
This code was created for the project of [kcs](https://github.com/Kray-G/kcs), and was derived from that project.
Main feature is:

*   Parsing JSON structure.
*   Accessing elements.
*   Calculating in the structure. ex) `+`, `-`, `*`, `/`, `%`, `&`, `|`, `^`, `(expr)`, etc.
*   One header & source file.

Please see details of the parser syntax [here](src/kc-json.y).

## Build

Just do it, and you will find `kc-json.h`, `kc-json.c`, `sample(.exe)`, and `sample.json`/`sample_ext1.json` under `dist` folder.

```
$ make
```

Run the samples with below.

```
$ make sample
```

## Example

### Sample C Code

```c
#include <stdio.h>
#include "kc-json.h"

int main()
{
    json_object_t *j = json_parse_file("sample.json");
    if (j) {
        /* Printing elements */
        json_pretty_print(j);

        /* Counting elements */
        int count = json_get_element_count(j);
        printf("element count = %d\n", count);

        /* Accessing elements */
        json_object_t *e = json_get_element(j, 1);
        json_object_t *p = json_get_property(e, "path");

        /* Getting the value */
        string_t *s = json_get_string(p);
        printf("json[1].path = %s\n", s ? s->cstr : "<not found..>");

        /* Releasing all allocated memory */
        json_free_all(j);
    } else {
        printf("Parse Error: %s\n", json_error_message());
    }
    return 0;
}
```

### Sample for Normal JSON
#### Sample JSON

```json
[ "Sample",
    { "x": 410, "y": 150, "type": "link", "path": "/Applications" },
    {
        "p1": { "x": 130, "y": 150, "type": "file" },
        "p2": { "x": 230, "y": 90, "type": "directory" }
    }
]
```

#### Result

```
[
    "Sample",
    {
        "x": 410,
        "y": 150,
        "type": "link",
        "path": "/Applications"
    },
    {
        "p1": {
            "x": 130,
            "y": 150,
            "type": "file"
        },
        "p2": {
            "x": 230,
            "y": 90,
            "type": "directory"
        }
    }
]
element count = 3
json[1].path = /Applications
```

### Sample for Extended JSON
#### Sample JSON

```json
[ "Sample" + " (" + 1 + ")",
    { "x": 410, "y": 150 * (20 + 1), "type": "link", "path": "/Applications" },
    {
        "p1": { "x": 130, "y": 150, "type": "file" },
        "p2": { "x": 230, "y": 90, "type": "directory" }
    }
]
```

#### Result

```
[
    "Sample (1)",
    {
        "x": 410,
        "y": 3150,
        "type": "link",
        "path": "/Applications"
    },
    {
        "p1": {
            "x": 130,
            "y": 150,
            "type": "file"
        },
        "p2": {
            "x": 230,
            "y": 90,
            "type": "directory"
        }
    }
]
element count = 3
json[1].path = /Applications
```

## TODO

*   Supporting to edit the structure.
*   Supporting [JSONPath].

[JSONPath]: http://goessner.net/articles/JsonPath/

## License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

Thanks for [Miniyacc][] which is a good parser generator that I modified and used.
And many thanks for all users of this product.

[Miniyacc]: https://c9x.me/yacc/
