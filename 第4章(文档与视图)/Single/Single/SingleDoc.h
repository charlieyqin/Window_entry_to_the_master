// SingleDoc.h : CSingleDoc ��Ľӿ�
//


#pragma once

#define MAX_X_NUM 80
#define MAX_Y_NUM 50

class CSingleDoc : public CDocument
{
protected: // �������л�����
	CSingleDoc();
	DECLARE_DYNCREATE(CSingleDoc)

// ����
public:

// ����
public:

// ��д
public:
//	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CSingleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

	
private:
	BOOL	grid[MAX_X_NUM][MAX_Y_NUM] ;

public:
	VOID	SetGrid ( int x, int y ) ;
	BOOL	GetGridStatus ( int x, int y ) ;
	VOID	ResetGrid () ;
public:
	virtual void SetTitle(LPCTSTR lpszTitle);
public:
	virtual BOOL OnNewDocument();
};


