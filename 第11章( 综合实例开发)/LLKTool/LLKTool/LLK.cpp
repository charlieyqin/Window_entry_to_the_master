#include "StdAfx.h"
#include "LLK.h"

CLLK::CLLK()
{

}

CLLK::~CLLK()
{
	this->ScreenDC.DeleteDC () ;
}

BOOL CLLK::LLK_Initial ()
{
	// ����LLK��������
	strcpy ( this->szWindowTitle, "QQ��Ϸ - ��������ɫ��" ) ;

	// Ѱ��LLK����
	this->hWnd = FindWindowA ( NULL, szWindowTitle ) ;
	if ( hWnd == NULL )
		return FALSE;

	// ���ÿͻ���������
	RECT WindowRect ;
	GetWindowRect ( this->hWnd, &WindowRect ) ;
	this->dwClientPosX = WindowRect.left ;
	this->dwClientPosY = WindowRect.top ;

	// ����LLKͼ���������ƫ��
	this->dwStartOffsetX = 14 ;
	this->dwStartOffsetY = 181 ;

	// ����LLKͼ���С
	this->dwIconSizeX = 31 ;
	this->dwIconSizeY = 35 ;

	// ����LLK���������ͼ����Ŀ
	this->dwIconNumX = 19 ;
	this->dwIconNumY = 11 ;

	// ������ĻDC
	this->ScreenDC.DeleteDC () ;
	this->ScreenDC.CreateDC ( L"DISPLAY", NULL, NULL, NULL ) ;

	int i, j ;
	this->dwIconNum = 0 ;
	this->dwColorNum = 0 ;
	memset ( this->bValidIcon, 0, sizeof(bValidIcon) ) ;
	memset ( this->dwColorType, 0, sizeof(this->dwColorType) ) ;
	for ( i = 0; i < MAX_ICON_NUM*MAX_ICON_NUM; i++ )
		this->IconList[i].clear() ;

	// �����ڲ����ݽṹ
	POINT pt ;
	for ( i = 0; i < this->dwIconNumY; i++ )
	{
		for ( j = 0; j < this->dwIconNumX; j++ )
		{
			pt.x = j ;	pt.y = i ;
			// ���ָ���߼�����λ�õ�ͼ������
			DWORD dwIconType = this->LLK_GetSpecifyIconType ( &pt ) ;			
			if ( dwIconType == 0xFFFFFFFF )
				continue ;

			this->dwIconNum++ ;
			this->bValidIcon[i][j] = TRUE ;
			this->IconList[dwIconType].push_back ( pt ) ;
		}
	}

	return TRUE ;
}

BOOL CLLK::LLK_DelSpecifyPairs ( UINT nCount )
{
	int i ;
	for ( i = 0; i < nCount; i++ )
	{
		if ( this->LLK_FindPAIR () == FALSE )
			return FALSE ;
	}
	return TRUE ;
}

BOOL CLLK::LLK_FindPAIR ()
{
	if ( this->hWnd == NULL )
		return FALSE ;

	if ( this->dwIconNum == 0 )
		return TRUE ;
	
	// ö���ڽ�����
	for ( int i = 0; i < this->dwColorNum; i++ )
	{
		if ( this->IconList[i].empty() == TRUE )
			continue ;

		vector<POINT>::iterator p, q ;
		// ˫��ѭ����ÿ��������ԣ�����Ƿ���������
		for ( p = this->IconList[i].begin(); p != this->IconList[i].end(); p++ )
		{
			for ( q = p; q != this->IconList[i].end(); q++ )
			{
				if ( q == p )
					continue ;
				PAIR pair ( *p, *q ) ;
				if ( this->LLK_IsValidPair ( &pair ) )
				{
					// ����ȥ������ͼ��λ�ñ�Ϊ��
					this->bValidIcon[p->y][p->x] = FALSE ;
					this->bValidIcon[q->y][q->x] = FALSE ;
					// ��ȥͼ�꣬��ģ��������
					this->LLK_DeletePair ( &pair ) ;
					// ���ڽ�������ɾ�����
					this->IconList[i].erase ( q ) ;
					this->IconList[i].erase ( p ) ;
					// ������2
					this->dwIconNum -= 2 ;
					return TRUE ;
				}
			}
		}
	}

	return ( this->dwIconNum == 0 ) ? TRUE : FALSE ;
}

