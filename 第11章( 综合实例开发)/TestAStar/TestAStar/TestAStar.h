// TestAStar.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestAStarApp:
// �йش����ʵ�֣������ TestAStar.cpp
//

class CTestAStarApp : public CWinApp
{
public:
	CTestAStarApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestAStarApp theApp;