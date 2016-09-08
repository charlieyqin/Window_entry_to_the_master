#pragma once

#ifndef _MOMORY_H
#include <memory.h>
#endif

#ifndef UINT
typedef unsigned int UINT ;
#endif	

template<class Type>
class Node 
{
public:
	Type	Item ;
	Node<Type>*	pForw ;
	Node<Type>* pNext ;

public:
	Node<Type> ( Type x )
	{
		memcpy ( &Item, &x, sizeof(Item) ) ;
		pForw = p ;
		pNext = q ;
	}
	~Node()	{} 
} ;

template <class Type>
class CCList
{
public:
	Node<Type>*	pList ;
	Node<Type>* pTail ;
	UINT nNodeCount ;

public:
	CCList()	 
	{	
		pList = pTail = NULL ;
		nNodeCount = 0 ;
	}
	~CCList() { DeleteAll() ; }

public:
	bool IsEmpty ()	{ return ( pList ? true : false ) ;	}
	UINT GetNodeCount ( ) { return nNodeCount ;	}

	//���뵽������
	void InsertNullList ( Type Item )
	{
		Node<Type>* pNewNode	= ConvertItemToNode ( Item ) ;
		pList = pTail = pNewNode ;
		nNodeCount++ ;
	}

	//���뵽�����ײ�
	void InsertInHead ( Type Item )
	{
		Node<Type>* pNewNode	= ConvertItemToNode ( Item ) ;
		pNewNode->pNext = pList ;
		pList = pList->pForw = pNewNode ;
		nNodeCount++ ;
	}
	
	//���뵽����β��
	void InsertInTail ( Type Item )
	{
		Node<Type>* pNewNode	= ConvertItemToNode ( Item ) ;
		pNewNode->pForw = pTail ;
		pTail = pTail->pNext = pNewNode ;
		nNodeCount++ ;
	} 

	// ���뵽�����ڲ�
	void InsertInIntl ( Node<Type>* pOldNode, Type Item ) 
	{
		Node<Type>* pNewNode	= ConvertItemToNode ( Item ) ;
		pNewNode->pForw		= pOldNode->pForw ;
		pNewNode->pNext		= pOldNode ;
		pOldNode->pForw->pNext = pNewNode ;
		pOldNode->pForw		= pNewNode ;
		nNodeCount++ ;
	}

	void InsertByIndex ( Type Item, UINT nPos  ) 
	{
		nPos = nPos > nNodeCount ? nNodeCount : nPos ;
		Node<Type>* pNode	= GetNodeByIndex ( nPos ) ;

		if ( nNodeCount == 0 )	
			InsertNullList ( Item ) ;
		else if ( nPos == 0 )	
			InsertInHead ( Item ) ;
		else if ( nPos == nNodeCount ) 
			InsertInTail ( Item ) ;
		else			
			InsertInIntl ( pNode, Item ) ;
	}                                           
	
	void DeleteAll ( )
	{
		UINT i, nCount = this->nNodeCount ;
		for ( i = 0; i < nCount; i++ )
			DeleteByIndex ( 0 ) ;
		this->pList = this->pTail = NULL ;
	}

	void DeleteByIndex ( UINT nPos ) 
	{
		Node<Type>* pOldNode = GetNodeByIndex ( nPos ) ;

		if ( nNodeCount == 0 || nPos >= nNodeCount )
			return ;
		else if ( nPos == 0 )				//ɾ������ͷ���
		{
			if ( nNodeCount == 1 )
			{
				pList = pTail = NULL ;
			}
			else 
			{
				pOldNode->pNext->pForw = NULL ;
				pList = pOldNode->pNext ;
			}
		}
		else if ( nPos == nNodeCount-1 )	//ɾ������β���
		{
			pOldNode->pForw->pNext = NULL ;
			pTail = pOldNode->pForw ;
		}
		else								//ɾ�������ڲ��Ľ��
		{
			pOldNode->pForw->pNext = pOldNode->pNext ;
			pOldNode->pNext->pForw = pOldNode->pForw ;
		}

		nNodeCount-- ;
		delete pOldNode ;
	}

	Type GetItemByIndex ( UINT nIndex ) 
	{
		return GetNodeByIndex ( nIndex )->Item ;
	}

protected:
	Node<Type>* ConvertItemToNode ( Type Item )
	{
		Node<Type>* p = (Node<Type>*)malloc ( sizeof(Node<Type>) ) ;
		memcpy ( &(p->Item), &Item, sizeof(Item) ) ;
		p->pForw = p->pNext = NULL ;

		return p ;
	}

	Node<Type>* GetNodeByIndex ( UINT nIndex )
	{
		if ( nIndex > nNodeCount )
			nIndex = nNodeCount ;

		Node<Type>* pNode = pList ;
		while ( nIndex-- )
			pNode = pNode->pNext ;

		return pNode ;
	}
} ;
