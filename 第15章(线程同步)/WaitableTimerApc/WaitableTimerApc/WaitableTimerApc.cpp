// WaitableTimerApc.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <iostream>
using namespace std;

#define REPEAT_COUNTS	5

// �ȴ���ʱ���������
VOID CALLBACK TimerAPCProc( LPVOID lpArg, DWORD dwTimerLowValue, DWORD dwTimerHighValue )
{
	DWORD dwIndex = *((DWORD*)lpArg) ;
	cout << "��" << dwIndex << "�α�ʱ��" << endl ;
}

void main( void ) 
{
	// �����ȴ���ʱ��
	HANDLE hTimer = CreateWaitableTimer ( NULL, FALSE, NULL ) ;
	if ( hTimer == NULL )
		return ;

	// ��һ�α�ʱ��5S���Ժ�ÿ��1S��ʱ1��
	LARGE_INTEGER   liDueTime;
	liDueTime.QuadPart  = -50000000 ;
	
	// ���õȴ���ʱ��
	DWORD dwParam = 1 ;
	if ( SetWaitableTimer ( hTimer, &liDueTime, 1000, TimerAPCProc, &dwParam, FALSE ) )
	{
		cout << "�ȴ�5S��ʼ��ʱ����" << endl ;
		for ( int i = 0; i < REPEAT_COUNTS; i++, dwParam++ )
		{
			// ����ɱ�ȴ�״̬
			SleepEx ( INFINITE, TRUE ) ;
		}
	} 

	// ȡ���ȴ���ʱ��
	CancelWaitableTimer ( hTimer ) ;
	CloseHandle( hTimer );
	return ;
}

