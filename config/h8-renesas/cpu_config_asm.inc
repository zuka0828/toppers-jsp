;
;  TOPPERS/JSP Kernel
;      Toyohashi Open Platform for Embedded Real-Time Systems/
;      Just Standard Profile Kernel
;
;  Copyright (C) 2000-2004 by Embedded and Real-Time Systems Laboratory
;                              Toyohashi Univ. of Technology, JAPAN
;  Copyright (C) 2001-2004 by Industrial Technology Institute,
;                              Miyagi Prefectural Government, JAPAN
;  Copyright (C) 2001-2004 by Dep. of Computer Science and Engineering
;                   Tomakomai National College of Technology, JAPAN
;
;  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation
;  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
;  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
;  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
;  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
;  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
;      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
;      ����������˴ޤޤ�Ƥ��뤳�ȡ�
;  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
;      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
;      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
;      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
;  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
;      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
;      �ȡ�
;    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
;        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
;    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
;        ��𤹤뤳�ȡ�
;  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
;      ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
;
;  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
;  ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
;  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
;  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
;
;  @(#) $Id: cpu_config_asm.inc,v 1.6 2005/11/13 14:05:01 honda Exp $
;

;       �ץ����å���¸�⥸�塼�� ������֥��������H8�ѡ�
;���������������ͥ������ǻ��Ѥ������

 .AIFDEF _CPU_CONFIG_ASM_H_
 .AELSE

_CPU_CONFIG_ASM_H_: .DEFINE ""

        .INCLUDE "cpu_rename_asm.inc"
        .INCLUDE "util_asm.inc"

;
;  CCR�쥸���������
;    CCR��I,UI�ӥåȤ�����ߥޥ����ӥåȤȤ��ƻ��Ѥ��롣
;
CCR_I                   .DEFINE         "BIT7"
CCR_UI                  .DEFINE         "BIT6"

CCR_DISINT_ALL          .DEFINE         "(CCR_I | CCR_UI)"
CCR_ENAINT_ALL          .DEFINE         "(H'ff & ~CCR_DISINT_ALL)"

;
;  ����ߥޥ��������ꤹ���ͤ����
;

;  ��٥룰�����٤Ƥγ���ߤ�����դ���
IPM_LEVEL0              .DEFINE         "H'0"

;  ��٥룱��NMI����ӥץ饤����ƥ���٥룱�γ���ߤΤߤ�����դ���
IPM_LEVEL1              .DEFINE         "CCR_I"

;  ��٥룲��NMI�ʳ��γ���ߤ�����դ��ʤ�
IPM_LEVEL2              .DEFINE         "(CCR_I|CCR_UI)"
                        ;�����ڡ���������ȥޥ��������Ȥ����Ϥ��ʤ�


 .AENDI ; _CPU_CONFIG_ASM_H_
