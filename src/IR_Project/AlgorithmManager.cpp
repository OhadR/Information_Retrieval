#include "AlgorithmManager.h"
#include "Parser.h"
#include <algorithm>		//sort

using namespace std;

/****************************************************************/
/*     constants to determine the paths and files names         */
/****************************************************************/

const string	DEFAULT_SEARCHED_FILES_PATH= "..\\FILES\\";

void WriteWordInfoToFile(CIndexFile* pFile, const SWordInfo& WI)
{
	pFile->WriteString( WI.m_Word );
	pFile->WriteSpace();
	pFile->WriteInt( WI.m_DocID );
	pFile->WriteSpace();
	pFile->WriteInt( WI.m_IndexInDoc );
	pFile->WriteLine();
}

CAlgorithmManager::CAlgorithmManager()
:	m_Dictionary(NULL),
	m_nTotalWordsCounter(0),
	m_nUniqueWordsCounter(0),
	m_HashTable( MAX_NUM_OF_WORDS ),
	m_pListener(NULL),
	m_nNumOfWordsFilteredSinceTooShort(0),
	m_nNumOfWordsFilteredSinceTooLong(0)
	//m_nNumOfWordsFilteredSinceDigitWasIn(0)
{
}

CAlgorithmManager::~CAlgorithmManager()
{
	CloseDictionaryFile();
}

void CAlgorithmManager::CloseDictionaryFile()
{
	if( !m_Dictionary )
		return;
	//m_Dictionary->Close();
	delete m_Dictionary;
	m_Dictionary = NULL;
}

void CAlgorithmManager::SetSearchedFilesPath(const std::string& Path)
{
	if( ! Path.empty() )
		m_SearchedFilesPath = Path;
	else
		m_SearchedFilesPath = DEFAULT_SEARCHED_FILES_PATH;
}


void CAlgorithmManager::PrepareDictionaryFile()
{
	string pcTemp = m_SearchedFilesPath;
	pcTemp += "\\DICTIONARY.TXT" ;
	//make sure i didnt created it already
	CloseDictionaryFile();
	m_Dictionary = new CIndexFile( pcTemp, false );
	
	//write header to Dictionary file:
	m_Dictionary->WriteString( "Word" );
	m_Dictionary->WriteSpace();
	m_Dictionary->WriteString( "DocID" );
	m_Dictionary->WriteSpace();
	m_Dictionary->WriteString( "IndexInDoc" );
	m_Dictionary->WriteLine();
}

/**
  * search the *.SGM file(s), in each one search for documents and split to words:
  * and put the words that are OK in the vector.
  * when building the DB, the flag is true, when searching it is false:
  **/
void CAlgorithmManager::SearchReuterFiles(
							bool bIsBuildProcess,
							int nSearchDocID /*= 0*/)
{
	long hFile;
	struct _finddata_t fileinfo;
  
	string strFileSpec = m_SearchedFilesPath + "*.SGM";
	
	//open current directory
	if ( (hFile = _findfirst( strFileSpec.c_str(), &fileinfo)) == -1L)
	{
		return;
	}	

	if( bIsBuildProcess )
		FileHandlerInBuildProcess( fileinfo );
	else
		FileHandlerInSearchProcess( fileinfo, nSearchDocID );

	while ( _findnext(hFile, &fileinfo) != -1 ) 
	{
		if( bIsBuildProcess )
			FileHandlerInBuildProcess( fileinfo );
		else
			FileHandlerInSearchProcess( fileinfo, nSearchDocID );
	}

	_findclose( hFile );
}

