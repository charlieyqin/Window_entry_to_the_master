// IPC_Mailslot.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIPC_MailslotApp:
// �йش����ʵ�֣������ IPC_Mailslot.cpp
//

class CIPC_MailslotApp : public CWinApp
{
public:
	CIPC_MailslotApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIPC_MailslotApp theApp;