/****************************************************************/
/*						  Hash.H						        */
/*				      by: Ohad Redlich							*/
/*						15.8.2000								*/
/****************************************************************/


/* Using CHashTable
 * class T must have the functions : 
 * 1) int HashValue() const
 *    that returns the hash value of the T object
 * 2) bool operator==(const T&) const
 * 3) default constructor
 */

#ifndef _HASH_H
#define _HASH_H

#include "DynamicVector.h"

enum RecordStates {Value,NoValue,Deleted};


template <class T>
class CHashNode
{
public:
    CHashNode();
    CHashNode(T val);
    
	bool operator==(const CHashNode<T>& node);
	void ClearNode();

	RecordStates    state;
    T				value;

};


template <class T>
class CHashTable
{
public:
	CHashTable(int size);
	// Find returns the element in the HashTable that is equal to val
	// using operator==. If the element wasn't found, it returns NULL
	T*		Find(T val);
	int		Insert(T val);
	int		Remove(T val);
	//Update allows to update a node without deleting it and inserting it back
	bool	Update(T val);		//not in use
	int		FindIndex(T val);	// finds the index of val (-1 if not found)
	void	Clear();

private:  
   unsigned int Hash(T val);
   CVector < CHashNode<T> > m_elements;

};


/****************************************************************/
/*              class CHashNode implementation                  */
/****************************************************************/

template <class T>
CHashNode<T>::CHashNode()
{
    state=NoValue;
}

template <class T>
CHashNode<T>::CHashNode(T val)
{
    value=val;
    state=Value;
}

template <class T>
bool CHashNode<T>::operator==(const CHashNode<T>& node)
{
    return state==node.state && value==node.value;
} 

template <class T>
void CHashNode<T>::ClearNode()
{
    state = NoValue;
	value = NULL;
} 


/****************************************************************/
/*             class CHashTable implementation                  */
/****************************************************************/

template <class T>
CHashTable<T>::CHashTable( int size ) : m_elements( size )
{
    CHashNode<T> NullNode;
    for (int index=0; index<size; index++)
        m_elements.Insert(NullNode);
}

template <class T>
unsigned int CHashTable<T>::Hash(T val) 
{
    return (val.HashValue() % m_elements.Size());
}

/**
  * This method get a T, and inserts it into the hash table. It returns -1
  * if the table is full, and the index of T if insertion was successful
  **/
template <class T>
int CHashTable<T>::Insert(T val) 
{
	int initialPos = Hash(val);		//expected index in the vector
	int pos = initialPos;
	while (m_elements[pos].state == Value) 
	{
		pos= ++pos % m_elements.Size();
		if (pos == initialPos)		//we got to same place where started - table is full
			return -1;
	}
	//inserting T into the table:
	CHashNode<T> Val(val);
	m_elements[pos] = Val;
	return pos;
}


template <class T>
int CHashTable<T>::FindIndex(T val) 
{
  int initialPos=Hash(val);
  int pos=initialPos;
  while (!(m_elements[pos].value==val)) {
      pos= ++pos % m_elements.Size();
      if ((m_elements[pos].state==NoValue) || (pos==initialPos)) 
         return -1;
  }
  return pos;
}

template <class T>
T* CHashTable<T>::Find(T val) 
{
  int pos=FindIndex(val);
  if (pos!=-1)
	  return &m_elements[pos].value; //returns the address of the item.
  else
     return NULL;
}


template <class T>
int CHashTable<T>::Remove(T val)
{
  int pos=FindIndex(val);
  if (pos<0) 
     return -1;
  CHashNode<T> DeletedNode;
  DeletedNode.state=Deleted;
  m_elements[pos]=DeletedNode;
  return pos;
}


/**
  * Update method enables updating a Node in the hash table, without deleting it
  * and re-inserting, so the previous position of the Node remains. If successful
  * it returns true, otherwise false.
  **/
template <class T>
bool CHashTable<T>::Update(T val)
{
	int pos = FindIndex( val );
	//T* xxx = Find( val );
	if ( pos == -1 )
	{
		return false;
	}
	//inserting new T into the table:
	CHashNode<T> Val(val);
	m_elements[pos] = Val;
	return true;
}


template <class T>
void CHashTable<T>::Clear()
{
	for( int i = 0; i < m_elements.Size(); i++ )
	{
		m_elements[ i ].ClearNode();
	}

}


#endif