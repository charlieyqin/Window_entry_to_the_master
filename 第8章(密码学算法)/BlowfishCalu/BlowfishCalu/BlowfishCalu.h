// BlowfishCalu.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBlowfishCaluApp:
// �йش����ʵ�֣������ BlowfishCalu.cpp
//

class CBlowfishCaluApp : public CWinApp
{
public:
	CBlowfishCaluApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBlowfishCaluApp theApp;