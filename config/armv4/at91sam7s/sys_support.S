/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003      by Advanced Data Controls, Corp
 *  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2006 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id$
 */

#define _MACRO_ONLY
#include "jsp_kernel.h"
#include <at91sam7s.h>


/*
 *  ���٥�Υ������åȥ����ƥ��¸�ν����
 *
 *  �������ȥ��åץ⥸�塼�����ǡ��������������˸ƤӽФ���롥
 */

        .text
        .align 2
        .global hardware_init_hook
hardware_init_hook:
        ldr     r10, =TADR_BASE_RSTC
        ldr     r0, =0xA5000c01		/* NRST enable */
        str     r0, [r10, #TOFF_RSTC_MR]
									/* Set up FLASH wait state */
        ldr     r10, =TADR_MC_BASE
        ldr     r0, =(50<<MC_FMR_FMCN_SHIFT) | MC_FMR_FWS_1FWS
        str     r0, [r10, #TOFF_MC_FMR]
									/* Disable Watchdog */
        ldr     r10, =TADR_WDT_BASE
        ldr     r0, =WDT_MR_WDDIS
        str     r0, [r10, #TOFF_WDT_MR]
									/* Enable the main oscillator */
        ldr     r10, =TADR_PMC_BASE
        ldr     r0, =(6<<CKGR_MOR_OSCOUNT_SHIFT)|CKGR_MOR_MOSCEN
        str     r0, [r10, #TOFF_CKGR_MOR]
									/* Wait for main oscillator to stabilize */
oscillator_wait:
        ldr     r0, [r10, #TOFF_PMC_SR]
        tst     r0, #PMC_SR_MOSCS
        beq     oscillator_wait
									/* Set up the PLL */
									/* MCK=18.432[MHz]/(DIV=14)*((MUL=72)+1)/2=48054857[Hz] */
        ldr     r0, =(14<<CKGR_PLLR_DIV_SHIFT) | (28<<CKGR_PLLR_PLLCOUNT_SHIFT) | (72<<CKGR_PLLR_MUL_SHIFT)
        str     r0, [r10, #TOFF_CKGR_PLLR]
									/* Wait for PLL to lock */
PLLlock_wait:
        ldr     r0, [r10, #TOFF_PMC_SR]
        tst     r0, #PMC_SR_LOCK
        beq     PLLlock_wait
									/* Select PLL as clock source */
        ldr     r0, =(PMC_MCKR_CSS_PLL_CLOCK|PMC_MCKR_PRES_CLK_2)
        str     r0, [r10, #TOFF_PMC_MCKR]
									/* Setup the stack for each mode */
        mov     r0, sp
        msr     cpsr_c, #(CPSR_FIQ|CPSR_IRQ_BIT|CPSR_FIQ_BIT)	/* Set up Fast Interrupt Mode and set FIQ Mode Stack */
        ldr     r8, =TADR_AIC_BASE                      /* Init the FIQ register */

        msr     cpsr_c, #(CPSR_IRQ|CPSR_IRQ_BIT|CPSR_FIQ_BIT)	/* Set up Interrupt Mode and set IRQ Mode Stack */
        mov     r13, r0                                 /* Init stack IRQ */

        msr     cpsr_c, #(CPSR_SVC|CPSR_IRQ_BIT|CPSR_FIQ_BIT)   /* Return Supervisor Mode and set Supervisor Mode */

init_done:
        mov     pc, lr


        .text
        .align 2
        .global software_init_hook
software_init_hook:
        mov     pc, lr

        .text
        .align 2
        .global software_term_hook
software_term_hook:
        mov     pc, lr


/*
 *
 *  ����ߤν����������
 *
 */
        .text
        .align 4
        .global IRQ_Handler
IRQ_Handler:

        /* 
         * ����ߥ⡼�� 
         * 
         * cpsr��spsr_irq�������褬r14_irq(lp)�����ꡤ
         * spsr_irq��r14_irq��r13(sp)_irq�� r14,r13�Ȥʤ롥
         */

        /* 
         *  ��������ư����⡼��(�����ѡ��Х������⡼��)��
         */
        mov     sp,#(CPSR_SVC | CPSR_FIQ_BIT | CPSR_IRQ_BIT) 
        msr     cpsr_all, sp
        stmfd   sp!, {r0-r3,ip,lr,pc} /* pc�ϥ��ߡ� */


        /*
         * spsr��������Ϥ�������뤿���IRQ�⡼�ɤ�
         */
        mov     r0,#(CPSR_IRQ | CPSR_FIQ_BIT | CPSR_IRQ_BIT)
        msr     cpsr,r0
        sub     r0,lr,#4
        mrs     r1,spsr

        /*
         *  �����ѡ��Х������⡼�ɤ�
         */
        and     r2,  r1, #CPSR_FIQ_BIT /* FIQ�ӥåȤηѾ� */
        orr     r2,  r2, #(CPSR_SVC|CPSR_IRQ_BIT)
        msr     cpsr_all, r2
        str     r0, [sp,#0x18] /* Store pc */
        stmfd   sp!,{r1}       /* spsr */


        /*
         *  ¿�ų����ߤ�Ƚ��
         */
        ldr     r2, =interrupt_count
        ldr     r3, [r2]
        add     r0,r3,#1
        str     r0, [r2]
        cmp     r3, #0x00

        moveq   r2,sp            /* �ͥ��ȳ����ߤǤʤ���� */
        ldreq   sp,=STACKTOP     /* �����å����ѹ�    */
        stmeqfd sp!,{r2}         /* �����������å�����¸ */

        /*
         *  �������װ���Ƚ�ꡥ
         */
        ldr     r3, =TADR_AIC_BASE
        ldr     r0, [r3, #TOFF_AIC_IVR]
        str     r3, [r3, #TOFF_AIC_IVR]

        /*
         * �����ߵ���
         */
        mrs     r2, cpsr
        and     r2,  r2, #~CPSR_IRQ_BIT /* ����ߵ��� */
        msr     cpsr,r2

        /*
         * Call Handler
         */
        mov     lr,  pc
        mov     pc,  r0

        /* 
         * �����߶ػ� 
         */
        mrs     r2, cpsr
        and     r2,  r2, #CPSR_FIQ_BIT /* FIQ�ӥåȤηѾ� */
        orr     r2,  r2, #(CPSR_SVC|CPSR_IRQ_BIT)
        msr     cpsr,r2

        /*
         * ����ߥ��ꥢ
         */
        ldr     r3, =TADR_AIC_BASE
        mov     r0, #0
        str     r0, [r3, #TOFF_AIC_EOICR]

        /* 
         * ����ߥͥ��Ȳ��(interrupt_count) �ǥ������ 
         */
        ldr     r2, =interrupt_count
        ldr     r1, [r2]
        sub     r3, r1, #1
        str     r3, [r2]
        cmp     r3, #0x00
        bne     return_to_task_irq

        /* 
         * �����������å������� 
         */
        ldmfd   sp!,{r0}
        mov     sp, r0

        ldr     r1, =reqflg    /* Check reqflg */
        ldr     r0, [r1]
        cmp     r0, #0
        beq     return_to_task_irq
        mov     r0, #0
        str     r0, [r1]       /* Clear reqflg */
        b       ret_int

return_to_task_irq:
        /*
         *  ��������
         *  �����ߵ��ĤȤʤ뤬����������ƥ����Ⱦ����¸���Ƥ��뤿�ᡤ
         *  ����Ϥʤ�
         */
        ldmfd   sp!,{r1}           /* CPSR���������� */
        mrs     r2, cpsr           /* FIQ��Ѿ�            */
        and     r2, r2, #CPSR_FIQ_BIT
        and     r1, r1, #~CPSR_FIQ_BIT
        orr     r1, r1, r2                 
        msr     spsr, r1           /* �����ߵ���   */
        ldmfd   sp!,{r0-r3,ip,lr,pc}^ /*���������� + ����ߵ��� */

        .text
        .align 4
        .global FIQ_Handler
FIQ_Handler:
         /* Switch in SVC/User Mode to allow User Stack access for C code */
         /* because the FIQ is not yet acknowledged */
         /* Save and r0 in FIQ_Register */
         mov    r9, r0
         ldr    r0, [r8, #TOFF_AIC_FVR]
         msr    cpsr_c,#(CPSR_SVC|CPSR_IRQ_BIT|CPSR_FIQ_BIT)
         /* Save scratch/used registers and LR in User Stack */
         ldr    sp, =(STACKTOP+FIQ_DATA_SIZE)
         stmfd  sp!, { r1-r3, r12, lr}
         /* Branch to the routine pointed by the AIC_FVR */
         mov    r14, pc
         bx     r0
         /* Restore scratch/used registers and LR from User Stack */
         ldmia  sp!, { r1-r3, r12, lr}
         /* Leave Interrupts disabled and switch back in FIQ mode */
         msr    cpsr_c, #(CPSR_FIQ|CPSR_IRQ_BIT|CPSR_FIQ_BIT)
         /* Restore the R0 ARM_MODE_SVC register */
         mov    r0, r9
         /* Restore the Program Counter using the LR_fiq directly in the PC */
         subs   pc, lr, #4

