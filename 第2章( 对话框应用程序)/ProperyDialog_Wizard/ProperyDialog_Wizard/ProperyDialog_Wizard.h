// ProperyDialog_Wizard.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CProperyDialog_WizardApp:
// �йش����ʵ�֣������ ProperyDialog_Wizard.cpp
//

class CProperyDialog_WizardApp : public CWinApp
{
public:
	CProperyDialog_WizardApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CProperyDialog_WizardApp theApp;