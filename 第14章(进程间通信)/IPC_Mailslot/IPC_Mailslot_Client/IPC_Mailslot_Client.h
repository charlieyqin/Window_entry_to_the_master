// IPC_Mailslot_Client.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIPC_Mailslot_ClientApp:
// �йش����ʵ�֣������ IPC_Mailslot_Client.cpp
//

class CIPC_Mailslot_ClientApp : public CWinApp
{
public:
	CIPC_Mailslot_ClientApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIPC_Mailslot_ClientApp theApp;