// IDEACalu.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIDEACaluApp:
// �йش����ʵ�֣������ IDEACalu.cpp
//

class CIDEACaluApp : public CWinApp
{
public:
	CIDEACaluApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIDEACaluApp theApp;