// SimMouseMsg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSimMouseMsgApp:
// �йش����ʵ�֣������ SimMouseMsg.cpp
//

class CSimMouseMsgApp : public CWinApp
{
public:
	CSimMouseMsgApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSimMouseMsgApp theApp;