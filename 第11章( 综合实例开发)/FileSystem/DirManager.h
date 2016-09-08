#ifndef _DIR_MANAGER_H
#define _DIR_MANAGER_H

#include "Info.h"

class CDirManager {
public:
	LPVOID	lpBase ;
public:
	// ��ָ����Ŀ¼�������Ŀ¼��
	UINT AddDirectoryItem ( UINT nCluIndex, PDIRECTORY_ITEM pItem )
	{
		UINT nCurAddr = (UINT)lpBase + nCluIndex * CLUSTER_SIZE ;
		for ( UINT i = 0; i < MAX_DIR_ITEM_IN_PAGE; i++ )
		{
			if ( ((PBYTE)nCurAddr)[0] == 0xE5 || ((PBYTE)nCurAddr)[0] == 0 )
			{
				memcpy ( (LPVOID)nCurAddr, (LPVOID)pItem, DIRECTORY_ITEM_SIZE ) ;
				break ;
			}
			nCurAddr += DIRECTORY_ITEM_SIZE ;
		}
		return nCurAddr ;
	}

	// ��ָ����Ŀ¼����ɾ��ָ�����ļ�Ŀ¼�ͬʱ���Է��ظ�Ŀ¼�
	UINT DelDirectoryItem ( UINT nCluIndex, LPSTR lpDirName, PDIRECTORY_ITEM pItem = NULL )
	{
		UINT nCurAddr = (UINT)lpBase + nCluIndex * CLUSTER_SIZE ;
		for ( UINT i = 0; i < MAX_DIR_ITEM_IN_PAGE; i++ )
		{
			if ( memcmp ( (LPVOID)nCurAddr, lpDirName, strlen(lpDirName) ) == 0 )
			{
				if ( pItem != NULL )
					memcpy ( pItem, (LPVOID)nCurAddr, DIRECTORY_ITEM_SIZE ) ;
				((PBYTE)nCurAddr)[0] = 0xE5 ;
				break ;
			}
			nCurAddr += DIRECTORY_ITEM_SIZE ;
		}
		return nCurAddr ;
	}

	// ��ָ��Ŀ¼����ȡ���ļ�Ŀ¼��
	BOOL GetDirectoryItem ( UINT nCluIndex, LPSTR lpName, PDIRECTORY_ITEM pItem )
	{	
		UINT nCurAddr = (UINT)lpBase + nCluIndex * CLUSTER_SIZE ;
		for ( UINT i = 0; i < MAX_DIR_ITEM_IN_PAGE; i++ )
		{
			if ( memcmp ( (LPVOID)nCurAddr, lpName, strlen(lpName) ) == 0 )
			{
				memcpy ( pItem, (LPVOID)nCurAddr, DIRECTORY_ITEM_SIZE ) ;
				break ;
			}
			nCurAddr += DIRECTORY_ITEM_SIZE ;
		}
		return TRUE ;
	}

	// ����Ŀ¼���Ƿ������ļ�
	BOOL IsDirItemFile ( PDIRECTORY_ITEM pItem )
	{
		return ( pItem->bAttribute & 0x3 ) ? TRUE : FALSE ;
	}

	// ����Ŀ¼���Ƿ�������Ŀ¼
	BOOL IsDirItemDir ( PDIRECTORY_ITEM pItem ) 
	{
		return ( pItem->bAttribute & 0x4 ) ? TRUE : FALSE ;
	}
} ;

#endif