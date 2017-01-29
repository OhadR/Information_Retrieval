///////////////////////////////////////////////////////////////
// VectorianModel.cpp

#include "VectorianModel.h"



/****************************************************************/
/*     constants to determine the paths and files names         */
/****************************************************************/

const char* DEFAULT_SEARCHED_FILES_PATH	= "D:\\MY DOCUMENTS\\IR_PROJECT\\FILES\\";
const char* DEFAULT_OUTPUT_FILES_PATH	= "D:\\MY DOCUMENTS\\IR_PROJECT\\FILES\\";

const char* DICTIONARY_FILE_NAME		= "\\DICTIONARY.TXT";
const char* FILE_INDEX_FILE_NAME		= "\\FILE_INDEX.TXT";
const char* INVERTED_INDEX_FILE_NAME	= "\\INVERTED_INDEX.TXT";
const char* IDF_FILE_NAME				= "\\IDF.TXT";
const char* FILES_AND_RANKS				= "\\FILES_AND_RANKS.TXT";



/****************************************************************/
/*               class CHashedWord implementation               */
/****************************************************************/

CHashedWord::CHashedWord()
{
	m_nWordIndex	= 0;
}


int CHashedWord::HashValue() const
{
	int i = 0;			//index
	int nHashVal = 0;	//hash value
	while( m_Word[i] != '\0')
	{
		nHashVal += ( m_Word[i] * ( i+1 ) );
		i++;
	}
	return nHashVal;
}

bool CHashedWord::operator ==(const CHashedWord& HashedWord)const
{
	if( !strcmp( m_Word, HashedWord.m_Word ) )	//strings are identical
	{
		return true;
	}
	return false;
}

CHashedWord& CHashedWord::operator = (const CHashedWord& HashedWord)
{
    strcpy(m_Word, HashedWord.m_Word);
	m_nWordIndex = HashedWord.m_nWordIndex;

    return *this;
}

/**
  *	this operator is used to clean the node, when cleaning the hast table:
  **/
CHashedWord& CHashedWord::operator = ( void* something )
{
    strcpy( m_Word, "" );
	m_nWordIndex = 0;

    return *this;
}


/****************************************************************/
/*             class CVectorianModel implementation             */
/****************************************************************/

CVectorianModel::CVectorianModel() 
	:	m_HashTable( MAX_NUM_OF_WORDS )
{
	m_bFirstSearch			= true;
}


CVectorianModel::~CVectorianModel()
{
}


void CVectorianModel::Build( const char* SearchPath, const char* OutputPath, Status& nBuildResultStatus )
{
	InitializeBuild();

	if( strcmp( OutputPath, "" ) == 0 )
	{
		strcpy( OUTPUT_FILES_PATH, DEFAULT_OUTPUT_FILES_PATH );
	}
	else
	{
		strcpy( OUTPUT_FILES_PATH, OutputPath );
	}
	
	char pcTemp[ SIZE_OF_FILENAME ];
	strcpy( pcTemp, OUTPUT_FILES_PATH );
	strcat( pcTemp, DICTIONARY_FILE_NAME );
	m_Dictionary = new CIndexFile( pcTemp, false );

	strcpy( pcTemp, OUTPUT_FILES_PATH );
	strcat( pcTemp, FILE_INDEX_FILE_NAME );
	m_FileIndex = new CIndexFile( pcTemp, false );

	strcpy( pcTemp, OUTPUT_FILES_PATH );
	strcat( pcTemp, INVERTED_INDEX_FILE_NAME );
	m_InvertedIndex = new CIndexFile( pcTemp, false );

	if( !AreDBFilesOK() )
	{
		m_ResultStatus = COULD_NOT_CREATE_DB_FILES;
		nBuildResultStatus = m_ResultStatus;
		return;
	}

	if( strcmp( SearchPath, "" ) == 0 )
	{
		strcpy( SEARCHED_FILES_PATH, DEFAULT_SEARCHED_FILES_PATH );
	}
	else
	{
		strcpy( SEARCHED_FILES_PATH, SearchPath );
		strcat( SEARCHED_FILES_PATH, "\\");
	}
	
	SearchStemmedFiles();
	CalculateIDFandTF();
	PrintFileIndex();
	CloseFiles();

	//indicator to searcher, to update its storage structures since Build maybe changed 
	//the DB files:
	m_bFirstSearch = true;

	nBuildResultStatus = m_ResultStatus;	//Send Build Status
}


