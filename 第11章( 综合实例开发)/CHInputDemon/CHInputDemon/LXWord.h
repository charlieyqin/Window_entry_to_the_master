#pragma once


#include <vector>
using namespace std ;

#define MAX_WORD_NUM	65536			// ���������
#define MAX_LXWORD_NUM	200000			// ���ʻ�����ʵ��157200���ң�
#define MAX_WORD_LEN	16				// ���ʻ㳤��

// �ڽӱ���
typedef struct _ITEM {
	UINT	nMatchPos ;				// nLXWordIndex����ʾ�ʻ��������
	UINT	nLXWordIndex ;			// �ʻ�����
	struct _ITEM () {
		nMatchPos = 0 ;
		nLXWordIndex = 0 ;	
	}
	struct _ITEM ( UINT nPos, UINT nIndex ) {
		nMatchPos = nPos ;
		nLXWordIndex = nIndex ;
	}
} ITEM, *PITEM ;

// �����ֵ�ԭʼ����
typedef struct _LX_ITEM {
	WCHAR	CHWord[MAX_WORD_LEN] ;	// �ʻ�
	UINT	nFreq ;					// ��Ƶ
} LX_ITEM, *PLX_ITEM ;

// ��ʱ�������������������б�
typedef struct _TEMP_ARRAY {
	UINT	nIndex ;
	__int64	nFreq ;
} TEMP_ARRAY, *PTEMP_ARRAY ;

class CLXWord
{
public:
	CLXWord(void);
public:
	~CLXWord(void);

private:
	PLX_ITEM	pLXItem ;		// ���������ֵ�ԭʼ����

public:
	// ���������ֵ�
	BOOL	LX_LoadDic ( LPSTR lpDicName ) ;
	// ����������
	BOOL	LX_SearchWord ( LPWSTR lpWord, LPWSTR lpLXWord, UINT &nWordNum ) ;
	// ���������Ӵ�С����
	friend int SortCmp ( const void* a, const void* b ) ;

private:
	// �ַ���ת��
	inline BOOL		LX_BTW ( LPSTR lpSrc, LPWSTR lpDst ) ;
	inline BOOL		LX_WTB ( LPWSTR lpSrc, LPSTR lpDst ) ;
};
