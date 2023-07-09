# TOPPERS/ASP Arduino UNO R4 ライブラリ（TA2LIB）

## 本ライブラリについて

本ライブラリは，[TOPPERS/ASPカーネル](https://www.toppers.jp/asp-kernel.html)（以下，ASPカーネル）を Arduino UNO R4 で動作させる Arduino IDE 用のライブラリである．

## 特徴

- Arduino 環境でマルチタスクプログラミングが可能．
- Arduino IDEでビルド可能
- Arduino の各種ライブラリを使用可能．

## オリジナルのASPカーネルとの違い

- 静的APIをサポートしていない
 - オブジェクトは初期化関数で実行時に生成する．
  -  [asp_wo_cfg](https://dev.toppers.jp/trac_user/contrib/browser/asp_wo_cfg/)をベースとしている．

- syslog()は未サポート．

## R2CAとの違い

- [R2CA](https://dev.toppers.jp/trac_user/contrib/wiki/rtos_arduino)は，ArduinoライブラリをASPカーネルでビルドすることを目的としている．
  一方，本ライブラリは Arduino IDE でASPカーネルの機能を使用することを目的としています．

## 動作確認バージョン

- Arduino IDE : 2.1.1
	- プリコンパイル済のライブラリを使用するため，1.8.6以上が必要．
- Ardino UNO R4 Boards : 1.0.1


## 使用方法

### Arduino UNO R4 用の環境の準備

[このページ](https://docs.arduino.cc/tutorials/uno-r4-minima/minima-getting-started)を参考に Arduino UNO R4用の環境を用意する．

### ライブラリのダウンロードとインストール

GitHubからZipファイルをダウンロードして，ファイル名の最後の-master を削除して，ArduinoIDEの

```
 スケッチ -> ライブラリをインクルード -> .ZIP形式のライブラリをインストール
```

を選択してリリースパッケージをインストールする．

Arduino IDE を再起動する．

もしくは，Arduino ライブラリフォルダへcloneする．

### サンプルのビルド

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

- SerialUSBの初期化
	- 必ず以下の順序で記載する．
- その他の初期化(オプション)
	- ポートの初期化等を記載する．
- カーネルの起動
	- StartToppersASP()を呼び出すことでカーネルが起動する．

```
void setup() {
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

各オブジェクトのIDは次の値を使用する．nは1～10を指定可能．10個以上のオブジェクトを使用したい場合は，./doc/customize.txt を参考のこと．

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

## Tips

Arduino IDEから書き込めない場合は，Wio Terminalの電源スイッチを下に素早く2回スライドすることによりブートローダが起動して書き込み可能となる．

## フォルダ構成

- src 
	- ライブラリ本体
- examples
	- サンプル．
- asp_wo_cfg
	- ASPカーネル本体
- doc
	- 各種ドキュメント．