/**
  *	this method cleans all the data structures from previous build
  **/
void CVectorianModel::InitializeBuild()
{
	//clean hash table (in case of more than one "Build", table already contains
	//all words, so nothing will be registered to it. Therefore, Dictionary file
	//will be empty!
	m_HashTable.Clear();
	//clean also this vector, since WordIndex is determeined by its size:
	m_DocumentsVector.Clear();
	m_WordsVector.Clear();
	m_ListedVector.Clear();

	m_ResultStatus	= OK;
}


/**
  *	this method checks wether the DataBase files were opened properly or not:
  **/
bool CVectorianModel::AreDBFilesOK()
{
	if ( m_Dictionary->EndOfFile()  ||
		 m_FileIndex->EndOfFile()	||
		 m_InvertedIndex->EndOfFile() )
	{
		return false;
	}
	else
	{
		return true;
	}
}


/**
  * This method searches all stemmed files, creates the hash table and 
  * fills the class members.
  **/
void CVectorianModel::SearchStemmedFiles()
{
	char cFileSpec[SIZE_OF_FILENAME];
	long hFile;
	struct _finddata_t fileinfo;
	m_DocAndWeight.DocumentIndex = -1;	//we update b4 entering, & cant in end otherwise index will b 2 big
  
	//printf("dir %s\n", SEARCHED_FILES_PATH);	//good for console application:

	sprintf( cFileSpec, "%s%s", SEARCHED_FILES_PATH, "*.STEM");
	
	//write header to Dictionary file:
	m_Dictionary->WriteString( "Word" );
	m_Dictionary->WriteSpace();
	m_Dictionary->WriteString( "Word Index" );
	m_Dictionary->WriteLine();

	//open current directory
	if ( (hFile = _findfirst( cFileSpec, &fileinfo)) == -1L)
	{
		/* //good for console application:
		printf( "No files in current directory!\n" );
		exit(1);
		*/
		m_ResultStatus = NO_FILES_IN_DIRECTORY;
		return;
	}	

	FileHandler( fileinfo );

	while ( _findnext(hFile, &fileinfo) != -1 ) 
	{

		FileHandler( fileinfo );

	}

	_findclose( hFile );
}


void CVectorianModel::FileHandler( const struct _finddata_t fileinfo )
{
	FILE*	fp;       
	char*	word;
	char	fileName[SIZE_OF_FILENAME];
	char	line [MAXLINE];
	int		nNumberOfWordsInDoc;
	DocFileAndNorm		DocFileAndNorm;


	//updating the document index:
	m_DocAndWeight.DocumentIndex++;
	//new document - clear words counter:
	nNumberOfWordsInDoc = 0;

	sprintf( fileName, "%s%s", SEARCHED_FILES_PATH, fileinfo.name );
	//printf( "FileName: %s\n", fileName );	//good for console application
	   
	//open file:
	if ( (fp = fopen((fileName) , "r")) == NULL)
	{
		/* //good for console application:
		printf("can't open file filename %s\n",fileName);
		exit(1);
		*/
		m_ResultStatus = CANNOT_OPEN_FILE;
		return;
	}

	while (fgets(line, MAXLINE, fp)!= NULL)	//if NULL, it's EOF or error
	{
		//since its a stemmed file, the only delimeter is space or \n\t
		word = strtok(line, " ,.:;&^%@'`!?*-+/#=()<>[]{}\\\"\n\t");
		while(word != NULL)
		{
			//updating the number of words in the document:
			nNumberOfWordsInDoc++;

			WordHandler( word );
				   
			word = strtok(NULL, " ,.:;&^%@'`!?*-+/#=()<>[]{}\\\"\n\t");
		}
	}
	fclose (fp);
   	   
	DocFileAndNorm.NumberOfWordsInDoc = nNumberOfWordsInDoc;
	strcpy( DocFileAndNorm.DocumentFileName, fileinfo.name );
	DocFileAndNorm.Norm = double( 0 );

	//make new entry in the vector for the DocFile&Norm:
	m_DocumentsVector.Insert( DocFileAndNorm );
}


