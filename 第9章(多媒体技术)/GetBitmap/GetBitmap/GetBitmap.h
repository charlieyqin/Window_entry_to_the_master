// GetBitmap.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGetBitmapApp:
// �йش����ʵ�֣������ GetBitmap.cpp
//

class CGetBitmapApp : public CWinApp
{
public:
	CGetBitmapApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGetBitmapApp theApp;