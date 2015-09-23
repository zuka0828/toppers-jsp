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
;  @(#) $Id: h8_3048f_asm.inc,v 1.6 2005/11/13 14:05:01 honda Exp $
;

;  H8/3048F������ʥ�����֥��ѡ�

 .AIFDEF _H8_3048F_ASM_H_
 .AELSE

_H8_3048F_ASM_H_: .DEFINE ""

        .INCLUDE "util_asm.inc"

;
;  �����쥸���������
;

;
;  �⡼�ɥ���ȥ�����쥸����
;
H8MDCR:                 .DEFINE         "H'fffff1"

;
;  I/O�ݡ���
;

;
;  �ݡ���1
;
H8P1DDR:                .DEFINE         "H'ffffc0"

;
;  �ݡ���2
;
H8P2DDR:                .DEFINE         "H'ffffc1"

;
;  �ݡ���5
;
H8P5DDR:                .DEFINE         "H'ffffc8"

;
;  �ݡ���8
;
H8P8DDR:                .DEFINE         "H'ffffcd"
H8P8DDR_CS1:            .DEFINE         "BIT3"


;
;  �Х����ơ��ȥ���ȥ�����
;

;���Х�������ȥ�����쥸����
H8ABWCR:                .DEFINE         "H'ffffec"
H8ABWCR_ABW1_BIT:       .DEFINE         "1"

;���������������ơ��ȡ�����ȥ����롦�쥸����
H8ASTCR:                .DEFINE         "H'ffffed"
H8ASTCR_AST1_BIT:       .DEFINE         "1"

;���Х�����꡼��������ȥ����롦�쥸����
H8BRCR:                 .DEFINE         "H'fffff3"
H8BRCR_BRLE_BIT:        .DEFINE         "0"
H8BRCR_A21E_BIT:        .DEFINE         "5"

 .AENDI ; _H8_3048F_ASM_H_
