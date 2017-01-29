////////////////////////////////////////////////////////////////////////
// VectorianModel.h

#ifndef _SEARCHVECTORIANMODEL_H_
#define _SEARCHVECTORIANMODEL_H_

#include <stdio.h>		// FILE
#include <stdlib.h>		// exit
#include <string.h>
#include <io.h>			// _findfirst, etc...
#include <math.h>		// log

#include "../Basic/Hash.h"
#include "../Basic/List.h"
#include "../Basic/IndexFile.h"
#include "SearchStructs.h"


//const long  MAX_NUM_OF_WORDS  = 2000000;
//const int	MAXLINE			  =	1000;
//const int	SIZE_OF_FILENAME  = 150;
//const int	SIZE_OF_WORD	  =	20;




/****************************************************************/
/*          class CSearchVectorianModel definition              */
/****************************************************************/

class CSearchVectorianModel
{
public:
	CSearchVectorianModel( int nNumOfWordsInQuery, char* Query[] );
	virtual ~CSearchVectorianModel();


private:
	void FillHashTable();
	void FillListedVector();
	void FillDocumentsVector();
	void HandleQuery( int nNumOfWordsInQuery, char* Query[] );

	void WordHandler( const char* Word );
	void SortAndPrintDocuments();

	CHashTable<CHashedWord>		m_HashTable;
	CVector<DocFileAndNorm>		m_DocumentsVector;
	CVector< CDoubleEndedList<DocAndWeight> >	m_ListedVector;
	CIndexFile*					m_Dictionary;
	CIndexFile*					m_FileIndex;
	CIndexFile*					m_InvertedIndex;
};


#endif		//_SEARCHVECTORIANMODEL_H_