VOID CLLK::LLK_DeletePair ( LPPAIR lpPair )
{
	DWORD x, y ;
	x = this->dwClientPosX + this->dwStartOffsetX + lpPair->a.x * this->dwIconSizeX ;
	y = this->dwClientPosY + this->dwStartOffsetY + lpPair->a.y * this->dwIconSizeY ;
	SetCursorPos ( x, y ) ;
	mouse_event ( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 ) ;
	mouse_event ( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 ) ;

	x = this->dwClientPosX + this->dwStartOffsetX + lpPair->b.x * this->dwIconSizeX ;
	y = this->dwClientPosY + this->dwStartOffsetY + lpPair->b.y * this->dwIconSizeY ;
	SetCursorPos ( x, y ) ;
	mouse_event ( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 ) ;
	mouse_event ( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 ) ;
}

BOOL CLLK::LLK_IsValidPair ( LPPAIR lpPair )
{
	// �����Ƿ��غ�
	if ( lpPair->a.x == lpPair->b.x && lpPair->a.y == lpPair->b.y )
		return FALSE ;

	//
	// 0�ۣ����㴦��ͬһֱ��
	//
	BOOL isSameLine = FALSE ;
	if ( lpPair->a.x == lpPair->b.x || lpPair->a.y == lpPair->b.y )
	{
		isSameLine = TRUE ;
		if ( this->LLK_IsPairInlineValid ( lpPair ) == TRUE )
			return TRUE ;
	}

	//
	// 1�ۣ����㲻��ͬһֱ��
	//
	POINT a, b ;		// �����۵�
	a.x = lpPair->a.x ;	a.y = lpPair->b.y ;
	b.x = lpPair->b.x ;	b.y = lpPair->a.y ;
	if ( this->bValidIcon[a.y][a.x] == FALSE )
	{
		PAIR FirPair ( a, lpPair->a ) ;
		PAIR SecPair ( a, lpPair->b ) ;
		if ( this->LLK_IsPairInlineValid( &FirPair ) && \
			 this->LLK_IsPairInlineValid( &SecPair ) )
			 return TRUE ;
	}
	if ( this->bValidIcon[b.y][b.x] == FALSE )
	{
		PAIR FirPair ( b, lpPair->a ) ;
		PAIR SecPair ( b, lpPair->b ) ;
		if ( this->LLK_IsPairInlineValid( &FirPair ) && \
			 this->LLK_IsPairInlineValid( &SecPair ) )
			 return TRUE ;
	}

	//
	// 2�ۣ�����
	//
	int i, j, nMinA, nMaxA, nMinB, nMaxB, min, max ;
	this->LLK_GetValidRangeH ( lpPair->a, nMinA, nMaxA ) ;
	this->LLK_GetValidRangeH ( lpPair->b, nMinB, nMaxB ) ;
	min = nMinA > nMinB ? nMinA : nMinB ;
	max = nMaxA < nMaxB ? nMaxA : nMaxB ;
	if ( min <= max )
	{
		for ( j = min; j <= max; j++ )
		{
			if ( j == lpPair->a.x || j == lpPair->b.x )
				continue ;

			// �����۵㣨a��PairAͬ�У�b��PairBͬ�У�
			POINT a, b ;
			a.x = j ;	a.y = lpPair->a.y ;
			b.x = j ;	b.y = lpPair->b.y ;

			PAIR PairA ( lpPair->a, a ) ;
			PAIR PairB ( lpPair->b, b ) ;
			PAIR PairC ( a, b ) ;
			if ( this->bValidIcon[a.y][a.x] == FALSE && \
				 this->bValidIcon[b.y][b.x] == FALSE && \
				 this->LLK_IsPairInlineValid ( &PairA ) && \
				 this->LLK_IsPairInlineValid ( &PairB ) && \
				 this->LLK_IsPairInlineValid ( &PairC ) )
				 return TRUE ;
		}
	}

	// 2�ۣ�����
	this->LLK_GetValidRangeV ( lpPair->a, nMinA, nMaxA ) ;
	this->LLK_GetValidRangeV ( lpPair->b, nMinB, nMaxB ) ;
	min = nMinA > nMinB ? nMinA : nMinB ;
	max = nMaxA < nMaxB ? nMaxA : nMaxB ;
	if ( min <= max )
	{
		for ( i = min; i <= max; i++ )
		{
			if ( i == lpPair->a.y || i == lpPair->b.y )
				continue ;

			// �����۵㣨a��PairAͬ�У�b��PairBͬ�У�
			POINT a, b ;
			a.x = lpPair->a.x ;		a.y = i ;
			b.x = lpPair->b.x ;		b.y = i ;

			PAIR PairA ( lpPair->a, a ) ;
			PAIR PairB ( lpPair->b, b ) ;
			PAIR PairC ( a, b ) ;
			if ( this->bValidIcon[a.y][a.x] == FALSE && \
				 this->bValidIcon[b.y][b.x] == FALSE && \
				 this->LLK_IsPairInlineValid ( &PairA ) && \
				 this->LLK_IsPairInlineValid ( &PairB ) && \
				 this->LLK_IsPairInlineValid ( &PairC ) )
				 return TRUE ;
		}
	}

	return FALSE ;
}

