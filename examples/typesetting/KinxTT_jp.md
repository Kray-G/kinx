# Kinx Tiny Typesetting

<param style="JBookA4"/>
<param titleSize="42.8"/>
<param subtitleSize="14.4"/>
<param subtitle="Small and Easy, but Beautiful Design For You"/>
<param author="Kray-G, Mr.Diamond Global Blue Publisher"/>
<param date="September 18, 2020"/>

## イントロダクション

### KinxTT とは

Kinx Tiny Typesetting（以下、KinxTT）は、
Kinx で実装された簡易組版システムです。
Markdown 形式からの簡易トランスレーターを実装しているため、
Markdown 形式で書かれたドキュメントを美しく組版することができます。
本文書自体も Markdown で記載されているものを自動組版した一つの事例です。

考え方は \\LaTeX に近く、
テキスト形式で管理している文書ファイルを美しく組版することを目的としています。
より具体的には、本システムは \\LaTeX を置き換えることを目的とはしていませんが、
以下を実現することによって、
より個人的な利用シーンの中で、より簡単に利用できるようにすることを目的としています。

*   小さなシステムを維持すること
*   それなりに美しく組版できること
*   直接 PDF ファイルを出力できること

KinxTT は小さなシステムながらある程度美しく組版できる機能を持ち、
Markdown で書かれた文書から直接 PDF ファイルとして出力することができる組版システムです。

#### Versus \\LaTeX

\\LaTeX は巨大なシステムです。
拡張性にも優れ、多くの人々に支えられた美しい文書を作成するための組版システムです。
KinxTT も \\LaTeX と同じ目的を持つ組版システムですが、
限られた機能しか提供しない代わりに小さなシステムとして提供されます。

\\LaTeX の巨大さは、インストールの複雑さにもつながります。
\\TeX、\\LaTeX では様々な機能を提供するためにディストリビューションそのものが複数存在しています。
それにより、ユーザーはまずどのディストリビューションを使うべきかで悩むことになります。
KinxTT は、Kinx パッケージに標準で組み込まれており、
Kinx をインストールすることですぐに使えるようになります。
もっと具体的に言えば、一般的な利用シーンとして Kinx をインストールするだけで Markdown 文書から PDF ファイルをすぐに作成できるようになります。

ただし、小さく、そして簡単に使える代わりにトレードオフとして限られた機能しか提供されないといった欠点があります。
尚、「限られた機能」に関しては、「\\nameref{機能概要}」を参照してください。

まとめると、以下のような利点、欠点が存在します。

*   **利点**
    *   小さなシステム
    *   インストールが簡単
*   **欠点**
    *   限られた機能のみ提供

#### Versus Word

WYSIWYG\\footnote{**W**hat **Y**ou **S**ee **I**s **W**hat **Y**ou **G**et の頭文字をとったもの。見たままのものを実際に作成出力するという意味。}
のワードプロセッサとして代表的な Word ですが、考え方が異なります。
WYSIWYG では見たままの形式で編集可能ですが、
その見た目情報を一緒に保存するために多くの場合バイナリ形式で保存されます。
そのため、中に何が書かれているか知るには一般的に専用のソフトウェア（この場合 Word）が必要となります。

KinxTT は \\LaTeX 同様、テキストエディタさえあれば内容を知ることができ、編集することも可能です。

テキストで保存されるということは、別のソフトウェアで処理することも簡単であり、
Git のようなバージョン管理システム上で差分を確認することも容易です。
このことは特に、差分管理をバージョン管理システム上で実現したい場合には必須となる特徴です。

また、文書構造に関しても Word ではメタ情報として記録されており、
直接的にその見た目から「それが構造化されたもの」か「単に見た目としてそう見えているものか」の区別がつきません。
例えば、章番号がきちんと章番号として設定され、
文章の配置やレイアウトを変更した際に正しく番号を付け直してくれるよう配慮されているかどうかが判別しづらいといった欠点もあります。
特に、どのような書き方をしたとしても「見た目として正しく見えてしまっている」という事実により、
知見のない作成者が意図せず正しく設定してくれていなかった、といった不運もたびたび見られます。

KinxTT では、文書構造をテキストで表現する関係上、
章やセクション、図、表などのリファレンスを常に正しく把握し、
適切な番号付け、および相互参照機能を実現することができます。

その代わり、WYSIWYG のようにその場で出力後の体裁（見た目）を確認することができない、
といった欠点があります。

まとめると、以下のような利点、欠点が存在します。

*   **利点**
    *   バージョン管理システムでの差分管理が容易
    *   文書構造を常に適切に把握し、相互参照などを正確に実施
*   **欠点**
    *   その場で実際の見た目をすぐに確認できない

#### 結論

要約すると、以下のケースにおいて KinxTT の利用が有益となります。

