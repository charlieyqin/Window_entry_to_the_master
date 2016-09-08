#pragma once

#include <windows.h>

// ������Կ����С����
#define MIN_KEY_SIZE	4

// ������Կ����󳤶�
#define MAX_KEY_SIZE	56

class CBlowfish
{
public:
	CBlowfish(void);
public:
	~CBlowfish(void);

private:
	BYTE	bMode ;			// ����ģʽ��0��ECB��1��CBC��
	DWORD	PArray[18] ;	// ����Կ��
	DWORD	SBox[4][256] ;	// S��

public:
	// ������Կ������ʼ������Կ��S��
	BOOL	BF_SetKey ( LPBYTE lpKey, UINT nLen ) ;
	// ���ù���ģʽ����ǰ��֧��ECB��CBC
	VOID	BF_SetMode ( BYTE bMode ) ;
	// ����
	BOOL	BF_Encrypt ( LPBYTE lpData, UINT nSize, LPBYTE lpOut, UINT* lpSize ) ;
	// ����
	BOOL	BF_Decrypt ( LPBYTE lpData, UINT nSize, LPBYTE lpOut, UINT lpSize ) ;

private:
	VOID	BF_Encode ( DWORD& pl, DWORD& pr ) ;
	VOID	BF_Decode ( DWORD& pl, DWORD& pr ) ;

};
