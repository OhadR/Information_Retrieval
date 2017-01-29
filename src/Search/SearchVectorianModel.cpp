///////////////////////////////////////////////////////////////
// VectorianModel.cpp

#include "SearchVectorianModel.h"


/****************************************************************/
/*     constants to determine the paths and files names         */
/****************************************************************/

const char* SEARCHED_FILES_PATH		= "D:\\MY DOCUMENTS\\IR_PROJECT\\FILES\\";
const char* OUTPUT_FILES_PATH		= "D:\\MY DOCUMENTS\\IR_PROJECT\\FILES\\";

const char* DICTIONARY_FILE_NAME		= "DICTIONARY.TXT";
const char* FILE_INDEX_FILE_NAME		= "FILE_INDEX.TXT";
const char* INVERTED_INDEX_FILE_NAME	= "INVERTED_INDEX.TXT";



void swap (CVector< DocFileAndNorm > & Vec, int i, int j);
void myQsort (CVector< DocFileAndNorm > & Vec, int left ,int right);



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



/****************************************************************/
/*         class CSearchVectorianModel implementation           */
/****************************************************************/

CSearchVectorianModel::CSearchVectorianModel( int nNumOfWordsInQuery, char* Query[] ) 
	:	m_HashTable( MAX_NUM_OF_WORDS )
{
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

	FillHashTable();
	FillListedVector();
	FillDocumentsVector();
	HandleQuery( nNumOfWordsInQuery, Query );
}

CSearchVectorianModel::~CSearchVectorianModel()
{
}


void CSearchVectorianModel::FillHashTable()
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


void CSearchVectorianModel::FillListedVector()
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
		while( (DocAndWeight.DocumentIndex = m_InvertedIndex->GetIntAndWaitInSameLine() ) != -1 )
		{
			m_InvertedIndex->GetStringAndWaitInSameLine( String, 10 );
			DocAndWeight.fTF = m_InvertedIndex->GetFloatAndWaitInSameLine();

			m_ListedVector[ nWordIndex ].AddToEnd( DocAndWeight );
		}
		m_InvertedIndex->SkipLine();		//go to next line in file
	}
}


void CSearchVectorianModel::FillDocumentsVector()
{
	DocFileAndNorm DocFileAndNorm;
	char FileName[ SIZE_OF_FILENAME ];
	int nDocumentIndex;
	
	m_FileIndex->SkipLine();
	m_FileIndex->SkipLine();
	while ( !m_FileIndex->EndOfFile() )
	{
		m_FileIndex->GetStringAndWaitInSameLine( FileName, SIZE_OF_FILENAME );
		strcpy( DocFileAndNorm.DocumentFileName, FileName );
		nDocumentIndex = m_FileIndex->GetIntAndWaitInSameLine();
		DocFileAndNorm.Norm = m_FileIndex->GetFloat();
		DocFileAndNorm.fSearchRank = float( 0 );
		
		m_DocumentsVector.Insert( DocFileAndNorm ); 
	}
}


/**
  *  This method goes all over the words in the query, and calculates for each
  *  relevant document its rank, and finally prints the sorted vector.
  *  
  **/
void CSearchVectorianModel::HandleQuery( int nNumOfWordsInQuery, char* Query[] )
{
	//goes all over the words in query, and calculate
	for( int i = 0; i < nNumOfWordsInQuery; i++ )
	{
		WordHandler( Query[ i ] );
	}

	SortAndPrintDocuments();


}


void CSearchVectorianModel::WordHandler( const char* Word )
{
	CHashedWord HashedWord;
	int nIndexInTable;
	int nIndexOfWordInVector;
	strcpy( HashedWord.m_Word, Word );

	nIndexInTable = m_HashTable.FindIndex( HashedWord );

	if( nIndexInTable == -1)		//word is not in hash table - it doesn't exist
	{
		printf( "The word %s was not found in the table\n" );
	}
	else		//word was found in the table
	{
		//we give only the word, and get all information about it from hash table:
		HashedWord = *m_HashTable.Find( HashedWord );

		nIndexOfWordInVector = HashedWord.m_nWordIndex;

		//calculating the IDF value of this word:
		int nCount = m_ListedVector[nIndexOfWordInVector].GetLength();
		double dIDF = log10( double( m_DocumentsVector.Size() ) / double( nCount ) );

		for (link<DocAndWeight> * p=m_ListedVector[nIndexOfWordInVector].first;	p!=NULL; p = p->next )
		{
			float fSearchRank = p->value.fTF * (dIDF*dIDF) / m_DocumentsVector[ p->value.DocumentIndex ].Norm;
			m_DocumentsVector[ p->value.DocumentIndex ].fSearchRank += fSearchRank;
		}
	}
}


/**
  *  This method copies the documents vector to another vector, and sorts the
  *  new vector. the origion vector remains the same.
  **/
void CSearchVectorianModel::SortAndPrintDocuments()
{
	CVector< DocFileAndNorm > tempVec( m_DocumentsVector );

	myQsort( tempVec, 0, tempVec.Size()-1 );

	for( int i=0; i < tempVec.Size(); i++ )
	{
		printf( "%d. %s\t%f \n", i, tempVec[ i ].DocumentFileName, tempVec[ i ].fSearchRank );
	}

}




void swap (CVector< DocFileAndNorm > & Vec, int i, int j)
{ 
    DocFileAndNorm temp;
	temp = Vec[i];
	Vec[i] = Vec[j];
	Vec[j] = temp;
}

void myQsort (CVector< DocFileAndNorm > & Vec, int left ,int right)
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