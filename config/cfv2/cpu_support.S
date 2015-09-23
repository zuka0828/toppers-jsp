/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2007 by KURUSUGAWA Electronics Industry Inc, JAPAN
 *  Copyright (C) 2008 by Takahisa Yokota
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
 *  @(#) $Id: cpu_support.S,v 1.16 2005/11/12 14:58:46 hiro Exp $
 */

/*
 *	�ץ����å���¸�⥸�塼�� ������֥��������MCF52235�ѡ�
 */

#define	_MACRO_ONLY
#include "jsp_kernel.h"
#include "offset.h"

/*
 *  �������ǥ����ѥå���
 *
 *  dispatch �ϡ��ޥ����⡼�ɡ�����߶ػ߾��֤ǸƤӽФ��ʤ���Фʤ��
 *  ����exit_and_dispatch �⡤�ޥ����⡼�ɡ�����߶ػ߾��֤ǸƤӽФ���
 *  ����§�Ǥ��뤬�������ͥ뵯ư�����б����뤿�ᡤ����ߥ⡼�ɤǸƤӽ�
 *  �������ˤ��б����Ƥ��롥
 */
	.text
	.globl dispatch
	.globl exit_and_dispatch
dispatch:
	lea  -44(%sp), %sp
	movem.l %d2-%d7/%a2-%a6, (%sp)	/* �쥸��������¸ */
	move.l runtsk, %a0		/* A0 �� runtsk �� */
	move.l %sp, TCB_msp(%a0)	/* �����������å�����¸ */
	move.l #dispatch_r, %d2
	move.l %d2, TCB_pc(%a0)	/* �¹ԺƳ����Ϥ���¸ */
	jbra dispatcher

dispatch_r:
	movem.l (%sp), %d2-%d7/%a2-%a6	/* �쥸���������� */
	lea 44(%sp), %sp
	btst.b #TCB_enatex_bit, TCB_enatex(%a0)
	jbeq dispatch_r_1		/* enatex �� FALSE �ʤ�꥿���� */
	tst.l TCB_texptn(%a0)		/* texptn �� 0 �Ǥʤ����           */
	jbne call_texrtn		/*   �������㳰�����롼����θƽФ� */
dispatch_r_1:
	rts

exit_and_dispatch:
	clr.l	intnest

dispatcher:
	/*
	 *  �����Ǥϥޥ����⡼�ɡ�����߶ػ߾��֤Ǥʤ���Фʤ�ʤ���
	 */
	move.l schedtsk, %a0
	move.l %a0, runtsk		/* schedtsk �� runtsk �� */
	jbeq   dispatcher_1		/* runtsk �����뤫�� */
	move.l TCB_msp(%a0), %sp	/* �����������å������� */
	move.l TCB_pc(%a0),  %a1	/* �¹ԺƳ����Ϥ����� */
	jmp (%a1)
dispatcher_1:
	addq.l  #1, intnest
	move.l  #STACKTOP, %sp
	stop #0x2000			/* ������Ԥ��ʳ���ߥ⡼�ɡ� */
	/*
	 *  �����ǳ���ߥ⡼�ɤ��ڤ괹����Τϡ�����ߥϥ�ɥ����
	 *  �Υ������ǥ����ѥå����ɻߤȤ���2�Ĥΰ�̣�����롥
	 *
	 *  ���� stop̿��ϡ�IPM �� 0 �ˤ��뤬������� task_intmask ��
	 *  ���ꤹ�٤��Ǥ��롥M68040 �Ǥϡ�stop ̿��Υѥ�᡼�������
	 *  �����Ȥ�ʤ����ᡤ���򤨤� 0 �ˤ��Ƥ����stop ̿��� 8��
	 *  �¤٤ơ�task_intmask ���ͤ�����ʬ�����Ϥ��뤬�������ޤ�
	 *  ���յ��Ϥʤ��ȹͤ����ˡ�
	 *
	 *  �ץ����å����Ԥ��⡼�ɤ˰ܹԤ���������ȡ�����ߵ��ĤȤϡ�
	 *  �Բ�ʬ�˹Ԥʤ�ɬ�פ������M68040 �Ǥ� stop̿���ξ���Ԥʤ�
	 *  �Τ�����ʤ��ˡ�������Բ�ʬ�˹Ԥʤ�ʤ���硤����ߤ����
	 *  ����ľ��˳���ߤ����ꡤ������ǥ��������¹Բ�ǽ���֤ˤʤ�
	 *  �ȡ��¹Ԥ��٤�������������ˤ⤫����餺�ץ����å����Ԥ��⡼
	 *  �ɤˤʤäƤ��ޤ���
	 *
	 *  ����ߤ��ԤĴ֤ϡ�runtsk �� NULL��=0�ˤ����ꤷ�ʤ���Фʤ�
	 *  �ʤ������Τ褦�����ꤷ�ʤ��ȡ�����ߥϥ�ɥ餫�� iget_tid 
	 *  ��ƤӽФ����ݤ�ư����ͤ˹��פ��ʤ��ʤ롥
	 */
	move.w #0x2700, %sr		/* ����߶ػ� */
	clr.l intnest
	tst.l reqflg			/* reqflg �� FALSE �ʤ� */
	jbeq dispatcher_1		/*      dispatcher_1 �� */
	clr.l reqflg			/* reqflg �� FALSE �� */
	jbra dispatcher

/*
 *  no_reg_exception()
 *  CPU�㳰�Ȥ�����Ͽ����Ƥ��ʤ��㳰��ȯ������ȸƤӽФ����
 *  �㳰��ȯ������������pc,sr,pr,r0��15����Ϥ��ƥ����ͥ�
 *  ����ߤ��롣
 */
	.text
	.align 2
	.globl no_reg_exception
no_reg_exception:
	move.l  %a7, %sp@-
	move.l  %a6, %sp@-
	move.l  %a5, %sp@-
	move.l  %a4, %sp@-
	move.l  %a3, %sp@-
	move.l  %a2, %sp@-
	move.l  %a1, %sp@-
	move.l  %a0, %sp@-
	move.l  %d7, %sp@-
	move.l  %d6, %sp@-
	move.l  %d5, %sp@-
	move.l  %d4, %sp@-
	move.l  %d3, %sp@-
	move.l  %d2, %sp@-
	move.l  %d1, %sp@-
	move.l  %d0, %sp@-
	move.l %sp, %sp@-
	jbsr  cpu_experr

/*
 *  ��������ư������
 */
	.text
	.globl activate_r
activate_r:
	/*
	 *  ��������ưľ��ϥ������㳰�������ػߤ���Ƥ��뤿�ᡤ�����ǥ�
	 *  �����㳰�����롼�����ƤӽФ���������Ω���ʤ���
	 */
#ifdef SUPPORT_CHG_IPM			/* t_unlock_cpu �����ν��� */
	move.w %sr, %d0			/* ����ߥޥ����� task_intmask �� */
	and.l  #~0x00000700, %d0
	clr.l	%d1
	move.w task_intmask, %d1
	or.l   %d1, %d0
	move.w %d0, %sr
#else /* SUPPORT_CHG_IPM */
	move.w %sr, %d0			
	and.l #~0x00000700, %d0		/* ����ߵ��� */
	move.w %d0, %sr
#endif /* SUPPORT_CHG_IPM */
	move.l (%sp)+, %a0		/* �������ε�ư���Ϥ� a0 �� */
	jmp (%a0)

/**
 *
 *  CPU�㳰������������³��
 *
 *  CPU�㳰�ϥ�ɥ�ϡ��󥿥�������ƥ����ȤǼ¹Ԥ��롥���Τ��ᡤCPU��
 *  ���ϥ�ɥ��ƤӽФ����˳���ߥ⡼�ɤ˰ܹԤ����꥿���󤷤Ƥ������
 *  ���Υ⡼�ɤ��᤹�����Υ⡼�ɤ��᤹����ˡ�����ߥ⡼�ɤ˰ܹԤ�����
 *  �� SR �����ߥ����å������¸���롥CPU�㳰������������ƥ����Ȥ�
 *  ȯ������reqflg �� TRUE �ˤʤä����ˡ�ret_exc ��ʬ�����롥
 *  reqflg ������å��������˳���ߤ�ػߤ��ʤ��ȡ�reqflg ������å���
 *  �˵�ư���줿����ߥϥ�ɥ���ǥǥ����ѥå����׵ᤵ�줿���ˡ��ǥ�
 *  ���ѥå�����ʤ���
 *  ��
 *  ��������̿��ξ���������Ϥ�2�Х��ȿʤ��ɬ�פ����뤬
 *  �б����Ƥ��ʤ�
 *  ��GDB stub���֥졼���ݥ���ȤȤ��ƻ��Ѥ��롣��
 *  ��
 * ����CPU�㳰�װ����Ÿ�������롼�����r0,r1����¸����
 * ��������߶ػߤˤ����塢
 *��������d1������߼���ľ���SR�Υ��ԡ�
 *��������a0��C����롼�������Ƭ���ɥ쥹
 * �����ξ��֤Ǥ�������롣
 * ����
 * �����쥸��������
 * ������r4��C����롼����ΰ���
 * ���������������å�����Ѥޤ줿SR�Υ��ɥ쥹
 * ������r7�������������å��ݥ���
 */
	.text
	.align 2
	.globl cpu_exception_entry
cpu_exception_entry:
	/*  ����ߡ�CPU�㳰�ͥ��ȥ����󥿤Υ����å� 	*/
	tst.l	intnest         /* CPU�㳰ȯ�����Υ���ƥ����Ȥ�Ƚ��  	*/
	bne	_exc_from_int   /* ¿���㳰�ʤ饸����   		*/
	addq.l  #1, intnest

        /* 	���ʤ�CPU�㳰�ξ��					*/
				/* �����å������ؤ�����			*/
				/* �����������å��ݥ��󥿤���¸        	*/
	move.l  %sp, %a1
				/* ����ߥ����å����ڤ��ؤ�		*/
	move.l  #STACKTOP, %sp
	move.l	%a1,-(%sp) 	/*       ��  			*/
	move.w 	%d1, %sr	/*  ����ߵ���                          */
				/*    �����������å��ݥ��󥿤�		*/
				/*    ����ߥ����å����Ѥ�  		*/
	jsr	(%a0)		/* C����롼����ƤӽФ�		*/
									
        move.l  #(MAX_IPM << 8), %d0 /*  ����߶ػ�		*/
        ori.l   #0x00003000, %d0
	move.w	%d0, %sr
				/* �����/CPU�㳰�ͥ��ȥ����󥿤򥯥ꥢ */
	clr.l	intnest
	move.l	(%sp),%sp	/* �����å����ؤ�  			*/
				/* reqflg�Υ����å�                    	*/
	tst.l	reqflg
	jbne	ret_exc
	movem.l (%sp), %d0-%d1/%a0-%a1
	adda.l  #16,%sp
	rte

/*
 *  ����ߤθ�������³��
 *
 * ����������װ����Ÿ�������롼�����r0,r1����¸����
 * ��������߶ػߤˤ����塢
 *��������d1������߼���ľ���SR�Υ��ԡ�
 *��������a0:C����롼�������Ƭ���ɥ쥹
 * �����ξ��֤Ǥ�������롣
 * ����
 * �����쥸��������
 * ������r7�������������å��ݥ���
 */
	.text
	.align 2
	.globl interrupt_entry
interrupt_entry:
	/*  ����ߡ�CPU�㳰�ͥ��ȥ����󥿤Υ����å� 	*/
	tst.l	intnest		/* ¿�ų���ߤʤ饸����   		*/
	bne	_interrupt_from_int
	addq.l	#1, intnest	/* ����ߥͥ��ȥ����󥿤򥤥󥯥���� */

                                /* ���ʤγ���ߤξ��		*/
				/* �����å������ؤ�����			*/
				/* �����������å��ݥ��󥿤���¸        	*/
	move.l  %sp, %a1	/* ����ߥ����å����ڤ��ؤ�		*/
	move.l  #STACKTOP, %sp 
	move.l	%a1,-(%sp) 	/*    �����������å��ݥ��󥿤�		*/
	move.w  %d1, %sr	/*  ����ߵ���  */
				/*    ����ߥ����å����Ѥ�  		*/
	jsr	(%a0)		/* C����롼����ƤӽФ�		*/
				/*  ����߶ػ�		*/
        move.l  #(MAX_IPM << 8), %d0
        ori.l   #0x00002000, %d0
	move.w	%d0, %sr	/*  ����߶ػ�			*/
				/* ����ߡ�CPU�㳰�ͥ��ȥ����󥿤򥯥ꥢ*/
	clr.l	intnest
	move.l	(%sp),%sp	/* �����å����ؤ�  			*/
				/* reqflg�Υ����å�                    	*/
	tst.l	reqflg
	jbne	ret_int
	movem.l (%sp), %d0-%d1/%a0-%a1
	adda.l  #16,%sp
	rte

/* ¿�ų���ߤξ�� 							*/
/* 	�����ȯ�����Υ���ƥ����Ȥ�Ƚ�̸塢 				*/
/*   		����߶ػ� 						*/
/*   		a0��C����롼�������Ƭ���ɥ쥹				*/
/*   		d0�������ߥͥ��Ȳ��			                */
/*��������      d1������߼���ľ���SR�Υ��ԡ�                          */
/* 	�ξ��֤Ǥ���������Ǥ��� 					*/
_exc_from_int:
_interrupt_from_int:
	addq.l	#1, intnest		/* ����ߥͥ��ȥ����󥿤򥤥󥯥���� */
	move.w	%d1,%sr			/*  ����ߵ���	*/
	
	jsr	(%a0)			/*  C����롼����ƤӽФ� 	*/
	
        move.l  #(MAX_IPM << 8), %d0
        ori.l   #0x00002000, %d0
	move.w	%d0, %sr	/*  ����߶ػ�			*/
	/* ����ߡ�CPU�㳰�ͥ��ȥ����󥿤�ǥ��������	*/
	subq.l	#1, intnest
	movem.l (%sp), %d0-%d1/%a0-%a1
	adda.l  #16,%sp
	rte

/*
 *  ����ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ�и�����
 *
 *  ret_int �ϳ���߶ػ߾��֤ǡ�ret_exc �ϥޥ����⡼�ɡ�
 *  ����߶ػ߾��֤ǸƤӽФ��ʤ���Фʤ�ʤ����ޤ� ret_exc �ϡ��������
 *  ���쥸��������¸�������֤ǸƤӽФ����ȡ�
 */
	.text
	.align 2
ret_int:
ret_exc:
	clr.l reqflg			/* reqflg �� FALSE �� */
	move.l runtsk, %a0		/* A0 �� runtsk */
	tst.l enadsp			/* enadsp �� FALSE �ʤ� */
	jbeq  ret_int_1			/*         ret_int_1 �� */
	cmp.l schedtsk, %a0		/* runtsk �� schedtsk ��Ʊ���ʤ� */
	jbeq ret_int_1			/*                  ret_int_1 �� */
	lea	-44(%sp), %sp
	movem.l %d2-%d7/%a2-%a6, (%sp)	/* �Ĥ�Υ쥸��������¸ */
	move.l %sp, TCB_msp(%a0)	/* �����������å�����¸ */
	move.l #ret_int_r, %d2
	move.l %d2, TCB_pc(%a0)	/* �¹ԺƳ����Ϥ���¸ */
	jbra dispatcher
ret_int_r:
	movem.l (%sp), %d2-%d7/%a2-%a6	/* �쥸���������� */
	lea  44(%sp), %sp
ret_int_1:
	btst.b #TCB_enatex_bit, TCB_enatex(%a0)
	jbeq ret_int_2			/* enatex �� FALSE �ʤ�꥿���� */
	tst.l TCB_texptn(%a0)		/* texptn �� 0 �ʤ�꥿���� */
	jbeq ret_int_2
	jsr call_texrtn			/* �������㳰�����롼����θƽФ� */
ret_int_2:
#ifdef SUPPORT_CHG_IPM
	move.l  16(%sp),  %d0	               /* �����γ���ߥޥ����� */
	and.l   #~0x00000700, %d0		/*        task_intmask �� */
	clr.l	%d1
	move.w	task_intmask, %d1
	or.l	%d1, %d0
	move.l  %d0, 16(%sp)
#endif /* SUPPORT_CHG_IPM */
	movem.l (%sp), %d0-%d1/%a0-%a1	/* ������å��쥸���������� */
	adda.l  #16, %sp
	rte

/*
 *  ���������Ԥ�
 */
	.globl _sil_dly_nse
_sil_dly_nse:
	subi.l #SIL_DLY_TIM1, %d0	/* D0 ���� SIL_DLY_TIM1 ����� */
	jbhi _sil_dly_nse_1		/* ��̤� 0 �ʲ��ʤ�꥿���� */
	rts
_sil_dly_nse_1:
	subi.l #SIL_DLY_TIM2, %d0	/* D0 ���� SIL_DLY_TIM2 ����� */
	jbhi _sil_dly_nse_1		/* ��̤� 0 ����礭����Х롼�� */
	rts