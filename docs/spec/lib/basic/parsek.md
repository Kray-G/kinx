# Parsek

## Overview

### using Parsek

Parsek Library is not an embedded library, so you should load it by `using`.
The library is provided as a class, so it will prefer to make it be instantiated.

```javascript
using Parsek;

var $ = new Parsek();
```

You can use `$` as a variable name.

### Interfaces

#### Predefined Parser

The instance of `Parsek` class has some predefined parsers.

|     Parser      |                                                       Content                                                       |
| --------------- | ------------------------------------------------------------------------------------------------------------------- |
| $.eof           | Succeeds when it is EOF.                                                                                            |
| $.any           | Succeeds for any character.                                                                                         |
| $.all           | Succeeds after processing all.                                                                                      |
| $.index         | Returns a current position as `{ offset, line, column}`. `offset` is 0 origin, and `line` and `column` is 1 origin. |
| $.letter        | Same as `$.regex(/[a-zA-Z]/)`.                                                                                      |
| $.letters       | Same as `$.regex(/[a-zA-Z]*/)`.                                                                                     |
| $.digit         | Same as `$.regex(/[0-9]/)`.                                                                                         |
| $.digits        | Same as `$.regex(/[0-9]*/)`.                                                                                        |
| $.whitespace    | Same as `$.regex(/\s+/)`.                                                                                           |
| $.optWhitespace | Same as `$.regex(/\s*/)`.                                                                                           |
| $.cr            | Same as `$.string("\r")`.                                                                                           |
| $.lf            | Same as `$.string("\n")`.                                                                                           |
| $.crlf          | Same as `$.string("\r\n")`.                                                                                         |
| $.newline       | Same as `$.alt($.crlf, $.lf, $.cr)`.                                                                                |
| $.end           | Same as `$.alt($.newline, $.eof)`.                                                                                  |

#### Function To Create Parser

The instance of `Parsek` class has functions to create a parser as follows.

|           Function           |                                                                          Content                                                                           |
| ---------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------- |
| $.string(str)                | Creates a parser which is succeeded when it matches a string specified by `str`.                                                                           |
| $.regex(re, groupIndex)      | Creates a parser which is succeeded when it matches a regular expression specified by `re`. `value` will be a string of a group specified by `groupIndex`. |
| $.succeed(result)            | Creates a parser which is always successful with setting `result` to `value`.                                                                              |
| $.fail(message)              | Creates a parser which is always failed with `message`.                                                                                                    |
| $.oneOf(chars)               | Creates a parser which is succeeded when it matches one of `chars`.                                                                                        |
| $.noneOf(chars)              | Creates a parser which is succeeded when it matches none of `chars`.                                                                                       |
| $.sepBy(content, separator)  | Create a parser which returns the result of separating a string parsed by `content` with `separator`.                                                      |
| $.sepBy1(content, separator) | Almost same as `sepBy` which will allow 0 matches, but `sepBy1` will needs one or more matches.                                                            |
| $.lazy(description, f)       | Creates a generator which generates a parser by the function specified by `f` when it is used at first time.                                               |
| $.alt(...parsers)            | Creates a parser which is succeeded when one of parsers is succeeded. The order to apply a parser is the order you specified.                              |
| $.takeWhile(predicate)       | Creates a parser which is always succeeded while the result of `predicate` is true.                                                                        |
| $.seq(...parsers)            | Creates a parser which is succeeded when all parsers are succeeded in order. The result is an array of each parser's result.                               |
| $.seqMap(...parsers, mapf)   | Creates a parser which is succeeded when all parsers are succeeded in order. The result is an array of applying `mapf` for each parser's result.           |

### ParsekParser

The parser generated by a method of `Parsek` class is an instance of `ParsekParser` class.
This class has methods to chain parsers.

#### Parse All

After preparing a parser you want to use, parsing can be fired by the following method.

|         Method          |               Content               |
| ----------------------- | ----------------------------------- |
| parser.parseAll(target) | Parses all to `target` by `parser`. |

#### Parser Generators