DWORD CLLK::LLK_GetSpecifyIconType ( LPPOINT pt )
{
	// ���߼�����ת��Ϊ��Ļ��������
	DWORD x = this->dwClientPosX + this->dwStartOffsetX + pt->x * this->dwIconSizeX ;
	DWORD y = this->dwClientPosY + this->dwStartOffsetY + pt->y * this->dwIconSizeY ;

	// ����ĻDC����ȡͼ��λͼ
	CBitmap CurBmp ;
	CDC		MemoryDC ;
	CurBmp.CreateCompatibleBitmap ( &this->ScreenDC, this->dwIconSizeX, this->dwIconSizeY ) ;
	MemoryDC.CreateCompatibleDC ( &this->ScreenDC ) ;
	MemoryDC.SelectObject ( &CurBmp ) ;
	MemoryDC.BitBlt ( 0, 0, this->dwIconSizeX, this->dwIconSizeY, &this->ScreenDC, x, y, SRCCOPY ) ;

	/*
	// DEBUG:����ͼ��
	CString szPathName ;
	szPathName.Format ( "%d-%d.bmp", pt->y, pt->x ) ;
	this->LLK_SaveSpecifyBmp ( &CurBmp, szPathName ) ;
	*/

	// ����Ƿ���Ч��ͼ��
	if ( this->LLK_IsValidIcon ( &CurBmp ) == FALSE )
		return 0xFFFFFFFF ;

	// ������ʱ�洢������ȡλͼ����
	LPVOID lpBmpOffset = VirtualAlloc ( NULL, \
		this->dwIconSizeX*this->dwIconSizeY, MEM_COMMIT, PAGE_READWRITE ) ;
	if ( lpBmpOffset != NULL )
		CurBmp.GetBitmapBits ( this->dwIconSizeX * this->dwIconSizeY, lpBmpOffset ) ;

	// ʹ��CRC32�����ݽ���hash
	DWORD dwCrcValue = this->crc.CRC32_Calc ( \
		(LPBYTE)lpBmpOffset, this->dwIconSizeX * this->dwIconSizeY ) ;

	// �ͷſռ�
	VirtualFree ( lpBmpOffset, this->dwIconSizeX*this->dwIconSizeY, MEM_RELEASE ) ;

	// ��⵱ǰͼ�������Ƿ��Ѿ�����
	for ( int i = 0; i < this->dwColorNum; i++ )
	{
		if ( this->dwColorType[i] == dwCrcValue )
			return i ;
	}
	// ��������ڣ������������
	this->dwColorType[this->dwColorNum++] = dwCrcValue ;
	return (this->dwColorNum-1) ;
}

