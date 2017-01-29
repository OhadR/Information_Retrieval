//List.h:
//--------
#ifndef LIST_H
#define LIST_H

#include <assert.h>

/* Using CList
 *
 * if using functions Find or Includes,
 * T class must have the function
 * bool operator == (const T&) const
 */

/****************************************************************/
/*  class CList
/*      arbitrary size lists of elements
/*      permits insertion and removal only
/*      from the front of the list
/****************************************************************/

template <class T> class link;

template <class T> class CList
{
public:
    // constructors
    CList();
    ~CList();

    // operations
    CList<T>&   operator = (const CList<T>&);
    virtual void	Add(T value);
    T				FirstElement() const;
    int				IsEmpty() const;
    void			RemoveFirst();
    virtual void	Clear();
	T*				Find(T value) const;
	int				GetLength() const;

//protected:
    // data field
    link<T> *     first;
};


/****************************************************************/
/*  class link
/*      facilitator for operations on lists
/*      maintains a single element for the linked list class
/****************************************************************/

template <class T> class link
{
public:
    // constructor
    link(T linkValue, link<T> * nextPtr);
    link(const link<T> &);

    // data areas
    T			value;
    link<T> *    next;
};


/****************************************************************/
/*  class CDoubleEndedList
/*      a variation on lists - can add elements to end
/*      as well as to front
/****************************************************************/

template <class T> class CDoubleEndedList : public CList<T> {
public:
    // constructors
    CDoubleEndedList ();

    // override the following methods from class CList
    CDoubleEndedList<T>&   operator = (const CDoubleEndedList<T>&);
    virtual void    Add (T value);
    virtual void    Clear ();
    virtual void    RemoveFirst ();
    T*				GetLastElement() /*const*/;

    // add a new element to the end of the list
    void			AddToEnd (T value);

protected:
    // data area -- link to end
    link<T> * last;
};

 
/****************************************************************/
/*              class CList implementation                      */
/****************************************************************/

template <class T>
CList<T>::CList() : first(NULL)
{
    // no further initialization
}

template <class T>
CList<T>::~CList()
{
    Clear();
}


template <class T>
CList<T> &CList<T>::operator = (const CList<T>& list)
{
    first = list.first;

    return *this;
}


template <class T>
void CList<T>::Clear()
{
	 // empty all elements from the list
    link<T> * next;

    for (link<T> * p=first; p != NULL; p=next)
    {
    // delete the element pointed to by p
      next=p->next;
      p->next=NULL;
      delete p;
    }

    // mark that the list contains no elements
    first=NULL;
}


template <class T>
void CList<T>::Add(T val)
{
    // Add a new value to the front of a linked list
    first=new link<T>(val, first);
    assert(first != NULL);
}


template <class T>
T CList<T>::FirstElement() const
{
    // return first value in list
	assert(first != NULL);
    return first->value;
}


template <class T>
T* CList<T>::Find(T value) const
{
    // loop to test each element
    for (link<T> * p=first; p!=NULL ; p=p->next)
        if (value == p->value)
            return &p->value;

    // not found
    return NULL;
}

template <class T>
int CList<T>::IsEmpty() const
{
    // test to see if the list is empty
    // list is empty if the pointer to the first link is null
    return first == NULL;
}



template <class T>
void CList<T>::RemoveFirst()
{
    // make sure there is a first element
    assert(first != NULL);

    // save pointer to the removed node
    link<T> * p=first;

    // reassign the first node
    first=  p->next;

    // recover memory used by the first element
    delete p;
}

template <class T>
int CList<T>::GetLength() const
{
    int nCount = 0;
	// loop to count each element
    for (link<T> * p=first; p!=NULL ; p=p->next, nCount++)
		;

    return nCount;

}


/****************************************************************/
/*                 class link implementation                    */
/****************************************************************/

template <class T> link<T>::link(T val, link<T> * nxt)
    : value(val), next(nxt)
{
    // create and initialize a new link field
}

template <class T> link<T>::link(const link<T> & source)
    : value(source.value), next(source.next)
{
}


/****************************************************************/
/*          class CDoubleEndedList implementation                */
/****************************************************************/
    
template <class T>
CDoubleEndedList<T>::CDoubleEndedList() 
    : CList<T>()
{
    last = NULL;
}

template <class T>
CDoubleEndedList<T> &CDoubleEndedList<T>::operator = (const CDoubleEndedList<T>& DElist)
{
    first = DElist.first;
	last = DElist.last;

    return *this;
}

template <class T>
void CDoubleEndedList<T>::Add(T val)
{   // add an element to the front of a double ended list
    // only need to handle addition to empty list
	if (IsEmpty())
    {
		CList<T>::Add(val);
        last = first;
    }
    else
		CList<T>::Add(val);
}

template <class T>
void CDoubleEndedList<T>::AddToEnd(T val)
{
	// add a new element to the end of a double ended list
    // if there is an end, add to it

	if (last != NULL)
	{
        last->next = new link<T>(val,NULL);
        last = last->next;
    }

    // otherwise, just add to front
    else
        Add(val);
}

template <class T>
void CDoubleEndedList<T>::RemoveFirst()
{
    // remove the first element from double ended list
    
	// invoke the method from list to do the work:
    CList<T>::RemoveFirst();

    // only do something different if we removed last element:
    if (IsEmpty())
        last = NULL;
}

template <class T>
T* CDoubleEndedList<T>::GetLastElement() /*const*/
{
    // return last value in list
	assert(last != NULL);
    return &last->value;
}

template <class T>
void CDoubleEndedList<T>::Clear()
{   
    // delete all values from collection
    // invoke the list method to do the actual work

	 CList<T>::Clear();

    // then set the pointer to the last element to zero
    
    last = NULL;
}


#endif