|         Function         |                                                                                   Content                                                                                   |
| ------------------------ | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| parser.desc(description) | Sets a message when parsing by `parser` is failed.                                                                                                                          |
| parser.or(nextParser)    | Creates a parser which tries `nextParser` when parsing by `parser` is failed.                                                                                               |
| parser.and(nextParser)   | Creates a parser which executes `nextParser` when parsing by `parser` is succeeded. The result will be returned as an array.                                                |
| parser.then(nextParser)  | Creates a parser which executes `nextParser` when parsing by `parser` is succeeded. The result of `nextParser` will be returned and the result of `parser` will be ignored. |
| parser.skip(nextParser)  | Creates a parser which executes `nextParser` when parsing by `parser` is succeeded. The result of `parser` will be returned and the result of `nextParser` will be ignored. |
| parser.many()            | Creates a parser which parses it as 0 or more times.                                                                                                                        |
| parser.many1()           | Creates a parser which parses it as 1 or more times.                                                                                                                        |
| parser.times(min, max)   | Creates a parser which parses it from `min` to `max` times. If `max` is omitted, it will be succeeded when it is just `min` times.                                          |
| parser.sepBy(separator)  | Create a parser which returns the result of separating a parsed string with `separator`.                                                                                    |
| parser.sepBy1(separator) | Almost same as `sepBy` which will allow 0 matches, but `sepBy1` will needs one or more matches.                                                                             |
| parser.map(f)            | Uses a result as a result after applying the function specified by `f`.                                                                                                     |
| parser.chain(f)          | Pass the result of `parser` to the function `f`, and connect the parsers so that the new parser returned by `f` is used as the next parser.                                 |
| parser./(nextParser)     | The alias of `parser.or(nextParser)`.                                                                                                                                       |
| parser.+(nextParser)     | When `nextParser` is not specofoed, it is the alias of `parser.many1()`. When `nextParser` is specified, the alias of `parser.and(nextParser)`.                             |
| parser.*()               | The alias of `parser.many()`.                                                                                                                                               |

## Examples

### Example 1. Number

#### Code

```javascript
using Parsek;
var $ = new Parsek();

var number = $.regex(/[1-9][0-9]*|[0-9]/);

System.println(number.parseAll("0"));       // => {"position":1,"status":1,"value":"0"}
System.println(number.parseAll("10"));      // => {"position":2,"status":1,"value":"10"}
System.println(number.parseAll("129"));     // => {"position":3,"status":1,"value":"129"}
System.println(number.parseAll("abc"));     // => {"position":0,"status":0,"value":null}
System.println(number.parseAll("0129"));    // => {"position":1,"status":0,"value":null}
```

#### Result

```
{"position":1,"status":1,"value":"0"}
{"position":2,"status":1,"value":"10"}
{"position":3,"status":1,"value":"129"}
{"position":0,"status":0,"value":null}
{"position":1,"status":0,"value":null}
```

### Example 2. Map

#### Code

```javascript
using Parsek;
var $ = new Parsek();

var number = $.regex(/[1-9][0-9]*|[0-9]/).map(Integer.parseInt);
System.println(number.parseAll("129"));     // => {"position":3,"status":1,"value":129}
```

#### Result

```
{"position":3,"status":1,"value":129}
```

### Example 3. oneOf

#### Code

```javascript
using Parsek;
var $ = new Parsek();

var addsub = $.oneOf("+-");
var muldiv = $.oneOf("*/%");

System.println(addsub.parseAll("+"));       // => {"position":1,"status":1,"value":"+"}
System.println(addsub.parseAll("-"));       // => {"position":1,"status":1,"value":"-"}
System.println(addsub.parseAll("*"));       // => {"position":0,"status":0,"value":null}
System.println(muldiv.parseAll("*"));       // => {"position":1,"status":1,"value":"*"}
System.println(muldiv.parseAll("/"));       // => {"position":1,"status":1,"value":"/"}
System.println(muldiv.parseAll("%"));       // => {"position":1,"status":1,"value":"%"}
System.println(muldiv.parseAll("a"));       // => {"position":0,"status":0,"value":null}
```

#### Result

```
{"position":1,"status":1,"value":"+"}
{"position":1,"status":1,"value":"-"}
{"position":0,"status":0,"value":null}
{"position":1,"status":1,"value":"*"}
{"position":1,"status":1,"value":"/"}
{"position":1,"status":1,"value":"%"}
{"position":0,"status":0,"value":null}
```