void CAlgorithmManager::FileHandlerInBuildProcess( const struct _finddata_t fileinfo )
{
	string	fileName;

	fileName = m_SearchedFilesPath + fileinfo.name;
	   
	//open file:
	if ( (m_pFile = fopen(fileName.c_str() , "r")) == NULL)
	{
		return;
	}

	WORD nDocID(0);
	while( true )
	{
		//put the "fp" on the new document
		nDocID = SearchForNewDoc();
		if( nDocID == -1 )		//if error
		{
			ErrorMessageBox("Error while searching for a new document");
			break;
		}
		else if( ! nDocID )		//if end of *.SGM file
		{
			break;	
		}
		string FirstLineInDocument;
		if( ! SearchForDocBody( FirstLineInDocument ) )
		{
			ErrorMessageBox("Error while searching for document body");
		}
		m_DocumentsIdColl.push_back( nDocID );
		HandleDocument( nDocID, FirstLineInDocument );
	}
	fclose (m_pFile);
}

//search a document by "NEWID"; return value:
// the document ID,
// 0 means end-of-file,
// -1 means error
long CAlgorithmManager::SearchForNewDoc()
{
	char*	word;
	static char	line [MAXLINE];

	//read another line from the file:
	while( fgets(line, MAXLINE, m_pFile) != NULL )	//if NULL, it's EOF or error
	{
		word = strtok(line, "1234567890 ,.:;&^%@'`!?*-+/#=()<>[]{}\\\"\n\t");
		while(word != NULL)
		{
			//read the sentence untill u meet "NEWID"
			if( strcmp(word, "NEWID") == 0 )
			{
				//get the document ID and get out:
				word = strtok(NULL, " ,.:;&^%@'`!?*-+/#=()<>[]{}\\\"\n\t");
				return atoi(word);
			}
				   
			word = strtok(NULL, "1234567890 ,.:;&^%@'`!?*-+/#=()<>[]{}\\\"\n\t");
		}
	}
	//EOF or error
	if( feof( m_pFile ) )
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

bool CAlgorithmManager::SearchForDocBody(OUT string& strStartOfDocumentText)
{
	char*	word;
	static char	line[MAXLINE];

	//read another line from the file:
	while( fgets(line, MAXLINE, m_pFile) != NULL )	//if NULL, it's EOF or error
	{
		word = strtok(line, "1234567890 ,.:;&^%@'`!?*-+/#=()<>[]{}\\\"\n\t");
		while(word != NULL)
		{
			//read the sentence untill u meet "BODY"
			if( strcmp(word, "BODY") == 0 )
			{
				/*//the distance of "BODY" from line's beginning:
				int nDistance = word - line;
				nDistance += 5;		//add 5 for the BODY\n sub-string
				strStartOfDocumentText = &line[ nDistance ];*/
				strStartOfDocumentText = word + 5;	//add 5 for the BODY\n sub-string
				return true;
			}
				   
			word = strtok(NULL, "1234567890 ,.:;&^%@'`!?*-+/#=()<>[]{}\\\"\n\t");
		}
	}
	//error: couldn't find <BODY>
	return false;
}

void CAlgorithmManager::HandleDocument(long nDocID,
									   IN const std::string& strFirstLineOfDocument)
{
	char*	word;
	static char	line[MAXLINE];
	int		nNumberOfWordsInDoc(0);

	//first, handle the first line in the text (we got it as parameter):
	strcpy( line, strFirstLineOfDocument.c_str() );

	do
	{
		word = strtok(line, "1234567890 ,.:;&^%@'`!?*-+/#=()<>[]{}\\\"\n\t");
		while(word != NULL)
		{
			//if we got to </BODY> - it's end of document:
			if( strcmp(word, "BODY") == 0 )
			{
				return;
			}
			//updating the number of words in the document:
			++nNumberOfWordsInDoc;

			WordHandler( word, nDocID, nNumberOfWordsInDoc );
				   
			word = strtok(NULL, "1234567890 ,.:;&^%@'`!?*-+/#=()<>[]{}\\\"\n\t");
		}
	}
	//read another line from the file:
	while( fgets(line, MAXLINE, m_pFile) != NULL );	//if NULL, it's EOF or error

	//error: couldn't find <BODY>
	ErrorMessageBox("Error while searching for end of document ");
}

void CAlgorithmManager::WordHandler(
								IN string Word,
								long	nDocID,
								long	nIndexOfWordInDoc)
{
	//statistics:
	++m_nTotalWordsCounter;
	
	//make sure there are no numbers in the word,
	//and that the length is between 3 - 13:
	if( ! WordFilterForBuild( Word ) )
		return;

	SWordInfo WordInfo;
	WordInfo.m_Word = Word;
	WordInfo.m_DocID = nDocID;
	WordInfo.m_IndexInDoc = nIndexOfWordInDoc;

	m_WordInfoColl.push_back( WordInfo );

	//write the word and it's index (in the vector) to dictionary file:
	//WriteWordInfoToFile( m_Dictionary, WordInfo );
}

//filter a word. returns true if word is OK, false means "drop it!"
bool CAlgorithmManager::WordFilterForBuild(IN string& Word) const
{
	//filter the size of the word:
	if( Word.size() < s_nMinSizeOfWord )
	{
		++m_nNumOfWordsFilteredSinceTooShort;
		return false;
	}

	if( Word.size() > s_nMaxSizeOfWord )
	{
		++m_nNumOfWordsFilteredSinceTooLong;
		return false;
	}

	//now, convert all letters to lower-case, and check for numbers in the word.
	//if there is a number in the word - drop it:
	for(string::iterator it = Word.begin(); it != Word.end(); ++it)
	{
		if( *it >= 'A' && *it <= 'Z' )
		{
			*it += 32;
		}
		/*if( *it >= '0' && *it <= '9' )
		{
			++m_nNumOfWordsFilteredSinceDigitWasIn;
			return false;
		}*/
	}

	return true;
}


// when one SWordInfo is smaller that the other?
// 1, when its string is smaller, according to string::operator<
// 2. when the strings are equal, but the document index is smaller
bool operator < (const SWordInfo& lhs, const SWordInfo& rhs)
{
	return ( 
/*.1.*/		( lhs.m_Word < rhs.m_Word ) ||			
/*.2.*/		( (lhs.m_Word == rhs.m_Word) && (lhs.m_DocID < rhs.m_DocID) ) ||
/* 3 */		( (lhs.m_Word == rhs.m_Word) && (lhs.m_DocID == rhs.m_DocID) && (lhs.m_IndexInDoc < rhs.m_IndexInDoc) )	);
}


void CAlgorithmManager::SortWordsCollection()
{
	sort(m_WordInfoColl.begin(), m_WordInfoColl.end());
}

void CAlgorithmManager::CalcAndRemoveStopWords()
{
	int			nInstanceCounter(0);
	string		PreviousWord = m_WordInfoColl[0].m_Word;
	SWordInfoCollection::iterator StartWordIt, it;
	const int c_nMaxInstancesOfWordAllowed = m_nTotalWordsCounter * 0.005;
	for(it = m_WordInfoColl.begin();
		it != m_WordInfoColl.end(); ++it)
	{
		++nInstanceCounter;
		if( (*it).m_Word != PreviousWord )
		{
			if( nInstanceCounter >= c_nMaxInstancesOfWordAllowed )
			{
				//delete the word
				it = m_WordInfoColl.erase(StartWordIt, it);
				//add the word to the stop list:
				m_StopList.push_back( PreviousWord );
			}
			//update the veriables:
			PreviousWord = (*it).m_Word;
			StartWordIt = it;
			nInstanceCounter = 0;	//for the next word
		}
	}
	
	//debug
	for(it = m_WordInfoColl.begin();
		it != m_WordInfoColl.end(); ++it)
	{
		WriteWordInfoToFile( m_Dictionary, *it );
	}
}


void CAlgorithmManager::BuildHashTable()
{
	CHashedWord HashedWord;
	string		PreviousWord = m_WordInfoColl[0].m_Word;
	int			nIndex(0);
	int			nInstanceCounter(-1);	//because of the first iteration, i need the ++ to bring me to 0, not to 1
	for(int i = 0; i < m_WordInfoColl.size(); ++i)
	{
		++nInstanceCounter;
		//NOTE: i insert hte (previous) word only when i meet new word!!!
		if( m_WordInfoColl[i].m_Word != PreviousWord )
		{
			HashedWord.m_Word = PreviousWord;
			HashedWord.m_nWordIndex = nIndex;
			HashedWord.m_nNumOfInstances = nInstanceCounter;
			m_HashTable.Insert( HashedWord );
			//debug:
			++m_nUniqueWordsCounter;
		
			//update the veriables:
			PreviousWord = m_WordInfoColl[i].m_Word;
			nIndex = i;
			nInstanceCounter = 0;	//for the next word
		}
	}
}

/*****************************************************/

/*****************************************************/

void CAlgorithmManager::FileHandlerInSearchProcess(
											const struct _finddata_t fileinfo,
											int nSearchedDocId)
{
	string	fileName;

	fileName = m_SearchedFilesPath + fileinfo.name;
	   
	//open file:
	if ( (m_pFile = fopen(fileName.c_str() , "r")) == NULL)
	{
		return;
	}

	long nRetVal(0);
	while( true )
	{
		//put the "fp" on the new document
		nRetVal = SearchForSpecificDoc( nSearchedDocId );
		if( nRetVal == -1 )		//if error
		{
			ErrorMessageBox("Error while searching for a specific document");
			fclose (m_pFile);
			return;
		}
		else if( ! nRetVal )		//if end of *.SGM file
		{
			fclose (m_pFile);
			return;
		}
		else if( nRetVal == -2 )	//found!!!
		{
			break;
		}
	}
	string StartOfDocumentText;
	if( ! SearchForDocBody( StartOfDocumentText ) )
	{
		ErrorMessageBox("Error while searching for document body");
	}
	GetDocument( StartOfDocumentText );
	fclose (m_pFile);
}

//search a document by "NEWID" and the document ID; return value:
// 0 means end-of-file,
// -1 means error
// -2 if the document ID was found,
long CAlgorithmManager::SearchForSpecificDoc(int nSearchedDocId)
{
	char pc[30];
	sprintf(pc, "NEWID=\"%d\"", nSearchedDocId );

	char*	word;
	static char	line [MAXLINE];

	//read another line from the file:
	while( fgets(line, MAXLINE, m_pFile) != NULL )	//if NULL, it's EOF or error
	{
		//since im looking for <NEWID="XXX">, the delimiters can NOT be numbers:
		word = strtok(line, " ,.:;&^%@'`!?*-+/#()<>[]{}\\\n\t");
		while(word != NULL)
		{
			//read the sentence untill u meet "NEWID"
			if( strcmp(word, pc) == 0 )
			{
				//get the document ID and get out:
				word = strtok(NULL, " ,.:;&^%@'`!?*-+/#()<>[]{}\\\n\t");
				return -2;
			}
				   
			//since im looking for <NEWID="XXX">, the delimiters can NOT be numbers:
			word = strtok(NULL, " ,.:;&^%@'`!?*-+/#()<>[]{}\\\n\t");
		}
	}
	//EOF or error
	if( feof( m_pFile ) )
	{
		return 0;
	}
	else
	{
		return -1;
	}

}

void CAlgorithmManager::GetDocument(IN const std::string& strFirstLineOfDocument)
{
	//print line after line:
	char*			word;
	static char		line[MAXLINE];
	string			strLine = strFirstLineOfDocument;
	int				nNumberOfWordsInDoc(0);
	int				nStrLineSize, nNumOfCharsAdded;;

	//read another line from the file:
	while( fgets(line, MAXLINE, m_pFile) != NULL )	//if NULL, it's EOF or error
	{
		//delete the garbage in the end of the read string:
		strLine.erase( strLine.end() - 1 );
		//add \n to it:
		strLine += "\r\n";

		nStrLineSize = strLine.size();
		strLine += line;
		nNumOfCharsAdded = strLine.size() - nStrLineSize;
		//check if it is </BODY>. if so - it's end of document:
		word = strtok(line, "1234567890 ,.:;&^%@'`!?*-+/#=()<>[]{}\\\"\n\t");
		while(word != NULL)
		{
			//if we got to </BODY> - it's end of document:
			if( strcmp(word, "BODY") == 0 )
			{
				//end of document
				//the distance of "BODY" from line's beginning:
				int nNumOfCharsToDelete = line + nNumOfCharsAdded - word + 2;
				//nDistance += 5;		//add 5 for the BODY\n sub-string
				//delete the garbage in the end of the read string:
				strLine.erase( strLine.end() - nNumOfCharsToDelete, strLine.end() );

				m_pListener->Write( strLine );
				return;
			}
				   
			word = strtok(NULL, "1234567890 ,.:;&^%@'`!?*-+/#=()<>[]{}\\\"\n\t");
		}
	}
	//error: couldn't find <BODY>
	ErrorMessageBox("Error while searching for end of document ");
}

/*****************************************************/

/*****************************************************/

TDocIdVector CAlgorithmManager::Search(const std::string& Query)
{
	TDocIdVector ResultsVec = CParser::GetInstance()->Parse( Query );
	return ResultsVec;
}

//get a word and retrieve all the documents the word is in:
TDocIdVector CAlgorithmManager::SearchWord(const std::string& Word)
{
	TDocIdVector ResultsColl;
	if( Word.empty() )
	{
		ErrorMessageBox("Error: empty word was entered");
		return ResultsColl;		//return empty vector
	}
	
	//make sure there are no numbers in the word,
	//and that the length is between 3 - 13:
	if( ! WordFilter( const_cast<string&>(Word) ) )
		return ResultsColl;

	//make sure the word is not on the stop-list:
	for(TWordsCollection::const_iterator c_WordsIt = m_StopList.begin();
	c_WordsIt != m_StopList.end(); ++c_WordsIt)
	{
		if( Word == *c_WordsIt )
		{
			ErrorMessageBox("Error: word entered is in Stop List");
			return ResultsColl;

		}
	}
	
	CHashedWord HashedWord;
	CHashedWord* pHashedWord;
	HashedWord.m_Word = Word;
	//retrieve from the table the data about the word we are looking for:
	pHashedWord = m_HashTable.Find( HashedWord );
	
	if( ! pHashedWord )		//if word was not found
	{
		string message("Error: word entered '" + Word + "' is not found in Hash Table");
		ErrorMessageBox(message);
		return ResultsColl;			//return empty vector
	}
	
	SWordInfo WordInfo;
	int		nPreviousDocId(0);
	for( int i = 0; i < pHashedWord->m_nNumOfInstances; ++i )
	{
		WordInfo = m_WordInfoColl[ pHashedWord->m_nWordIndex + i ];
		if( WordInfo.m_DocID != nPreviousDocId )
		{
			nPreviousDocId = WordInfo.m_DocID;
			ResultsColl.push_back( WordInfo.m_DocID );
		}
	}
	return ResultsColl;
}

TDocIdVector CAlgorithmManager::SearchNearWords(
		const TWordsCollection& LeftColl,
		const TWordsCollection& RightColl,
		int nBefore, int nAfter,
		bool bNot /*= false*/)
{
	TDocIdVector ResultsColl;
	TDocIdVector TempColl;
	for(TWordsCollection::const_iterator cit1 = LeftColl.begin(); cit1 != LeftColl.end(); ++cit1)
	{
		for(TWordsCollection::const_iterator cit2 = RightColl.begin(); cit2 != RightColl.end(); ++cit2)
		{
			TempColl = SearchNearWords(*cit1, *cit2, nBefore, nAfter, bNot);
			ResultsColl.insert( ResultsColl.end(), TempColl.begin(), TempColl.end() );
		}
	}
	return ResultsColl;
}

TDocIdVector CAlgorithmManager::SearchNearWords(
		const std::string& FirstWord,
		const std::string& SecondWord,
		int nBefore, int nAfter,
		bool bNot /*= false*/)
{
	TDocIdVector ResultsColl;
	if( FirstWord.empty() || SecondWord.empty() )
	{
		ErrorMessageBox("Error: empty word was entered in NEAR operator");
		return ResultsColl;		//return empty vector
	}
	
	//make sure there are no numbers in the word,
	//and that the length is between 3 - 13:
	if( ! WordFilter( const_cast<string&>(FirstWord) ) )
	{
		ErrorMessageBox("Error: 1st word entered in NEAR operator is wrong");
		return ResultsColl;
	}

	if( ! WordFilter( const_cast<string&>(SecondWord) ) )
	{
		ErrorMessageBox("Error: 2nd word entered in NEAR operator is wrong");
		return ResultsColl;
	}

	//make sure the word is not on the stop-list:
	for(TWordsCollection::const_iterator c_WordsIt = m_StopList.begin();
	c_WordsIt != m_StopList.end(); ++c_WordsIt)
	{
		if( FirstWord == *c_WordsIt || SecondWord == *c_WordsIt )
		{
			ErrorMessageBox("Error: word entered in NEAR operator is in Stop List");
			return ResultsColl;
		}
	}
	
	CHashedWord HashedWord;
	HashedWord.m_Word = FirstWord;
	//retrieve from the table the data about the word we are looking for:
	CHashedWord* pFirstHashedWord = m_HashTable.Find( HashedWord );
	HashedWord.m_Word = SecondWord;
	CHashedWord* pSecondHashedWord = m_HashTable.Find( HashedWord );
	
	if( ! pFirstHashedWord || ! pSecondHashedWord )		//if word was not found
	{
		ErrorMessageBox("Error: word entered in NEAR operator is not found in Hash Table");
		return ResultsColl;			//return empty vector
	}
	
	SWordInfo LeftWordInfo, RightWordInfo;
	int		nPreviousDocId(0);
	//the core of the NEAR operator:
	for( int i = 0; i < pFirstHashedWord->m_nNumOfInstances; ++i )
	{
		LeftWordInfo = m_WordInfoColl[ pFirstHashedWord->m_nWordIndex + i ];
		for( int j = 0; j < pSecondHashedWord->m_nNumOfInstances; ++j )
		{
			RightWordInfo = m_WordInfoColl[ pSecondHashedWord->m_nWordIndex + j ];
			if(RightWordInfo.m_DocID == LeftWordInfo.m_DocID)
			{
				if( (RightWordInfo.m_IndexInDoc > LeftWordInfo.m_IndexInDoc)
					&& ((RightWordInfo.m_IndexInDoc - LeftWordInfo.m_IndexInDoc) <= nAfter) )
				{
					ResultsColl.push_back( RightWordInfo.m_DocID );
					break;		//we found it compatible - no need 2 keep searching
				}
				if( (LeftWordInfo.m_IndexInDoc > RightWordInfo.m_IndexInDoc)
					&& ((LeftWordInfo.m_IndexInDoc - RightWordInfo.m_IndexInDoc) <= nBefore) )
				{
					ResultsColl.push_back( RightWordInfo.m_DocID );
					break;		//we found it compatible - no need 2 keep searching
				}
			}
			else if(RightWordInfo.m_DocID > LeftWordInfo.m_DocID)
			{
				break;
			}
		}
	}
	return ResultsColl;
}

/*****************************************************/

/*****************************************************/

bool CAlgorithmManager::AddGroup(const std::string& GrpName, const std::string& GrpMembers) const
{
	return CParser::GetInstance()->AddGroup(GrpName, GrpMembers);
}
