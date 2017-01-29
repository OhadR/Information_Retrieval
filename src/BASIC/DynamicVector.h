/****************************************************************/
/*                    DynamicVector.H					        */
/*				      by: Ohad Redlich							*/
/*						10.8.2000								*/
/****************************************************************/

#include <iostream.h>
#include <assert.h>

#ifndef _VECTOR_H
#define _VECTOR_H



// default capacity for the dynamic vector:
const int DEF_CAPACITY = 5;



template <class T>
class CVector
{
public:
    CVector(int capacity = DEF_CAPACITY);
    CVector(const CVector<T>& vec);
    ~CVector();

    /*const*/ T&      operator [](int index) const;
    CVector<T>&   operator = (const CVector<T>&);
    int           Size() const;
    int           Capacity() const;
    void          Insert(T value);
    void          Clear();
	T             DelLast();
	T*            Find(T value) const;

private:
	void	Resize();

	T*		m_data;
    int		m_nSize;
	int		m_nCapacity;
};


template <class T>
CVector<T>::CVector(int Capacity)
{
    m_nCapacity = Capacity;
    m_nSize = 0;
	m_data = new T[m_nCapacity];
    assert(m_data!=NULL);
}

template <class T>
CVector<T>::CVector(const CVector<T>& vec)
{
    m_nCapacity = vec.m_nCapacity;
    m_nSize = vec.m_nSize;
    m_data = new T[m_nCapacity];
    assert(m_data!=NULL);
    for (int index=0; index<m_nSize; index++)
        m_data[index] = vec.m_data[index];
}

template <class T>
CVector<T>::~CVector()
{
    if (m_data != NULL)
	{
        delete [] m_data;
        m_data = NULL;
    }
}


template <class T>
/*const*/ T& CVector<T>::operator [](int index) const
//changed: allows to get and put from places where nothing was inserted.
{
    assert(index >=0);

    return m_data[index];
}

template <class T>
CVector<T> &CVector<T>::operator = (const CVector<T>& vec)
{
    m_nSize = vec.m_nSize;
    m_nCapacity = vec.m_nCapacity;

    if (m_data)
        delete [] m_data;
    m_data = new T[m_nCapacity];
    assert(m_data!=NULL);
    for (int index=0; index<m_nSize; index++)
        m_data[index] = vec.m_data[index];

    return *this;
}

template <class T>
int CVector<T>::Size() const
{
    return m_nSize;
}

template <class T>
int CVector<T>::Capacity() const
{
    return m_nCapacity;
}

template <class T>
void CVector<T>::Insert(T value)
{
    if ( m_nSize == m_nCapacity )
	{
		Resize();
	}

    m_data[m_nSize] = value;
    m_nSize++;
}

template <class T>
void CVector<T>::Clear()
{
	m_nSize=0;
}

template <class T>
T CVector<T>::DelLast()
{
	assert(m_nSize>=0);
	return m_data[--m_nSize];
}

template <class T>
T* CVector<T>::Find(T value) const
{
	for (int i=0;i<m_nSize;i++)
	{
		if (value==m_data[i])
		{
			return m_data+i;
		}
	}
	return NULL;
}


/**
  * This method doubles the capacity of the vector. It makes the vector dynamic!
  **/
template <class T>
void CVector<T>::Resize()
{
	T* tempData = new T[ m_nCapacity ];
	for ( int index = 0; index < m_nSize; index++ )
        tempData[ index ] = m_data[ index ];

	m_nCapacity *= 2;
	//delete [] m_data;
	m_data = new T[ m_nCapacity ];
    assert(m_data!=NULL);
    for ( index = 0; index < m_nSize; index++)
        m_data[index] = tempData[index];
	//delete [] tempData;
}


#endif		//_VECTOR_H