///////////////////////////////////////////////////////////////
// HashedWord.h

#include "HashedWord.h"

using namespace std;

/****************************************************************/
/*               class CHashedWord implementation               */
/****************************************************************/

CHashedWord::CHashedWord()
:	m_nWordIndex(0),
	m_nNumOfInstances(0)
{
}


/**
  *	This is the Hash Function:
  **/
int CHashedWord::HashValue() const
{
	int i = 0;			//index
	int nHashVal = 0;	//hash value
	while( m_Word[i] != '\0')
	{
		nHashVal += ( m_Word[i] * ( i+1 ) * 10 );
		++i;
	}

	return nHashVal;
}

bool CHashedWord::operator ==(const CHashedWord& HashedWord)const
{
	if( m_Word == HashedWord.m_Word )	//strings are identical
	{
		return true;
	}
	return false;
}

CHashedWord& CHashedWord::operator = (const CHashedWord& HashedWord)
{
    m_Word = HashedWord.m_Word;
	m_nWordIndex = HashedWord.m_nWordIndex;
	m_nNumOfInstances = HashedWord.m_nNumOfInstances;

    return *this;
}

/**
  *	this operator is used to clean the node, when cleaning the hast table:
  **/
CHashedWord& CHashedWord::operator = ( void* something )
{
    m_Word = "";
	m_nWordIndex = 0;

    return *this;
}