void CVectorianModel::WordHandler( const char* Word )
{
	CHashedWord HashedWord;
	WordInfo	WordInfo;
	int nIndexInTable;
	strcpy( HashedWord.m_Word, Word );

	nIndexInTable = m_HashTable.FindIndex( HashedWord );
	if( nIndexInTable == -1)		//word is new (not in hash table)
	{
		//create a List object, so we can inset in the ListedVector:
		CDoubleEndedList<DocAndWeight> list;

		HashedWord.m_nWordIndex = m_WordsVector.Size();
		//insert new word into hash table:
		m_HashTable.Insert( HashedWord );

		WordInfo.nNumberOfDocuments = 1;

		m_DocAndWeight.NumberOfOccurrencesOfWordInDoc = 1;
		//make new entry in the vector for the list:
		m_ListedVector.Insert( list );
		//add word into the ListedVector as first element, by the index we got 
		m_ListedVector[HashedWord.m_nWordIndex].AddToEnd( m_DocAndWeight );
		//make new entry in the WordsVector, and keep the info there:
		m_WordsVector.Insert( WordInfo );
		//write the word and it's index (in the vector) to dictionary file:
		m_Dictionary->WriteString( Word );
		m_Dictionary->WriteSpace();
		m_Dictionary->WriteInt( HashedWord.m_nWordIndex );
		/********** 	printing hash value - not needed!!!!!!!!	******************/
		//m_Dictionary->WriteSpace();
		//m_Dictionary->WriteInt( HashedWord.HashValue() );
		/************************* until here not needed *****************************/
		m_Dictionary->WriteLine();
	}
	else	//word is not new - it's already in the hash table
	{
		//we give only the word, and get all information about it from hash table:
		HashedWord = *m_HashTable.Find( HashedWord );
		//if it's the first occurence of this word in this document
		if( m_ListedVector[HashedWord.m_nWordIndex].GetLastElement()->DocumentIndex != m_DocAndWeight.DocumentIndex/*Nd*/ )
		{
			m_ListedVector[HashedWord.m_nWordIndex].AddToEnd( m_DocAndWeight );
			
			m_WordsVector[HashedWord.m_nWordIndex].nNumberOfDocuments++;
		}
		//increase # of occurences of this word in this doc:
		m_ListedVector[HashedWord.m_nWordIndex].GetLastElement()->NumberOfOccurrencesOfWordInDoc++;
	}

}


/**
  *  TF(w,d) = NumberOfOccurrencesOf_wIn_d / NumbrOfWordsInDoc
  *  IDF(w) = log( TotalNumberOfDocs / DocsWith_w )
  *   this method runs all over the words, all over each word's list and calculates
  *   the TF value and IDF, multiply them and makes power, as required:
  *  NORM(d) = sqrt( sum_i( TF(w_i,d), IDF(w_i) )^2 )
  *   root will be done later.
  **/
