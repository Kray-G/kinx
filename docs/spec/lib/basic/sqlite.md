# SQlite

## Overview

SQLite database file is useful because it uses just one file and that file is portable and independent from a platform.

## SQLite Object

`SQLite` object is provided as a core library, but in fact `Database` object which wraps a `SQLite` object and has more useful interfaces is recommended.

### DB Connection

Generating by `new SQLite(filename[, timeout])` and it connects to the database.

```javascript
var db = new SQLite("sample.db", 30000);
```

### Exec/Query

Basically `SQLite` object has three methods of `exec`, `prepare`, `transaction` as a basic method.
By the way, `Database` object described later has more useful methods.

#### Exec

Use a `exec` method when it is not the case of using `SELECT`, otherwise use a `prepare` method to create a SQL object.

```javascript
db.exec("CREATE TABLE IF NOT EXISTS mytable "
    "("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL"
    ")"
);
```

#### Prepare

The SQL object returned by a `prepare` method has a `bind`, `exec`, `query`, and `next` method.
All methods will return the object itself after operations.

And a `next` method is available after calling a `query` method.
The result of `next` method is a row object, and its shape is like an example below.

```javascript
{
    "columnName": [ "col1", "col2", "col3" ],
    "value": [ val1, val2, val3 ]
}
```

For example, you can use it like below.

```javascript
var c, r = db.prepare("SELECT * FROM mytable WHERE (id > ? AND id < ?) OR id = ?")
            .bind(2)
            .bind(8, 10)    // bind() can be separated.
            .query();       // do binding & ready to next().

while (c = r.next()) {
    var cols = c.columnName;
    var vals = c.value;
    System.println("Record[%d]" % vals[0]);
    for (var i = 0, len = cols.length(); i < len; ++i) {
        System.println("    %-8s = %s" % cols[i] % vals[i]);
    }
}
```

A `query` method is available only when it is `SELECT`.
Bound values are always reset after executing SQL command when using `exec`.

#### Transaction

A `transaction` method provides a lock mechanism for whole command sequence.
For example, you can use it like below when inserting multiple values at one operation without interrupted.
It will be faster than doing it without `transaction`.

```javascript
var ins = db.prepare("INSERT INTO mytable (name) VALUES (?)");
db.transaction(&{
    for (var i = 0; i < 20; ++i) {
        ins.bind("name(%{i})").exec();
    }
});
```

## Database

The class `Database` is a wrapper class of `SQLite` described above.
It has methods as follows.

* `transaction` ... Does a transaction.
* `createTable` ... Creates a table.
* `dropTable` ... Removes a table.
* `insert` ... Inserts data.
* `delete` ... Removes data.
* `query` ... Returns a cursor object to fetch data.
* `queryAll` ... Fetch all data.

## Instantiation

You can instantiate a `Database` object by `new` operator.

```javascript
var db = new Database(dbfile[, options]);
```

The options when instantiating it are as follows.

* `force` ... When it is true, the file will be created if the file does not exist. When it is false, an exception will be raised. It is false by default.
* `timeout` ... Specify a timeout of database operations in milliseconds. It is 10 seconds by default.

Here is an example below.

```javascript
var db = new Database("dbfile.db", { force: true });
```

Moreover, you can pass multiple database names as an array, it means to use `ATTACH DATABASE`.
The matster database is the first item of an array and the rest items will be attached to the master.
And then, the stem of filename, which is `abc` for `abc.db`, is automatically used as an alias.
You can specify the name of `main` for the master database, and you can specify the stem of filename as alias for other databases.

### Transaction

You can use `transaction` with more useful, but normally it is used almost same as a method of `SQLite` object.

```javascript
db.transaction(&{
    ...
});
```

When operations in the transaction is successfully done, it will commit automatically.
Otherwise, for example when an exception occurs, it will try to rollback

And a `transaction` method of `Database` class has a mode as a first argument.
The mode should be specified by a string as follows.

