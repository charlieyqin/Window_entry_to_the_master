// PropertyDialog_MultiPage.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPropertyDialog_MultiPageApp:
// �йش����ʵ�֣������ PropertyDialog_MultiPage.cpp
//

class CPropertyDialog_MultiPageApp : public CWinApp
{
public:
	CPropertyDialog_MultiPageApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPropertyDialog_MultiPageApp theApp;