// DefMultipleDoc.h : CDefMultipleDoc ��Ľӿ�
//


#pragma once


class CDefMultipleDoc : public CDocument
{
protected: // �������л�����
	CDefMultipleDoc();
	DECLARE_DYNCREATE(CDefMultipleDoc)

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
	virtual ~CDefMultipleDoc();
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


