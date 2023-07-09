#ifndef TOPPERS_KERNEL_CFG_H
#define TOPPERS_KERNEL_CFG_H

/*
 *  各カーネルオブジェクトの最大登録数
 */
#define TNUM_TSKID	8		/* タスクの数 */
#define TNUM_SEMID	8		/* セマフォの数 */
#define TNUM_FLGID	4		/* イベントフラグ */
#define TNUM_DTQID	4		/* データキュー */
#define TNUM_PDQID	0		/* 優先度データキュー */
#define TNUM_MBXID	0		/* メールボックス */
#define TNUM_MPFID	0		/* 固定長メモリプール */
#define TNUM_CYCID	4		/* 周期ハンドラ */
#define TNUM_ALMID	4		/* アラームハンドラ */
#define TNUM_ISRID	10		/* 割込みサービスルーチン */

/*
 *  カーネルが割り付けるメモリ領域のサイズ
 */
#ifdef ARDUINO_SEEED_XIAO_M0
#define	KMM_SIZE	(1024 * 16)
#else /* ARDUINO_SEEED_XIAO_M0 */
#define	KMM_SIZE	(1024 * 6)
#endif /* ARDUINO_SEEED_XIAO_M0 */

#endif /* TOPPERS_KERNEL_CFG_H */
