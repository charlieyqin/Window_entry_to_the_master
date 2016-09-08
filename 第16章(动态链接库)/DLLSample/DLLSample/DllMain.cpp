
#include  <windows.h>

#define _EXPORT
#include "Interface.h"

int			value ;
POSITION	pos ;

BOOL WINAPI DllMain ( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved )
{
    // �ֱ������֪ͨ
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
            // Ϊ�½��̳�ʼ����ֻ�ܽ���1��
            // �������ʧ���򷵻�FALSE
			value = 5 ;
			pos.x = 6 ;
			pos.y = 7 ;
            break;
        case DLL_THREAD_ATTACH:
            // ִ���̳߳�ʼ������
            break;
        case DLL_THREAD_DETACH:
            // ִ���߳��������
            break;
        case DLL_PROCESS_DETACH:
            // ִ���������
            break;
    }
    return TRUE;
}


int FUN_Add ( int a, int b )
{
	return a + b ;
}

int FUN_Mul ( int a, int b ) 
{
	return a * b ;
}

CPerson::CPerson ()
{
}

CPerson::~CPerson ()
{
}

CPerson::CPerson ( char* lpName, int nAge )
{
	this->age = nAge ;
	if ( lpName )
	{
		int len = strlen(lpName) ;
		if ( len >= 127 )
			len = 127 ;
		memcpy ( this->szName, lpName, len ) ;
		this->szName[len] = 0 ;
	}
}

char* CPerson::GetName ()
{
	return this->szName ;
}

int CPerson::GetAge ()
{
	return this->age ;
}