# TOPPERS/ASP Arduino UNO R4 ライブラリ（TA2LIB）

## 本ライブラリについて

本ライブラリは，[TOPPERS/ASPカーネル](https://www.toppers.jp/asp-kernel.html)（以下，ASPカーネル）を Arduino UNO R4 で動作させる Arduino IDE 用のライブラリである．

## 特徴

- Arduino 環境でマルチタスクプログラミングが可能．
- Arduino IDEでビルド可能
- Arduino の各種ライブラリと併用可能．

## オリジナルのASPカーネルとの違い

- 静的APIをサポートしていない
	- オブジェクトは初期化関数で実行時に生成する．
	-  [asp_wo_cfg](https://dev.toppers.jp/trac_user/contrib/browser/asp_wo_cfg/)をベースとしている．
- syslog()は未サポート．


## 動作確認バージョン

- Arduino IDE : 2.2.1
- Ardino UNO R4 Boards : 1.0.5

## 動作確認ハードウエア
- [Arduinno UNO R4 MINIMA](https://store.arduino.cc/products/uno-r4-minima)
- [Arduinno UNO R4 WIFI](https://store.arduino.cc/products/uno-r4-wifi)

## 使用方法

### Arduino UNO R4 用の環境の準備

[このページ](https://docs.arduino.cc/tutorials/uno-r4-minima/minima-getting-started)を参考に Arduino UNO R4用の環境を用意する．

### ライブラリのインストール

#### ZIPファイルによるインストール

GitHubからリリースファイルをダウンロードして，ArduinoIDEの

```
 スケッチ -> ライブラリをインクルード -> .ZIP形式のライブラリをインストール
```

を選択してリリースパッケージをインストールする．

Arduino IDE を再起動する．


#### gitによるインストール

Arduino ライブラリフォルダへcloneして，Arduino IDE を再起動する．

### サンプル
Arduinno UNO R4 MINIMA と Arduinno UNO R4 WIFI でサンプルが異なる．

- Arduinno UNO R4 MINIMA 用
	- ToppersASP_Blink
		- タスクを2個作成
			- task1/task2 : 1秒毎にログを出力
		- メインループ（タスク）
			- LEDを1秒間隔でON/OFF

	- ToppersASP_Button
		- タスクを2個作成
			- task1 : 1秒毎にログを出力
			- task2 : Pin2に接続したボタンを押すと起床されてログを出力
		- メインループ（タスク）
			- LEDを1秒間隔でON/OFF

- Arduinno UNO R4 WIFI 用
	- ToppersASP_LEDMatrix
		- タスクを2個作成
			- task1/task2 : 1秒毎にログを出力
		- メインループ（タスク）
			- LED Matrixに文字列を表示する

	- ToppersASP_WebServer
		- タスクを2個作成
			- task1 : 1秒毎にログを出力
			- task2 : Pin2に接続したボタンを押すと起床されてログを出力
		- メインループ（タスク）
			- Webサーバーを動作させる


### サンプルのビルド
- ToppersASP_Blink を例に説明する．
- サンプルのプロジェクトを選択する．

```
 ファイル -> スケッチの例 -> ToppersASP-renesas_uno -> ToppersASP_Blink 
```

- Arduino UNO R4のUSB端子とPCを接続する．

- マイコンボードに書き込むを選択して書き込む．

- ターミナルエミュレータを接続
	- USB端子によるCOMポートに接続．

- 実行
	- USB端子によるCOMポート にターミナルエミュレータを接続すると実行が開始される．


## 使用方法

### 初期化(setup())

setup()では，以下の内容を記載する．

- Serialの初期化(オプシション)
	- MINIMAの場合
		- SerialUSBを使用する．
		- 必ず以下の順序で記載する．
	- WIFIの場合
		- Serialを使用する．
- その他の初期化(オプション)
	- ポートの初期化等を記載する．
- カーネルの起動
	- StartToppersASP()を呼び出すことでカーネルが起動する．

```
void setup() {
  //MINIMAの場合	
  SerialUSB.begin(115200);
  while (!SerialUSB);

  //その他の初期化(オプション)

  //カーネルの起動
  StartToppersASP();
}
```

### カーネルオブジェクトの初期化(user_inirtn())
カーネル起動後に呼び出される．カーネルオブジェクトの初期化処理を記載する．
これらのサービスコールは，この関数内で飲み呼び出し可能．

```
	ER	cre_tsk(ID tskid, const T_CTSK *pk_ctsk);
	ER	cre_sem(ID semid, const T_CSEM *pk_csem);
	ER	cre_flg(ID flgid, const T_CFLG *pk_cflg);
	ER	cre_dtq(ID dtqid, const T_CDTQ *pk_cdtq);
	ER	cre_pdq(ID pdqid, const T_CPDQ *pk_cpdq);
	ER	cre_mbx(ID mbxid, const T_CMBX *pk_cmbx);
	ER	cre_mpf(ID mpfid, const T_CMPF *pk_cmpf);
	ER	cre_cyc(ID cycid, const T_CCYC *pk_ccyc);
	ER	cre_alm(ID almid, const T_CALM *pk_calm);
	ER	cfg_int(INTNO intno, const T_CINT *pk_cint);
	ER	att_isr(const T_CISR *pk_cisr);
	ER	def_inh(INHNO inhno, const T_DINH *pk_dinh);
	ER	def_exc(EXCNO excno, const T_DEXC *pk_dexc);
```

各オブジェクトのIDは次の値を使用する．nは1～10を指定可能．10個以上のオブジェクトを使用したい場合は，[customize.md](doc/customize.md) を参考のこと．

| オブジェクト | マクロ |
----|---- 
|  タスク              | TASKn | 
|  セマフォ            | SEMn  | 
|  イベントフラグ      | FLGn  | 
|  データキュー        | DTQn  | 
|  優先度データキュー  | PDQn  | 
|  メールボックス      | MBXn  | 
|  メッセージバッファ  | MBFn  | 
|  周期ハンドラ        | CYCHDRn  | 
|  アラームハンドラ    | ALMHDRn  | 

#### タスク生成の例
タスクを生成する例は次のようになる．

```
void
user_inirtn() {

  T_CTSK  ctsk;
  ER    ercd;

  ctsk.tskatr = TA_ACT;
  ctsk.exinf = 1;
  ctsk.task = task1;
  ctsk.itskpri = 10;
  ctsk.stksz = 1024;
  ctsk.stk = NULL;
  ercd = cre_tsk(TASK1, &ctsk);

  ....
}
```

タスク本体の記述は通常のASPカーネルと同じである．タスク本体では，ASPカーネルのAPIとArduinoの両方を呼び出し可能である．

```
void
task1(intptr_t exinf)
{
  int count = 0;
  while(1){    
	SerialUSB.print("task1 is running. ");
    SerialUSB.println(count++);
    delay(1000);
  }
}
```

### loop()

loop()関数はASPカーネルの最低優先度のタスクとして実行される．タスクIDは，IDLE_TASK である．

### カーネルの終了処理(user_terrtn()) オプション

カーネル終了時に呼ばれる関数．必要なら定義して終了処理等を記載する．

## 使用しているリソース

本ライブラリは以下のリソースを使用する．

- ROM/RAM
	- コードとデータを配置する．
	- 使用量はオブジェクト数に依存する．
  
- SysTick
	- カーネル内部のティックの生成に用いる．

## デバッグ
MINIMAはJTAG-ICEによるデバッグが可能である．詳細は[debug.md](doc/debug.md) を参考のこと．

## Tips
- Arduino IDEから書き込めない場合
	- リセットスイッチを押した後にIDEにより書き込みすることで解決する場合がある．

## フォルダ構成

- src 
	- ライブラリ本体
- examples
	- サンプル．
- asp_wo_cfg
	- ASPカーネル本体
- doc
	- 各種ドキュメント．

以上．
