// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <windows.h>
#include "..\\DLLSample\\Interface.h"

#include <iostream>
using namespace std ;

int _tmain(int argc, _TCHAR* argv[])
{
	// ���Ե�������
	cout << "value=" << value << endl ;
	cout << "pos=(" << pos.x << "," << pos.y << ")" << endl ;

	// ���Ե�������
	cout << "FUN_Add(5,6)=" << FUN_Add(5,6) << endl ;
	cout << "FUN_Mul(5,6)=" << FUN_Mul(5,6) << endl ;

	// ���Ե�����
	CPerson person ( "Zhang", 23 ) ;
	cout << "Name=" << person.GetName() << endl ;
	cout << "Age=" << person.GetAge() << endl ;

	cin.get() ;
	return 0;
}

