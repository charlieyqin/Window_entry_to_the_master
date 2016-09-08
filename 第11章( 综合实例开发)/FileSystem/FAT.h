#ifndef _FAT_H
#define _FAT_H

#include "Info.h"

class CFAT {
public:
	UINT	nCluPos ;	// ������Ŀ��дغ�
	LPVOID	lpBase ;	// �ļ�ϵͳӳ�����ַ

public:
	CFAT	() ;
	~CFAT	();

	// ȡ��һ�����д�
	UINT	GetIdleCluster	();

	// ����ָ����Ϊ����
	void	SetIdleCluster	( UINT nCluIndex ) ;

	// ȡ��ָ���صĺ�̴�
	UINT	GetNextCluster	( UINT nCluIndex ) ;
	
	// ����ָ���صĺ�̴�
	void	SetNextCluster	( UINT nCluIndex, UINT nNewClundex ) ;

public:
	// ȡ��ָ���صĵ�ַ
	UINT	GetAddByIndex	( UINT nCluIndex ) ;

	// ȡ��ָ���صı�ʶ��ַ������FAT�е�λ�ã�
	UINT	GetCluPointer	( UINT nCluIndex ) ;

	// �жϸô��Ƿ�Ϊβ�ؿɣ����޺�̴أ�
	BOOL	IsTailCluster	( UINT nCluIndex ) ;

	// ȡ��ָ��·����Ŀ¼��
	UINT	GetCluIndexByPathName ( LPSTR lpPathName ) ;
};

#endif