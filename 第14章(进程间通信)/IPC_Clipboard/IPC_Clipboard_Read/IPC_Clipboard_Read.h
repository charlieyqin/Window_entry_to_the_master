// IPC_Clipboard_Read.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIPC_Clipboard_ReadApp:
// �йش����ʵ�֣������ IPC_Clipboard_Read.cpp
//

class CIPC_Clipboard_ReadApp : public CWinApp
{
public:
	CIPC_Clipboard_ReadApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIPC_Clipboard_ReadApp theApp;