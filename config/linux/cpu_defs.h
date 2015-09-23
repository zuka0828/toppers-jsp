/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  上記著作権者は，Free Software Foundation によって公表されている 
 *  GNU General Public License の Version 2 に記述されている条件か，以
 *  下の条件のいずれかを満たす場合に限り，本ソフトウェア（本ソフトウェ
 *  アを改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを再利用可能なバイナリコード（リロケータブルオブ
 *      ジェクトファイルやライブラリなど）の形で利用する場合には，利用
 *      に伴うドキュメント（利用者マニュアルなど）に，上記の著作権表示，
 *      この利用条件および下記の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを再利用不可能なバイナリコードの形または機器に組
 *      み込んだ形で利用する場合には，次のいずれかの条件を満たすこと．
 *    (a) 利用に伴うドキュメント（利用者マニュアルなど）に，上記の著作
 *        権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 利用の形態を，別に定める方法によって，上記著作権者に報告する
 *        こと．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者を免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者は，
 *  本ソフトウェアに関して，その適用可能性も含めて，いかなる保証も行わ
 *  ない．また，本ソフトウェアの利用により直接的または間接的に生じたい
 *  かなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: cpu_defs.h,v 1.7 2001/11/15 01:55:24 hiro Exp $
 */

/*
 *	プロセッサに依存する定義（68040用）
 */

#ifndef _CPU_DEFS_H_
#define _CPU_DEFS_H_

#define LINUX

#ifndef _MACRO_ONLY

#include <setjmp.h>
#include <signal.h>

typedef UINT        INHNO;		/* 割込ハンドラ番号 */
typedef	sigset_t	IMS;		/* 割込みマスク        */
typedef	UINT		EXCNO;		/* CPU例外ハンドラ番号 */

extern ER	chg_ims(IMS ims);
extern ER	get_ims(IMS *p_ims);

#endif /* _MACRO_ONLY */

/*
 *  INTNO型と割り込みの禁止/許可
 */

#ifndef _MACRO_ONLY

typedef INT	INTNO;		/* 割込み番号 */
extern  ER	dis_int(INTNO intno);
extern  ER	ena_int(INTNO intno);

#endif /* _MACRO_ONLY */

/*
 *  タイムティックの定義
 */
#define	TIC_NUME	10		/* タイムティックの周期の分子 */
#define	TIC_DENO	1		/* タイムティックの周期の分母 */

#endif /* _CPU_DEFS_H_ */


