// IPC_Clipboard.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIPC_ClipboardApp:
// �йش����ʵ�֣������ IPC_Clipboard.cpp
//

class CIPC_ClipboardApp : public CWinApp
{
public:
	CIPC_ClipboardApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIPC_ClipboardApp theApp;