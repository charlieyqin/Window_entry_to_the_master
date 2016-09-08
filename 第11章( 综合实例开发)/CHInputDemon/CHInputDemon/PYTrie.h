#pragma once

#include <windows.h>
#include <vector>
#include <list>
#include <string>
using namespace std ;

#define MIN_BUF_SIZE	32
#define MAX_BUF_SIZE	2048
#define MAX_PY_NUM		512

typedef struct _NODE {
	struct _NODE*	lpNode[26] ;	
	int				nWordIndex ;	// �������б�����
	struct _NODE () {
		nWordIndex = -1 ;
		for ( int i = 0; i <  26; i++ )
			lpNode[i] = NULL ;
	}
} NODE, *PNODE ;


class CPYTrie
{
private:
	NODE			RootNode ;				// Trie�������
	vector<WCHAR>	WordVect[MAX_PY_NUM] ;	// �洢�������б�

public:
	// �����ֵ�
	BOOL PYT_LoadDic ( LPSTR lpDicName ) ;
	// ����ƴ������λƴ������Ӧ����
	BOOL PYT_SearchWord ( LPSTR lpPY, LPWSTR lpWord, UINT &nWordNum ) ;

private:
	// ���Trie���Ľ����
	VOID PYT_AddItem ( LPSTR lpPY, UINT nIndex ) ;
	// ���ƴ���Ƿ�Ϸ�
	BOOL PYT_IsValidPY ( LPSTR lpPY ) ;
	// �ַ���ת�������ַ�ת��Ϊ���ַ�
	BOOL BTW(LPSTR lpSrc,LPWSTR lpDst) ;
	// �ַ���ת�������ַ�ת��Ϊ���ַ�
	BOOL WTB(LPWSTR lpSrc,LPSTR lpDst) ;

public:
	CPYTrie(void);
public:
	~CPYTrie(void);
};
