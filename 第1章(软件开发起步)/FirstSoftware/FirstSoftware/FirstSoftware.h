// FirstSoftware.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFirstSoftwareApp:
// �йش����ʵ�֣������ FirstSoftware.cpp
//

class CFirstSoftwareApp : public CWinApp
{
public:
	CFirstSoftwareApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFirstSoftwareApp theApp;