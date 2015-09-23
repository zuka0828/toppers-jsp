/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2004 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001-2004 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2001-2004 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 *
 *  @(#) $Id: cpu_defs.h,v 1.6 2005/11/13 14:05:01 honda Exp $
 */

/*
 *      �ץ����å��˰�¸���������H8�ѡ�
 *�������������ץꥱ�������ɬ�פȤ������
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�kernel.h �� sil.h �ǥ��󥯥롼�ɤ���롥
 *  ¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ��뤳�ȤϤʤ������Υե�����򥤥�
 *  ���롼�ɤ������ˡ�t_stddef.h �� itron.h �����󥯥롼�ɤ����Τǡ�
 *  �����˰�¸���Ƥ�褤��
 */

#ifndef _CPU_DEFS_H_
#define _CPU_DEFS_H_

/*
 *  �桼�����������
 */
#include <user_config.h>        /*  SUPPORT_VXGET_TIM�ޥ��������  */

#include <h8.h>

#define H8

/* �����ͥ뵯ư���Υ�å����� */
#define COPYRIGHT_CPU \
"Copyright (C) 2001-2005 by Industrial Technology Institute,\n" \
"                            Miyagi Prefectural Government, JAPAN\n" \
"Copyright (C) 2001-2004 by Dep. of Computer Science and Engineering,\n" \
"                 Tomakomai National College of Technology, JAPAN\n"

/*
 *  CPU �ΥХ��Ƚ�˴ؤ������
 */

#define SIL_ENDIAN              SIL_ENDIAN_BIG

#ifndef _MACRO_ONLY

typedef UINT    INHNO;                  /* ����ߥϥ�ɥ��ֹ� */
typedef UINT    EXCNO;                  /* CPU�㳰�ϥ�ɥ��ֹ� */

/*
 *  �������åȥ����ƥ��¸�Υ����ӥ�������
 */

/*
 *  ����ߥޥ����η��ȳ���ߥޥ������ѹ�������
 */
typedef UB              IPM;            /* ����ߥޥ��� */

#endif /* _MACRO_ONLY */
/*
 *  ��٥룰�����٤Ƥγ���ߤ�����դ���
 */
#define IPM_LEVEL0      0u

/*
 *  ��٥룱��NMI����ӥץ饤����ƥ���٥룱�γ���ߤΤߤ�����դ���
 */
#define IPM_LEVEL1      CCR_I

/*
 *  ��٥룲��NMI�ʳ��γ���ߤ�����դ��ʤ�
 */
#define IPM_LEVEL2      (CCR_I | CCR_UI)

#ifndef _MACRO_ONLY

#ifdef SUPPORT_CHG_IPM
extern ER       chg_ipm(IPM ipm) throw();
extern ER       get_ipm(IPM *p_ipm) throw();
#endif  /*  SUPPORT_CHG_IPM  */


/*
 *  �ץ饤����ƥ���٥������ѤΥǡ�����¤
 */
typedef struct {
        UB *ipr;        /* ���ꤹ��IPR�쥸���������� */
        UB bit;         /* IPR�쥸�����γ�������ӥå��ֹ� */
        IPM ipm;        /* ���ꤹ�����ߥ�٥� */
                        /* IPM_LEVEL0,IPM_LEVEL1�Τ����줫 */
} IRC;                  /* IRC:Interrupt Request Controller */


/*
 *  ��ǽɾ���ѥ����ƥ�����¬��ǽ
 */
#ifdef SUPPORT_VXGET_TIM

typedef UW  SYSUTIM;    /* ��ǽɾ���ѥ����ƥ���� */

extern ER   vxget_tim(SYSUTIM *pk_sysutim) throw();

#endif  /*  SUPPORT_VXGET_TIM  */

/*
 *  �����ƥ�����ǽ���
 */
Inline void kernel_abort(void);

Inline void
kernel_abort(void)
{
        while (1) {}
}

/*
 * ���������Ԥ�
 * �������ջ��ࡧ
 * ������ɸ��Ǥ�dlytim��UINT������16�ӥåȤ����ʤ��Τǡ�
 * ������UW�����ѹ����Ƥ��롣
 * ������sil_dly_nse()��������sil_dly_nse_long()��ƤӽФ���
 */
extern void sil_dly_nse_long(UW dlytim) throw();

#endif /* _MACRO_ONLY */

#endif /* _CPU_DEFS_H_ */