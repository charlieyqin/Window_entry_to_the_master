// ColorDlg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CColorDlgApp:
// �йش����ʵ�֣������ ColorDlg.cpp
//

class CColorDlgApp : public CWinApp
{
public:
	CColorDlgApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CColorDlgApp theApp;