
# 名前空間・クラス・モジュール
## 名前空間

### 名前空間オブジェクト

キーワード `namespace` を使用して、名前空間を使用可能です。

名前空間は **オブジェクト** であり、
名前空間内で宣言されたクラス、モジュールは名前空間オブジェクトに設定されます。
ただし、定数等は名前空間オブジェクトには自動的に設定されないため、自分で設定する必要があります。

```javascript
namespace N {
    class A {
        ...
    }

    const X = 10;
    N.X = 100;

    var a = new A(); // OK
    ...
}

// var a = new A(); // エラー
var a = new N.A(); // OK

// System.println(X); // エラー
System.println(N.X); // OK
```

名前空間はネストできます。

```javascript
namespace A {
namespace B {

    class X { ... }

} // namespace B

    var x = new B.X(); // OK

} // namespace A

var x = new A.B.X(); // OK
```

## クラス
### クラスとは
### クラスの定義
### サブクラスと継承
## モジュール
### モジュールとは
### モジュールの定義
### ミックスイン
