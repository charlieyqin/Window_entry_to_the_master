// CHInputDemon.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCHInputDemonApp:
// �йش����ʵ�֣������ CHInputDemon.cpp
//

class CCHInputDemonApp : public CWinApp
{
public:
	CCHInputDemonApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCHInputDemonApp theApp;