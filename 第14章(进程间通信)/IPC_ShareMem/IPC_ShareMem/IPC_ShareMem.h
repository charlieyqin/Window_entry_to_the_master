// IPC_ShareMem.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIPC_ShareMemApp:
// �йش����ʵ�֣������ IPC_ShareMem.cpp
//

class CIPC_ShareMemApp : public CWinApp
{
public:
	CIPC_ShareMemApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIPC_ShareMemApp theApp;