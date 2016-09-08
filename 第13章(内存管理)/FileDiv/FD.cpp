// FD.cpp: implementation of the CFD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "File Divide.h"
#include "FD.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAX_BUF_SIZE 1024

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFD::CFD()
{

}

CFD::~CFD()
{

}

DWORD CFD::FDFileDivide	( PFILE_ITEM_INFO pItem )
{
	// ɾ�����ļ�ԭ�еķֿ��ļ�
	this->DeleteAllPartFiles ( pItem->szFileName ) ;

	// ������Ϣ�ļ�
	HANDLE hFile = CreateFile ( pItem->szFileName + ".INFO", GENERIC_READ|GENERIC_WRITE,\
		FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL ) ;
	if ( hFile == INVALID_HANDLE_VALUE )
		return GetLastError() ;
	else
	{
		// д����Ϣ�ļ�
		DWORD dwWriteByte ;
		WriteFile ( hFile, &(pItem->dwLowFileSize),	sizeof(DWORD),	&dwWriteByte, NULL ) ;
		WriteFile ( hFile, &(pItem->dwPartSize),	sizeof(DWORD),	&dwWriteByte, NULL ) ;
		WriteFile ( hFile, &(pItem->dwPartNum),		sizeof(DWORD),	&dwWriteByte, NULL ) ;
		CloseHandle ( hFile ) ;
	}

	// ��Ŀ���ļ�
	hFile = CreateFile ( pItem->szFileName,GENERIC_READ, 
		FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL ) ;
	if ( hFile == INVALID_HANDLE_VALUE )
		return GetLastError() ;

	// �����ļ��ڴ�ӳ���ں˶���
	HANDLE hMapFile = CreateFileMapping(hFile,NULL,PAGE_READONLY,0,0,NULL ) ;
	if ( hMapFile == NULL )
	{
		CloseHandle ( hFile ) ;
		return GetLastError() ;
	}

	CString TempStr ;
	DWORD	dwCurAddr = 0, dwCurPart = 0 ;
	LPVOID lpMapAddr = 0 ;

	// �ֿ�ѭ��ӳ���ļ�
	for ( UINT i = 1; i <= pItem->dwPartNum; i++ )
	{
		dwCurPart = pItem->dwLowFileSize - dwCurAddr ;
		if ( dwCurPart > pItem->dwPartSize )
			dwCurPart = pItem->dwPartSize ;

		lpMapAddr = MapViewOfFile ( hMapFile, FILE_MAP_READ, 0, dwCurAddr, dwCurPart ) ;
		if ( lpMapAddr == NULL )
		{
			CloseHandle ( hMapFile ) ;
			CloseHandle ( hFile ) ;
			return GetLastError() ;
		}

		dwCurAddr += dwCurPart ;

		TempStr.Format ( "%s.PART_%d", pItem->szFileName, i ) ;
		DeleteFile ( TempStr ) ;
		
		// �������ļ�
		HANDLE hNewFile = CreateFile (TempStr,GENERIC_READ|GENERIC_WRITE, \
			FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL ) ;
		if ( hFile == INVALID_HANDLE_VALUE )
			return GetLastError() ;
		
		HANDLE hNewMapFile = CreateFileMapping ( hNewFile,NULL,PAGE_READWRITE,0,dwCurPart,NULL ) ;
		if ( hNewMapFile == NULL )
		{
			CloseHandle ( hNewFile ) ;
			return GetLastError() ;
		}

		LPVOID lpNewMapAddr = MapViewOfFile ( hNewMapFile, FILE_MAP_WRITE, 0, 0, 0 ) ;
		if ( lpMapAddr == NULL )
		{
			CloseHandle ( hNewMapFile ) ;
			CloseHandle ( hNewFile ) ;
			return GetLastError() ;
		}

		// ������д�뵽���ļ�
		memcpy ( lpNewMapAddr, lpMapAddr, dwCurPart ) ;
		
		UnmapViewOfFile ( lpMapAddr ) ;
		UnmapViewOfFile ( lpNewMapAddr ) ;
		CloseHandle ( hNewMapFile ) ;
		CloseHandle ( hNewFile ) ;
	}

	CloseHandle ( hMapFile ) ;
	CloseHandle ( hFile ) ;
	return 0 ;
}