void CVectorianModel::CalculateIDFandTF()
{
	char pcTemp[ SIZE_OF_FILENAME ];
	strcpy( pcTemp, OUTPUT_FILES_PATH );
	strcat( pcTemp, IDF_FILE_NAME );

	CIndexFile* IDFFile = new CIndexFile( pcTemp, false );
	int nTotalNumberOfDocs = m_DocAndWeight.DocumentIndex + 1;
	int nIndex, nNumOfWordsInDoc;
	IDFFile->WriteString( "Word Index" );
	IDFFile->WriteSpace();
	IDFFile->WriteString( "IDF Value" );
	IDFFile->WriteLine();

	//running all over the words:
	for( int i = 0; i < m_ListedVector.Size(); i++ )
	{
		m_InvertedIndex->WriteInt( i );
		m_InvertedIndex->WriteSpace();

		//calculating this word's IDF value:
		m_WordsVector[ i ].dIDF = log10( double( nTotalNumberOfDocs ) / double(m_WordsVector[i].nNumberOfDocuments) );
		
		//can print a pair (word-index : IDF-value) to file:
		IDFFile->WriteInt( i );
		IDFFile->WriteSpace();
		IDFFile->WriteFloat( float(m_WordsVector[ i ].dIDF) );
		IDFFile->WriteLine();
		
		// we go over the list, and print it to a file. NOTE: if there are
		// more than 50 elements in a row, I write "MORE->", start a new 
		// line, and a tab.
		int nItemsInRow = 0;
		for (link<DocAndWeight> * p=m_ListedVector[i].first; p!=NULL; p = p->next )
		{
			nIndex = p->value.DocumentIndex;
			nNumOfWordsInDoc = m_DocumentsVector[ nIndex ].NumberOfWordsInDoc;
			//calculating the TF for the word-document:
			p->value.Weight = float( p->value.NumberOfOccurrencesOfWordInDoc ) / float( nNumOfWordsInDoc );
			//write results to InvertedIndex file:
			m_InvertedIndex->WriteInt( nIndex );
			m_InvertedIndex->WriteString( " / " );
			m_InvertedIndex->WriteFloat( p->value.Weight );	//Weight is the TF value for now
			m_InvertedIndex->WriteSpace();

			p->value.Weight *= float( m_WordsVector[ i ].dIDF );	//Weight is the TF*IDF value now
			m_DocumentsVector[ nIndex ].Norm += ( p->value.Weight * p->value.Weight);

			nItemsInRow++;
			if( nItemsInRow == MAX_ITEMS_IN_ROW )
			{
				m_InvertedIndex->WriteString( "MORE->" );
				m_InvertedIndex->WriteLine();
				m_InvertedIndex->WriteSpace();
				nItemsInRow = 0;
			}
		}
		m_InvertedIndex->WriteLine();
	}
	
	IDFFile->Close();
	delete IDFFile;
}


bool CVectorianModel::PrintFileIndex()
{
	m_FileIndex->WriteString( "Doc File Name" );
	m_FileIndex->WriteSpace();
	m_FileIndex->WriteString( "Document Index" );
	m_FileIndex->WriteSpace();
	m_FileIndex->WriteString( "Norm" );
	m_FileIndex->WriteLine();

	for( int i = 0; i < m_DocumentsVector.Size(); i++ )
	{
		m_FileIndex->WriteString( m_DocumentsVector[ i ].DocumentFileName );
		m_FileIndex->WriteSpace();

		m_FileIndex->WriteInt( i );
		m_FileIndex->WriteSpace();

		m_FileIndex->WriteFloat( float( sqrt( m_DocumentsVector[ i ].Norm )) );

		m_FileIndex->WriteLine();
	}
	return true;
}

/**
  * this method closes the files (so someone else can use them properly) and
  * deletes the associated poiter
  **/
void CVectorianModel::CloseFiles()
{
	m_Dictionary->Close();
	m_FileIndex->Close();
	m_InvertedIndex->Close();

	delete m_Dictionary;
	delete m_FileIndex;
	delete m_InvertedIndex;
}




/************************************************/
/*				s e a r c  h					*/
/************************************************/

void myQsort (CVector< Search_DocFileAndNorm > & Vec, int left ,int right);


void CVectorianModel::Search( const char* OutputPath, const char* Query, char ResultsSortedVector[][SIZE_OF_FILENAME], Status& nSearchResultStatus ) 
{
	// opening the files and filling the storage structures is needed only
	// if it is a first search. otherwise i can use the current data in 
	// the storage structures:
	if( m_bFirstSearch )
	{
		//when building the storage structures, clean them first:
		InitializeSearch();

		if( strcmp( OutputPath, "" ) == 0 )
		{
			strcpy( OUTPUT_FILES_PATH, DEFAULT_OUTPUT_FILES_PATH );
		}
		else
		{
			strcpy( OUTPUT_FILES_PATH, OutputPath );
		}

		char pcTemp[ SIZE_OF_FILENAME ];
		strcpy( pcTemp, OUTPUT_FILES_PATH );
		strcat( pcTemp, DICTIONARY_FILE_NAME );
		m_Dictionary = new CIndexFile( pcTemp );

		strcpy( pcTemp, OUTPUT_FILES_PATH );
		strcat( pcTemp, FILE_INDEX_FILE_NAME );
		m_FileIndex = new CIndexFile( pcTemp );

		strcpy( pcTemp, OUTPUT_FILES_PATH );
		strcat( pcTemp, INVERTED_INDEX_FILE_NAME );
		m_InvertedIndex = new CIndexFile( pcTemp );

		if( !AreDBFilesOK() )
		{
			m_ResultStatus = DB_FILES_NOT_FOUND;
			nSearchResultStatus = m_ResultStatus;
			return;
		}
		FillHashTable();
		FillListedVector();
		FillDocumentsVector();
		CloseFiles();
		m_bFirstSearch = false;		//so next search i won't read these files
	}
	ResetDocumentsVector();			//befor query-handling,reset the +/- operators flag.
	HandleQuery( Query );
	SortAndPrintDocuments( ResultsSortedVector );
	m_ResultStatus = OK;
	nSearchResultStatus = m_ResultStatus;
	return;

}


