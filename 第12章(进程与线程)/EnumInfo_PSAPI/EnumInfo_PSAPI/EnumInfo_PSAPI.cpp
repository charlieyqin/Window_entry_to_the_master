// EnumInfo_PSAPI.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <windows.h>

#include "psapi.h"
#pragma comment ( lib, "psapi.lib" )

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std ;

#define MAX_BUF_SIZE 1024

BOOL EnumProcessInformation ()
{
	ofstream fout ( "EnumInfo_psapi.txt" ) ;

    DWORD dwProcessId[1024], cbNeededProcess;
	// ö�ٽ���
    if ( !EnumProcesses( dwProcessId, sizeof(dwProcessId), &cbNeededProcess ) )
        return FALSE;

	// ö�ٽ�����Ϣ
    for ( unsigned int i = 0; i < ( cbNeededProcess/sizeof(DWORD) ); i++ )
	{
		char szProcessName[MAX_PATH] = "unknown";

		// ͨ������ID�򿪽���
		HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE, dwProcessId[i] );
		if ( hProcess != NULL )
		{	
			HMODULE hMods[MAX_BUF_SIZE] = {0} ;
			DWORD cbNeededModule = 0 ;
			char szModuleName[MAX_BUF_SIZE] = { 0 } ;
			PROCESS_MEMORY_COUNTERS ProcessMemCounters ;

			// ö�ٽ���ģ����Ϣ
			EnumProcessModules( hProcess, hMods, sizeof(hMods), &cbNeededModule ) ;
			// ȡ����ģ��ȫ����ÿ�����̵ĵ�һģ�鼴Ϊ������ģ�飬����ʹ��ANSI��
			::GetModuleFileNameExA ( hProcess, hMods[0], szModuleName, sizeof(szModuleName) ) ;
			// ȡ�ý��̵��ڴ�ʹ����Ϣ
			GetProcessMemoryInfo ( hProcess, &ProcessMemCounters, sizeof(ProcessMemCounters) ) ;

			// ������������Ϣ���ļ�
			fout << "ProcessId=" << dwProcessId[i] << " " << szModuleName << endl ;
			fout << '\t' << "PageFaultCount                 :" << \
				hex << setw(8) << ProcessMemCounters.PageFaultCount << endl ;
			fout << '\t' << "PeakWorkingSetSize             :" << \
				hex << setw(8) << ProcessMemCounters.PeakWorkingSetSize	<< endl ;
			fout << '\t' << "WorkingSetSize                 :" << \
				hex << setw(8) << ProcessMemCounters.WorkingSetSize << endl ;
			fout << '\t' << "QuotaPeakPagedPoolUsage        :" << \
				hex << setw(8) << ProcessMemCounters.QuotaPeakPagedPoolUsage << endl ;
			fout << '\t' << "QuotaPagedPoolUsage            :" << \
				hex << setw(8) << ProcessMemCounters.QuotaPagedPoolUsage << endl ;
			fout << '\t' << "QuotaPeakNonPagedPoolUsage     :" << \
				hex << setw(8) << ProcessMemCounters.QuotaPeakNonPagedPoolUsage	<< endl ;
			fout << '\t' << "QuotaNonPagedPoolUsage         :" << \
				hex << setw(8) << ProcessMemCounters.QuotaNonPagedPoolUsage	<< endl ;
			fout << '\t' << "PagefileUsage                  :" << \
				hex << setw(8) << ProcessMemCounters.PagefileUsage << endl ;
			fout << '\t' << "PeakPagefileUsage              :" << \
				hex << setw(8) << ProcessMemCounters.PeakPagefileUsage << endl ;

			// �رս��̾��
			CloseHandle( hProcess );
		}
	}

	// �ر��ļ���������
	fout.close() ;
	return TRUE ;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if ( EnumProcessInformation () == FALSE )
		cout << "Enum process information error!" << endl ;
	return 0;
}

