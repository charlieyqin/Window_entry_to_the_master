// ReserveAndSubmit.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CReserveAndSubmitApp:
// �йش����ʵ�֣������ ReserveAndSubmit.cpp
//

class CReserveAndSubmitApp : public CWinApp
{
public:
	CReserveAndSubmitApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CReserveAndSubmitApp theApp;