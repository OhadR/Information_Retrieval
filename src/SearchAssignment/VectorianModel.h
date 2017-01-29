////////////////////////////////////////////////////////////////////////
// VectorianModel.h

/****************************************************************/
/*					NEW VERSION - OCTOBER 2000					*/
/*		all CVector's were replaced by vector of STL!!!			*/
/*		CDoubleEndedList was replaced by list of STL!!!			*/
/****************************************************************/

#ifndef _VECTORIANMODEL_H_
#define _VECTORIANMODEL_H_

#include <stdio.h>		// FILE
#include <string.h>
#include <io.h>			// _findfirst, etc...
#include <math.h>		// log, sqrt

#include "../Basic/Hash.h"
#include "../Basic/IndexFile.h"
#include "../Basic/HashedWord.h"

#include <string>
#include <vector>
#include <list>
using namespace std;



const long  MAX_NUM_OF_WORDS  = 100000;
const int	MAX_NUM_OF_FILES  =	1000;
const int	MAXLINE			  =	1000;
const int	MAX_ITEMS_IN_ROW  = 50;
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
	string	DocumentFileName;
	int		NumberOfWordsInDoc;
	double	Norm;
};


struct WordInfo
{
	int		nNumberOfDocuments;	//the number of Docs this word occurs in.
	double	dIDF;
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
	string	DocumentFileName;
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
	void Search( const char* OutputPath, const char* Query, string ResultsSortedVector[], Status& nSearchResultStatus );
	void Show( string& FilePath );

private:
	void InitializeBuild();
	void InitializeSearch();
	//search the .stem files, fills the hash table
	//and calculates the tf value for each word:
	void SearchStemmedFiles();
	void CalculateIDFandTF();

	void FileHandler( const struct _finddata_t fileinfo );
	void WordHandler( const string Word );
	bool PrintFileIndex();
	void CloseFiles();
	bool AreDBFilesOK();


	CHashTable<CHashedWord>		m_HashTable;
	vector<DocFileAndNorm>		m_DocumentsVector;
	vector<WordInfo>			m_WordsVector;	//in parallel to the listed vector; holds the WordInfo
	vector< list<DocAndWeight> >	m_ListedVector;
	CIndexFile*					m_Dictionary;
	CIndexFile*					m_FileIndex;
	CIndexFile*					m_InvertedIndex;
	DocAndWeight				m_DocAndWeight;
	string						SEARCHED_FILES_PATH;
	string						OUTPUT_FILES_PATH;

	//for Search:
	void FillHashTable();
	void FillListedVector();
	void FillDocumentsVector();
	void ResetDocumentsVector();
	void HandleQuery( const char* Query );
	void QueryWordHandler( const string& Word );
	void SortAndPrintDocuments( string ppcResultsSortedVector[] );

	vector<Search_DocFileAndNorm>		m_SearchDocumentsVector;
	bool						m_bFirstSearch;		//flag that indicates first search
	Status						m_ResultStatus;

};


#endif		//_VECTORIANMODEL_H_