/**
  *	this method cleans all the data structures from previous build
  **/
void CVectorianModel::InitializeSearch()
{
	m_HashTable.Clear();
	m_SearchDocumentsVector.Clear();
	m_WordsVector.Clear();
	m_ListedVector.Clear();
}


void CVectorianModel::FillHashTable()
{
	CHashedWord HashedWord;
	char pcWord[ SIZE_OF_WORD ];
	int nWordIndex;
	m_Dictionary->SkipLine();
	m_Dictionary->SkipLine();
	while ( !m_Dictionary->EndOfFile() )
	{
		m_Dictionary->GetStringAndWaitInSameLine( pcWord, SIZE_OF_WORD );
		nWordIndex = m_Dictionary->GetInt();	//read int and go to next line
		strcpy( HashedWord.m_Word,  pcWord );
		HashedWord.m_nWordIndex = nWordIndex;
		m_HashTable.Insert( HashedWord );
	}
}


void CVectorianModel::FillListedVector()
{
	//create a List object, so we can insert into the ListedVector:
	CDoubleEndedList<DocAndWeight> list;

	DocAndWeight DocAndWeight;
	char String[ 10 ];	//string for reading the '/'
	int nWordIndex = 0;
	m_InvertedIndex->SkipLine();
	while ( !m_InvertedIndex->EndOfFile() )
	{
		nWordIndex = m_InvertedIndex->GetIntAndWaitInSameLine();
		m_ListedVector.Insert( list );
		int nItemsInRow = 0;
		while( (DocAndWeight.DocumentIndex = m_InvertedIndex->GetIntAndWaitInSameLine() ) != -1 )
		{
			m_InvertedIndex->GetStringAndWaitInSameLine( String, 10 );
			DocAndWeight.Weight = m_InvertedIndex->GetFloatAndWaitInSameLine();

			m_ListedVector[ nWordIndex ].AddToEnd( DocAndWeight );
			
			nItemsInRow++;
			if( nItemsInRow == MAX_ITEMS_IN_ROW )	//maybe there are "MORE->"...
			{
				m_InvertedIndex->GetStringAndWaitInSameLine( String, 10 );
				if( strcmp ( String, "MORE->" ) == 0 )
				{
					m_InvertedIndex->SkipLine();	//go to next line, but with the same word!
				}
				nItemsInRow = 0;
			}
		}
		m_InvertedIndex->SkipLine();		//go to next line in file
	}
}


void CVectorianModel::FillDocumentsVector()
{
	Search_DocFileAndNorm Search_DocFileAndNorm;
	char FileName[ SIZE_OF_FILENAME ];
	int nDocumentIndex;
	
	m_FileIndex->SkipLine();
	m_FileIndex->SkipLine();
	while ( !m_FileIndex->EndOfFile() )
	{
		m_FileIndex->GetStringAndWaitInSameLine( FileName, SIZE_OF_FILENAME );
		strcpy( Search_DocFileAndNorm.DocumentFileName, FileName );
		nDocumentIndex = m_FileIndex->GetIntAndWaitInSameLine();
		Search_DocFileAndNorm.Norm = m_FileIndex->GetFloat();
		Search_DocFileAndNorm.fSearchRank = float( 0 );
		
		m_SearchDocumentsVector.Insert( Search_DocFileAndNorm ); 
	}
}


void CVectorianModel::ResetDocumentsVector()
{
	for( int i = 0; i < m_SearchDocumentsVector.Size(); i++ )
	{
		//reset the = or - operator flag, for each document:
		m_SearchDocumentsVector[ i ].DocStat = DONT_CARE;
		//clear Search Rank for all documents from previous search:
		m_SearchDocumentsVector[ i ].fSearchRank = float( 0 );
	}
}


