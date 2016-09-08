
#ifndef _DES_H
#define _DES_H

class CDES {
public:
	BYTE bOriMsg[8] ;				// ��ʼ��Ϣ ( 64 bit )
	BYTE LMsg[17][4], RMsg[17][4] ;	// �м����L0-->L16,R0-->R16 ( 32 bit )
	BYTE bKey[8] ;					// ������Կ ( 64 bit )
	BYTE bSubKey[17][6] ;			// ��������ԿK1-->K16 ( 48 bit )
	BYTE bCryptedMsg[8] ;			// ����

public:
	void DES_Encrypt ( ) ;
	void DES_Decrypt ( ) ;
	BOOL DES_Encrypt ( LPBYTE lpSour, LPBYTE lpDest, UINT uLen, LPBYTE lpKey ) ;
	BOOL DES_Decrypt ( LPBYTE lpSour, LPBYTE lpDest, UINT uLen, LPBYTE lpKey ) ;

public:
	// ��ʼ�û�
	void DESInitSwap ( ) ;
	// ��ʼ���û�
	void DESInitReSwap () ;
	// ��������Կ
	void DESGenSubKey ( ) ;
	// DES�ĵ��ּ��ܹ���
	void DESSingleTurn ( BYTE nTurnIndex, BOOL bMode ) ;
	// DES��F����
	void DES_f ( BYTE bTurnIndex, BOOL bMode ) ;

public:
	// ��ʼ��
	void DES_SysInit () ; 
	// ��������
	void DES_SetOriMsg ( PBYTE pMsg, UINT uLen ) ;
	// ������Կ
	void DES_SetKey ( PBYTE pKey, UINT uLen ) ;
} ;
#endif