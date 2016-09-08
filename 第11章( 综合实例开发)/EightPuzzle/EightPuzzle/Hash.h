#pragma once

#define MAX_HASH_RANGE	10000
#define MAX_CRASH_NUM	150

class CHash
{
public:
	CHash(void);
public:
	~CHash(void);

private:
	int		nCount[MAX_HASH_RANGE] ;	// ��¼ÿһ��hashֵ�е����ݸ���
	int*	pHashTable[MAX_HASH_RANGE] ;// hash��

public:
	BOOL	IsValueExist ( int nValue ) ;	// ����Ƿ��Ѵ���
	VOID	AddValue ( int nValue ) ;		// �������
};
