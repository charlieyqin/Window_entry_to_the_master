// VirtualMemory.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CVirtualMemoryApp:
// �йش����ʵ�֣������ VirtualMemory.cpp
//

class CVirtualMemoryApp : public CWinApp
{
public:
	CVirtualMemoryApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVirtualMemoryApp theApp;