* `'EXCLUSIVE'` ... Starts transaction with `BEGIN EXCLUSIVE` mode.
* `'IMMEDIATE'` ... Starts transaction with `BEGIN IMMEDIATE`  mode.

It will be `BEGIN DEFERRED` when it is not specified or any other strings.

```javascript
db.transaction('EXCLUSIVE', &{
    ...
});
```

### Create Table

`createTable` will receive a table name and a schema.
A schema should be just a string or an array.
If it is an array, it will be just joined by `,` and wrapped by `(` and `)`.

```javascript
db.createTable("mytable", [
    "id INTEGER PRIMARY KEY AUTOINCREMENT",
    "name TEXT NOT NULL"
]);
```

By the way, a table will be created always with `IF NOT EXISTS`.

### Drop Table

`dropTable` will receive only a name of a table.

```javascript
db.dropTable("mytable");
```

By the way, it will always do with `IF EXISTS`.

**Note**  
You will see `RuntimeException` of `database is locked` when a statement is remaining.
You have to do `dropTable` in the condition that no references to a statement is remaining.

### Insert

`insert` will receive parameters as follows.

| パラメータ |                                                              内容                                                               |
| ---------- | ------------------------------------------------------------------------------------------------------------------------------- |
| `into`     | **Mandatory**, a table name.                                                                                                    |
| `replace`  | true or false, false when omitted.                                                                                              |
| `column`   | **Mandatory**, a column name string, or an array of column names.                                                               |
| `bind`     | **Mandatory**, bound values for each `column` as an array, and it is needed the same number of items as the number of `column`. |

Normally, `insert` in transaction is faster than it without transaction.

```javascript
db.transaction(&{
    for (var i = 0; i < 20; ++i) {
        db.insert({
            into: "mytable",
            column: ["name"],
            bind: ["name(%{i})"],
        });
    }
});
```

### Delete

`delete` will use `from`, `where`, and `bind`. All parameters are mandatory.

```javascript
db.delete({
    from: "mytable",
    where: "id = ?",
    bind: [4]
});
```

### Query

This method `query` will return a `DatabaseCursor` object to fetch data mathed by a condition.
The initial state of a `DatabaseCursor` object is the condition of nothing fetched.

The parameters for `query()` is as follows.

|  パラメータ   |                                                内容                                                 |
| ------------- | --------------------------------------------------------------------------------------------------- |
| `distinct`    | true or false, false when omitted.                                                                  |
| `select`      | `*` when omitted, or a column name string or an array of column names.                              |
| `from`        | **Mandatory**, a table name.                                                                        |
| `innerJoin`   | INNER JOIN clause (`innerJoin` and `outerJoin` can not be specified at the same time)               |
| `outerJoin`   | OUTER JOIN clause.                                                                                  |
| `on`          | Available only when specifying `innerJoin` or `outerJoin`                                           |
| `where`       | WHERE clause, a string, or an array. It will join by `AND` when it is an array.                     |
| `bind`        | An array of bound values against WHERE clause. The number of items is the same number of `?`.       |
| `groupby`     | GROUP BY clause.                                                                                    |
| `having`      | HAVING clause.                                                                                      |
| `orderby`     | ORDER BY clause. (`orderby`, `orderbyAsc`, and `orderbyDesc` can not be specified at the same time) |
| `orderbyAsc`  | It is same as `orderby`.                                                                            |
| `orderbyDesc` | ORDER BY clause with DESC.                                                                          |
| `limit`       | LIMIT clause.                                                                                       |
| `offset`      | OFFSET clause.                                                                                      |

Here is an example below.

```javascript
var c = db.query({
    select: "*",
    from: "mytable",
    where: "(id > ? AND id < ?) OR id = ?",
    bind: [2, 8, 10]
});
```

The `c` above is a `DatabaseCursor` object, and it has a `next()`, `columns()`, and `values()` method.
A `columns()` returns an array of column names and `values()` returns an array of values.

Using a `DatabaseCursor` object, all data can be acquired by fetching until returning `null`.

