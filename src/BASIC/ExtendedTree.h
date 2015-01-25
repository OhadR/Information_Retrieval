#if !defined(__EXTENDED_TREE_H__)
#define __EXTENDED_TREE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cassert>
#include <stdlib.h>		//NULL, new, ...

template <class T>
class CExNode  
{
public:
	CExNode( T val );
	virtual ~CExNode()		{}

	int			NumOfChilds() const;
	
	CExNode*	m_LeftChild;
	CExNode*	m_NodeInRight;
	T			m_Val;
};

template <class T>
class CExTree
{
public:
	CExTree();
	CExTree( T val );
	CExTree(const CExTree& rhs);
	
	virtual ~CExTree();

	CExTree&	operator=(const CExTree& rhs);
	virtual void	AddChild(const CExTree& Tree);
	
    bool			IsEmpty() const;
    void			Clear() { Clear(m_Root); }
    virtual void	PreOrder() { PreOrder(m_Root); }
    void			PostOrder() { PostOrder(m_Root); }
	
protected:
	void			Clear(CExNode<T> * current);

private:
    void			PreOrder(CExNode<T> * current) const;
	void			PostOrder(CExNode<T> * current);
    virtual void	Visit(CExNode<T>* current) const		= 0;
	
	
protected:
	//gets a source tree, COPIES it and return a root-node of the copied tree:
	CExNode<T>*	Copy(CExNode<T>* SourceRoot);

	CExNode<T>*	m_Root;
};



/**********************************************
			CExNode definitions
/**********************************************/
template <class T>
CExNode<T>::CExNode( T Val)
{
	m_LeftChild		= NULL;
	m_NodeInRight	= NULL;
	m_Val			= Val;
}

template <class T>
int	CExNode<T>::NumOfChilds() const
{
	if( !m_LeftChild )					//no childs
		return 0;
	CExNode*	current	= m_LeftChild;
	if( !m_LeftChild->m_NodeInRight )	//only one child, with no brothers
		return 1;
	CExNode*	next	= m_LeftChild->m_NodeInRight;
	int nNumOfChilds = 2;
	while( next )
	{
		current = next;
		next	= next->m_NodeInRight;
		++nNumOfChilds;
	}
	return nNumOfChilds;
}


/**********************************************
			CExTree definitions
/**********************************************/
template <class T>
CExTree<T>::CExTree()
:	m_Root(NULL)
{
}

template <class T>
CExTree<T>::CExTree( T Val)
{
	m_Root = new CExNode<T>(Val);
}

/**
  * this copy cons is good for copying trees - especially in the STypedString
  **/
template <class T>
CExTree<T>::CExTree(const CExTree& rhs)
{
	m_Root = Copy(rhs.m_Root);
}

template <class T>
CExTree<T>::~CExTree()
{
    if ( m_Root )
    {
		Clear(m_Root);
    }    
}

template <class T>
CExTree<T>& CExTree<T>::operator=(const CExTree& rhs)
{
	//if root is already allocated, delete it
    if ( m_Root )
    {
		Clear(m_Root);
    }    
	m_Root = Copy(rhs.m_Root);
	return *this;
}

/**
  * this method get a tree (root), and adds this tree to itself's root (this->m_root)
  * as another child. this thing CAN NOT be done in a binary tree
  **/
template <class T>
void CExTree<T>::AddChild(const CExTree& Tree)
{
	assert(m_Root);

	if(!m_Root->m_LeftChild)
	{
		m_Root->m_LeftChild = Copy(Tree.m_Root);
		return;
	}
	
	CExNode<T>* current	= m_Root->m_LeftChild;
	CExNode<T>* right	= m_Root->m_LeftChild->m_NodeInRight;
	while (right)
	{
		current = right;
		right	= right->m_NodeInRight;
	}
	current->m_NodeInRight = Copy(Tree.m_Root);
}

template <class T>
void CExTree<T>::Clear(CExNode<T> * current)
{
	// Release memory associated with children
	if (current->m_LeftChild)
		Clear(current->m_LeftChild);
	
    if (current->m_NodeInRight)
		Clear(current->m_NodeInRight);
    
	delete current;
    current = NULL;
}

template <class T>
void CExTree<T>::PreOrder(CExNode<T>* current) const
{
	//stopping condition:
	if(!current)
		return;
	
	//visit current:
	Visit(current);
	//visit childs:	(left child, and through him all other child)
	PreOrder(current->m_LeftChild);
	//visit "brother":
	PreOrder(current->m_NodeInRight);
}

template <class T>
CExNode<T>* CExTree<T>::Copy(CExNode<T>* /*this is the source*/	SourceRoot)
{
	//stoping condition:
	if( !SourceRoot )
	{
		return NULL;
	}
	
	CExNode<TYPE>* current = new CExNode<TYPE>(SourceRoot->m_Val);
	current->m_LeftChild = Copy(SourceRoot->m_LeftChild);
	current->m_NodeInRight = Copy(SourceRoot->m_NodeInRight);
	
	return current;
}

#endif // !defined(__EXTENDED_TREE_H__)