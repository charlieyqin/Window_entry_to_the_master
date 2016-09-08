// DefSingleView.h : CDefSingleView ��Ľӿ�
//


#pragma once


class CDefSingleView : public CView
{
protected: // �������л�����
	CDefSingleView();
	DECLARE_DYNCREATE(CDefSingleView)

// ����
public:
	CDefSingleDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CDefSingleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DefSingleView.cpp �еĵ��԰汾
inline CDefSingleDoc* CDefSingleView::GetDocument() const
   { return reinterpret_cast<CDefSingleDoc*>(m_pDocument); }
#endif

