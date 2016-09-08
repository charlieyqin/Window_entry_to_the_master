// Mutex.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"



#include <windows.h>

#include <iostream>
using namespace std;

#define DEF_DATA_SIZE	1024			// �������ݴ�С
#define DEF_THREAD_NUM	30				// �����߳�����

// ���干������
typedef struct _SHARE_DATA {
	LONG	nCount ;					// ��������
	BYTE	data[DEF_DATA_SIZE] ;		// ������������
} SHARE_DATA ;
SHARE_DATA	ShareData = {0};

// ���廥�����
HANDLE	hMutex = NULL ;

// �����߳�
DWORD WINAPI WorkThread ( LPVOID lParam )
{
	for ( int i = 0; i < 100; i++ )
	{
		// ��ȡ�������
		WaitForSingleObject ( hMutex, INFINITE ) ;

		// ������������
		ShareData.nCount ++ ;
		for ( int i = 0; i < DEF_DATA_SIZE; i++ )
			ShareData.data[i] = (BYTE)lParam ;

		// �ͷŻ������
		ReleaseMutex ( hMutex ) ;
	}
	return 0 ;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// �����������
	hMutex = CreateMutex ( NULL, FALSE, NULL ) ;
	if ( hMutex == NULL )
	{
		cout << "�����������ʧ�ܣ�" << endl ;
		return 0 ;
	}

	int i = 0 ;
	HANDLE hThread[DEF_THREAD_NUM] = {0} ;
	// ��������߳�
	for ( i = 0; i < DEF_THREAD_NUM; i++ )
	{
		hThread[i] = CreateThread ( NULL, 0, WorkThread, (LPVOID)i, 0, NULL ) ;
		if ( hThread[i] == NULL )
		{
			cout << "�����߳�ʧ��" << endl ;
			break ;
		}
	}

	if ( i == DEF_THREAD_NUM )
	{
		// �ȴ������߳̽���
		WaitForMultipleObjects ( DEF_THREAD_NUM, hThread, TRUE, INFINITE ) ;
		cout << "count=" << ShareData.nCount << endl ;
	}

	// �ر������߳̾��
	for ( i = 0; i < DEF_THREAD_NUM; i++ )
	{
		if ( hThread[i] )
			CloseHandle ( hThread[i] ) ;
	}

	// ɾ���������
	CloseHandle ( hMutex ) ;
	return 0;
}


