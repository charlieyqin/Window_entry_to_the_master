// DAOSample.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDAOSampleApp:
// �йش����ʵ�֣������ DAOSample.cpp
//

class CDAOSampleApp : public CWinApp
{
public:
	CDAOSampleApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDAOSampleApp theApp;