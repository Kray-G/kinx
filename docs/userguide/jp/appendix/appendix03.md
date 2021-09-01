
# 特殊メソッド

## Integer 特殊メソッド

<context label="Table:KinxIntegerMethods"/>
<context caption="特殊メソッド（整数）"/>
<context limit-column="0"/>

|           メソッド            |                                                 意味                                                  |
| ----------------------------- | ----------------------------------------------------------------------------------------------------- |
| `Integer.times(val, f)`       | `i = 0 ～ (val - 1)` の範囲として、`f` があれば `f(i)`　の結果で、無ければ `i` で配列を作成して返す。 |
| `Integer.upto(val, max, f)`   | `i = val ～ max` の範囲で引数として `f(i)` を呼ぶ。                                                   |
| `Integer.downto(val, min, f)` | `i = min ～ val` の範囲で引数として `f(i)` を呼ぶ。                                                   |
| `Integer.toString(val, rdx)`  | `val` を文字列に変換する。`rdx` は基数を表す。                                                        |
| `Integer.toDouble(val)`       | `val` を Double に変換する。                                                                          |

64bit 整数と多倍長整数はシームレスに相互変換されますので、Integer 特殊オブジェクトは多倍長整数にも適用されます。
ただし多倍長整数にループ系のメソッドが適用された場合、ループ回数が極端に大きくなりますのでご注意ください。

## Double 特殊メソッド

<context label="Table:KinxDoubleMethods"/>
<context caption="特殊メソッド（実数）"/>
<context limit-column="0"/>

|          メソッド           |                                                              意味                                                               |
| --------------------------- | ------------------------------------------------------------------------------------------------------------------------------- |
| `Double.toString(val, fmt)` | `val` を文字列に変換する。`fmt` は `%` で始まり、`a`、`A`、`e`、`E`、`f`、`F`、`g`、`G` のいずれかで終わる文字列。省略時は `%g` |
| `Double.toInt(val)`         | `val` を Integer に変換する。                                                                                                   |

実数に関する特殊メソッドは、基本的に型変換しか用意されていません。

## String 特殊メソッド

<context label="Table:KinxStringMethods"/>
<context caption="特殊メソッド（文字列）"/>
<context limit-column="0"/>

|            メソッド             |                                                      意味                                                       |
| ------------------------------- | --------------------------------------------------------------------------------------------------------------- |
| `String.startsWith(str, s)`     | 文字列が `s` で始まれば true。                                                                                  |
| `String.endsWith(str, s)`       | 文字列が `s` で終れば true。                                                                                    |
| `String.toUpper(str, [s, e])`   | `str` の `s` 文字目（0～）から `e` 文字目の前まで大文字化する。引数省略時は全てを大文字化する。                 |
| `String.toLower(str, [s, e])`   | `str` の `s` 文字目（0～）から `e` 文字目の前まで小文字化する。引数省略時は全てを小文字化する。                 |
| `String.trim(str, [c])`         | `str` の先頭と末尾から `c` で指定された文字を削除する。引数省略時は空白文字（空白、タブ、改行）を削除する。     |
| `String.trimLeft(str, [c])`     | `str` の先頭から `c` で指定された文字を削除する。引数省略時は空白文字（空白、タブ、改行）を削除する。           |
| `String.trimRight(str, [c])`    | `str` の末尾から `c` で指定された文字を削除する。引数省略時は空白文字（空白、タブ、改行）を削除する。           |
| `String.find(str, s)`           | 文字列の中で `s` が見つかった位置（0～）を返す。見つからなかった場合は -1 を返す。                              |
| `String.subString(str, s[, l])` | `str` の `s` 文字目（0～）から `l` 文字分の部分文字列を返す。                                                   |
| `String.replace(str, c, r)`     | `str` から `c` にマッチする部分を全て `r` に置換する。`c` は文字列または正規表現オブジェクトが指定可能。        |
| `String.toInt(str)`             | `str` を整数値に変換する。                                                                                      |
| `String.toDouble(str)`          | `str` を実数値に変換する。                                                                                      |
| `String.parentPath(str)`        | `str` をパスと認識し、親パスとなる部分文字列を返す。例）`"ab/cd/ef.x".parentPath()` → `"ab/cd"`                 |
| `String.filename(str)`          | `str` をパスと認識し、親パス部分を削除したファイル名部分文字列を返す。例）`"ab/cd/ef.x".filename()` → `"ef.x"`  |
| `String.stem(str)`              | `str` をパスと認識し、ファイル名の stem 部分文字列を返す。例）`"ab/cd/ef.x".stem()` → `"ef"`                    |
| `String.extnsion(str)`          | `str` をパスと認識し、ファイル名の拡張子部分文字列を返す。例）`"ab/cd/ef.x".extnsion()` → `".x"`                |
| `String.split(str, sep)`        | `str` を `sep` を区切り文字として分割し、配列として返す。`sep` は文字列、または正規表現オブジェクトが指定可能。 |
| `String.each(str, f)`           | `str` を 1 文字ずつ分割し、それを引数にして `f` 関数を呼び出す。`f` 関数の第 2 引数に index (0～) も渡される。  |