### Example 4. string

#### Code

```javascript
using Parsek;
var $ = new Parsek();

var lbr = $.string("(");
var rbr = $.string(")");
var hoge = $.string("hoge");

System.println(lbr.parseAll("("));          // => {"position":1,"status":1,"value":"("}
System.println(lbr.parseAll(")"));          // => {"position":0,"status":0,"value":null}
System.println(rbr.parseAll("("));          // => {"position":0,"status":0,"value":null}
System.println(rbr.parseAll(")"));          // => {"position":1,"status":1,"value":")"}
System.println(hoge.parseAll("hoge"));      // => {"position":4,"status":1,"value":"hoge"}
System.println(hoge.parseAll("fuga"));      // => {"position":0,"status":0,"value":null}
```

#### Result

```
{"position":1,"status":1,"value":"("}
{"position":0,"status":0,"value":null}
{"position":0,"status":0,"value":null}
{"position":1,"status":1,"value":")"}
{"position":4,"status":1,"value":"hoge"}
{"position":0,"status":0,"value":null}
```

### Example 5. Expression

#### Code

```javascript
using Parsek;

var $ = new Parsek();
var number = $.regex(/[1-9][0-9]*|[0-9]/).map(Integer.parseInt);
var addsub = $.oneOf("+-");
var muldiv = $.oneOf("*/%");
var lbr = $.string("(");
var rbr = $.string(")");

var expression;
var factor = $.lazy(&() => $.alt(number, $.seq(lbr, expression, rbr)));
var term = $.seq(factor, $.seq(muldiv, factor).many());
expression = $.seq(term, $.seq(addsub, term).many());

// parse expression!
System.println(expression.parseAll("1+2*3+2*(14-2)"));
System.println(expression.parseAll("1+2*3+2*(14-2-)"));
```

#### Result

```
{"position":14,"status":1,"value":[[1,{}],[["+",[2,[["*",3]]]],["+",[2,[["*",["(",[[14,{}],[["-",[2,{}]]]],")"]]]]]]]}
{"position":7,"status":0,"value":null}
```

### Example 6. Making AST

#### Code

```javascript
using Parsek;

function makeAST(first, rest) {
    var expr = first;
    for (var i = 0, l = rest.length(); i < l; ++i) {
        expr = { lhs: expr, op: rest[i][0], rhs: rest[i][1] };
    }
    return expr;
}

var $ = new Parsek();
var number = $.regex(/[1-9][0-9]*|[0-9]/).map(Integer.parseInt);
var addsub = $.oneOf("+-");
var muldiv = $.oneOf("*/%");
var lbr = $.string("(");
var rbr = $.string(")");

var expression;
var factor = $.lazy(&() => $.alt(number, $.seq(lbr, expression, rbr).map(&(value) => value[1])));
var term = $.seqMap(factor, $.seq(muldiv, factor).many(), makeAST);
expression = $.seqMap(term, $.seq(addsub, term).many(), makeAST);

// test
System.println(expression.parseAll("1+2*3+2*(14-2)").value.toJsonString(true));
```

#### Result

```
{
    "lhs": {
        "lhs": 1,
        "op": "+",
        "rhs": {
            "lhs": 2,
            "op": "*",
            "rhs": 3
        }
    },
    "op": "+",
    "rhs": {
        "lhs": 2,
        "op": "*",
        "rhs": {
            "lhs": 14,
            "op": "-",
            "rhs": 2
        }
    }
}
```

### Example 7. Ignoring Spaces

#### Code

```javascript
using Parsek;

function makeAST(first, rest) {
    var expr = first;
    for (var i = 0, l = rest.length(); i < l; ++i) {
        expr = { lhs: expr, op: rest[i][0], rhs: rest[i][1] };
    }
    return expr;
}

var $ = new Parsek();
var ignore = $.optWhitespace;
var lexeme = &(p) => p.skip(ignore);

var number = lexeme($.regex(/[1-9][0-9]*|[0-9]/)).map(Integer.parseInt);
var addsub = lexeme($.oneOf("+-"));
var muldiv = lexeme($.oneOf("*/%"));
var lbr = lexeme($.string("("));
var rbr = lexeme($.string(")"));

var expression;
var factor = $.lazy(&() => $.alt(number, $.seq(lbr, expression, rbr).map(&(value) => value[1])));
var term = $.seqMap(factor, $.seq(muldiv, factor).many(), makeAST);
expression = $.seqMap(term, $.seq(addsub, term).many(), makeAST);

// test
System.println(ignore.then(expression).parseAll("  1 + 2 * 3 + 2 * ( 14 - 2 )  ").value.toJsonString(true));
```

