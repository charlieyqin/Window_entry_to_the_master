

#pragma once

#ifndef _MOMORY_H
#include <memory.h>
#endif

#include "CList.h"

#define DEFAULT_PAGE_SIZE ( 2 << 16 )
const int MAX_HEAD_SIZE = 1500 ;

class HuffNode
{
private:
	BYTE		value ;		// ���ASCIIֵ
	UINT		nCount ;	// Ȩֵ��Ƶ��ͳ��
	bool 		isLeaf ;	// �Ƿ�Ҷ�ӽ��

public:
	HuffNode*	pLeft ;		// ָ��������
	HuffNode*	pRight ;	// ָ��������

public:
	// Ĭ�Ϲ��캯��
	HuffNode () ;
	// ���������������������
	HuffNode ( HuffNode* lc, HuffNode* rc ) ;
	// ����Ƿ�Ҷ�ӽ��
	bool IsLeafNode ()  ;
	// ȡ�ý��ASCIIֵ
	BYTE GetValue () ;
	// ȡ��Ȩֵ
	UINT GetCount () ;
	// ����ASCII
	void SetValue ( BYTE value  ) ;
	// ����Ȩֵ
	void SetCount ( UINT nCount ) ;
	// ��Ӽ���
	void AddCount ( ) ;
} ;


class CHuffSystem
{
public:
	CHuffSystem () ;
	~CHuffSystem () ;

private:
	CCList<HuffNode>	HuffList ;		// ����б�
	HuffNode*			root ;			// ������������

public:
	HuffNode*			Item ;			// �����Ϣ
	CString*			CodingInBinStr ;// �����ֽڱ��봮
	DWORD				dwHighFileSize ;// �ļ���/����ʱ�ļ���С��32λ
	DWORD				dwLowFileSize ;	// �ļ���/����ʱ�ļ���С��32λ

public:
	// �ַ�������
	CString TextHuffEncoding ( CString szText ) ;
	// �ַ�������
	PBYTE TextHuffDecoding ( CString szBinStr ) ;
	// �ļ�����
	bool FileHuffEncoding ( CString szFileName ) ;
	// �ļ�����
	bool FileHuffDecoding ( CString szFileName ) ;
	// �����ļ�ͷ
	UINT GenHuffFileHead ( HANDLE hFile ) ;

protected:
	// ��ʼ������
	void InitContext () ;
	// ͳ���ֽڳ���Ƶ��
	void GenFreqPair ( LPVOID lpByte, UINT nSize ) ;
	// ͳ���ļ��ֽڳ���Ƶ��
	bool GenFreqPairByFile ( CString szFileName ) ;
	// ����Huffman������
	HuffNode* BuildHuffTree () ;
	// ɾ��Huffman������
	void DeleteHuffTree ( HuffNode* SubTree );
	// ����ָ���������б���
	void GenHuffCoding ( HuffNode* root, CString code = "" );

protected:
	// �������
	CString HuffEncoding ( PBYTE pStr, UINT nStrLen );
	// �������
	PBYTE HuffDecoding ( CString szText, UINT uStrLen );
	// �ļ��������
	UINT HuffEncodingByFile ( HANDLE hTarFile, CString szFileName );
	// д�����ļ�
	bool WriteConToNewFile ( CString szFileName, BYTE pbNewFile[], DWORD dwNewFileSize, bool flag );

protected:
	// ����Ƶ������
	void BuildSortList();
	// ������������ز�����
	void InsertNodeInSort ( HuffNode NewNode );

public:
	// ���ֽڴ�ת��Ϊ�����ƴ�
	CString ConvertByteArrayToBinStr ( PBYTE pBeg, UINT nBits );
} ;
