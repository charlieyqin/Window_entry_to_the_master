// CreateThreadSample.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "windows.h"

//DWORD WINAPI NewThread ( LPVOID lpParam )
//{
//	// ȡ�ù����̱߳�ʶ
//	UINT nThreadId = *((UINT*)lpParam ) ;
//
//	// ���ݲ�ͬ�ı�ʶ����ͬ�����ݻ�������
//	switch ( nThreadId )
//	{
//	case 0:	{ /*����0�����ݻ�����*/	} break ;
//	case 1:	{ /*����1�����ݻ�����*/	} break ;
//	case 2:	{ /*����2�����ݻ�����*/	} break ;
//	// ����
//	}
//	return 0 ;
//}
//
//VOID CreateNewThread ()
//{
//	const UINT WORK_THREAD_NUM = 4 ;			// ���幤���̵߳�����
//	DWORD dwProcessId[WORK_THREAD_NUM] = {0} ;	// �����洢�߳�ID
//
//	for ( UINT i = 0; i < WORK_THREAD_NUM; i++ )
//		CreateThread ( NULL, 0, NewThread, &i, 0, &dwProcessId[i] ) ;
//}

typedef struct _CLIENT_INFO {
	// ����
} CLIENT_INFO, *PCLIENT_INFO ;

DWORD WINAPI NewThread ( LPVOID lpParam )
{
	// ȡ�ÿͻ���Ϣ�ṹ
	PCLIENT_INFO pClientInfo = (PCLIENT_INFO)lpParam ;

	// ����ͻ�����
	return 0 ;
}

VOID Server ()
{
	// ���ϵؽ��ܿͻ�������
	while ( TRUE )
	{
		// ���ÿͻ���Ϣ�ṹ��ʡ�Զ�ClientInfo�ṹ�����
		CLIENT_INFO ClientInfo ;

		// ���������̴߳���ͻ�������
		CreateThread ( NULL, 0, NewThread, &ClientInfo, 0, NULL ) ;
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

