# RotaryEncoder library
このライブラリはArduino Unoなどでロータリーエンコーダを簡単に使用できるようにするためのライブラリです．

動作確認は秋月電子の[EC12PLRGBSDVBF-D-25K-24-24C-61](http://akizukidenshi.com/catalog/g/gP-05773/)で行いました．

サンプルプログラムは [こちら](https://github.com/SeeLog/RotaryEncoder/blob/master/src/main.cpp)

[English](https://github.com/SeeLog/RotaryEncoder/blob/master/README.md)

## チュートリアル

![image](https://i.imgur.com/3KIpfHg.png)

### 1. プロジェクトのディレクトリに以下のファイルをコピーします
- RotaryEncoder.h
- RotaryEncoder.cpp

### 2. ライブラリをincludeします
```cpp
#include "RotaryEncoder.h"
```

### 3. セットアップを行います
  
  1. 使用するピン番号をdefineします
  ```cpp
  #define PIN_A 2
  #define PIN_B 3
  ```
  2. RotaryEncoderを定義し，初期化します
  ```cpp
  RotaryEncoder encoder = RotaryEncoder(PIN_A, PIN_B);
  ```
  
### 4. 値を取得します
```cpp
int val = encoder.getRotationValue();
```

## その他
- 値の最大値と最小値を設定

```cpp
encoder.setMaxValue(255);
encoder.setMinValue(0);
```

- 1度にどれだけ値を増減させるかを設定

```cpp
encoder.skipValue = 4;
```

例えばこのように設定すると，値は `0,4,8, ...` と増え， `0,-4,-8,...` と減少します．

- 値のローテーション

```cpp
encoder.isRotateValue = true;
```

例えば最大値が10，最小値が0のとき
`...,9,10,0,1,...`と増加し，`...,1,0,10,9,...`と減少するようになります．
