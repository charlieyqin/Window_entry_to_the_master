// DefMultipleView.h : CDefMultipleView ��Ľӿ�
//


#pragma once


class CDefMultipleView : public CView
{
protected: // �������л�����
	CDefMultipleView();
	DECLARE_DYNCREATE(CDefMultipleView)

// ����
public:
	CDefMultipleDoc* GetDocument() const;

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
	virtual ~CDefMultipleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DefMultipleView.cpp �еĵ��԰汾
inline CDefMultipleDoc* CDefMultipleView::GetDocument() const
   { return reinterpret_cast<CDefMultipleDoc*>(m_pDocument); }
#endif

