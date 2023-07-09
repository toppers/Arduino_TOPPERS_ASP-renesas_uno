# 各種情報

## このドキュメントについて
TOPPERS/ASP Arduino ライブラリについて他のドキュメントに記載していない情報を記載する．

## ライブラリの再ビル

makeが使えてARM用のGCCのパスが通った環境で，以下のフォルダでmakeを実行する．

```
 ./src/cortex-m4
```

## Arduino関数の置き換え

以下の関数はArduinoのオリジナルの関数をToppersASP.cpp内で置き換えている．

- yield(void)
 - dly_tsk(0)に置き換え
- delay(unsigned long ms)
 - dly_tsk(ms)に置き換え

