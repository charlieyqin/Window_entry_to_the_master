// NoModalDlg_win32.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNoModalDlg_win32App:
// �йش����ʵ�֣������ NoModalDlg_win32.cpp
//

class CNoModalDlg_win32App : public CWinApp
{
public:
	CNoModalDlg_win32App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNoModalDlg_win32App theApp;