// NoModalDlg_MFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNoModalDlg_MFCApp:
// �йش����ʵ�֣������ NoModalDlg_MFC.cpp
//

class CNoModalDlg_MFCApp : public CWinApp
{
public:
	CNoModalDlg_MFCApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNoModalDlg_MFCApp theApp;