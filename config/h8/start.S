/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2001,2002 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
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
 *  @(#) $Id: start.S,v 1.4 2002/04/14 11:36:50 hiro Exp $
 */
#define _MACRO_ONLY
#include "sys_config.h"
#include "cpu_config.h"	
	
/*
 *   H8�ѥ������ȥ��åץ⥸�塼��
 *   �����ͥ�ϥ��ץꥱ�������ȥ�󥯤��ƻ��Ѥ���
 *   �����ʤΤ�JSP�����ͥ�Τ߻��Ѥ��롣	
 */
	.h8300h

	.text
	.align 2

	.global	_start
_start:

	/*
	 * ��������Ω�Υ����å���STACKTOP�˽��������
	 * STACKTOP�ϡ�sys_config.h�����
	 */

	mov.l	#STACKTOP, sp

	/*
	 *  _hardware_init_hook ��ƤӽФ���(0�Ǥʤ����)
	 *
	 *  �ϡ��ɥ�������¸��ɬ�פʽ����������������ϡ�
	 *  hardware_init_hook �Ȥ����ؿ����Ѱդ���Ф褤��
	 *  ����Ū�ˤ�ROM���κݡ�RAM����Ѳ�ǽ�ˤ��뤿���
	 *  �Х�����ȥ�����ν��������Ԥ���
	 *  sys_support.S ��� hardware_init_hook ��������Ƥ�
	 *  �롥
	 */

start_0:
	mov.l  	@_hardware_init_hook_k, er0
	or.l	er0, er0
	beq	start_1
	jsr	@er0
	
	/*
         * bss���������򥯥ꥢ
	 */

start_1:		
	mov.l	#__bss_start, er0
	mov.l	#_end, er1
	sub.l	er2, er2
start_2:
        mov.l	er2, @er0
	add.l	#4, er0
 	cmp.l	er1, er0
 	blo	start_2		/* er1 > er0 */

	/*
	 *  data�������������������ROM���б��ˡ�
	 *
	 *  __idata_start ���� __idata_end �ޤǤ�__data_start �ʹߤ�
	 *  ���ԡ����롥
	 */

	mov.l	#__idata_start, er0
	mov.l	#__idata_end, er1
	mov.l	#__data_start, er2
start_4:
	mov.l	@er0+, er4	/* *er2++ = *er0 ++; */
	mov.l	er4, @er2
	add.l	#4, er2
	cmp.l	er1, er0
	blo	start_4		/* er1 > er0 */

	/*
	 *  software_init_hook ��ƤӽФ���0 �Ǥʤ����ˡ�
	 *
	 *  ���եȥ������Ķ����ä˥饤�֥��ˤ˰�¸����ɬ�פʽ������
	 *  ����������ϡ�software_init_hook �Ȥ����ؿ����Ѱդ����
	 *  �褤��
	 */

	mov.l	@_software_init_hook_k, er0
	or.l	er0, er0
	beq	start_6		
	jsr	@er0
		
	/*	
         *  �����ͥ��ư����
	 */

start_6:
	jmp	@_kernel_start

	.align 4
_hardware_init_hook_k:	
	.long   _hardware_init_hook
_software_init_hook_k:	
	.long   _software_init_hook