## Array 特殊メソッド

<context label="Table:KinxArrayMethods"/>
<context caption="特殊メソッド（配列）"/>
<context limit-column="0"/>

|            メソッド            |                                                             意味                                                              |
| ------------------------------ | ----------------------------------------------------------------------------------------------------------------------------- |
| `Array.length(ary)`            | 配列 `ary` の要素数を返す。                                                                                                   |
| `Array.keySet(obj)`            | オブジェクト `obj` のキー一覧を配列として返す。                                                                               |
| `Array.push(ary, e)`           | 配列 `ary` の最後の要素として `e` を追加する。                                                                                |
| `Array.pop(ary)`               | 配列 `ary` の最後の要素を返し、`ary` から削除する。                                                                           |
| `Array.unshift(ary, e)`        | 配列 `ary` の最初の要素として `e` を追加する。                                                                                |
| `Array.shift(ary)`             | 配列 `ary` の最初の要素を返し、`ary` から削除する。後ろの要素は順次先頭方向に移動する。                                       |
| `Array.join(ary, sep)`         | 配列 `ary` の要素を全てつなげた文字列として返す。要素と要素の間は `sep` でつなぐ。                                            |
| `Array.reverse(ary)`           | 配列 `ary` の要素を逆順にした新たな配列を返す。                                                                               |
| `Array.flatten(ary)`           | 配列 `ary` の要素をフラットにした形で新たな配列として返す。                                                                   |
| `Array.toString(ary)`          | 配列 `ary` を文字列化して返す。デフォルトのセパレータは `", "`                                                                |
| `Array.toJsonString(ary, idt)` | 配列 `ary` を JSON 文字列化して返す。`idt` を true とすると、インデントした形で整形する。                                     |
| `Array.apply(ary, f)`          | `f(ary)` を実行する。                                                                                                         |
| `Array.each(ary, f)`           | `ary` の各要素 `e` に対して `f(e, index)` を実行する。                                                                        |
| `Array.map(ary, f)`            | `ary` の各要素 `e` に対して `f(e, index)` の結果の集合となる新たな配列を返す。                                                |
| `Array.flatMap(ary, f)`        | `map` した新たな配列をフラットにして返す。                                                                                    |
| `Array.filter(ary, f)`         | `ary` の各要素 `e` に対して `f(e, index)` の結果が真となるもののみの集合として新たな配列を返す。                              |
| `Array.reject(ary, f)`         | `ary` の各要素 `e` に対して `f(e, index)` の結果が偽となるもののみの集合として新たな配列を返す。                              |
| `Array.reduce(ary, f, i)`      | 前の要素までの結果を `r`（初期値は `i`、デフォルト null）として、`ary` の各要素 `e` に対し `f(r, e)` を行った最終結果を返す。 |
| `Array.sort(ary, comp)`        | 任意の `ary` の要素 `e1`, `e2` に対する `comp(e1, e2)` の結果を利用して `ary` 全体をソートした新たな配列を返す。              |
| `Array.clone(obj)`             | `obj` のディープ・コピーを作成する。                                                                                          |
| `Array.extend(obj, obj2)`      | `obj` の内容を `obj2` の内容で拡張する。同じキーがあれば上書きする。                                                          |
| `Array.println(ary)`           | `ary` の各要素 `e` に対して `System.println(e)` を適用する。                                                                  |

`push`、`pop`、`unshift`、`shift` は破壊的な操作を行います。
Array の特殊メソッドはオブジェクトにも適用されることに注意してください。
使い分ける場合は呼び出された後に区別します。
詳しくは「\\nameref{配列とオブジェクト}」をご参照ください。

## Binary 特殊メソッド

