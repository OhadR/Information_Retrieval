////////////////////////////////////////////////////////////////////////
// HashedWord.h

#ifndef __HASHED_WORD_H__
#define __HASHED_WORD_H__

#include <string>

/****************************************************************/
/*			     class CHashedWord definition 			        */
/*																*/
/*	CHashedWord class is for the Hash table, and it contains	*/
/*	the word, default constructor, the hash function and		*/
/*	operator ==													*/
/****************************************************************/

class CHashedWord
{
public:
	CHashedWord();

	int		HashValue() const;
	bool	operator==(const CHashedWord&) const;
    CHashedWord&   operator=(const CHashedWord&);
    CHashedWord&   operator=(void* something);

	std::string		m_Word;
	unsigned int	m_nWordIndex		: 20;			//the index of the word in the Vector
	unsigned int	m_nNumOfInstances	: 12;		//number of times that the word appears
};


#endif	//__HASHED_WORD_H__