BOOL CLLK::LLK_IsPairInlineValid ( LPPAIR lpPair )
{
	// �����Ƿ��غ�
	if ( lpPair->a.x == lpPair->b.x && lpPair->a.y == lpPair->b.y )
		return FALSE ;

	// ���㲻��ͬһֱ��
	if ( lpPair->a.x != lpPair->b.x && lpPair->a.y != lpPair->b.y )
		return FALSE ;

	// ���㴦��ͬһֱ��
	int i, j ;
	if ( lpPair->a.x == lpPair->b.x )
	{
		int	min = this->LLK_GetMin ( lpPair->a.y, lpPair->b.y ) + 1;
		int max = this->LLK_GetMax ( lpPair->a.y, lpPair->b.y ) - 1;
		if ( min > max )
			return TRUE ;

		for ( i = min; i <= max; i++ )
		{
			if ( this->bValidIcon[i][lpPair->a.x] == TRUE )
				return FALSE ;
		}
		return TRUE ;
	}
	else if ( lpPair->a.y == lpPair->b.y )
	{
		int	min = this->LLK_GetMin ( lpPair->a.x, lpPair->b.x ) + 1;
		int max = this->LLK_GetMax ( lpPair->a.x, lpPair->b.x ) - 1;
		if ( min > max )
			return TRUE ;

		for ( j = min; j <= max; j++ )
		{
			if ( this->bValidIcon[lpPair->a.y][j] == TRUE )
				return FALSE ;
		}
		return TRUE ;
	}
	return FALSE ;
}

BOOL CLLK::LLK_IsValidIcon ( CBitmap* pBmp )
{
	DWORD dwSize = this->dwIconSizeX * this->dwIconSizeY * 4 ;
	LPBYTE lpBits = new BYTE [ dwSize ] ;
	pBmp->GetBitmapBits ( dwSize, lpBits ) ;

	int i, j ;
	int r, g, b ;
	BOOL flag = TRUE ;
	for ( i = this->dwIconSizeY - 20; i < this->dwIconSizeY; i++ )
	{
		for ( j = 0; j < 20; j++ )
		{
			DWORD dwOffset = ( i * this->dwIconSizeX + j ) * 4 ;
			if ( flag )
			{
				flag = FALSE ;
				r = lpBits[dwOffset] ;
				g = lpBits[dwOffset+1] ;
				b = lpBits[dwOffset+2] ;
			}
			else
			{
				if ( lpBits[dwOffset] != r || \
					lpBits[dwOffset+1] != g || lpBits[dwOffset+2] != b )
				{
					delete lpBits ;
					return TRUE ;
				}
			}
		}
	}
	delete lpBits ;
	return FALSE ;
}

