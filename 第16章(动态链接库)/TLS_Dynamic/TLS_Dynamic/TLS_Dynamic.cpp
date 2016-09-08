// TLS_Dynamic.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include <windows.h>
#include <iostream>
using namespace std ;

// ȫ�ֱ�������TLSʱ϶����ֵ
// Լ�������̶߳�ʹ��TLS�����ʱ϶
UINT	nTlsIndex = 0 ;

DWORD WINAPI NewThread ( LPVOID lParam )
{
	// �������߳�TLSֵ
	TlsSetValue ( nTlsIndex, (LPVOID)10 ) ;
	// ȡ�����߳�TLSֵ
	cout << "���߳�" << nTlsIndex << "��TLSʱ϶ֵΪ" << (DWORD)TlsGetValue(nTlsIndex ) << endl ;
	return 0 ;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// ��̬����TLSʱ϶
	nTlsIndex = TlsAlloc () ;
	if ( nTlsIndex != TLS_OUT_OF_INDEXES )
	{
		cout << "TLSʱ϶Ϊ" << nTlsIndex << endl ;

		// ���߳�TLSָ��ʱ϶��ֵ
		TlsSetValue ( nTlsIndex, (LPVOID)5 ) ;

		// �������߳�
		HANDLE hThread = CreateThread ( NULL, 0, NewThread, NULL, 0, NULL ) ;
		if ( hThread )
		{
			// �ȴ����߳̽���
			WaitForSingleObject ( hThread, INFINITE ) ;
			// ȡ�����߳�TLS��ֵ���۲��Ƿ񱻸ı�
			cout << "���߳�" << nTlsIndex << "��TLSʱ϶ֵΪ" << (DWORD)TlsGetValue(nTlsIndex ) << endl ;
		}

		// ��ʹ��ʱӦ���ͷ�TLSʱ϶
		TlsFree ( nTlsIndex ) ;
	}
	else
	{
		cout << "û�п��õ�TLSʱ϶��" << endl ;
	}

	cin.get () ;
	return 0;
}

