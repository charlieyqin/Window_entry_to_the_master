// Ping.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "Winsock2.h"
#pragma comment ( lib, "ws2_32.lib" )

#include <windows.h>
#include "stdio.h"

// ����Ĭ�ϵĻ���������
#define DEF_BUF_SIZE		1024

// ����IP��ͷ����
#define IP_HEADER_SIZE		20

// ����ICMP��ͷ����
#define ICMP_HEADER_SIZE	( sizeof(ICMP_HEADER) )

// ����ICMP��ʵ�����ݳ���
#define ICMP_DATA_SIZE		32

// ����ICMP���ܳ���
#define ICMP_PACK_SIZE		( ICMP_HEADER_SIZE + ICMP_DATA_SIZE )

// ����ICMP��ͷ
typedef struct _ICMP_HEADER {
	BYTE	bType ;			// ����
	BYTE	bCode ;			// ����
	USHORT	nCheckSum ;		// У���
	USHORT	nId ;			// ��ʶ��������ID
	USHORT	nSequence ;		// ���к�
	UINT	nTimeStamp ;	// ��ѡ�����Ϊʱ�䣬���ڼ���ʱ��
} ICMP_HEADER, *PICMP_HEADER ;

// ���ڸ�ʽ�������Ϣ�Ļ�����
char szInfo[DEF_BUF_SIZE] ;

BOOL Ping ( char* lpDestIp ) ;
USHORT GetCheckSum ( LPBYTE lpBuf, DWORD dwSize ) ;

int main(int argc, char* argv[])
{
	int value[4] ;
	char szDestIp[DEF_BUF_SIZE] = {0} ;
	while ( scanf ( "%s", szDestIp) )
		Ping ( szDestIp ) ;
	return 0;
}

// ʵ��PING����
// ������Ŀ���ַIP�ַ�������ʽ�硰127.0.0.1��
BOOL Ping ( char* lpDestIp )
{
	// ����Ŀ���ַ
	SOCKADDR_IN DestSockAddr ;
	DestSockAddr.sin_family = AF_INET ;
	DestSockAddr.sin_addr.s_addr = inet_addr( lpDestIp ) ;
	DestSockAddr.sin_port = htons ( 0 ) ;

	// ����ICMP���������
	char ICMPPack[ICMP_PACK_SIZE] = {0} ;
	PICMP_HEADER pICMPHeader = (PICMP_HEADER)ICMPPack ;
	pICMPHeader->bType = 8 ;
	pICMPHeader->bCode = 0 ;
	pICMPHeader->nId = (USHORT)::GetCurrentProcessId() ;
	pICMPHeader->nCheckSum = 0 ;
	pICMPHeader->nTimeStamp = 0 ;
	memset ( &(ICMPPack[ICMP_HEADER_SIZE]), 'E', ICMP_DATA_SIZE ) ;	// ������ݲ��֣���������

	// ��ʼ��WinSock��
	WORD wVersionRequested = MAKEWORD( 2, 2 );
	WSADATA wsaData;
	if ( WSAStartup( wVersionRequested, &wsaData ) != 0 )
		return FALSE ;

	// ����ԭʼ�׽���
	SOCKET	RawSock = socket ( AF_INET, SOCK_RAW, IPPROTO_ICMP ) ;
	if ( RawSock == INVALID_SOCKET )
	{
		printf ( "Create socket error!\n" ) ;
		return FALSE ;
	}
	
	// ���ý��ճ�ʱΪ1��
	int nTime = 1000 ;
	int ret = ::setsockopt ( RawSock, SOL_SOCKET,SO_RCVTIMEO, (char*)&nTime, sizeof(nTime));
	
	char szRecvBuf [ DEF_BUF_SIZE] ;
	SOCKADDR_IN	SourSockAddr ;
	for ( int i = 0 ; i < 4; i++ )
	{
		pICMPHeader->nCheckSum = 0 ;				// ��ʼʱУ��ֵΪ0
		pICMPHeader->nSequence = i ;				// ���
		pICMPHeader->nTimeStamp = ::GetTickCount() ;// ��ǰʱ��

		// ����У��ֵ��У��ֵҪ��ICMP���ݱ���������ܼ���
		pICMPHeader->nCheckSum = GetCheckSum ( (LPBYTE)ICMPPack, ICMP_PACK_SIZE ) ;
		
		// ����ICMP���ݰ�
		int nRet = ::sendto ( RawSock, ICMPPack, ICMP_PACK_SIZE,0,(SOCKADDR*)&DestSockAddr, sizeof(DestSockAddr) ) ;
		if ( nRet == SOCKET_ERROR )
		{
			printf ( "sendto error!\n" ) ;
			return FALSE ;
		}

		// ����ICMP��Ӧ
		int nLen = sizeof(SourSockAddr) ;
		nRet = ::recvfrom ( RawSock, szRecvBuf, DEF_BUF_SIZE,0,(SOCKADDR*)&SourSockAddr, &nLen ) ;
		if ( nRet == SOCKET_ERROR )
		{
			if ( ::WSAGetLastError() == WSAETIMEDOUT )
			{
				printf ( "Request Timeout\n" ) ;
				continue ;
			}
			else
			{
				printf ( "recvfrom error!\n" ) ;
				return FALSE ;
			}
		}

		// ����ICMP���ݱ���ʱ���
		int nTime = ::GetTickCount() - pICMPHeader->nTimeStamp ;

		int nRealSize = nRet - IP_HEADER_SIZE - ICMP_HEADER_SIZE ;
		if ( nRealSize < 0  )
		{
			printf ( "To less recv bytes!\n" ) ;
			continue ;
		}

		// ����Ƿ�ǰ��������ICMP��Ӧ��
		PICMP_HEADER pRecvHeader = (PICMP_HEADER)(szRecvBuf+IP_HEADER_SIZE) ;
		if ( pRecvHeader->bType != 0 )
		{
			printf ( "Not ICMP respond type!\n" ) ;
			return FALSE ;
		}

		if ( pRecvHeader->nId != ::GetCurrentProcessId () )
		{
			printf ( "not valid id!\n" ) ;
			return FALSE ;
		}

		printf ( "%d bytes replay from %s : bytes=%d time=%dms\n", \
			nRet, inet_ntoa(SourSockAddr.sin_addr), nRealSize, nTime ) ;

		::Sleep ( 1000 ) ;
	}
	
	closesocket ( RawSock ) ;
	WSACleanup () ;

	return TRUE ;
}

// ����ICMP��У��ֵ
// ����1��ICMP��������
// ����2��ICMP������
USHORT GetCheckSum ( LPBYTE lpBuf, DWORD dwSize )
{
	DWORD	dwCheckSum = 0 ;
	USHORT* lpWord = (USHORT*)lpBuf ;

	// �ۼ�
	while ( dwSize > 1 )
	{
		dwCheckSum += *lpWord++ ;
		dwSize -= 2 ;
	}

	// �������������
	if ( dwSize == 1 )
		dwCheckSum += *((LPBYTE)lpWord) ;

	// ��16λ�͵�16λ���
	dwCheckSum = ( dwCheckSum >> 16 ) + ( dwCheckSum & 0xFFFF ) ;

	// ȡ��
	return (USHORT)(~dwCheckSum ) ;
}