*   \\TeX のような巨大なシステムではなく、小さな組版システムで簡単に利用したい
*   Git のようなバージョン管理システムを付かった差分管理をしたい
*   文書構造を常に適切に把握し、相互参照などを正確に実施したい

ちょっとした文書作成のために \\TeX をフルセットで使うには巨大すぎる、と感じている方で、
テキストで文書管理をしたい、と考えている方\\footnote{つまり、私のような方。}のために本システムを用意しました。
特に、Git で差分を含めた文書管理を行いたい場合、
WYSIWYG で実現されているワープロソフトでの管理は大変困難ですので、
主にそういった利用シーンを想定しています。

### サポート機能

KinxTT は、以下の機能をサポートしています。

*   基本機能
    *   ハイフネーション・ジャスティフィケーション・行分割
    *   ウィドウ／オーファン
    *   箇条書き
    *   数式
    *   イメージ
    *   テーブル
    *   色
    *   プログラム・コード
    *   相互参照
    *   外部リンク
    *   脚注
    *   合字
*   日本語用処理
    *   日本語禁則処理
    *   日本語ルビ

基本機能に加え、日本語特有の処理が組み込まれています。
日本語の言語への拡張は私自身に知見が乏しいためシステムのソースコードに影響する可能性がありますが、
ソースコードは公開されているので必要に応じて拡張することは可能と考えています。
ただし、言語ごとの固有の拡張ポイントを意識していないので、
大幅な修正、もしくは機能追加が必要かもしれません。

## さあ始めよう

### インストール

インストールは以下の 2 ステップを実施します。

1. Kinx のインストール
2. KinxTT 追加モジュールのインストール

### ビルド

通常、ビルドから実施する必要はありません。
既にインストーラが提供されており、手順に従ってインストールを実施することで本システムを利用することができます。
あえてビルドから実行したい、といった場合は以下の手順によってビルドを実施できます。

### hello, world

次の文書を作成し、`helloworld.md` ファイルとして保存します。

```markdown:lineNumber=false
hello, world
```

## 機能概要

### 基本機能

#### ハイフネーション・ジャスティフィケーション・行分割

![float=right,scale=0.6,caption=ハイフネーションとジャスティフィケーション](examples/typesetting/linebreak.png)

Franklin M. Liang のアルゴリズムに基づくハイフネーションをサポートしています。
また、ハイフネーションに伴うジャスティフィケーション（両端揃え）機能をサポートしています。

行分割は Knuth-Plass Line Breaking アルゴリズムを採用しています。
本アルゴリズムは、Box、Glue、Penalty によって分割位置をコントロールするアルゴリズムであり、
\\TeX で実装されているアルゴリズムと同様です。
これらハイフネーション・アルゴリズムも行分割アルゴリズムは、
今のところ組版システムでは最良の方法として知られている方法です。
ただし、実装自体は Kinx で改めて行われているため、
必ずしも出力結果は \\TeX での出力と同一にはならない場合があります。

#### ウィドウ／オーファン

ウィドウ、およびオーファンに対するペナルティ処理を一部ですが実施します。
全てのケースで有効ではありませんのでご注意ください。
具体的には以下のケースで有効です。

*   セクション名がページの最後に取り残されるケースを抑止。
    *   この場合、セクション名ごと次のページに送り出されます。
*   複数行パラグラフにおいて、最後の行のみ次のページに送られるケースを抑止。
    *   この場合、最後の 2 行分が次のページに送り出されます。

#### 箇条書き

箇条書きは記号によるものと番号付きのものが利用できます。
次の例は記号による箇条書きの例です。

```
*   レベル1
    *  レベル2
        *   レベル3
    *  レベル2
        *   レベル3
            *  レベル4
            *  レベル4
```

これは以下のように整形されます。

*   レベル1
    *  レベル2
    *  レベル2
        *   レベル3
    *  レベル2
        *   レベル3
            *  レベル4
            *  レベル4

また、両者を混在させることも可能です。
次の例は混在させた場合の箇条書きの例です。

```
*   レベル1
    1.  レベル2
    2.  レベル2
        *   レベル3
    3.  レベル2
        *   レベル3
            1.  レベル4
            2.  レベル4
```

これは以下のように整形されます。

*   レベル1
    1.  レベル2
    2.  レベル2
        *   レベル3
    3.  レベル2
        *   レベル3
            1.  レベル4
            2.  レベル4

#### 数式

#### イメージ

#### テーブル

#### 色

#### プログラム・コード

#### 相互参照

#### 外部リンク

#### 脚注

#### 合字

### 日本語用機能

#### 日本語禁則処理

#### 日本語ルビ

## コマンド

### パラグラフ処理コマンド

### スタンドアロン・コマンド

## 機能拡張

### スタイル

### 禁則処理
