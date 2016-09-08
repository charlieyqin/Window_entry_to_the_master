// Event.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <windows.h>
#include <iostream>
using namespace std;

HANDLE hEvent[2] = {0} ;
HANDLE hThread[2] = {0} ;

// �߳�1
DWORD WINAPI FirstThread ( LPVOID lParam )
{
	// �ȴ��߳�2���¼�֪ͨ
	WaitForSingleObject ( hEvent[0], INFINITE ) ;

	// ���յ��߳�2���¼�֪ͨ����������
	// ����

	// ֪ͨ�߳�2����ǰ�������Ѿ��������
	SetEvent ( hEvent[1] ) ;
	return 0 ;
}

// �߳�2
DWORD WINAPI SecondThread ( LPVOID lParam )
{
	// ֪ͨ�߳�1��ʹ�俪ʼ����
	SetEvent ( hEvent[0] ) ;

	// �ȴ��߳�1�����Ľ���
	WaitForSingleObject ( hEvent[1], INFINITE ) ;

	// ���յ��߳�1���������֪ͨ
	// ����
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// �����ں��¼�����
	hEvent[0] = CreateEvent ( NULL, TRUE, FALSE, NULL ) ;
	hEvent[1] = CreateEvent ( NULL, TRUE, FALSE, NULL ) ;

	// �����߳�
	hThread[0] = CreateThread ( NULL, 0, FirstThread, NULL, 0, NULL ) ;
	hThread[1] = CreateThread ( NULL, 0, SecondThread, NULL, 0, NULL ) ;

	// �ȴ�2���߳̽���
	WaitForMultipleObjects ( 2, hThread, TRUE, INFINITE ) ;
	cout << "finish!" << endl ;

	CloseHandle ( hEvent[0] ) ;
	CloseHandle ( hEvent[1] ) ;
	CloseHandle ( hThread[0] ) ;
	CloseHandle ( hThread[1] ) ;
	return 0;
}

