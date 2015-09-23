/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001,2002 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *
 *  �嵭����Ԥϡ�Free Software Foundation �ˤ�äƸ�ɽ����Ƥ���
 *  GNU General Public License �� Version 2 �˵��Ҥ���Ƥ����狼����
 *  ����(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ���
 *  ������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ�����������Ѳ�ǽ�ʥХ��ʥꥳ���ɡʥ���������֥륪��
 *      �������ȥե������饤�֥��ʤɡˤη������Ѥ�����ˤϡ�����
 *      ��ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ����
 *      �������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ�������������Բ�ǽ�ʥХ��ʥꥳ���ɤη��ޤ��ϵ������
 *      �߹�����������Ѥ�����ˤϡ����Τ����줫�ξ������������ȡ�
 *    (a) ���Ѥ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
 *        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) ���Ѥη��֤��̤�������ˡ�ˤ�äơ��嵭����Ԥ���𤹤�
 *        ���ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥϡ�
 *  �ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����ޤ�ơ������ʤ��ݾڤ�Ԥ�
 *  �ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū����������
 *  ���ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 *
 *  @(#) $Id: cpu_defs.h,v 1.5 2002/04/11 11:30:20 imai Exp $
 */

#ifndef _CPU_DEFS_H_
#define _CPU_DEFS_H_

/*
 *  �ץ����å��˰�¸���������SH1�ѡ�
 */
#define SH1

/* �����ͥ뵯ư���Υ�å�����   */
#define COPYRIGHT_CPU \
"Copyright (C) 2001 by Industrial Technology Institute,\n" \
"                            Miyagi Prefectural Government, JAPAN\n"


#ifndef _MACRO_ONLY

typedef	UINT	INHNO;			/* ����ߥϥ�ɥ��ֹ� */
typedef	UINT	EXCNO;			/* CPU�㳰�ϥ�ɥ��ֹ� */

typedef	UINT	IPM;			/* ����ߥޥ��� */
extern ER	chg_ipm(IPM ipm);	/* ����ߥޥ������ѹ� */
extern ER	get_ipm(IPM *p_ipm);	/* ����ߥޥ����μ��� */

/*
 *  INTNO���ȳ���ߤζػ�/����
 */

typedef	UINT	INTNO;			/* ������ֹ� */

#if 0		/*  SH1�ǤǤϥ��ݡ��Ȥ��Ƥ��ʤ�  */
extern ER	dis_int(INTNO intno);
extern ER	ena_int(INTNO intno);
#endif

/*
 *  �������åȥ����ƥ��¸�Υ����ӥ�������
 */

   /*
    * cpu_defs.h��sys_defs.h�򥤥󥯥롼�ɤ�����֤�
    * �ط���SUPPORT_VXGET_TIM�ޥ����ǤϰϤޤʤ�
    * ��_MACRO_ONLY�ޥ����ǰϤ�С���ʬ��
   */

typedef	UD  SYSUTIM;	/* ��ǽɾ���ѥ����ƥ���� */

extern ER   vxget_tim(SYSUTIM *pk_sysutim);

#endif /* _MACRO_ONLY */
#endif /* _CPU_DEFS_H_ */