// ProgressCtrl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CProgressCtrlApp:
// �йش����ʵ�֣������ ProgressCtrl.cpp
//

class CProgressCtrlApp : public CWinApp
{
public:
	CProgressCtrlApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CProgressCtrlApp theApp;