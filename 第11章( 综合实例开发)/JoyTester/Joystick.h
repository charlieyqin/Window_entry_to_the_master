#pragma once

#include <windows.h>
#include <dinput.h>
#pragma comment ( lib, "dinput8.lib" )
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dxerr9.lib" )

// ֧���ֱ����������
#define JS_MAXNUM			8

class CJoystick
{
private:
	UINT					uDeviceNum ;	// �ֱ�����
	LPDIRECTINPUT8			lpDI ;			// Direct Input����
	LPDIRECTINPUTDEVICE8	lpDID[JS_MAXNUM] ;				// Direct Input�ֱ��豸����
	DIDEVICEINSTANCE		DIDeviceInstance[JS_MAXNUM] ;	// �ֱ��豸ʵ��

public:
	CJoystick(void);
public:
	~CJoystick(void);

public:
	// ��ʼ��DirectInput������DI�����ö�������豸
	bool	JS_Initial ( ) ;
	// ���������豸
	bool	JS_StartByIndex ( UINT uIndex, \
					HWND hwnd, bool bExclusive = false, bool bForeGround = true ) ;
	// ȡ�������豸����������
	bool	JS_GetStateByIndex ( UINT uIndex, DIJOYSTATE2* lpState ) ;
	// ֹͣ�����豸
	void	JS_StopByIndex ( UINT uIndex ) ;

public:
	UINT	JS_GetDeviceNum () ;

friend BOOL CALLBACK EnumDeviceProc ( LPCDIDEVICEINSTANCE lpddi, LPVOID lpRef ) ;
friend BOOL CALLBACK EnumObjectProc ( LPCDIDEVICEOBJECTINSTANCE lpddi, LPVOID lpRef ) ;
} ;

