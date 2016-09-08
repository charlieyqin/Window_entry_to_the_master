#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "Info.h"
#include "DirManager.h"
#include "FAT.h"

class CSystem {
public:
	LPSTR			lpCurUser ;		// ��ǰ��½���û���
	SYSTEM_HANDLE	SysHandle ;		// ӳ��ṹ
	CDirManager		DirManager ;	// Ŀ¼�����
	CFAT			FATManager ;	// FAT����

public:
	// ����/��������
	CSystem () {}
	~CSystem () {}

	// ��װ�ļ�ϵͳ
	BOOL	SysInstall		() ;

	// ж���ļ�ϵͳ
	BOOL	SysUnstall		() ;

	// ��ʼ���ļ�ϵͳ
	BOOL	SysInitial		() ;

	// ȡ���û���Ϣ��������ö���û���Ϣ��
	UINT	SysGetUserInfo	( PUSER_INFO pItem, UINT nCurAddr ) ;

	// ����û��Ƿ����
	BOOL	SysIsUserExist	( LPSTR lpUserName ) ;

	// ����½��Ϣ�Ƿ�Ϸ�
	BOOL	SysCheckLogInfo	( LPSTR lpUserName, LPSTR lpUserPwd ) ;

	// ����û�
	BOOL	SysAddUserInfo	( LPSTR lpUserName, LPSTR lpUserPwd ) ;

	// ɾ��ָ�����û�
	BOOL	SysDeleteUser	( LPSTR lpUserName ) ;

	// ��⵱ǰ��½�û���Ȩ��
	BOOL	SysCheckUserPow	( LPSTR lpPath, LPSTR lpName ) ;

	// ö��ָ��Ŀ¼
	UINT	SysFirstEnumDir	( LPSTR lpPath, PDIRECTORY_ITEM pItem ) ;
	UINT	SysNextEnumDir	( UINT nCurAddr, PDIRECTORY_ITEM pItem ) ;

	// �����ָ��Ŀ¼�µ��ļ��Ƿ����
	BOOL	SysIsFileExist	( LPSTR lpPath, LPSTR lpName ) ;

	// �������ļ�
	BOOL	SysCreateFile	( LPSTR lpPath, LPSTR lpName, LPSTR lpExt, LPSTR lpContent ) ;

	// ɾ��ָ���ļ�
	BOOL	SysDeleteFile	( LPSTR lpPath, LPSTR lpName ) ;
	
	// ��ȡָ���ļ�������
	CString SysReadFile		( LPSTR lpPath, LPSTR lpName ) ;

	// ������Ŀ¼
	BOOL	SysCreateSubDir	( LPSTR lpPath, LPSTR lpSubDirName ) ;
	
	// ɾ����Ŀ¼
	BOOL	SysDeleteSubDir	( LPSTR lpPath, LPSTR lpSubDirName ) ;

	// �ͼ���ʽ��
	BOOL	SysLowFormat	() ;
	
	// �߼���ʽ��
	BOOL	SysHighFormat	() ;

public:
	// �����ļ�ϵͳ�ڴ�ӳ��
	BOOL	SysCreateMap	( DWORD dwCreateFlag ) ;
	
	// ɾ���ļ�ϵͳ���ڴ�ӳ��
	void	SysDeleteMap	() ;

	// ˢ��ӳ�����ݵ������ļ�
	BOOL	SysFlushData	( LPVOID lpAddr, UINT nNumToFlush ) ;
} ;

#endif