#### Result

```
{
    "lhs": {
        "lhs": 1,
        "op": "+",
        "rhs": {
            "lhs": 2,
            "op": "*",
            "rhs": 3
        }
    },
    "op": "+",
    "rhs": {
        "lhs": 2,
        "op": "*",
        "rhs": {
            "lhs": 14,
            "op": "-",
            "rhs": 2
        }
    }
}
```

### Example 8. Interpreter (1)

#### Code

```javascript
using Parsek;

class Interpreter(opts_) {
    private sequence(r, op, lhs, rhs) {
        return if (!opts_.enableSequence);
        System.println("%d %s %d -> %d" % lhs % op % rhs % r);
    }
    public eval(ast) {
        var lhs = ast.lhs.isObject ? eval(ast.lhs) : ast.lhs;
        var rhs = ast.rhs.isObject ? eval(ast.rhs) : ast.rhs;
        var r = 0;
        switch (ast.op) {
        case '+':
            r = lhs + rhs;
            break;
        case '-':
            r = lhs - rhs;
            break;
        case '*':
            r = lhs * rhs;
            break;
        case '/':
            r = lhs / rhs;
            break;
        case '%':
            r = lhs % rhs;
            break;
        default:
            throw RuntimeException('Invalid operator');
        }
        sequence(r, ast.op, lhs, rhs);
        return r;
    }
}

function makeAST(first, rest) {
    var expr = first;
    for (var i = 0, l = rest.length(); i < l; ++i) {
        expr = { lhs: expr, op: rest[i][0], rhs: rest[i][1] };
    }
    return expr;
}

var $ = new Parsek();
var ignore = $.optWhitespace;
var lexeme = &(p) => p.skip(ignore);

var number = lexeme($.regex(/[1-9][0-9]*|[0-9]/)).map(Integer.parseInt);
var addsub = lexeme($.oneOf("+-"));
var muldiv = lexeme($.oneOf("*/%"));
var lbr = lexeme($.string("("));
var rbr = lexeme($.string(")"));

var expression;
var factor = $.lazy(&() => $.alt(number, $.seq(lbr, expression, rbr).map(&(value) => value[1])));
var term = $.seqMap(factor, $.seq(muldiv, factor).many(), makeAST);
expression = $.seqMap(term, $.seq(addsub, term).many(), makeAST);

// test
System.println(
    "Result = ",
    new Interpreter({ enableSequence: true })
        .eval(ignore.then(expression)
                    .parseAll("  1 + 2 * 3 + 2 * ( 14 - 2 )  ").value)
);
```

#### Result

```
2 * 3 -> 6
1 + 6 -> 7
14 - 2 -> 12
2 * 12 -> 24
7 + 24 -> 31
Result = 31
```

### Example 9. Interpreter (2)

#### Code