DWORD CFD::FDFileConnect	( PFILE_ITEM_INFO pItem )
{
	DeleteFile ( pItem->szFileName ) ;

	// ��Ŀ���ļ�
	HANDLE hFile = CreateFile (pItem->szFileName, GENERIC_READ|GENERIC_WRITE, \
		FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL ) ;
	if ( hFile == INVALID_HANDLE_VALUE )
		return GetLastError() ;

	// �����ļ��ڴ�ӳ���ں˶���
	HANDLE hMapFile = CreateFileMapping(hFile,NULL,PAGE_READWRITE,0,pItem->dwLowFileSize,NULL) ;
	if ( hMapFile == NULL )
	{
		CloseHandle ( hFile ) ;
		return GetLastError() ;
	}

	CString TempStr ;
	DWORD	dwCurAddr = 0, dwCurPart = 0 ;
	LPVOID lpMapAddr = 0 ;

	// �ֿ�ѭ��ӳ���ļ�
	for ( UINT i = 1; i <= pItem->dwPartNum; i++ )
	{
		dwCurPart = pItem->dwLowFileSize - dwCurAddr ;
		if ( dwCurPart > pItem->dwPartSize )
			dwCurPart = pItem->dwPartSize ;

		lpMapAddr = MapViewOfFile ( hMapFile, FILE_MAP_WRITE, 0, dwCurAddr, dwCurPart ) ;
		if ( lpMapAddr == NULL )
		{
			CloseHandle ( hMapFile ) ;
			CloseHandle ( hFile ) ;
			return GetLastError() ;
		}

		dwCurAddr += dwCurPart ;

		TempStr.Format ( "%s.PART_%d", pItem->szFileName, i ) ;
		
		// �����ļ����������ڴ�ӳ��
		HANDLE hNewFile = CreateFile ( TempStr,GENERIC_READ, \
			FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL ) ;
		if ( hFile == INVALID_HANDLE_VALUE )
		{
			UnmapViewOfFile ( lpMapAddr ) ;
			CloseHandle ( hMapFile ) ;
			CloseHandle ( hFile ) ;
			return GetLastError() ;
		}
		
		HANDLE hNewMapFile = CreateFileMapping (hNewFile,NULL,PAGE_READONLY,0,0,NULL ) ;
		if ( hNewMapFile == NULL )
		{	
			UnmapViewOfFile ( lpMapAddr ) ;
			CloseHandle ( hMapFile ) ;
			CloseHandle ( hFile ) ;
			CloseHandle ( hNewFile ) ;
			return GetLastError() ;
		}

		LPVOID lpNewMapAddr = MapViewOfFile ( hNewMapFile, FILE_MAP_READ, 0, 0, 0 ) ;
		if ( lpMapAddr == NULL )
		{	
			UnmapViewOfFile ( lpMapAddr ) ;
			CloseHandle ( hMapFile ) ;
			CloseHandle ( hFile ) ;
			CloseHandle ( hNewMapFile ) ;
			CloseHandle ( hNewFile ) ;
			return GetLastError() ;
		}

		memcpy ( lpMapAddr, lpNewMapAddr, dwCurPart ) ;
		FlushViewOfFile ( lpMapAddr, dwCurPart ) ;

		UnmapViewOfFile ( lpMapAddr ) ;
		UnmapViewOfFile ( lpNewMapAddr ) ;
		CloseHandle ( hNewMapFile ) ;
		CloseHandle ( hNewFile ) ;
	}

	CloseHandle ( hMapFile ) ;
	CloseHandle ( hFile ) ;

	// ɾ���������ļ�
	this->DeleteAllPartFiles ( pItem->szFileName ) ;

	return 0 ;
}

DWORD CFD::FDGenFileInfo	( CString szFileName, PFILE_ITEM_INFO pItem ) 
{
	HANDLE hFile = CreateFile ( 
		szFileName, 
		GENERIC_READ, 
		FILE_SHARE_READ|FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL ) ;
	if ( hFile == INVALID_HANDLE_VALUE )
		return GetLastError() ;

	pItem->szFileName = szFileName ;

	pItem->dwLowFileSize = GetFileSize ( hFile, &(pItem->dwHighFileSize) ) ;
	pItem->dwPartNum = pItem->dwLowFileSize / pItem->dwPartSize ;
	if ( pItem->dwLowFileSize % pItem->dwPartSize > 0 )
		pItem->dwPartNum += 1 ;

	CloseHandle ( hFile ) ;
	return 0 ;
}

DWORD CFD::FDGetFileInfo	( CString szFileName, PFILE_ITEM_INFO pItem )
{
	HANDLE hFile = CreateFile ( 
		szFileName, 
		GENERIC_READ, 
		FILE_SHARE_READ|FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL ) ;
	if ( hFile == INVALID_HANDLE_VALUE )
		return GetLastError() ;

	DWORD dwReadByte ;
	ReadFile ( hFile, &(pItem->dwLowFileSize),	sizeof(DWORD),	&dwReadByte, NULL ) ;
	ReadFile ( hFile, &(pItem->dwPartSize),		sizeof(DWORD),	&dwReadByte, NULL ) ;
	ReadFile ( hFile, &(pItem->dwPartNum),		sizeof(DWORD),	&dwReadByte, NULL ) ;

	pItem->szFileName = szFileName ;
	pItem->szFileName.SetAt ( pItem->szFileName.GetLength()-5, 0 ) ;

	CloseHandle ( hFile ) ;
	return 0 ;
}

void CFD::DeleteAllPartFiles ( CString szFileName ) 
{
	HANDLE hFile ;
	CString TempStr ;
	TempStr.Format ( "%s.INFO", szFileName ) ;
	DeleteFile ( TempStr ) ;

	for ( UINT i = 1; ;i++ )
	{
		TempStr.Format ( "%s.PART_%d", szFileName, i ) ;

		hFile = CreateFile ( 
			TempStr, 
			GENERIC_READ, 
			FILE_SHARE_READ|FILE_SHARE_WRITE, 
			NULL, 
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, 
			NULL ) ;
		if ( hFile == INVALID_HANDLE_VALUE )
			return ;
		
		CloseHandle ( hFile ) ;
		DeleteFile ( TempStr ) ;
	}
}