/**
  *  This method goes all over the words in the query, and calculates for each
  *  relevant document its rank, and finally prints the sorted vector.
  *  
  **/
void CVectorianModel::HandleQuery( const char* Query )
{
	char* QueryWord;
	
	char pcQuery[ SIZE_OF_WORD * SIZE_OF_WORD ];	//max words in query is 20

	strcpy( pcQuery, Query );

	const char* Delimiters = " ,\t\n";

	QueryWord = strtok( pcQuery, Delimiters );
	while( QueryWord != NULL )
	{
		/* While there are tokens in "Query" */
		QueryWordHandler( QueryWord );

		/* Get next token: */
		QueryWord = strtok( NULL, Delimiters );
	}
}


void CVectorianModel::QueryWordHandler( const char* Word )
{
	CHashedWord HashedWord;
	int nIndexInTable;
	int nIndexOfWordInVector;
	char HandledWord[ SIZE_OF_WORD ];
	strcpy( HandledWord, Word );
	DocumentStatus DocStat = DONT_CARE;		//initializing
	
	if( HandledWord[0] == '+' )
	{
		DocStat = REQUIRED;
		strcpy( HandledWord, HandledWord + 1 );
	}
	else if( HandledWord[0] == '-' )
	{
		DocStat = FORBIDDEN;
		strcpy( HandledWord, HandledWord + 1 );
	}
	strcpy( HashedWord.m_Word, HandledWord );

	nIndexInTable = m_HashTable.FindIndex( HashedWord );

	if( nIndexInTable == -1)		//word is not in hash table - it doesn't exist
	{
		/* //good for console application:
		printf( "The word %s was not found in the table\n" );
		*/
		return;
	}
	else		//word was found in the table
	{
		//we give only the word, and get all information about it from hash table:
		HashedWord = *m_HashTable.Find( HashedWord );

		nIndexOfWordInVector = HashedWord.m_nWordIndex;

		//calculating the IDF value of this word:
		int nCount = m_ListedVector[nIndexOfWordInVector].GetLength();
		double dIDF = log10( double( m_SearchDocumentsVector.Size() ) / double( nCount ) );

		//for the current word, we pass all over it's Documents' list:
		for (link<DocAndWeight> * p=m_ListedVector[nIndexOfWordInVector].first;	p!=NULL; p = p->next )
		{
			float fSearchRank = p->value.Weight * (dIDF*dIDF) / m_SearchDocumentsVector[ p->value.DocumentIndex ].Norm;
			m_SearchDocumentsVector[ p->value.DocumentIndex ].fSearchRank += fSearchRank;
			//if DocStat is "-", word must not appear, so update all documents in any case.
			//if its "+", then update only if in the vector its DONTCARE, because if in the
			//vector its "+", there is no change, and if its "-" - do not change!
			if ( DocStat == FORBIDDEN )
			{
				m_SearchDocumentsVector[ p->value.DocumentIndex ].DocStat = FORBIDDEN;	//high priority
			}
			else if ( DocStat == REQUIRED )
			{
				if ( m_SearchDocumentsVector[ p->value.DocumentIndex ].DocStat == DONT_CARE )
				{
					m_SearchDocumentsVector[ p->value.DocumentIndex ].DocStat = REQUIRED;
				}
			}
		}
	}
}


/**
  *  This method copies the documents vector to another vector, and sorts the
  *  new vector. the origion vector remains the same.
  **/
