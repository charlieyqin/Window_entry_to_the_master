#pragma once


#include <vector>
#include <list>
using namespace std ;

#define DEF_BMP_SIZE 32

typedef struct _ITEM {
	int nIndex ;
	int nValue ;
	struct _ITEM (){}
	struct _ITEM ( int index, int value ) {
		nIndex = index ;
		nValue = value ;
	}
} ITEM ;

class CEightPuzzleGame
{
public:
	CEightPuzzleGame(void);
	~CEightPuzzleGame(void);

private:
	BYTE	bBegMetrix[3][3] ;			// ��ʼ״̬����
	BYTE	bEndMetrix[3][3] ;			// ��ֹ״̬����
	BYTE	bCurMetrix[3][3] ;			// ��ǰ״̬����

	list<int>	PathList ;				// ·������
	CBitmap		DigitBmp ;				// λͼ����
	UINT		nBlankPosX, nBlankPosY ;// ��ǰ�ո񣨼���0��������λ��

public:
	// ���������ʼ״̬
	VOID	RandomBegStatus () ;
	// ����
	VOID	Restart () ;
	// �ƶ���nDir��ʾ����0:�ϣ�1:��2:�£�3:�ң�
	BOOL	SingleMove ( int nDir ) ;
	// ʵ�������㷨��������·����������ʾ
	UINT	GetSlove () ;
	// ��ʾ����
	VOID	DemoShow ( CClientDC* pdc ) ;
	// ����Ƿ񵽴�Ŀ��״̬
	BOOL	IsFinish ( ) ;

private:
	// ��״̬����ת��Ϊ����
	int		ConvertMetrixToInt ( BYTE pMetrix[3][3] ) ;
	// ������״̬Ϊ״̬����
	VOID	ConvertIntToCurMetrix ( int nValue ) ;

public:
	// ������ʼ״̬ͼ
	VOID	PaintBegStatus ( CClientDC* pdc ) ;
	// ���Ƶ�ǰ״̬ͼ
	VOID	PaintCurStatus ( CClientDC* pdc ) ;
	// ������ֹ״̬ͼ
	VOID	PaintEndStatus ( CClientDC* pdc ) ;
};
