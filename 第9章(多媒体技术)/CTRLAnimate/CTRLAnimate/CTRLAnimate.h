// CTRLAnimate.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCTRLAnimateApp:
// �йش����ʵ�֣������ CTRLAnimate.cpp
//

class CCTRLAnimateApp : public CWinApp
{
public:
	CCTRLAnimateApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCTRLAnimateApp theApp;