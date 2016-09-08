// EnumInfo_ToolHelp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <fstream>
using namespace std ;

#define MAX_BUF_SIZE 2048

// ö�����н�����Ϣ
BOOL EnumProcessInfo () ;
// ö�������߳�
BOOL EnumThreadInfo () ;

int _tmain( )
{
	if ( EnumProcessInfo () == FALSE )
	{
		cout << "EnumProcessInfo failed!" << endl ;
	}
	if ( EnumThreadInfo () == FALSE )
	{
		cout << "EnumThreadInfo failed!" << endl ;
	}
	return 0;
}

// ö��ϵͳ��ǰ���н�����Ϣ
// ������Ϣ���������Ŀ¼��EnumInfo_ToolHelp_process.txt
BOOL EnumProcessInfo()
{
	// ���������Ϣ�ṹ
	PROCESSENTRY32 pe32 = {sizeof(pe32)} ;

	// ����ϵͳ��ǰ���̿���
	HANDLE hProcessShot = CreateToolhelp32Snapshot ( TH32CS_SNAPPROCESS, 0 ) ;
	if ( hProcessShot == INVALID_HANDLE_VALUE )
		return FALSE ;

	// ���������Ϣ���ļ�
	ofstream fout ( "EnumInfo_ToolHelp_process.txt" ) ;

	// ѭ��ö�ٽ�����Ϣ
	char szBuf[MAX_BUF_SIZE] = {0} ;
	if ( Process32First ( hProcessShot, &pe32 ) )
	{
		do {
			memset ( szBuf, 0, sizeof(szBuf) ) ;
			// �ѿ��ַ��Ľ�����ת��ΪANSI�ַ���
			WideCharToMultiByte (CP_ACP, 0, pe32.szExeFile, wcslen(pe32.szExeFile), szBuf, sizeof(szBuf), NULL, NULL );
			
			fout << "Process: " << szBuf << endl ;
			fout << '\t' << "Usage           : " << pe32.cntUsage << endl ;
			fout << '\t' << "ProcessID       : " << pe32.th32ProcessID << endl ;
			fout << '\t' <<	"DefaultHeapID   : " << (ULONG_PTR)pe32.th32DefaultHeapID << endl ;
			fout << '\t' << "ModuleID        : " << pe32.th32ModuleID << endl ;
			fout << '\t' << "ThreadNum       : " << pe32.cntThreads	<< endl ;
			fout << '\t' << "ParentProcessID : " << pe32.th32ParentProcessID << endl ;
			fout << '\t' << "PriClassBase    : " << pe32.pcPriClassBase << endl ;
		}while ( Process32Next ( hProcessShot, &pe32 ) ) ;
	}

	fout.close () ;
	CloseHandle ( hProcessShot ) ;
	return TRUE ;
}

// ö��ϵͳ��ǰ�����߳���Ϣ
// ������Ϣ���������Ŀ¼��EnumInfo_ToolHelp_thread.txt
BOOL EnumThreadInfo ()
{
	// �����߳���Ϣ�ṹ
	THREADENTRY32 te32 = {sizeof(THREADENTRY32)} ;

	//����ϵͳ�߳̿���
	HANDLE hThreadSnap = CreateToolhelp32Snapshot ( TH32CS_SNAPTHREAD, 0 ) ;
	if ( hThreadSnap == INVALID_HANDLE_VALUE )
		return FALSE ;

	// ����߳���Ϣ���ļ�
	ofstream fout ( "EnumInfo_ToolHelp_thread.txt" ) ;

	// ѭ��ö���߳���Ϣ
	if ( Thread32First ( hThreadSnap, &te32 ) )
	{
		do{
			fout << "ThreadId : "   << te32.th32ThreadID << endl ;
			fout << '\t' << "OwnerProcessID : " << te32.th32OwnerProcessID << endl ;
			fout << '\t' << "Usage          : "	<< te32.cntUsage << endl ;
			fout << '\t' << "Delta Priority : " << te32.tpDeltaPri << endl ;
			fout << '\t' << "Base Priority  : " << te32.tpBasePri << endl ;
		}while ( Thread32Next ( hThreadSnap, &te32 ) ) ;
	}

	fout.close () ;
	CloseHandle ( hThreadSnap ) ;
	return TRUE ;
}