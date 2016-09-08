#pragma once

#ifndef _WINDOWS_H
#include <windows.h>
#endif

#include <iomanip>
#include <fstream>
using namespace std ;

#include "crc32.h"

#include <vector>
using namespace std ;

#define MAX_TITLE_LEN	256
#define MAX_ICON_NUM	64
#define DEL_ALL_PAIRS	999

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

class CLLK  
{
public:
	CLLK();
	virtual ~CLLK();

private:
	BOOL	bActive ;							// LLK�Ƿ���ڴ��ڼ���״̬
	HWND	hWnd ;								// LLK���ھ��
	CHAR	szWindowTitle[MAX_TITLE_LEN+1] ;	// LLK���ڱ���
	DWORD	dwClientPosX, dwClientPosY ;		// LLK�ͻ���������
	DWORD	dwStartOffsetX, dwStartOffsetY ;	// LLKͼ�������ͻ������ƫ������
	DWORD	dwIconSizeX, dwIconSizeY ;			// LLKͼ���С
	DWORD	dwIconNumX, dwIconNumY ;			// LLK����������ͼ����

private:
	DWORD	dwIconNum ;										// ͼ������
	BOOL	bValidIcon[MAX_ICON_NUM+1][MAX_ICON_NUM+1] ;	// ��ʶָ��λ�õ�ͼ���Ƿ����
	DWORD	dwColorNum ;									// ͼ��������
	DWORD	dwColorType[MAX_ICON_NUM*MAX_ICON_NUM] ;		// ����ÿ��ͼ���hashֵ
	vector<POINT>	IconList[MAX_ICON_NUM*MAX_ICON_NUM] ;	// �ڽ�����

private:
	CRC32	crc ;		// ʹ��CRC32��Ϊhash�㷨
	CDC		ScreenDC ;	// ��ĻDC

public:
	// ��ʼ����ȡ��������
	BOOL	LLK_Initial () ;

	// ��ȥָ����Ŀ�����
	BOOL	LLK_DelSpecifyPairs ( UINT nCount = DEL_ALL_PAIRS ) ;


private:
	// ���ͼ����Ƿ�Ϸ�
	BOOL	LLK_IsValidPair ( LPPAIR lpPair ) ;

	// ȡ��ָ��ͼ������
	DWORD	LLK_GetSpecifyIconType ( LPPOINT pt ) ;

	// ����TRUE��������ͬһֱ��������֮�����ϰ�
	BOOL	LLK_IsPairInlineValid ( LPPAIR lpPair ) ;

	// ȡ��ָ���������Ч����
	VOID	LLK_GetValidRangeH ( POINT pt, int &min, int &max ) ;

	// ȡ��ָ����������Ч����
	VOID	LLK_GetValidRangeV ( POINT pt, int &min, int &max ) ;

	// ����ָ��ͼ��
	VOID	LLK_SaveSpecifyBmp ( CBitmap* pBmp, CString szPathName ) ;

	// ���ָ��BMP�Ƿ�Ϊ��ͼ��
	BOOL	LLK_IsValidIcon ( CBitmap* pBmp ) ;

	// Ѱ�����
	BOOL	LLK_FindPAIR () ;

	// ��ȥ���
	VOID	LLK_DeletePair ( LPPAIR lpPair ) ;

private:
	int		LLK_GetMin ( int a, int b ) ;
	int		LLK_GetMax ( int a, int b ) ;
};
