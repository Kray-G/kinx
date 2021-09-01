
# さあ始めよう
## インストール・アンインストール
### インストール

#### Windows

Windows での Kinx のインストールは Scoop を使用します。

```console
// scoop bucket add is needed only at the first time.
$ scoop bucket add kinx https://github.com/Kray-G/kinx
$ scoop install kinx
```

Bucket の登録は最初に 1 度だけ必要です。
Kinx がインストールできたら、パスが通っているか確認するために一度バージョン表示をしてみましょう。

```console
$ kinx.exe -v
kinx.exe version 1.1.0 built on 4b2bd84d86fc4e30a78fffbf84805158dc097193
```

Kinx へのパスが通っていることを確認したら、
今後追加するかもしれないパッケージ・コマンドに対しても正しくパスが通るように、
以下のコマンドを実行しておきます。

```console
$ kinx --install-path
```

これで準備は完了です。

#### Linux(Ubuntu)

Linux(Ubuntu) の場合は、インストーラを使ってインストールします。
[Relases](https://github.com/Kray-G/kinx/releases) ページから `.deb` ファイルをダウンロードします[^releasefile]。
ダウンロードしたディレクトリに移動し、次のようにインストールします。

[^releasefile]: ファイル名にバージョン番号が含まれます。必要なバージョンをダウンロードしてください

```console
$ sudo apt install ./kinx_1.1.0-0_amd64.deb
```

Kinx がインストールできたら、パスが通っているか確認するために一度バージョン表示をしてみましょう。

```console
$ kinx -v
kinx version 1.1.0 built on 4b2bd84d86fc4e30a78fffbf84805158dc097193
```

これで準備は完了です。

### アンインストール

#### Windows

Windows でアンインストールする場合は、以下のように実施します。

```console
$ scoop uninstall kinx
```

これで、Kinx 本体および Kinx パッケージが全て削除されます。
また、Bucket も削除したい場合は、以下のようにします。

```console
$ scoop bucket rm kinx
```

これで Bucket も削除されます。
もう一度登録する場合は、最後 `scoop bucket add` コマンドを実行して登録してください。

#### Linux

Linux でアンインストールする場合は、以下のように実施します。

```console
$ sudo apt remove kinx
```

これで、Kinx 本体および Kinx パッケージが全て削除されます。

## Kinx の実行
### 実行方法

Kinx の実行方法は以下の通りです。

```console
$ kinx [options] <kinx-file>.kx
```

標準的な Kinx の拡張子は `.kx` ですが、特に `.kx` であることは意識していません。
任意の拡張子のファイルを Kinx スクリプトとして実行できます。

### コマンドライン引数

主なコマンドライン引数として、以下が利用可能です。

<context label="Table:KinxCommandLineArguments"/>
<context caption="コマンドライン引数"/>
<context limit-column="0"/>

|   オプション    |                               意味                               |
| --------------- | ---------------------------------------------------------------- |
| `-h`            | ヘルプを表示する。                                               |
| `-c`            | シンタックスチェックのみ。実際の実行は行わない。                 |
| `-d`            | 中間表現形式を出力する。実際の実行は行わない。                   |
| `-D`            | 抽象構文木(AST)を出力する。実際の実行は行わない。                |
| `-u`            | 標準入出力での UTF8 変換を行わない。(Windows のみ)               |
| `-q`            | コンパイル時の各種出力を行わない。                               |
| `-i`            | ソースを標準入力から入力する。                                   |
| `-v`            | 簡易バージョンを出力する。                                       |
| `--version`     | 詳細バージョンを出力する。                                       |
| `--debug`       | デバッガー・モードで実行する。                                   |
| `--dot`         | 中間表現を `.dot` 形式で出力する。                               |
| `--with-native` | `-d` と一緒に使用し、`native` 関数のアセンブリコードを出力する。 |

デバッガ―・モードで起動するとデバッガが起動します。
デバッガに関しては「\\nameref{デバッガ}」を参照してください。
また、`--with-native` オプションに関しては「\\nameref{`native` 関数}」で一部説明しています。

### hello, world.

では誰もが最初に書くスクリプト、`hello, world.` を書いてみましょう。
以下の内容を記載し、`hello.kx` というファイル名で保存します。

```kinx:hello.kx
System.println("hello, world.");
```

早速実行してみましょう。

```console
$ kinx hello.kx
hello, world.
```

このように、Kinx はスクリプト言語ですので複雑で面倒なセットアップ・コードなどは一切不要です。
自分のしたいことにフォーカスし、すぐに実行して試すことができます。

## Kinx ツアー

Kinx の全体像を知るために、まずは簡単な Kinx の機能紹介をしていきましょう。
各セクションでは、それぞれの機能の解説ページへのリンクを記載しています。
機能詳細を確認したい場合は、それぞれのリンク先を確認してみてください。

### プログラム構造

プログラムはトップレベルから記述可能です。
先の `hello, world.` プログラムのように、
プログラムの先頭から直接プログラム・コードを記述できます。

```kinx:hello.kx
System.println("hello, world.");
```

### コメント

コメントは C/C++ 形式と Perl のような `#` 形式と両方利用可能です。

```javascript
/* Comment */
// Comment
```
```coffee
# Comment
```

好みに応じて使い分けてください。

### 変数宣言

変数宣言は `var`、または `const` で宣言します。
初期化子を使って初期化できます。
初期化子を書かなかった場合、初期値は `null` となります。

```javascript
var a = 10;
const b = 100;
var c;
System.println([a, b, c]);
```

```console
[10, 100, null]
```

`const` を使用した場合、新たなデータの代入はできなくなります（コンパイル・エラー）。

```javascript
const b = 100;
b = 10;
```

```console
Error: Can not assign a value to the 'const' variable near the <test.kx>:2
```

代入には **分割代入**、**パターンマッチ代入** という方法を使うこともできます。
宣言文や、関数の引数でも同じスタイルを使えます。

```javascript
[a, b, , ...c] = [1, 2, 3, 4, 5, 6];
{ x, y } = { x: 20, y: { a: 30, b: 300 } };
{ x: d, y: { a: e, b: 300 } } = { x: 20, y: { a: 30, b: 300 } };
System.println([a, b, c, d, e, { x, y }]);
{ x: d, y: { a: e, b: 300 } } = { x: 20, y: { a: 30, b: 3 } };  // Exception occurs.
```

```console
[1, 2, [4, 5, 6], 20, 30, {"x":20,"y":{"a":30,"b":300}}]
Uncaught exception: No one catch the exception.
NoMatchingPatternException: Pattern not matched
Stack Trace Information:
        at <main-block>(test.kx:5)
```

これらについては「\\nameref{分割代入とパターンマッチ}」で解説しています。

### 基本データ型

Kinx は動的型付け言語ですが、内部に型を持っています。
内部で保持している型は、以下のプロパティでチェック可能です。

<context label="Table:KinxBasicType"/>
<context caption="基本データ型"/>
<context limit-column="0"/>

|   プロパティ   |        例        |                         意味                          |
| -------------- | :--------------: | ----------------------------------------------------- |
| `.isUndefined` |       null       | 初期化されていない値。                                |
| `.isInteger`   |    100, 0x02     | 整数。演算では自動的に Big Integer と相互変換される。 |
| `.isDouble`    |       1.5        | 実数。                                                |
| `.isString`    | `"aaa"`, `'bbb'` | 文字列。                                              |
| `.isBinary`    |    `<1,2,3>`     | バイトの配列。要素は全て 0x00-0xFF に丸められる。     |
| `.isArray`     | `[1,a,["aaa"]]`  | 配列。扱える型は全て保持可能。`isObject` も true。    |
| `.isObject`    | `{ a: 1, b: x }` | JSON のようなキーバリュー構造。                       |
| `.isFunction`  |  `function(){}`  | 関数。                                                |

Kinx において、`null` と `undefined` は同じ意味となります。
値が `null` または `undefined` の場合、`.isUndefined` が true となります。
一方、`null`、`undefined` 以外の値の場合、`.isDefined` が true になります。

また、真偽値リテラルの `true`、`false` は単純に整数の 1、0 のエイリアスとなります。
Boolean 型はありませんが Boolean クラスは用意されており、
そのインスタンスとして真偽を表す `True`、`False` という定数が定義されています。
式の中で使用すると、`True` オブジェクトは真（true）として評価され、`False` オブジェクトは偽（false）と評価されます。
整数値とどうしても区別したい場合はそちらを使用してください。

```javascript
System.println(True ? "true" : "false");
System.println(False ? "true" : "false");
```

```console
true
false
```

データ型に関しては、「\\nameref{データ型}」で詳しく説明しています。

### 配列とオブジェクト

Kinx では内部的に配列とオブジェクトは同じであり、両方の値を同時に保持できます。
配列とオブジェクトに関しては、それぞれ「\\nameref{配列}」「\\nameref{オブジェクト}」を参照してください。

```javascript
var a = { a: 100 };
a.b = 1_000;
a["c"] = 10_000;
a[1] = 10;
System.println(a[1]);
System.println(a.a);
System.println(a.b);
System.println(a.c);
```

```console
10
100
1000
10000
```

### 式・文

#### 式（エクスプレッション）

「式（エクスプレッション）」とは、**評価され、値を持つもの** を言います。
「式」は組み合わせて使用することができ、四則演算、関数呼び出し、オブジェクト操作等が可能です。
「式」の評価が最終的に完了すると、式全体が特定の値を示します。
また、その値は変数への代入が可能です。

```javascript
// 式
z = 5 + (a * 2) + some(x)
```

「式」の詳細については「\\nameref{式と演算子}」で説明しています。

#### 文（ステートメント）

一方、「文（ステートメント）」は **手続き** を意味し、値を持ちません。
プログラムは「文」の集合であり、「文」の中で「式」が使用されます。

また、「文」には「式文」と「ブロック文」があります。
「式文」としては、宣言文、代入文、`continue`文、`break`文、`return`文、`throw`文、`yield`文が利用可能です。
「式文」の終端はセミコロン（`;`）であり、このセミコロンは常に必要となります。
「ブロック文」としては、ブロック（`{ ... }`）、`if-else`、`while`、`do-while`、`for`、`for-in`、`switch-case/when`、`try-catch-finally` が利用可能です。
なお、`if` 文は C 言語と同様にぶら下がり `else` です。

```javascript
// if 文の例
if (expression1) {
    return a;   // 式文
} else if (expression2) {
    return b;
} else {
    return c;
}
```

「文」の詳細については「\\nameref{文と制御構造}」を参照してください。

### 関数・クロージャ・ファイバー

関数の利用が可能です。
関数には通常の関数の他に、`native` 関数、クロージャ、ラムダ（匿名関数）、クラス（モジュール）・メソッドなどがあります。

#### 関数・クロージャ

関数はレキシカル・スコープを持ち、クロージャの利用も可能です。

```javascript
function func(x) {          // 通常の関数
    return &(y) => x + y;   // 匿名関数、x を束縛したクロージャを返す
}

var f = func(10);           // クロージャを受け取る
System.println(f(20));      // => 30
```

```console
30
```

通常の関数、および `native` 関数に関しては「\\nameref{関数}」を、
クロージャに関しては「\\nameref{クロージャ}」を参照してください。
また、クラス・メソッドに関しては「\\nameref{クラス}」、
モジュール・メソッドに関しては「\\nameref{モジュール}」をそれぞれ参照してください。

#### ファイバー

クラス `Fiber` のコンストラクタに関数を渡すことでファイバーも利用可能です。
ファイバーでは `yield` 文を継続のために使用しますが、この `yield` 文は通常の関数内で使用することはできません。
ファイバーで指定する関数内でだけ `yield` が使用できます。
ファイバー以外で `yield` を使用した場合は、実行時エラー（例外）が送出されます。

```javascript
var fiber = new Fiber {
    System.println("fiber 1");
    yield;
    System.println("fiber 2");
};

System.println("main 1");
fiber.resume();
System.println("main 2");
fiber.resume();
System.println("main 3");
```

```console
main 1
fiber 1
main 2
fiber 2
main 3
```

ファイバーに関しては、「\\nameref{ファイバー}」で説明しています。

### 名前空間・クラス・モジュール

名前空間の利用も可能です。
また、Kinx はオブジェクト指向言語ですので、クラスの定義が可能です。
一方、モジュールはクラス内に `mixin` することで、複数のクラスに後から共通の機能を追加できる仕組みです。

```javascript
namespace NS {
    module X {
        public sayHello() {
            System.println("hello");
        }
    }
    class A {
        mixin X;
        private trySayHello() {
            @sayHello();
        }
        public doSayHello() {
            trySayHello();
        }
    }
}
var x = new NS.A();
x.sayHello();   // => hello
```

```console
hello
```

名前空間に関しては「\\nameref{名前空間}」を参照してください。
また、クラスに関しては「\\nameref{クラス}」を、モジュールに関しては「\\nameref{モジュール}」をそれぞれ参照してください。

### ライブラリ

Kinx には便利なライブラリがオールインワンで提供されています。
これは、良く使う機能は最初から使えるようにしておくことがスクリプト言語の使い勝手を良くすると考えられるためです。
Pyhton における「Batteries Included」哲学と似ています。

オールインワンで提供されるライブラリは以下の通りです。

* **Zip** ... ZIPパスワードだけでなく、AESパスワードを使って ZIP/Unzip が可能。
* **Xml** ... XML DOM をサポート。
* **libCurl** ... HTTP のみ実装済です。（もっと色々できるはずですが）
* **SSH** ... SSH ログインしてコマンドを実行することができます。
* **Socket** ... シンプルな TCP/UDP ソケット。
* **Iconv** ... テキスト・エンコーディング変換。
* **Database** ... SQLite3 を利用する便利な Database クラス。
* **Parser Combinator** ... `Parsec` のような `Parsek` という名前のパーサコンビネータ。
* **PDF** ... HaruPDF ベースの PDF コアライブラリ。
* **JIT** ... 抽象化アセンブラ・ライブラリによる、様々なプラットフォームで使用可能な JIT ライブラリ。

標準ライブラリは「\\nameref{標準ライブラリ}」で解説しています。
かなりボリュームがありますが、参考になるでしょう。

### Kinx パッケージ・システム

Kinx にはパッケージ・システムが内蔵されています。
パッケージ・システムを使うことで標準にはないライブラリを後から追加したり、
必要なライブラリのみをインストールしたりすることができます。

パッケージシステムに関しては「\\nameref{パッケージ管理}」で詳しく解説しています。
