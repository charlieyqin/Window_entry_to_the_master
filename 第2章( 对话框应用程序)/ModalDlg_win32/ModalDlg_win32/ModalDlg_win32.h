// ModalDlg_win32.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CModalDlg_win32App:
// �йش����ʵ�֣������ ModalDlg_win32.cpp
//

class CModalDlg_win32App : public CWinApp
{
public:
	CModalDlg_win32App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CModalDlg_win32App theApp;