VOID CLLK::LLK_SaveSpecifyBmp ( CBitmap* pBmp, CString szPathName )
{
	CDC		MemoryDC ;
	MemoryDC.CreateCompatibleDC ( &this->ScreenDC ) ;
	MemoryDC.SelectObject ( &pBmp ) ;

	//ȡ��λͼ����Ļ�����Ϣ��bmp
	BITMAP bmp ;
	pBmp->GetBitmap ( &bmp ) ;
	
	//����λͼ��Ϣͷ
	BITMAPINFOHEADER BmpInformHeader = {0} ;
	BmpInformHeader.biSize			= sizeof(BITMAPINFOHEADER); 
	BmpInformHeader.biWidth			= bmp.bmWidth ;
	BmpInformHeader.biHeight		= bmp.bmHeight ;
	BmpInformHeader.biPlanes		= 1 ;
    BmpInformHeader.biBitCount		= bmp.bmBitsPixel ;
    BmpInformHeader.biCompression	= BI_RGB ;
	//BmpInformHeader.biSizeImage		= bmp.bmWidthBytes * bmp.bmHeight ;

	//����λͼ�ļ�ͷ
	BITMAPFILEHEADER BmpFileHeader = {0} ;
	BmpFileHeader.bfType	= (WORD)0x4d42 ;
	BmpFileHeader.bfOffBits	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) ;
	BmpFileHeader.bfSize	= BmpFileHeader.bfOffBits + bmp.bmWidthBytes*bmp.bmHeight ;

	//������ʱ�洢����
	LPVOID lpBmpOffset = VirtualAlloc ( NULL, \
		bmp.bmWidthBytes*bmp.bmHeight, MEM_COMMIT, PAGE_READWRITE ) ;
	if ( GetLastError() != 0 )
	{
		(::AfxGetApp()->GetMainWnd())->MessageBox ( L"Memory allocate failed!" ) ;
		return ;
	}
	else
	{
		//��λͼ���ݿ�������ʱ����
		GetDIBits(MemoryDC.m_hDC, (HBITMAP) pBmp->m_hObject, 0, bmp.bmHeight, \
			lpBmpOffset, (LPBITMAPINFO)&BmpInformHeader, DIB_RGB_COLORS);
	}

	//�����ļ�
	FILE *fp = fopen ( (LPSTR)szPathName.GetBuffer(szPathName.GetLength()), "wb" ) ;
	DWORD dwErrorCode = GetLastError() ;
	if ( fp == NULL )
	{
		(::AfxGetApp()->GetMainWnd())->MessageBox ( L"Create file error!" ) ;
		VirtualFree ( lpBmpOffset, bmp.bmWidthBytes*bmp.bmHeight, MEM_RELEASE ) ;
		return ;
	}

	//������д�뵽�ļ�
	if ( !( fwrite(&BmpFileHeader, 1, sizeof(BITMAPFILEHEADER), fp) &&
			fwrite(&BmpInformHeader, 1, sizeof(BITMAPINFOHEADER), fp) &&
			fwrite(lpBmpOffset, 1, bmp.bmWidthBytes*bmp.bmHeight, fp) ) )
	{
		(::AfxGetApp()->GetMainWnd())->MessageBox ( L"Write file error!" ) ;
		VirtualFree ( lpBmpOffset, bmp.bmHeight*bmp.bmWidth, MEM_RELEASE ) ;
		fclose ( fp ) ;
		return ;
	}
	
	VirtualFree ( lpBmpOffset, bmp.bmHeight*bmp.bmWidth, MEM_RELEASE ) ;
	fclose(fp) ;
}

VOID CLLK::LLK_GetValidRangeH ( POINT pt, int &min, int &max )
{
	min = max = pt.x ;

	int j ;
	for ( j = pt.x - 1; j >= 0; j-- )
	{
		if ( j < 0 || this->bValidIcon[pt.y][j] == TRUE )
			break ;
		min = j ;
	}
	for ( j = pt.x + 1; j < this->dwIconNumX; j ++ )
	{
		if ( j >= this->dwIconNumX || this->bValidIcon[pt.y][j] == TRUE )
			break ;
		max = j ;
	}
}

VOID CLLK::LLK_GetValidRangeV ( POINT pt, int &min, int &max )
{
	min = max = pt.y ;
	
	int i ;
	for ( i = pt.y - 1; i >= 0; i-- )
	{
		if ( i < 0 || this->bValidIcon[i][pt.x] == TRUE )
			break ;
		min = i ;
	}
	for ( i = pt.y + 1; i < this->dwIconNumY; i ++ )
	{
		if ( i >= this->dwIconNumY || this->bValidIcon[i][pt.x] == TRUE )
			break ;
		max = i ;
	}
}

int CLLK::LLK_GetMin ( int a, int b )
{
	return a <= b ? a : b ;
}

int CLLK::LLK_GetMax ( int a, int b )
{
	return a >= b ? a : b ;
}