```javascript
while (c.next()) {
    var cols = c.columns();
    var vals = c.values();
    System.println("Record[%d]" % vals[0]);
    for (var i = 0, len = cols.length(); i < len; ++i) {
        System.println("    %-8s = %s" % cols[i] % vals[i]);
    }
}
```

### Query All

You can use a `queryAll` method with two different way of usage.
That is the way of using a callback, or not using a callback.
If not using a callback, you can get all data at once, but it will use a lot of memory.
Therefore you can use a callback to fetch data one by one.

#### Getting Data At Once

When you want to get data at once, you do not write a callback like an example below.

```javascript
var res = db.queryAll({
    select: "*",
    from: "mytable",
    where: "(id > ? AND id < ?) OR id = ?",
    bind: [2, 8, 10]
});
```

Data structure will be the following.

```json
{
    "columns": ["id", "name"],
    "values": [
        [3, "name(2)"],
        [5, "name(4)"],
        [6, "name(5)"],
        [7, "name(6)"],
        [10, "name(9)"]
    ]
}
```

#### Do It With Callback

You can write a callback as a second argument like an example below.

```javascript
db.queryAll({
    select: "*",
    from: "mytable",
    where: "(id > ? AND id < ?) OR id = ?",
    bind: [2, 8, 10]
}, &(c, i) => {
    System.println("%2d => " % i, c.toJsonString());
});
```

The result is below. Each row object will be returned.
In this case, note that it is **NOT** a `DatabaseCursor` object.

```
 0 => {"columns":["id","name"],"values":[3,"name(2)"]}
 1 => {"columns":["id","name"],"values":[5,"name(4)"]}
 2 => {"columns":["id","name"],"values":[6,"name(5)"]}
 3 => {"columns":["id","name"],"values":[7,"name(6)"]}
 4 => {"columns":["id","name"],"values":[10,"name(9)"]}
```

If you want to stop iteration, return `false` like the following.

```javascript
db.queryAll({
    select: "*",
    from: "mytable",
    where: "(id > ? AND id < ?) OR id = ?",
    bind: [2, 8, 10]
}, &(c, i) => {
    System.println("%2d => " % i, c.toJsonString());
    return false if (i == 2);
});
```

Here is the result.

```
 0 => {"columns":["id","name"],"values":[3,"name(2)"]}
 1 => {"columns":["id","name"],"values":[5,"name(4)"]}
 2 => {"columns":["id","name"],"values":[6,"name(5)"]}
```

## Examples

### Example 1. SQLite - Create Table

#### Code

```javascript
File.remove("database.db");
var db = new SQLite("database.db", 3000);
db.exec("CREATE TABLE IF NOT EXISTS mytable "
    "("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL"
    ")"
);
System.println(File.exists("database.db"));
```

#### Result

```
1
```

### Example 2. SQLite - Insert

#### Code

```javascript
var db = new SQLite("database.db", 3000);
var ins = db.prepare("INSERT INTO mytable (name) VALUES (?)");
db.transaction(&{
    for (var i = 0; i < 20; ++i) {
        ins.bind("name(%{i})").exec();
    }
});
var c, r = db.prepare("SELECT * FROM mytable WHERE (id > ? AND id < ?) OR id = ?")
            .bind(2)
            .bind(8, 10)
            .query();
while (c = r.next()) {
    var cols = c.columnName;
    var vals = c.value;
    System.println("Record[%d]" % vals[0]);
    for (var i = 0, len = cols.length(); i < len; ++i) {
        System.println("    %-8s = %s" % cols[i] % vals[i]);
    }
}
```

#### Result

```
Record[3]
    id       = 3
    name     = name(2)
Record[4]
    id       = 4
    name     = name(3)
Record[5]
    id       = 5
    name     = name(4)
Record[6]
    id       = 6
    name     = name(5)
Record[7]
    id       = 7
    name     = name(6)
Record[10]
    id       = 10
    name     = name(9)
```

### Example 3. Database - CreateTable/Query

#### Code

