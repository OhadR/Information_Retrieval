
#ifndef _ALGORITHMMANAGER_H_
#define _ALGORITHMMANAGER_H_

#include <io.h>			// _findfirst, etc...
#include <cstdio>		// FILE
#include <cmath>		// log, sqrt
//#include <string>		//included by IndexFile.h
//#include <vector>		//included by Hash.h

#include "../Basic/Hash.h"
#include "../Basic/IndexFile.h"
#include "../Basic/HashedWord.h"
#include "Utils.h"

const long  MAX_NUM_OF_WORDS  = 100000;

const int	MAXLINE			  =	1000;

struct SWordInfo
{
	std::string		m_Word;
	short			m_DocID;
	short			m_IndexInDoc;

};

//for the "sort" function:
bool operator < (const SWordInfo& lhs, const SWordInfo& rhs);


/****************************************************************/
/*              class CRegistrated definition			        */
/****************************************************************/

struct CRegistrated
{
	virtual void Write(const std::string&) = 0;
};

/****************************************************************/
/*              class CAlgorithmManager definition              */
/****************************************************************/

class CAlgorithmManager
{
public:
	static CAlgorithmManager* Instance()
	{
		static CAlgorithmManager AlgorithmManager;
		return &AlgorithmManager;
	}

	void SetSearchedFilesPath(const std::string& Path);

	void BuildDataBase()
	{
		Clear();
		PrepareDictionaryFile();
		SearchReuterFiles(true);
		SortWordsCollection();
		CalcAndRemoveStopWords();
		BuildHashTable();
	}

	TDocIdVector Search(const std::string& Query);

	//get a word and retrieve all the documents the word is in:
	TDocIdVector SearchWord(const std::string& Word);

	//special implementation to the "near" operator:
	TDocIdVector SearchNearWords(
		const TWordsCollection& FirstWord,
		const TWordsCollection& SecondWord,
		int nBefore, int nAfter,
		bool bNot = false);

	//gets the vector of all the documents ID's:
	TDocIdVector GetDocuments() const
	{	return m_DocumentsIdColl;	}

	//when we wanna show document "DocId", the user call this function:
	void SearchForDocument(long nDocId)
	{
		SearchReuterFiles(false, nDocId);
	}

	void SetListener(CRegistrated* pListener)
	{	m_pListener = pListener;	}
	
	~CAlgorithmManager();

	bool AddGroup(const std::string& GrpName, const std::string& GrpMembers) const;

	//diagnostics interface:
	int GetNumOfWordsFilteredSinceTooShort() const
	{	return m_nNumOfWordsFilteredSinceTooShort;	}
	int GetNumOfWordsFilteredSinceTooLong() const
	{	return m_nNumOfWordsFilteredSinceTooLong;	}
	int GetNumOfTotalWords() const
	{	return m_nTotalWordsCounter;	}
	int GetNumOfUniqueWords() const
	{	return m_nUniqueWordsCounter;	}
	std::vector<std::string> GetStopList() const
	{	return m_StopList;	}

private:
	CAlgorithmManager();

	void		Clear()
	{
		m_WordInfoColl.clear();
		m_StopList.clear();
		m_HashTable.Clear();
		m_nTotalWordsCounter = 0;				//num of words, with repititions:
		m_nUniqueWordsCounter = 0;
		m_nNumOfWordsFilteredSinceTooShort = 0;		//with repititions, "up" can appear twice...
		m_nNumOfWordsFilteredSinceTooLong = 0;		//same remark like "Short"
		//m_nNumOfWordsFilteredSinceDigitWasIn = 0;
	}

	void CloseDictionaryFile();

	void PrepareDictionaryFile();

	//search the *.SGM file(s), in each one search for documents and split to words:
	//when building the DB, the flag is true, when searching it is false:
	void SearchReuterFiles(
		bool bIsBuildProcess,
		int nSearchDocID = 0);

	//handles *.SGM file in the build process
	void FileHandlerInBuildProcess( const struct _finddata_t fileinfo );
	//handles *.SGM file in the search process
	void FileHandlerInSearchProcess(
		const struct _finddata_t fileinfo,
		int nDocId );
	

	//search a document by "NEWID"; return value:
	// the document ID,
	// 0 means end-of-file,
	// -1 means error
	long SearchForNewDoc();
	
	//when finding <BODY>, there is the beginning of the text right after it, so
	//i must give out this string, since it is part of the text and if i don't,
	//i have no other way to get it:
	bool SearchForDocBody(OUT std::string& strStartOfDocument);
	void HandleDocument(long nDocID,
		IN const std::string& strFirstLineOfDocument);

	//handles a word
	void WordHandler(
		IN std::string Word,	//non-const, since we may change it to lower case
		long	nDocID,
		long	nIndexOfWordInDoc);

	//filter a word. returns true if word is OK, false means "drop it!"
	//this method is used in the build process, os it updates the "declined" members:
	bool WordFilterForBuild(IN std::string& Word) const;

	void SortWordsCollection();

	void CalcAndRemoveStopWords();

	void BuildHashTable();

	//search a document by "NEWID" and the document ID; return value:
	// -2 if the document ID was found,
	// 0 means end-of-file,
	// -1 means error
	long SearchForSpecificDoc(int nDocID);

	void GetDocument(IN const std::string& strFirstLineOfDocument);

	//special implementation to the "near" operator:
	TDocIdVector SearchNearWords(
		const std::string& FirstWord,
		const std::string& SecondWord,
		int nBefore, int nAfter,
		bool bNot = false);

	std::string					m_SearchedFilesPath;

	//the file-ptr that we work on in the build session:
	FILE*						m_pFile;		
	typedef	std::vector<SWordInfo>		SWordInfoCollection;
	SWordInfoCollection			m_WordInfoColl;
	std::vector<std::string>	m_StopList;
	TDocIdVector				m_DocumentsIdColl;
	CHashTable<CHashedWord>		m_HashTable;

	CRegistrated*				m_pListener;

	//statistics only:
	CIndexFile*					m_Dictionary;
	int							m_nTotalWordsCounter;				//num of words, with repititions:
	//num of words different from each other:
	int							m_nUniqueWordsCounter;
	mutable int					m_nNumOfWordsFilteredSinceTooShort;		//with repititions, "up" can appear twice...
	mutable int					m_nNumOfWordsFilteredSinceTooLong;		//same remark like "Short"
	//mutable int					m_nNumOfWordsFilteredSinceDigitWasIn;

};

void WriteWordInfoToFile(CIndexFile* pFile, const SWordInfo& WI);	


#endif		//_ALGORITHMMANAGER_H_