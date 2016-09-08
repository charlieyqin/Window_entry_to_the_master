#pragma once

class CIDEA
{
public:
	CIDEA(void);
	~CIDEA(void);

private:
	BYTE	bKey[16] ;		// �û���Կ��128λ
	UINT16	bEnKey[53] ;	// bEnKey[0]δ�ã�1--52
	UINT16	bDeKey[53] ;	// bDeKey[0]δ�ã�1--52

public:
	// ����128λ��Կ�������ɼ��ܺͽ�������Կ����
	BOOL	SetKey ( LPBYTE lpKey, UINT nSize ) ;
	// ��������
	BOOL	EncryptData ( LPBYTE lpData, UINT nSize, LPBYTE lpBuf, UINT* lpSize ) ;
	// ��������
	BOOL	DecryptData ( LPBYTE lpData, UINT nSize, LPBYTE lpBuf, UINT* lpSize ) ;

private:
	// ������������Կ����
	VOID	GenEncryptKey () ;
	// ������������Կ����
	VOID	GenDecryptKey () ;
	// ���ܹ����ֱ任
	VOID	EnRoundTransform ( UINT16& x1, UINT16& x2, UINT16& x3, UINT16& x4, UINT nRoundIndex ) ;
	// ���ܹ����ֱ任
	VOID	DeRoundTransform ( UINT16& x1, UINT16& x2, UINT16& x3, UINT16& x4, UINT nRoundIndex ) ;

private:
	// ȡ����Կָ��λ��ֵ
	inline int	GetBitByIndex ( UINT nIndex ) ;
	// ��չŷ������㷨����˷���Ԫ
	int		ExtendedEuclid ( int e, int f ) ;
};
