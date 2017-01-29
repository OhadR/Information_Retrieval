////////////////////////////////////////////////////////////////////////
// VectorianModel.h

#ifndef _VECTORIANMODEL_H_
#define _VECTORIANMODEL_H_

#include <stdio.h>		// FILE
#include <stdlib.h>		// exit
#include <string.h>
#include <io.h>			// _findfirst, etc...
#include <math.h>		// log, sqrt

#include "../Basic/Hash.h"
#include "../Basic/List.h"
#include "../Basic/IndexFile.h"




const long  MAX_NUM_OF_WORDS  = 2000000;
const int	MAX_NUM_OF_FILES  =	1000;
const int	MAXLINE			  =	1000;
const int	SIZE_OF_FILENAME  = 150;
const int	MAX_ITEMS_IN_ROW  = 50;
const int	SIZE_OF_WORD	  =	25;
enum Status {OK, COULD_NOT_CREATE_DB_FILES,
			DB_FILES_NOT_FOUND, NO_FILES_IN_DIRECTORY, CANNOT_OPEN_FILE};
enum DocumentStatus { DONT_CARE, REQUIRED, FORBIDDEN };




/**
  *	DocAndWeight struct is for the concatanated list, and it contains
  * a pair of document number and the weight
  **/
struct DocAndWeight
{
	int		DocumentIndex;
	int		NumberOfOccurrencesOfWordInDoc;
	float	Weight;		//where searching, weight is the TF value
};


/**
  *	DocFileAndNorm struct is for the vector, and it contains a pair of
  * the document-file-name (each document owns a file) and the norm value
  **/
struct DocFileAndNorm
{
	char	DocumentFileName[SIZE_OF_FILENAME];
	int		NumberOfWordsInDoc;
	double	Norm;
};


struct WordInfo
{
	int		nNumberOfDocuments;	//the number of Docs this word occurs in.
	double	dIDF;
};

	
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


	char	m_Word[SIZE_OF_WORD];
	int		m_nWordIndex;			//the index of the word in the Listed-Vector
};



/****************************************************************/
/*					     SearchStructs  				        */
/****************************************************************/

/**
  *	Search_DocFileAndNorm struct is for the vector, and it contains  of the 
  * document-file-name (each document owns a file), the norm value and
  * the search rank which is computed while searching
  **/
struct Search_DocFileAndNorm
{
	char	DocumentFileName[SIZE_OF_FILENAME];
	float	Norm;
	float	fSearchRank;		//document rank, computed while searching
	DocumentStatus DocStat;
};



/****************************************************************/
/*              class CVectorianModel definition                */
/****************************************************************/

class CVectorianModel
{
public:
	CVectorianModel();
	virtual ~CVectorianModel();

	void Build( const char* OutputPath, const char* SearchPath, Status& nBuildResultCode );	//returns true if build was OK
	void Search( const char* OutputPath, const char* Query, char ResultsSortedVector[][SIZE_OF_FILENAME], Status& nSearchResultStatus );
	void Show( char* FilePath );

private:
	void InitializeBuild();
	void InitializeSearch();
	//search the .stem files, fills the hash table
	//and calculates the tf value for each word:
	void SearchStemmedFiles();
	void CalculateIDFandTF();

	void FileHandler( const struct _finddata_t fileinfo );
	void WordHandler( const char* Word );
	bool PrintFileIndex();
	void CloseFiles();
	bool AreDBFilesOK();


	CHashTable<CHashedWord>		m_HashTable;
	CVector<DocFileAndNorm>		m_DocumentsVector;
	CVector<WordInfo>			m_WordsVector;	//in parallel to the listed vector; holds the WordInfo
	CVector< CDoubleEndedList<DocAndWeight> >	m_ListedVector;
	CIndexFile*					m_Dictionary;
	CIndexFile*					m_FileIndex;
	CIndexFile*					m_InvertedIndex;
	DocAndWeight				m_DocAndWeight;
	char						SEARCHED_FILES_PATH[ SIZE_OF_FILENAME ];
	char						OUTPUT_FILES_PATH[ SIZE_OF_FILENAME ];

	//for Search:
	void FillHashTable();
	void FillListedVector();
	void FillDocumentsVector();
	void ResetDocumentsVector();
	void HandleQuery( const char* Query );
	void QueryWordHandler( const char* Word );
	void SortAndPrintDocuments( char ppcResultsSortedVector[][SIZE_OF_FILENAME] );

	CVector<Search_DocFileAndNorm>		m_SearchDocumentsVector;
	bool						m_bFirstSearch;		//flag that indicates first search
	Status						m_ResultStatus;

};


#endif		//_VECTORIANMODEL_H_





