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
 *  @(#) $Id: serial_console.c,v 1.6 2001/11/12 14:55:23 takayuki Exp $
 */


/*
 * エディットボックスを使ったシリアルインターフェースモジュール
 */

#include "debugout.h"
#include <jsp_services.h>
#include "kernel_id.h"
#include "hal_msg.h"
#include "resource.h"

#define SERMSG_CREATE WM_APP

#define TRANSLATE_PORTID(x) \
	x = (x != 0) ? (x) : CONSOLE_PORTID 

#define CHECK_PORTID(x) \
	( (x) > 0 && (x) <= NUM_PORT )

#define NUM_PORT 1

	/* 入力用バッファサイズ (2^nであること) */
#define SERIAL_INPUTBUFFERSIZE 0x80

	/* 表示リミッターサイズ */
#define SERIAL_LIMITTERUPPERBOUND 0x1000
#define SERIAL_LIMITTERSIZE 0x500

	/* プロトタイピング */
void	serial_initialize(VP_INT portid);
ER		serial_open(ID portid);
int		serial_close(ID portid, int flush);
ER_UINT serial_read(ID portid, char *buf, unsigned int len);
ER_UINT serial_write(ID portid, char *buf, unsigned int len);
ER serial_ioctl(ID portid, UINT ioctl);
void	serial_handler(void);

static LRESULT CALLBACK KeyEventTrapper(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

typedef struct serial_port_control_block {
	void * DefWndProc;
	HWND	Handle;
	ID		InputSemaphore;
	char	Buffer[SERIAL_INPUTBUFFERSIZE];
	int		Top;
	int		Tail;
} SPCB;

SPCB spcb[NUM_PORT] =
{
	{	0l, 0l, SEM_SERIAL1_IN,"",0,0	}	
};

extern HINSTANCE ProcessInstance;

#define NEXT(x) (((x)+1) & (SERIAL_INPUTBUFFERSIZE-1))


#ifdef _MSC_VER

__forceinline __declspec(naked) void * __fastcall MemoryCopy(void * dest, void * src, unsigned int size)
{
	__asm	mov	eax, ecx
	__asm	mov edi, ecx
	__asm	mov esi, edx
	__asm	pop ebx
	__asm	pop ecx
	__asm	rep movsb
	__asm	jmp ebx
}

#else
#include <string.h>
#define MemoryCopy memcpy
#endif

Inline void
CloseAllHandles(SPCB * cb)
{
	if(cb->Handle != 0l)
	{
		DestroyWindow(cb->Handle);
		cb->Handle = 0l;
	}
}

static LRESULT CALLBACK ConsoleProc(HWND hDlg,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	switch(Msg)
	{
	case SERMSG_CREATE:
		{
			SPCB * work;
			work = (SPCB *)lParam;
			work->DefWndProc = (void *)GetWindowLong(GetDlgItem(hDlg,IDC_CONSOLE),GWL_WNDPROC);
			SetWindowLong(hDlg,GWL_USERDATA,lParam);
			SetWindowLong(GetDlgItem(hDlg,IDC_CONSOLE),GWL_WNDPROC,(long)KeyEventTrapper);
			SetWindowLong(GetDlgItem(hDlg,IDC_CONSOLE),GWL_USERDATA,lParam);
			ShowWindow(hDlg,SW_SHOWNA);
			break;
		}
	case WM_DESTROY:
		{
			SPCB * scope;
			scope = (SPCB *)GetWindowLong(hDlg,GWL_USERDATA);
			scope->Handle = 0l;
			break;
		}
	case WM_CLOSE:
		break;

	case WM_CHAR:
		{
			SPCB * scope;
			scope = (SPCB *)GetWindowLong(hDlg,GWL_USERDATA);
			if(NEXT(scope->Tail) == scope->Top)
				break;	/* Buffer Overflow */
			scope->Buffer[scope->Tail] = (char)wParam;
			scope->Tail = NEXT(scope->Tail);
			syscall(sig_sem(scope->InputSemaphore));
			break;
		}


	case WM_INITDIALOG:
	case WM_SIZE:
		{
			RECT client;
			GetClientRect(hDlg,&client);
			MoveWindow(GetDlgItem(hDlg,IDC_CONSOLE),0,0,client.right,client.bottom,TRUE);
			break;
		}

	default:
		return FALSE;
	}

	return TRUE;
}

static LRESULT CALLBACK KeyEventTrapper(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	SPCB * scope;
	
	if(Msg == WM_CHAR)
	{
		scope = (SPCB *)GetWindowLong(hWnd,GWL_USERDATA);
		PostMessage(scope->Handle,WM_CHAR,wParam,lParam);
		return TRUE;
	}

	scope = (SPCB *)GetWindowLong(hWnd, GWL_USERDATA);
	return CallWindowProc(scope->DefWndProc,hWnd,Msg,wParam,lParam);
}


static void SerialConsole_FinalRelease(void * param)
{
	SPCB * cb = (SPCB *)param;
	if(cb->Handle != 0l)
		DestroyWindow(cb->Handle);
}

	/*この関数はPrimaryThreadによって実行される
	 *#こうしないと初期化用スレッド終了時にウィンドウが閉じられてしまう
	 */
static void CreateSerialConsole(SPCB * cb)
{
	cb->Handle = CreateDialog(ProcessInstance, MAKEINTRESOURCE(CONSOLEDIALOG), PrimaryDialogHandle, ConsoleProc);
	SendMessage(cb->Handle,SERMSG_CREATE,0,(LPARAM)cb);
	UpdateWindow(cb->Handle);
	HALAddDestructionProcedure(SerialConsole_FinalRelease,cb);
}




/*
 *  シリアルインタフェースドライバの起動
 */
void
serial_initialize(VP_INT portid)
{
	syscall(serial_open((ID)portid));
	syslog_1(LOG_NOTICE, "Serial driver service starts on port %d.", portid);
}

ER
serial_open(ID portid)
{
	SPCB * cb;

	TRANSLATE_PORTID(portid);
	if(!CHECK_PORTID(portid))
		return E_PAR;

	cb = &spcb[portid-1];
	HALExecuteProcedure(CreateSerialConsole,cb);

	return E_OK;
}

int
serial_close(ID portid, int flush)
{
	SPCB * cb;

	return 0;
	TRANSLATE_PORTID(portid);
	if(!CHECK_PORTID(portid))
		return E_PAR;

	cb = &spcb[portid-1];
	if(cb->Handle == INVALID_HANDLE_VALUE)
		return E_OBJ;

	CloseAllHandles(cb);

	return E_OK;
}

ER_UINT
serial_read(ID portid, char * buf, unsigned int len)
{
	SPCB * cb;
	DWORD cnt;

	if(len == 0)
		return 0;
	TRANSLATE_PORTID(portid);
	if(!CHECK_PORTID(portid) || buf == 0l)
		return E_PAR;

	cb = &spcb[portid-1];
	if(cb->Handle == 0l)
		return E_OBJ;

	while(len>0)
	{
		cnt = 0;
		if(cb->Top != cb->Tail)
		{
			if(cb->Top > cb->Tail)
			{
				cnt = SERIAL_INPUTBUFFERSIZE - cb->Top;
				MemoryCopy(buf,cb->Buffer + cb->Top, cnt);
				buf += cnt;
				if(cb->Tail != 0)
				{
					MemoryCopy(buf,cb->Buffer, cb->Tail);
					buf += cb->Tail;
					cnt += cb->Tail;
				}
			}else
			{
				cnt = cb->Tail - cb->Top;
				MemoryCopy(buf,cb->Buffer + cb->Top, cnt);
				buf += cnt;
			}

			cb->Top = cb->Tail;
		}else
		{
			syscall(wai_sem(cb->InputSemaphore));
		}
		len -= cnt;
	}

	return E_OK;
}

ER_UINT
serial_write(ID portid,char * buf, unsigned int len)
{
	SPCB * cb;
	DWORD cnt;
	int i,j;
	char buffer[1024];
	HANDLE console;

	if(len == 0)
		return 0;
	TRANSLATE_PORTID(portid);
	if(!CHECK_PORTID(portid) || buf == 0l)
		return E_PAR;

	cb = &spcb[portid-1];
	if(cb->Handle == 0l)
		return E_OBJ;

	console = GetDlgItem(cb->Handle,IDC_CONSOLE);

	i = GetWindowTextLength(console);
	if(i > SERIAL_LIMITTERUPPERBOUND)
	{
		SendMessage(console,EM_SETSEL,0,i - SERIAL_LIMITTERSIZE);
		SendMessage(console,EM_REPLACESEL,(WPARAM)FALSE,(LPARAM)"");
	}

	cnt = 0;
	while(cnt<len)
	{
		i = len-cnt;
		if(i>512)
			i = 511;

		for(j=0;j<i;j++,buf++)
		{
			if( (buffer[j] = *buf) == '\n')
			{
				buffer[j] = '\r';
				buffer[++j] = '\n';
			}
		}
		buffer[j] = '\x0';

		j = GetWindowTextLength(console);
		SendMessage(console,EM_SETSEL,j,j);
		SendMessage(console,EM_REPLACESEL,(WPARAM)FALSE,(LPARAM)buffer);
		
		cnt += i;
	}
	return 1;

	
	return (UINT)cnt;
}

ER
serial_ioctl(ID portid, UINT ioctl)
{
	return E_OK;
}

void
serial_handler(void)
{}
