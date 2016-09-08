// book.h : CBook ���ʵ��



// CBook ʵ��

// ���������� 2007��12��15��, 19:29

#include "stdafx.h"
#include "book.h"
IMPLEMENT_DYNAMIC(CBook, CRecordset)

CBook::CBook(CDatabase* pdb)
	: CRecordset(pdb)
{
	column1 = 0;
	m_BookName = L"";
	m_Author = L"";
	m_Publish = L"";
	m_Price = 0;
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CBook::GetDefaultConnect()
{
	return _T("DSN=book;UID=Admin;") ;
	//return _T("DSN=book;DBQ=G:\\VC\x8f6f\x4ef6\x5f00\x53d1\\\x5b9e\x4f8b\x6e90\x7801\\\x7b2c11\x7ae0\\ODBCSample\\release\\book.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CBook::GetDefaultSQL()
{
	return _T("[book]");
}

void CBook::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[���]"), column1);
	RFX_Text(pFX, _T("[BookName]"), m_BookName);
	RFX_Text(pFX, _T("[Author]"), m_Author);
	RFX_Text(pFX, _T("[Publish]"), m_Publish);
	RFX_Long(pFX, _T("[Price]"), m_Price);

}
/////////////////////////////////////////////////////////////////////////////
// CBook ���

#ifdef _DEBUG
void CBook::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBook::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


