// MediaPlay.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMediaPlayApp:
// �йش����ʵ�֣������ MediaPlay.cpp
//

class CMediaPlayApp : public CWinApp
{
public:
	CMediaPlayApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMediaPlayApp theApp;