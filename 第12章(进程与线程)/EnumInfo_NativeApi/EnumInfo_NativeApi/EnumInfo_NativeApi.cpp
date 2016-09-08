// EnumInfo_NativeApi.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <windows.h>

#include <stdio.h>
#include <iostream>
using namespace std ;

#include "MyNtdll.h"

#define DEF_BUF_SIZE	0x1000

PFNNtQuerySystemInformation NtQuerySystemInformation ;

// ����2��ȡ��NtQuerySystemInformation������ַ
BOOL Initial ()
{
	// ��⵱ǰ�������Ƿ����ntdll.dll
	HMODULE	hMod = GetModuleHandle ( L"ntdll.dll" ) ;
	if ( hMod == NULL )
	{
		// ��������ڣ���ʹ��LoadLibrary������
		hMod = LoadLibrary ( L"ntdll.dll" ) ;
		if ( hMod == NULL )
			return FALSE ;
	}

	// ȡ�ú�����ַ
	NtQuerySystemInformation = (PFNNtQuerySystemInformation)GetProcAddress ( hMod, "NtQuerySystemInformation" ) ;
	return TRUE ;
}

// ���������Ϣ
VOID DisplayProcessInformation ( LPBYTE lpBuf )
{	
	cout << "///////////////////////////////////////////////////////////////////////" << endl ;
	cout << "//                       Process Information                         //" << endl ;
	cout << "///////////////////////////////////////////////////////////////////////" << endl ;
	PSYSTEM_PROCESSES pSysProcess = (PSYSTEM_PROCESSES)lpBuf ;
	while ( TRUE )
	{
		cout << "ProcessName:" << '\t' ; 
		if ( pSysProcess->ProcessName.Buffer != NULL )
			printf ( "%30S", pSysProcess->ProcessName.Buffer ) ;
		cout << endl ;
		
		cout << "InheritedFromProcessId:\t\t" << pSysProcess->InheritedFromProcessId << endl ;
		cout << "ProcessId:\t\t\t" << pSysProcess->ProcessId << endl ;
		cout << "HandleCount:\t\t\t" << pSysProcess->HandleCount << endl ;
		cout << "ThreadCount:\t\t\t" << pSysProcess->ThreadCount << endl ;

		cout << "-------------------------------------------------------------------------" << endl ;
		if ( pSysProcess->NextEntryDelta == 0 )
			break ;
		pSysProcess = (PSYSTEM_PROCESSES)( (DWORD)pSysProcess + pSysProcess->NextEntryDelta ) ;
	}
}

// ����3��ö�ٽ�����Ϣ
VOID QuerySystemInformation ( SYSTEM_INFORMATION_CLASS SystemInformationClass )
{
	NTSTATUS	status ;
	UINT		nSize = DEF_BUF_SIZE ;
	LPBYTE		lpBuf = NULL ;

	// �������Ȳ���֪����Ҫ���ٿռ����洢������Ϣ
	// �������ѭ�����Է���
	while ( TRUE )
	{
		// ��̬����ռ䣬�����洢������Ϣ
		if ( ( lpBuf = new BYTE [ nSize ] ) == NULL )
		{
			cout << "Allocate memory failed!" << endl ;
			return ;
		}
		
		// ö�ٽ�����Ϣ
		status = NtQuerySystemInformation ( SystemInformationClass, lpBuf, nSize, 0 ) ;
		if ( !NT_SUCCESS(status) )
		{
			// ����Ƿ񷵻ػ�����������
			if ( status == STATUS_INFO_LENGTH_MISMATCH )
			{
				nSize += DEF_BUF_SIZE ;
				delete lpBuf ;
				continue ;
			}
			else
			{
				cout << "NtQuerySystemInformation ErrorCode=0x" << hex << status << endl ;
				return ;
			}
		}
		else
			break ;
	}

	// ���������Ϣ
	DisplayProcessInformation ( lpBuf ) ;
	delete lpBuf ;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if ( Initial() == FALSE )
	{
		cout << "Initial failed!" << endl ;
		return 0 ;
	}

	QuerySystemInformation ( SystemProcessesAndThreadsInformation ) ;

	cin.get() ;
	return 0;
}