<context label="Table:KinxBinaryMethods"/>
<context caption="特殊メソッド（バイナリ）"/>
<context limit-column="0"/>

|             メソッド             |                                                                     意味                                                                      |
| -------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| `Binary.length(bin)`             | バイナリ `bin` の要素数を返す。                                                                                                               |
| `Binary.push(bin, e)`            | バイナリ `bin` の最後の要素として `e` を追加する。                                                                                            |
| `Binary.pop(bin)`                | バイナリ `bin` の最後の要素を返し、`bin` から削除する。                                                                                       |
| `Binary.unshift(bin, e)`         | バイナリ `bin` の最初の要素として `e` を追加する。                                                                                            |
| `Binary.shift(bin)`              | バイナリ `bin` の最初の要素を返し、`bin` から削除する。後ろの要素は順次先頭方向に移動する。                                                   |
| `Binary.join(bin, sep, fmt)`     | バイナリ `bin` の要素を全てつなげた文字列として返す。要素と要素の間は `sep` でつなぐ。`fmt` が省略された場合 `"0x02x"` でフォーマットされる。 |
| `Binary.reverse(bin)`            | バイナリ `bin` の要素を逆順にした新たなバイナリを返す。                                                                                       |
| `Binary.toString(bin, sep, fmt)` | バイナリ `bin` を文字列化して返す。デフォルトのセパレータは `", "`。`fmt` が省略された場合 `"0x02x"` でフォーマットされる。                   |
| `Binary.apply(bin, f)`           | `f(bin)` を実行する。                                                                                                                         |
| `Binary.each(bin, f)`            | `bin` の各要素 `e` に対して `f(e, index)` を実行する。                                                                                        |
| `Binary.map(bin, f)`             | `bin` の各要素 `e` に対して `f(e, index)` の結果の集合となる新たなバイナリを返す。                                                            |
| `Binary.filter(bin, f)`          | `bin` の各要素 `e` に対して `f(e, index)` の結果が真となるもののみの集合として新たなバイナリを返す。                                          |
| `Binary.reject(bin, f)`          | `bin` の各要素 `e` に対して `f(e, index)` の結果が偽となるもののみの集合として新たなバイナリを返す。                                          |
| `Binary.reduce(bin, f, itr)`     | 前の要素までの結果を `r` （初期値は `itr`、デフォルト null）として、`bin` の各要素 `e` に対し `f(r, e)` を行った最終結果を返す。              |
| `Binary.sort(bin, c)`            | 任意の `bin` の要素 `e1`, `e2` に対する `c(e1, e2)` の結果を利用して `bin` 全体をソートした新たなバイナリを返す。                             |
| `Binary.clone(bin)`              | `bin` のコピーを作成する。                                                                                                                    |
| `Binary.println(bin)`            | `bin` の各要素 `e` に対して `System.println(e)` を適用する。                                                                                  |

基本的にバイナリ列に適用することになるため、あまり複雑なことはできません。
Array と同様に `push`、`pop`、`unshift`、`shift` は破壊的な操作を行います。
`push`、`pop`、`unshift`、`shift` は破壊的な操作を行います。

また、バイナリに対するメソッドは、配列と比較してネイティブ・コードで最適化されているケースがいくつかあります。
例えば、`Array.sort(ary, compfunc)` と `Binary.sort(bin, compfunc)` はクイックソートですが、
Binary のほうは `compfunc` が省略された場合に `stdlib.h` の `qsort` を使うように最適化されています。
また、`Binary.reverse()` も C ルーチンで実装されています。
つまり、Binary に対しての降順ソートは `bin.sort(&(a, b) => b <=> a)` よりも `bin.sort().reverse()` としたほうが速い結果が出ます。

```javascript
function test(name, f) {
    var tmr = new SystemTimer();
    var sorted = f();
    var disp = [sorted[0], sorted[1], "...", sorted[-1]];
    System.println("%{name}%{disp} => ", tmr.elapsed());
}

var a = 10000.times(&() => Integer.parseInt(Math.random() * 100));
var bin = <...a>;
test("sort1", &() => bin.sort(&(a, b) => b <=> a));
test("sort2", &() => bin.sort().reverse());
```

上記プログラムで実測してみた結果が以下となります。

```console
sort1[99, 99, "...", 0] => 0.045096
sort2[99, 99, "...", 0] => 0.000582
```

100倍くらい速くなりました。
ただし、ここまで差が出るケースはまれですので、普段はあまり意識する必要はありません。

