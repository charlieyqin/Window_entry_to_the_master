// DefSingleDoc.h : CDefSingleDoc ��Ľӿ�
//


#pragma once


class CDefSingleDoc : public CDocument
{
protected: // �������л�����
	CDefSingleDoc();
	DECLARE_DYNCREATE(CDefSingleDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CDefSingleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void SetTitle(LPCTSTR lpszTitle);
};


