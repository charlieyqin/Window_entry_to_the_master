// WaitableTimer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
	// �����ȴ���ʱ��
	HANDLE hTimer = CreateWaitableTimer(NULL, TRUE, NULL );
	if ( !hTimer )
	{
		cout << "�����ȴ���ʱ��ʧ�ܣ�(" << GetLastError() << ")" << endl ;
		return 0 ;
	}

	// ���õȴ���ʱ�������ʱ�䣬5S
	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart=-50000000;
	if ( !SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, 0) )
	{
		cout << "���õȴ���ʱ��ʧ�ܣ�(" << GetLastError() << ")" << endl ;
		return 0 ;
	}

	cout << "�ȴ�5�롭��" << endl ;

	// �ȴ�����
	if ( WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0 )
		cout << "�ȴ�ʧ�ܣ�(" << GetLastError() << ")" << endl ;
	else
		cout << "���ܵ��ȴ���ʱ���źţ�" << endl ;

	CloseHandle ( hTimer ) ;
	return 0;
}

