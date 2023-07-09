# JTAGICEを用いたデバッグ方法について

## このドキュメントについて
TOPPERS/ASP Arduino ライブラリを用いたアプリケーションをJTAG-ICEを用い
てデバッグする方法についてまとめたものである．

## 動作確認済みデバッガ
- Segger J-Link

## デバッガの接続
ボード上のSWD端子に接続する．ONという名前のLEDがある側がGND．

## e2Studio のプロジェクトの作成

- ワークスペースを作成
- ファイル -> 新規 -> Renesas C/C++ Project -> Renesas Debug 
- プロジェクト名を入力
- Hardware に使用するデバッガを指定
    - J-Linkの場合はJ-Link ARM を選択
- Target Device に R7FA4M1AB を指定．
- Executable Path にスケッチをビルドするとログに表示されるプロジェクト名.elfを指定する．
    - Arduino IDE を起動し直すとフォルダが変更されるため注意すること．

### デバッグ
- 作成したプロジェクトに xxx.launch があるため右クリックしてデバッグを選択してデバッグを開始する．
