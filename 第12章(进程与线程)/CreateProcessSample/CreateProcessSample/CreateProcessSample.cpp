
#include <windows.h>
#include <string.h>

// ��������
VOID CreateProcessSample1 ()
{
	WCHAR lpPath[] = L"notepad.exe" ;
	STARTUPINFO si = { sizeof(si) } ;
	PROCESS_INFORMATION pi ;
	BOOL bStatus = CreateProcess ( NULL, lpPath, NULL, NULL, FALSE, 0,NULL, NULL, &si, &pi ) ;
	if ( bStatus == FALSE )
	{
		MessageBox ( 0, L"CreateProcess error, notepad.exe", 0, 0 ) ;
		return ;
	}
}

// �����������
VOID CreateProcessSample2 ()
{
	WCHAR lpPath[] = L"notepad.exe" ;
	STARTUPINFO si = { sizeof(si) } ;
	PROCESS_INFORMATION pi ;
	// ����1��ʹ��CREATE_SUSPENDED�����������
	BOOL bStatus = CreateProcess ( NULL, lpPath, NULL, NULL, FALSE, CREATE_SUSPENDED,NULL, NULL, &si, &pi ) ;
	if ( bStatus == FALSE )
	{
		MessageBox ( 0, L"CreateProcess error, notepad.exe", 0, 0 ) ;
		return ;
	}

	// ����2����������ӽ��̽������ݴ����ģ��ע��Ȳ���
	// ����
	// ����3���ָ�ִ��
	ResumeThread ( pi.hThread ) ;
}

VOID CreateProcessSample3 ()
{
	STARTUPINFO si = { sizeof(si) } ;
	PROCESS_INFORMATION pi ;
	
	WCHAR lpPath[] = L"notepad.exe" ;
	LPVOID lpEnvironment = GetEnvironmentStrings() ;

	int len = wcslen ( (LPWSTR)lpEnvironment ) * 2 + 2;
	LPVOID lpNewEnvironment = GlobalAlloc ( GPTR, len ) ;
	memcpy ( lpNewEnvironment, lpEnvironment, len ) ;

	BOOL bStatus = CreateProcess ( NULL, lpPath, NULL, NULL, TRUE, 0,lpNewEnvironment, NULL, &si, &pi ) ;
	FreeEnvironmentStrings ( (LPWCH)lpEnvironment ) ;
	if ( bStatus == FALSE )
	{
		MessageBox ( 0, L"CreateProcess error, notepad.exe", 0, 0 ) ;
		return ;
	}
}

VOID CreateProcessSample4 ()
{
	WCHAR lpPath[] = L"notepad.exe" ;

	STARTUPINFO si = { sizeof(si) } ;
	// ����STARTF_USESHOWWINDOW��ǣ�ʹ��STARTUPINFO�ṹ��wShowWindow�ֶ���Ч
	si.dwFlags |= STARTF_USESHOWWINDOW ;	
	// ���ô��ڵ���ʾ��ʽ��SW_HIDE��ʾ���ط�ʽ
	si.wShowWindow = SW_HIDE ;

	PROCESS_INFORMATION pi ;
	BOOL bStatus = CreateProcess ( NULL, lpPath, NULL, NULL, FALSE, 0,NULL, NULL, &si, &pi ) ;
	if ( bStatus == FALSE )
	{
		MessageBox ( 0, L"CreateProcess error, notepad.exe", 0, 0 ) ;
		return ;
	}
}

int WINAPI WinMain (HINSTANCE hinstExe,HINSTANCE, PSTR pszCmdLine, int nCmdShow )
{

	return 0 ;
}