```javascript
var db = new Database("dbfile.db", { force: true, timeout: 3000 });
db.dropTable("mytable");
db.createTable("mytable", [
    "id INTEGER PRIMARY KEY AUTOINCREMENT",
    "name TEXT NOT NULL"
]);
var c = db.query({
    select: "name",
    from: "sqlite_master",
    where: "type='table'",
});
while (c.next()) {
    var cols = c.columns();
    var vals = c.values();
    System.println("Record[%d]" % vals[0]);
    for (var i = 0, len = cols.length(); i < len; ++i) {
        System.println("    %-8s = %s" % cols[i] % vals[i]);
    }
}
```

#### Result

```
Record[sqlite_sequence]
    name     = sqlite_sequence
Record[mytable]
    name     = mytable
```

### Example 4. Database - Insert/Query

#### Code

```javascript
var db = new Database("dbfile.db", { force: true, timeout: 3000 });
db.transaction(&{
    for (var i = 0; i < 20; ++i) {
        db.insert({
            into: "mytable",
            column: ["name"],
            bind: ["name(%{i})"],
        });
    }
});
var c = db.query({
    select: "*",
    from: "mytable",
    where: "(id > ? AND id < ?) OR id = ?",
    bind: [2, 8, 10]
});
while (c.next()) {
    var cols = c.columns();
    var vals = c.values();
    System.println("Record[%d]" % vals[0]);
    for (var i = 0, len = cols.length(); i < len; ++i) {
        System.println("    %-8s = %s" % cols[i] % vals[i]);
    }
}
```

#### Result

```
Record[3]
    id       = 3
    name     = name(2)
Record[4]
    id       = 4
    name     = name(3)
Record[5]
    id       = 5
    name     = name(4)
Record[6]
    id       = 6
    name     = name(5)
Record[7]
    id       = 7
    name     = name(6)
Record[10]
    id       = 10
    name     = name(9)
```

### Example 5. Database - Delete/QueryAll (1)

#### Code

```javascript
var db = new Database("dbfile.db", { force: true, timeout: 3000 });
db.delete({
    from: "mytable",
    where: "id = ?",
    bind: [4]
});
var res = db.queryAll({
    select: "*",
    from: "mytable",
    where: "(id > ? AND id < ?) OR id = ?",
    bind: [2, 8, 10]
});
System.println(res.toJsonString(true));
```

#### Result

```
{
    "columns": ["id", "name"],
    "values": [[3, "name(2)"], [5, "name(4)"], [6, "name(5)"], [7, "name(6)"], [10, "name(9)"]]
}
```

### Example 6. Database - QueryAll (2)

#### Code

```javascript
var db = new Database("dbfile.db", { force: true, timeout: 3000 });
db.queryAll({
    select: "*",
    from: "mytable",
    where: "(id > ? AND id < ?) OR id = ?",
    bind: [2, 8, 10]
}, &(c, i) => {
    System.println("*%2d => " % i, c.toJsonString());
});
```

#### Result

```
* 0 => {"columns":["id","name"],"values":[3,"name(2)"]}
* 1 => {"columns":["id","name"],"values":[5,"name(4)"]}
* 2 => {"columns":["id","name"],"values":[6,"name(5)"]}
* 3 => {"columns":["id","name"],"values":[7,"name(6)"]}
* 4 => {"columns":["id","name"],"values":[10,"name(9)"]}
```

### Example 7. Database - QueryAll (3)

#### Code

```javascript
var db = new Database("dbfile.db", { force: true, timeout: 3000 });
db.queryAll({
    select: "*",
    from: "mytable",
    where: "(id > ? AND id < ?) OR id = ?",
    bind: [2, 8, 10]
}, &(c, i) => {
    System.println("*%2d => " % i, c.toJsonString());
    return false if (i == 2);
});
```

#### Result

```
* 0 => {"columns":["id","name"],"values":[3,"name(2)"]}
* 1 => {"columns":["id","name"],"values":[5,"name(4)"]}
* 2 => {"columns":["id","name"],"values":[6,"name(5)"]}
```
