/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *
 *  上記著作権者は，以下の条件を満たす場合に限り，本ソフトウェア（本ソ
 *  フトウェアを改変したものを含む．以下同じ）を使用・複製・改変・再配
 *  布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアをバイナリコードの形または機器に組み込んだ形で利
 *      用する場合には，次のいずれかの条件を満たすこと．
 *    (a) 利用に伴うドキュメント（利用者マニュアルなど）に，上記の著作
 *        権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 利用の形態を，別に定める方法によって，上記著作権者に報告する
 *        こと．
 *  (3) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者を免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者は，
 *  本ソフトウェアに関して，その適用可能性も含めて，いかなる保証も行わ
 *  ない．また，本ソフトウェアの利用により直接的または間接的に生じたい
 *  かなる損害に関しても，その責任を負わない．
 *
 *  @(#) $Id: cpu_insn.h,v 1.1 2001/05/04 09:07:50 imai Exp $
 */

#ifndef	_CPU_INSN_H_
#define	_CPU_INSN_H_

/*
 *  制御レジスタの操作関数
 */

/*
 *  ステータスレジスタ（SR）の現在値の読出し
 */
Inline UW
current_sr(void)
{
	UW sr;
	Asm("stc  sr,%0" : "=r"(sr));
	return(sr);
}


/*
 *  ステータスレジスタ（SR）の現在値の変更
 */
Inline void
set_sr(UW sr)
{
	Asm("ldc %0, sr" : : "r"(sr) );
}


/*
 *  NMIとデバッガを除くすべての割込みを禁止
 */
Inline void
disint(void)
{
    set_sr((current_sr() & ~0x000000f0) |  MAX_IPM << 4 );
}


/*
 *  すべての割込みを許可
 */
Inline void
enaint()
{
	set_sr(current_sr() & ~0x000000f0);
}

/*
 *  ベクタベースレジスタ（VBR）の現在値の読出し
 */
Inline VP
*current_vbr(void)
{
	VP vbr;
	Asm("stc vbr,%0" : "=r"(vbr));
	return(vbr);
}


/*
 *  ベクタベースレジスタ（VBR）の設定
 */
Inline void
set_vbr(VP vbr)
{
	Asm("ldc  %0, vbr" : : "r"(vbr) );
}


#endif /* _CPU_INSN_H_ */
