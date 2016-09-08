#pragma once

#include "crc32.h"

#include <fstream>
using namespace std ;

#define MAX_TITLE_LEN	256

// ÿһ��/ÿһ��ͼ����Ŀ
#define DEF_ICON_NUM	8

// ͼ���С
#define DEF_ICON_SIZE	48	

typedef struct _PAIR {
	POINT a, b ;
	struct _PAIR () {}
	struct _PAIR ( POINT x, POINT y ) {
		a.x = x.x ;
		a.y = x.y ;
		b.x = y.x ;
		b.y = y.y ;
	}
} PAIR, *LPPAIR ;	

class CDDP  
{
public:
	CDDP();
	virtual ~CDDP();

private:
	POINT	StartButtonPos ;
	HWND	hWnd ;										// DDP���ھ��
	CHAR	szWindowTitle[MAX_TITLE_LEN+1] ;			// DDP���ڱ���
	DWORD	dwStartOffsetX, dwStartOffsetY ;			// DDPͼ�������ͻ������ƫ������
	DWORD	dwIconType[DEF_ICON_NUM][DEF_ICON_NUM] ;	// ����ͼ������ֵ
	DWORD	dwClientPosX, dwClientPosY ;				// ��Ϸ���ڿͻ��������
	CRC32	crc ;										// ����hash����
	CBitmap CurBmp ;									// ��Ļλͼ
	CDC		ScreenDC, MemoryDC ;						// ��ĻDC���ڴ�DC

public:
	BOOL	DDP_Find () ;						// ��ȥ����

private:
	VOID	DDP_SwapPair ( LPPAIR lpPair ) ;	// ����ͼ�꣬ģ��������
	BOOL	DDP_CalcBmpValue ( int i, int j ) ;	// ����ָ������ͼ���hashֵ
	BOOL	DDP_IsWaiting () ;					// ����Ƿ��ڵȴ�״̬
};