```javascript
using Parsek;

class Interpreter(opts_) {
    private sequence(r, op, lhs, rhs) {
        return if (!opts_.enableSequence);
        System.println("%d %s %d -> %d" % lhs % op % rhs % r);
    }
    public eval(ast) {
        var lhs = ast.lhs.isObject ? eval(ast.lhs) : ast.lhs;
        var rhs = ast.rhs.isObject ? eval(ast.rhs) : ast.rhs;
        var r = 0;
        switch (ast.op) {
        case '+':
            r = lhs + rhs;
            break;
        case '-':
            r = lhs - rhs;
            break;
        case '*':
            r = lhs * rhs;
            break;
        case '/':
            r = lhs / rhs;
            break;
        case '%':
            r = lhs % rhs;
            break;
        default:
            throw RuntimeException('Invalid operator');
        }
        sequence(r, ast.op, lhs, rhs);
        return r;
    }
}

function makeAST(first, rest) {
    var expr = first;
    for (var i = 0, l = rest.length(); i < l; ++i) {
        expr = { lhs: expr, op: rest[i][0], rhs: rest[i][1] };
    }
    return expr;
}

var $ = new Parsek();
var ignore = $.optWhitespace;
var lexeme = &(p) => p.skip(ignore);

var number = lexeme($.regex(/[1-9][0-9]*|[0-9]/)).map(Integer.parseInt);
var addsub = lexeme($.oneOf("+-"));
var muldiv = lexeme($.oneOf("*/%"));
var lbr = lexeme($.string("("));
var rbr = lexeme($.string(")"));

var expression;
var factor = $.lazy(&() => $.alt(number, $.seq(lbr, expression, rbr).map(&(value) => value[1])));
var term = $.seqMap(factor, $.seq(muldiv, factor).many(), makeAST);
expression = $.seqMap(term, $.seq(addsub, term).many(), makeAST);

// test
System.println(
    "Result = ",
    new Interpreter({ enableSequence: true })
        .eval(ignore.then(expression)
                    .parseAll("(( 123 ) * 2 * 4 - 3 * ( 12 + 10 )) % 100").value)
);
```

#### Result

```
123 * 2 -> 246
246 * 4 -> 984
12 + 10 -> 22
3 * 22 -> 66
984 - 66 -> 918
918 % 100 -> 18
Result = 18
```

### Example 10. JIT Compiler (1)

#### Code

```javascript
using Parsek;
using Jit;

class Compiler(opts_) {
    var regs_, regsLen_;
    enum { MOV, BOP, DIVMOD, RET }
    private initialize() {
        regs_ = [
            // Jit.R0 and Jit.R1 is used as a work register when it is division.
            { reg: Jit.R2, used: false, name: "R2" },
            { reg: Jit.R3, used: false, name: "R3" },
            { reg: Jit.R4, used: false, name: "R4" },
            { reg: Jit.R5, used: false, name: "R5" },
            { reg: Jit.S0, used: false, name: "S0" },
            { reg: Jit.S1, used: false, name: "S1" },
            { reg: Jit.S2, used: false, name: "S2" },
            { reg: Jit.S3, used: false, name: "S3" },
            { reg: Jit.S4, used: false, name: "S4" },
            { reg: Jit.S5, used: false, name: "S5" },
        ];
        regsLen_ = regs_.length();
    }
    private listing(type, op, dst, op1, op2) {
        return if (!opts_.enableListing);
        switch (type) {
        case MOV:
            System.println("%s <- %s" % dst % op1);
            break;
        case BOP:
            System.println("%s <- %s %s %s" % dst % op1 % op % op2);
            break;
        case DIVMOD:
            System.println("R0 <- %s" % op1);
            System.println("R1 <- %s" % op2);
            System.println("%s <- R0 %s R1" % dst % op);
            break;
        case RET:
            System.println("ret %s" % dst);
            break;
        }
    }
    private getReg() {
        for (var i = 0; i < regsLen_; ++i) {
            if (!regs_[i].used) {
                regs_[i].used = true;
                return i;
            }
        }
        throw RuntimeException("Not enough register");
    }
    private releaseReg(i) {
        regs_[i].used = false;
    }
    private compileLeaf(c, leaf) {
        var r = getReg();
        c.mov(regs_[r].reg, Jit.IMM(leaf));
        listing(MOV, null, regs_[r].name, leaf);
        return r;
    }
    private compileNode(c, ast) {
        var rl = ast.lhs.isObject ? compileNode(c, ast.lhs) : compileLeaf(c, ast.lhs);
        var rr = ast.rhs.isObject ? compileNode(c, ast.rhs) : compileLeaf(c, ast.rhs);
        var r = getReg();
        switch (ast.op) {
        case '+':
            c.add(regs_[r].reg, regs_[rl].reg, regs_[rr].reg);
            listing(BOP, ast.op, regs_[r].name, regs_[rl].name, regs_[rr].name);
            break;
        case '-':
            c.sub(regs_[r].reg, regs_[rl].reg, regs_[rr].reg);
            listing(BOP, ast.op, regs_[r].name, regs_[rl].name, regs_[rr].name);
            break;
        case '*':
            c.mul(regs_[r].reg, regs_[rl].reg, regs_[rr].reg);
            listing(BOP, ast.op, regs_[r].name, regs_[rl].name, regs_[rr].name);
            break;
        case '/':
            c.mov(Jit.R0, regs_[rl].reg);
            c.mov(Jit.R1, regs_[rr].reg);
            c.sdiv();
            c.mov(regs_[r].reg, Jit.R0);
            listing(DIVMOD, ast.op, regs_[r].name, regs_[rl].name, regs_[rr].name);
            break;
        case '%':
            c.mov(Jit.R0, regs_[rl].reg);
            c.mov(Jit.R1, regs_[rr].reg);
            c.sdivmod();
            c.mov(regs_[r].reg, Jit.R1);
            listing(DIVMOD, ast.op, regs_[r].name, regs_[rl].name, regs_[rr].name);
            break;
        default:
            throw RuntimeException('Invalid operator');
        }
        releaseReg(rl);
        releaseReg(rr);
        return r;
    }
    public compile(ast) {
        var c = new Jit.Compiler();
        c.enter();
        var r = compileNode(c, ast);
        c.ret(regs_[r].reg);
        listing(RET, null, regs_[r].name);
        return c.generate();
    }
    public run(ast) {
        var code = compile(ast);
        return code.run();
    }
}

function makeAST(first, rest) {
    var expr = first;
    for (var i = 0, l = rest.length(); i < l; ++i) {
        expr = { lhs: expr, op: rest[i][0], rhs: rest[i][1] };
    }
    return expr;
}

var $ = new Parsek();
var ignore = $.optWhitespace;
var lexeme = &(p) => p.skip(ignore);

var number = lexeme($.regex(/[1-9][0-9]*|[0-9]/)).map(Integer.parseInt);
var addsub = lexeme($.oneOf("+-"));
var muldiv = lexeme($.oneOf("*/%"));
var lbr = lexeme($.string("("));
var rbr = lexeme($.string(")"));

var expression;
var factor = $.lazy(&() => $.alt(number, $.seq(lbr, expression, rbr).map(&(value) => value[1])));
var term = $.seqMap(factor, $.seq(muldiv, factor).many(), makeAST);
expression = $.seqMap(term, $.seq(addsub, term).many(), makeAST);

// test
System.println(
    "Result = ",
    new Compiler({ enableListing: true })
        .run(ignore.then(expression)
                   .parseAll("  1 + 2 * 3 + 2 * ( 14 - 2 )  ").value)
);
```

