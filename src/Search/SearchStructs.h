/****************************************************************/
/*                    SearchStructs.H					        */
/*				      by: Ohad Redlich							*/
/*						12.8.2000								*/
/****************************************************************/


const long  MAX_NUM_OF_WORDS  = 2000000;
const int	MAXLINE			  =	1000;
const int	SIZE_OF_FILENAME  = 150;
const int	SIZE_OF_WORD	  =	20;


/**
  *	DocAndWeight struct is for the concatanated list, and it contains
  * a pair of document number and the weight
  **/
struct DocAndWeight
{
	int		DocumentIndex;
	int		NumberOfOccurrencesOfWordInDoc;
	float	fTF;
};


/**
  *	DocFileAndNorm struct is for the vector, and it contains  of the 
  * document-file-name (each document owns a file), the norm value and
  * the search rank which is computed while searching
  **/
struct DocFileAndNorm
{
	char	DocumentFileName[SIZE_OF_FILENAME];
	float	Norm;
	float	fSearchRank;		//document rank, computed while searching
};


/**
  *	CHashedWord class is for the Hash table, and it contains the word, default
  * constructor, the hash function and operator ==
  **/
class CHashedWord
{
public:
	CHashedWord();

	int		HashValue() const;
	bool	operator==(const CHashedWord&) const;
    CHashedWord&   operator=(const CHashedWord&);

	char	m_Word[SIZE_OF_WORD];
	int		m_nWordIndex;			//the index of the word in the Listed-Vector
};
