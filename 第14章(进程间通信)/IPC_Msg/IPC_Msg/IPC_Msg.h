// IPC_Msg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIPC_MsgApp:
// �йش����ʵ�֣������ IPC_Msg.cpp
//

class CIPC_MsgApp : public CWinApp
{
public:
	CIPC_MsgApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIPC_MsgApp theApp;