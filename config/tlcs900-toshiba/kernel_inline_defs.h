/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2006-2010 by Witz Corporation, JAPAN
 * 
 *  The above copyright holders grant permission gratis to use,
 *  duplicate, modify, or redistribute (hereafter called use) this
 *  software (including the one made by modifying this software),
 *  provided that the following four conditions (1) through (4) are
 *  satisfied.
 * 
 *  (1) When this software is used in the form of source code, the above
 *      copyright notice, this use conditions, and the disclaimer shown
 *      below must be retained in the source code without modification.
 * 
 *  (2) When this software is redistributed in the forms usable for the
 *      development of other software, such as in library form, the above
 *      copyright notice, this use conditions, and the disclaimer shown
 *      below must be shown without modification in the document provided
 *      with the redistributed software, such as the user manual.
 * 
 *  (3) When this software is redistributed in the forms unusable for the
 *      development of other software, such as the case when the software
 *      is embedded in a piece of equipment, either of the following two
 *      conditions must be satisfied:
 * 
 *    (a) The above copyright notice, this use conditions, and the
 *           disclaimer shown below must be shown without modification in
 *        the document provided with the redistributed software, such as
 *        the user manual.
 * 
 *    (b) How the software is to be redistributed must be reported to the
 *        TOPPERS Project according to the procedure described
 *        separately.
 * 
 *  (4) The above copyright holders and the TOPPERS Project are exempt
 *      from responsibility for any type of damage directly or indirectly
 *      caused from the use of this software and are indemnified by any
 *      users or end users of this software from any and all causes of
 *      action whatsoever.
 * 
 *  THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
 *  THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
 *  PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
 *  TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
 *  INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ�
 *  �����ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭�����
 *      ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ�����
 *      ��������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻���
 *      �Ǥ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ����Ѽԥ�
 *      �˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ�����̵��
 *      �ڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻���
 *      �Ǥ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ������������ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
 *        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ���
 *        �𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»��
 *      ����⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ��ޤ���
 *      �ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���ͳ�˴��
 *      �����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ���
 *  ��TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū���Ф�
 *  ��Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ�����������
 *  �ˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ����
 *  ��ʤ���
 * 
 *  @(#) $Id: kernel_inline_defs.h,v 1.1 2006/04/10 08:19:25 honda Exp $
 */

/*
 *	TOSHIBA��ȯ�Ķ������ӥ�ȥ���(inline)�ؿ������
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ������ͥ�������c�ե����뤫�饤�󥯥롼��
 *  ����Ƥ���tool_defs.h ���饤�󥯥롼�ɤ���롥¾�Υե����뤫���ľ��
 *  ���󥯥롼�ɤ��뤳�ȤϤʤ���¾�Υ��󥯥롼�ɥե��������Ω�äƽ�����
 *  ��뤿�ᡤ¾�Υ��󥯥롼�ɥե�����˰�¸���ƤϤʤ�ʤ���
 */

#ifndef _KERNEL_INLINE_DEFS_H_
#define _KERNEL_INLINE_DEFS_H_

/*
 *  TOSHIBA IDE�Ǥ�#pragma inline���Ҥˤƥ���饤��ؿ����������
 *  ���Τ��ᥫ���ͥ������ˤΤ߰ʲ��ν�����Ŭ�Ѥ��롥
 *  tool_defs.h �ˤƥ����ͥ붦������Inline�����inline�����������
 *  ̵���Ȥ������ΤΥ���饤��ؿ����Ф���#pragma inline����ܥե�
 *  ����˵��ܤ��롥
 */
/* sil.h	*/
#pragma inline sil_reb_mem
#pragma inline sil_wrb_mem
#pragma inline sil_reh_mem
#pragma inline sil_wrh_mem
#pragma inline sil_reh_lem
#pragma inline sil_wrh_lem
#pragma inline sil_reh_bem
#pragma inline sil_wrh_bem
#pragma inline sil_rew_mem
#pragma inline sil_wrw_mem
#pragma inline sil_rew_lem
#pragma inline sil_wrw_lem
#pragma inline sil_rew_bem
#pragma inline sil_wrw_bem

/* t_services.h	*/
#pragma inline _t_perror
#pragma inline _t_panic

/* t_syslog.h	*/
#pragma inline _syslog_0
#pragma inline _syslog_1
#pragma inline _syslog_2
#pragma inline _syslog_3
#pragma inline _syslog_4
#pragma inline _syslog_5
#pragma inline _syslog_6

/* mailbox.c	*/
#pragma inline enqueue_msg_pri

/* task.c	*/
#pragma inline bitmap_search

/* time_event.c	*/
#pragma inline tmevtb_delete_top

/* wait.c	*/
#pragma inline make_non_wait
#pragma inline queue_insert_tpri
#pragma inline wobj_queue_insert

/* queue.h	*/
#pragma inline queue_initialize
#pragma inline queue_insert_prev
#pragma inline queue_delete
#pragma inline queue_delete_next
#pragma inline queue_empty

/* task_event.h	*/
#pragma inline tmevtb_enqueue
#pragma inline tmevtb_enqueue_evttim
#pragma inline tmevtb_dequeue

/* wait.h	*/
#pragma inline make_wait

/* serial.c	*/
#pragma inline serial_snd_chr


#endif	/* _KERNEL_INLINE_DEFS_H_	*/