#### Result

```
R2 <- 1
R3 <- 2
R4 <- 3
R5 <- R3 * R4
R3 <- R2 + R5
R2 <- 2
R4 <- 14
R5 <- 2
S0 <- R4 - R5
R4 <- R2 * S0
R2 <- R3 + R4
ret R2
Result = 31
```

### Example 11. JIT Compiler (2)

#### Code

```javascript
using Parsek;
using Jit;

class Compiler(opts_) {
    var regs_, regsLen_;
    enum { MOV, BOP, DIVMOD, RET }
    private initialize() {
        regs_ = [
            // Jit.R0 and Jit.R1 is used as a work register when it is division.
            { reg: Jit.R2, used: false, name: "R2" },
            { reg: Jit.R3, used: false, name: "R3" },
            { reg: Jit.R4, used: false, name: "R4" },
            { reg: Jit.R5, used: false, name: "R5" },
            { reg: Jit.S0, used: false, name: "S0" },
            { reg: Jit.S1, used: false, name: "S1" },
            { reg: Jit.S2, used: false, name: "S2" },
            { reg: Jit.S3, used: false, name: "S3" },
            { reg: Jit.S4, used: false, name: "S4" },
            { reg: Jit.S5, used: false, name: "S5" },
        ];
        regsLen_ = regs_.length();
    }
    private listing(type, op, dst, op1, op2) {
        return if (!opts_.enableListing);
        switch (type) {
        case MOV:
            System.println("%s <- %s" % dst % op1);
            break;
        case BOP:
            System.println("%s <- %s %s %s" % dst % op1 % op % op2);
            break;
        case DIVMOD:
            System.println("R0 <- %s" % op1);
            System.println("R1 <- %s" % op2);
            System.println("%s <- R0 %s R1" % dst % op);
            break;
        case RET:
            System.println("ret %s" % dst);
            break;
        }
    }
    private getReg() {
        for (var i = 0; i < regsLen_; ++i) {
            if (!regs_[i].used) {
                regs_[i].used = true;
                return i;
            }
        }
        throw RuntimeException("Not enough register");
    }
    private releaseReg(i) {
        regs_[i].used = false;
    }
    private compileLeaf(c, leaf) {
        var r = getReg();
        c.mov(regs_[r].reg, Jit.IMM(leaf));
        listing(MOV, null, regs_[r].name, leaf);
        return r;
    }
    private compileNode(c, ast) {
        var rl = ast.lhs.isObject ? compileNode(c, ast.lhs) : compileLeaf(c, ast.lhs);
        var rr = ast.rhs.isObject ? compileNode(c, ast.rhs) : compileLeaf(c, ast.rhs);
        var r = getReg();
        switch (ast.op) {
        case '+':
            c.add(regs_[r].reg, regs_[rl].reg, regs_[rr].reg);
            listing(BOP, ast.op, regs_[r].name, regs_[rl].name, regs_[rr].name);
            break;
        case '-':
            c.sub(regs_[r].reg, regs_[rl].reg, regs_[rr].reg);
            listing(BOP, ast.op, regs_[r].name, regs_[rl].name, regs_[rr].name);
            break;
        case '*':
            c.mul(regs_[r].reg, regs_[rl].reg, regs_[rr].reg);
            listing(BOP, ast.op, regs_[r].name, regs_[rl].name, regs_[rr].name);
            break;
        case '/':
            c.mov(Jit.R0, regs_[rl].reg);
            c.mov(Jit.R1, regs_[rr].reg);
            c.sdiv();
            c.mov(regs_[r].reg, Jit.R0);
            listing(DIVMOD, ast.op, regs_[r].name, regs_[rl].name, regs_[rr].name);
            break;
        case '%':
            c.mov(Jit.R0, regs_[rl].reg);
            c.mov(Jit.R1, regs_[rr].reg);
            c.sdivmod();
            c.mov(regs_[r].reg, Jit.R1);
            listing(DIVMOD, ast.op, regs_[r].name, regs_[rl].name, regs_[rr].name);
            break;
        default:
            throw RuntimeException('Invalid operator');
        }
        releaseReg(rl);
        releaseReg(rr);
        return r;
    }
    public compile(ast) {
        var c = new Jit.Compiler();
        c.enter();
        var r = compileNode(c, ast);
        c.ret(regs_[r].reg);
        listing(RET, null, regs_[r].name);
        return c.generate();
    }
    public run(ast) {
        var code = compile(ast);
        return code.run();
    }
}

function makeAST(first, rest) {
    var expr = first;
    for (var i = 0, l = rest.length(); i < l; ++i) {
        expr = { lhs: expr, op: rest[i][0], rhs: rest[i][1] };
    }
    return expr;
}

var $ = new Parsek();
var ignore = $.optWhitespace;
var lexeme = &(p) => p.skip(ignore);

var number = lexeme($.regex(/[1-9][0-9]*|[0-9]/)).map(Integer.parseInt);
var addsub = lexeme($.oneOf("+-"));
var muldiv = lexeme($.oneOf("*/%"));
var lbr = lexeme($.string("("));
var rbr = lexeme($.string(")"));

var expression;
var factor = $.lazy(&() => $.alt(number, $.seq(lbr, expression, rbr).map(&(value) => value[1])));
var term = $.seqMap(factor, $.seq(muldiv, factor).many(), makeAST);
expression = $.seqMap(term, $.seq(addsub, term).many(), makeAST);

// test
System.println(
    "Result = ",
    new Compiler({ enableListing: true })
        .run(ignore.then(expression)
                   .parseAll("(( 123 ) * 2 * 4 - 3 * ( 12 + 10 )) % 100").value)
);
```

#### Result

```
R2 <- 123
R3 <- 2
R4 <- R2 * R3
R2 <- 4
R3 <- R4 * R2
R2 <- 3
R4 <- 12
R5 <- 10
S0 <- R4 + R5
R4 <- R2 * S0
R2 <- R3 - R4
R3 <- 100
R0 <- R2
R1 <- R3
R4 <- R0 % R1
ret R4
Result = 18
```
