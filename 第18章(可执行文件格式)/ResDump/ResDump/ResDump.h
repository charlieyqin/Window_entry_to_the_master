// ResDump.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CResDumpApp:
// �йش����ʵ�֣������ ResDump.cpp
//

class CResDumpApp : public CWinApp
{
public:
	CResDumpApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CResDumpApp theApp;