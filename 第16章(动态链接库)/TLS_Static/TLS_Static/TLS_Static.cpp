// TLS_Static.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <Windows.h>
#include <iostream>
using namespace std ;

// ���徲̬TLSȫ�ֱ���
__declspec(thread) int value = 0 ;

DWORD WINAPI NewThread ( LPVOID lParam )
{
	// �������߳�valueΪ10������Ӱ�����߳�
	value = 10 ;
	// ȡ�����߳̾�̬TLS��ֵ
	cout << "���߳� value=" << value << endl ;
	return 0 ;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// �������߳̾�̬TLS��valueΪ5
	value = 5 ;
	// �������߳�
	HANDLE hThread = CreateThread ( NULL, 0, NewThread, NULL, 0, NULL ) ;
	if ( hThread )
	{
		// �ȴ�ֱ�����߳̽���
		WaitForSingleObject ( hThread, INFINITE ) ;
		// ȡ�����߳̾�̬TLS��ֵ
		cout << "���߳� value=" << value << endl ;
	}
	return 0;
}

