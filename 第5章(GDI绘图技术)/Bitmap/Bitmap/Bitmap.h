// Bitmap.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBitmapApp:
// �йش����ʵ�֣������ Bitmap.cpp
//

class CBitmapApp : public CWinApp
{
public:
	CBitmapApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBitmapApp theApp;