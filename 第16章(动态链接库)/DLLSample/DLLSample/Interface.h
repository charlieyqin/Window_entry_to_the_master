#pragma once 


#ifndef _EXPORT
#define VARABLE_EXPORT	extern "C" __declspec(dllimport)
#define FUNCTION_EXPORT extern "C" __declspec(dllimport)
#define CLASS_DECLARE	__declspec(dllimport)
#else 
#define VARABLE_EXPORT	extern "C" __declspec(dllexport)
#define FUNCTION_EXPORT extern "C" __declspec(dllexport)
#define CLASS_DECLARE	__declspec(dllexport)
#endif

typedef struct _POSITION {
	int x ;
	int y ;
} POSITION, *PPOSITION ;

// ���嵼������
VARABLE_EXPORT int		value ;	// ������ͨ����
VARABLE_EXPORT POSITION	pos ;	// �����ṹ�����

// ���嵼������
FUNCTION_EXPORT int FUN_Add ( int a, int b ) ;
FUNCTION_EXPORT int FUN_Mul ( int a, int b ) ;

// ���嵼����
// ����CPreson��
class CLASS_DECLARE CPerson {
private:
	char	szName[128] ;
	int		age ;
public:
	CPerson() ;
	~CPerson() ;
	CPerson ( char* lpName, int nAge ) ;
public:
	char* GetName () ;
	int GetAge () ;
} ;