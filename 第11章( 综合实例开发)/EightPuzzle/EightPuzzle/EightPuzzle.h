// EightPuzzle.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEightPuzzleApp:
// �йش����ʵ�֣������ EightPuzzle.cpp
//

class CEightPuzzleApp : public CWinApp
{
public:
	CEightPuzzleApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEightPuzzleApp theApp;