void CVectorianModel::SortAndPrintDocuments( char ppcResultsSortedVector[][SIZE_OF_FILENAME] )
{
	bool	bRequiredIndicator = false;
	char	pcTemp[ SIZE_OF_FILENAME ];
	strcpy( pcTemp, OUTPUT_FILES_PATH );
	strcat( pcTemp, FILES_AND_RANKS );

	CIndexFile* FileAndRank = new CIndexFile( pcTemp, false );
	//write header to "FilesAndRanks" file:
	FileAndRank->WriteString( "File" );
	FileAndRank->WriteSpace();
	FileAndRank->WriteSpace();
	FileAndRank->WriteSpace();
	FileAndRank->WriteString( "Norm" );
	FileAndRank->WriteSpace();
	FileAndRank->WriteSpace();
	FileAndRank->WriteString( "Rank" );
	FileAndRank->WriteSpace();
	FileAndRank->WriteSpace();
	FileAndRank->WriteString( "DocStat" );
	FileAndRank->WriteLine();

	//copying the DocumentsVector to a temporary one, using copy-constructor:
	CVector< Search_DocFileAndNorm > SortedVector( m_SearchDocumentsVector );
	CVector< Search_DocFileAndNorm > tempVec;

	myQsort( SortedVector, 0, SortedVector.Size()-1 );

	//reading the vector to its end or till rank are 0 (it's sorted by the ranks, so
	//I stop in the first 0)
	for( int i=0; ( i < SortedVector.Size() )&&( SortedVector[ i ].fSearchRank != 0 ); i++ )
	{
		/* //good for console application:
		printf( "%d. %s\t%f \n", i, SortedVector[ i ].DocumentFileName, SortedVector[ i ].fSearchRank );
		*/
		//can print a pair (file : rank) to file:
		FileAndRank->WriteString( SortedVector[ i ].DocumentFileName );
		FileAndRank->WriteSpace();
		FileAndRank->WriteFloat( SortedVector[ i ].Norm );
		FileAndRank->WriteSpace();
		FileAndRank->WriteFloat( SortedVector[ i ].fSearchRank );
		FileAndRank->WriteSpace();
		FileAndRank->WriteInt( SortedVector[ i ].DocStat );
		FileAndRank->WriteLine();
		
		//I want to insert the vector only files that their DocStat != FORBIDDEN:
		if( SortedVector[ i ].DocStat != FORBIDDEN )
		{
			tempVec.Insert( SortedVector[ i ] ); 
		}
		//I want an indicator if operator + was in use. if it was - show only 
		//REQUIRED files. otherwise, show all DONT_CARE:
		if( SortedVector[ i ].DocStat == REQUIRED )
		{
			bRequiredIndicator = true;	//  + was in use!
		}
	}
	//now, tempVec contains only docs with rank != 0, and are not FORBIDDEN
	//if + was in use, copy only REQUIRED docs. otherwise -  DONT_CARE....
	int j = 0;
	if( bRequiredIndicator == true )
	{
		for( i = 0; i < tempVec.Size(); i++ )
		{
			if( tempVec[ i ].DocStat == REQUIRED )
			{
				strcpy( ppcResultsSortedVector[ j ], tempVec[ i ].DocumentFileName );
				j++;
			}
		}
	}
	else
	{
		for( i = 0; i < tempVec.Size(); i++ )
		{
			strcpy( ppcResultsSortedVector[ i ], tempVec[ i ].DocumentFileName );
		}
		j = i;	//j is END_OF_VECTOR
	}

	//indicator of end-of-vector to outer program (SearchAssignmentDlg):
	strcpy( ppcResultsSortedVector[ j ], "END_OF_VECTOR" );

	FileAndRank->Close();
	delete FileAndRank;
}




void swap (CVector< Search_DocFileAndNorm > & Vec, int i, int j)
{ 
    Search_DocFileAndNorm temp;
	temp = Vec[i];
	Vec[i] = Vec[j];
	Vec[j] = temp;
}

void myQsort (CVector< Search_DocFileAndNorm > & Vec, int left ,int right)
{
	int i, last;
	if (left >= right)
	{
		return;
	}
	swap ( Vec, left , (left+right)/2 );
    last = left;
    for ( i=left+1; i <= right; i++)
	{
		if( Vec[i].fSearchRank > Vec[left].fSearchRank )
		{
			swap( Vec, ++last, i );
		}
	}
	swap ( Vec, left , last );
    myQsort( Vec, left , last-1 );
    myQsort( Vec, last+1, right );
}


/**
  *  This method is used for the Show action - it fills the FilePath argument
  *  with the file-to-show path
  **/
void CVectorianModel::Show( char* FilePath )
{
	if(  strcmp( FilePath, "" ) == 0 )
	{
		strcpy( FilePath, DEFAULT_SEARCHED_FILES_PATH );
	}
}

