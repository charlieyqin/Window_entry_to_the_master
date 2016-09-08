#ifndef _INFO_H
#define _INFO_H

#define SYSTEM_SPACE_NAME		"FileSystem"		// ָ���ļ�ϵͳ������
#define CLUSTER_SIZE			4096				// ָ��ÿ���صĴ�С�����ֽ�Ϊ��λ��
#define DEFAULT_SYSTEM_SPACE	( 256 * 1024 * 1024 ) // ָ���ļ�ϵͳ�Ĵ�С�����ֽ�Ϊ��λ��
#define FIRST_VALID_CLUSTER		33				// ָ���׸����ôصĴغ�
#define FAT_BIT16				2				// ָ��FAT���ͺ�Ϊλ
#define MAX_PATH_LENGTH			512				// �������·��������
#define MAX_DIR_ITEM_IN_PAGE	128				//ÿ���ļ��е�Ŀ¼�����128��
#define DIRECTORY_ITEM_SIZE		32				// �����ļ�Ŀ¼��ṹ�Ĵ�С
#define MAX_FILE_NAME_LEN		8				// ��������ļ�������
#define USER_INFO_SIZE			32				// �����û���Ϣ�ṹ�Ĵ�С
#define MAX_USER_NAME_LEN		12				// ��������û�������
#define MAX_USER_PWD_LEN		12				// ����������볤��

// �����ļ�ϵͳ��ӳ��ṹ
typedef struct {
	HANDLE	hFile ;				// �ļ����
	HANDLE	hMapFile ;			// �ں˾��
	LPVOID	lpFileMapping ;		// ӳ�����ַ
} SYSTEM_HANDLE ;

// �����ļ�Ŀ¼��ṹ
typedef struct _DIRECTORY_ITEM{
	BYTE	szFileName[8] ;		// �ļ���
	BYTE	szFileExt[3] ;		// ��չ��
	BYTE	bAttribute ;		// 0:ֻ����1����д�� 2��Ŀ¼
	unsigned short	nStartClu ;	// ��ʼ��
	UINT	nFileSize ;			// �ļ���С���ֽڣ�
	BYTE	szUserName[12] ;	// �����û�
	BYTE	bReserve[2] ;		// ����
} DIRECTORY_ITEM ;
typedef DIRECTORY_ITEM*	PDIRECTORY_ITEM ;

// �����û���Ϣ�ṹ
typedef struct _USER_INFO{
	BYTE	szUserName[12] ;	// �û���
	BYTE	szUserPwd[12] ;		// ����
	BYTE	bReserve[8] ;		// ����
} USER_INFO ;
typedef USER_INFO* PUSER_INFO ;

#endif