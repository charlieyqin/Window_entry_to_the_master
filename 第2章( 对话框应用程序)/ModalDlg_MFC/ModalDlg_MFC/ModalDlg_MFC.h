// ModalDlg_MFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CModalDlg_MFCApp:
// �йش����ʵ�֣������ ModalDlg_MFC.cpp
//

class CModalDlg_MFCApp : public CWinApp
{
public:
	CModalDlg_MFCApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CModalDlg_MFCApp theApp;