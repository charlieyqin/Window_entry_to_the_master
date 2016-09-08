// Semaphore.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <Windows.h>

#include <iostream>
using namespace std ;

#include "stdio.h"

#define DEF_DATA_SIZE		128
#define MAX_ACCESS_COUNT	3
#define MAX_THREAD_COUNT	5
#define SEMPHORE_NAME		L"TestSemphore"

BYTE data[DEF_DATA_SIZE] ;

DWORD WINAPI WorkThread ( LPVOID lParam )
{
	// ȡ���߳�������
	DWORD dwIndex = *((DWORD*)lParam) ;

	// ���ű��ں˶���
	HANDLE hSem = OpenSemaphore ( SEMAPHORE_ALL_ACCESS, FALSE, SEMPHORE_NAME ) ;
	if ( hSem )
	{
		// �ȴ��ű���Դ
		printf ( "[%d]�ȴ��ű���Դ\n", dwIndex ) ;
		if ( WaitForSingleObject ( hSem, INFINITE ) == WAIT_OBJECT_0 )
		{
			printf ( "[%d]ȡ���ű���Դ�����Է������ݣ�\n", dwIndex ) ;

			// ��������߳�ȡ�����ݷ���Ȩ�������������data��Ҫ3Sʱ��
			// ����
			Sleep ( 3000 ) ;
		}

		// �ͷ��ű���Դ
		printf ( "[%d]�ͷ��ű���Դ��\n", dwIndex ) ;
		ReleaseSemaphore ( hSem, 1, NULL ) ;
		CloseHandle ( hSem ) ;
	}
	else
	{
		printf ( "[%d]�޷����ű��ں˶���\n", dwIndex ) ;
	}
	return 0 ;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// ��ʼ������
	for ( BYTE i = 0; i < DEF_DATA_SIZE; i++ )
		data[i] = i ;

	// �����ű��ں˶���
	HANDLE hSem = CreateSemaphore ( NULL, 0, MAX_ACCESS_COUNT, SEMPHORE_NAME ) ;
	if ( hSem == NULL )
		return 0;

	// ���������߳�
	DWORD	dwIndex[MAX_THREAD_COUNT] = {0} ;
	HANDLE	hThread[MAX_THREAD_COUNT] = {0} ;
	for ( int i = 0; i < MAX_THREAD_COUNT; i++ )
	{
		dwIndex[i] = i + 1 ;
		hThread[i] = CreateThread ( NULL, 0, WorkThread, &dwIndex[i], 0, NULL ) ;
		if ( hThread[i] == NULL )
			return 0 ;
	}

	// Sleepһ��ʱ�䣬ʹ���������̶߳����ھ���״̬
	// ��ʹ���й����̶߳����ڵȴ��ű���Դ��״̬
	Sleep ( 2000 ) ;

	// �����ź�����������߳�
	printf ( "�����ź�����������߳�\n" ) ;
	ReleaseSemaphore ( hSem, MAX_ACCESS_COUNT, NULL ) ;

	// �ȴ��߳̽���
	WaitForMultipleObjects ( MAX_THREAD_COUNT, hThread, TRUE, INFINITE ) ;
	printf ( "�����̶߳��Ѿ�������\n" ) ;

	for ( int i = 0; i < MAX_THREAD_COUNT; i++ )
		CloseHandle ( hThread[i] ) ;
	CloseHandle ( hSem ) ;
	return 0;
}

