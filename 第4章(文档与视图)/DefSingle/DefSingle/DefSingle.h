// DefSingle.h : DefSingle Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CDefSingleApp:
// �йش����ʵ�֣������ DefSingle.cpp
//

class CDefSingleApp : public CWinApp
{
public:
	CDefSingleApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDefSingleApp theApp;