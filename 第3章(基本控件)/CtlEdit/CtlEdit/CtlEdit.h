// CtlEdit.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCtlEditApp:
// �йش����ʵ�֣������ CtlEdit.cpp
//

class CCtlEditApp : public CWinApp
{
public:
	CCtlEditApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCtlEditApp theApp;