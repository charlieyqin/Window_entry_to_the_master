// SimKeyMsg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSimKeyMsgApp:
// �йش����ʵ�֣������ SimKeyMsg.cpp
//

class CSimKeyMsgApp : public CWinApp
{
public:
	CSimKeyMsgApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSimKeyMsgApp theApp;