# Arduino UNO R4に関する情報

## デバイス
- SoC : RA4M1(R7FA4M1AB3CFM)
- Arduinoで使用しているタイマー
  - AGT
- Serial1として使用しているモジュール
  - SCI2
- 割込みの仕組み
  - 特定のベクターに割り付けられているではなく，
  - 割込みコントローラに登録することにより任意のベクタに配置可能 
  - Arduinoライブラリでは割込みを登録した順に登録する．
- 割込み本数
  - Cortex-Mの割り込み
    - 16個
  - デバイスの割込み
    - 48個

## Arduino core 付属のライブラリ(libfsp.a)について

- ソースコードは付属しておらずlibfsp.aをリンクする．
- ソースコードは以下にある
  - https://github.com/arduino/ArduinoCore-renesas

## Arduinoのライブラリ仕様
[オフィシャルドキュメント](https://arduino.github.io/arduino-cli/library-specification/)

### フォルダ
- ./src
- ./examples

### ビルド対象のコード
- src以下の全てのファイル

### インクルードルール
- library.propertiesにユーザーインクルードするファイルを指定可能．
- src内はインクルード対象．それ以外は対象ではないので相対パスで指定
  - srcより上のフォルダでも問題なさそう．

### スタティックライブラリの使い方．
[サンプル](https://wiki.seeedstudio.com/Software-Static-Library/)
- ライブラリがあってもソースはコンパイルしてくれる．
- -lはつけなくても勝手にしてくれる．
- インクルードファイルの挙動
  - ユーザー側のファイルはインクルードできない．
