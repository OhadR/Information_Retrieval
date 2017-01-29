/****************************************************************/
/*						IndexFile.CPP					        */
/*				      by: Ohad Redlich							*/
/*						10.8.2000								*/
/****************************************************************/

#include "IndexFile.h"


/****************************************************************/
/*                class CIndexFile implementation               */
/****************************************************************/


CIndexFile::CIndexFile( const char* FileName, bool ReadOnly ) : m_File(NULL)
{
	if ( !Open( FileName, ReadOnly ) )
	{
		/*
		printf("Error opening %s\n", FileName);	//ERROR!
		exit( 1 );
		*/
	}
	
	m_Line[0] = '\0';
    m_LineIsNew = true;
}

CIndexFile::~CIndexFile()
{
	Close();
}

bool CIndexFile::Open(const char* FileName, bool ReadOnly )
{
    m_File = fopen(FileName, ReadOnly ? "r" : "w");
    if (m_File == NULL)
        return false;
    return true;
}

float CIndexFile::GetFloat()
{
    return GetFloat(true);		//true for read and stay in same line
}

int CIndexFile::GetInt()
{
    return GetInt( true );		//true for read and stay in same line
}

void CIndexFile::GetString( char* Value, int Size)
{
	
    GetString(Value, Size, true );	//true for read and stay in same line
}

int CIndexFile::GetIntAndWaitInSameLine()
{
    return GetInt( false /* SkipLine */);
}

float CIndexFile::GetFloatAndWaitInSameLine()
{
    return GetFloat(false);
}

void CIndexFile::GetStringAndWaitInSameLine(char * Value, int Size)
{
    GetString(Value, Size, false);
}

void CIndexFile::WriteInt( int Value )
{
	int nWrittenBytes;
	nWrittenBytes = fprintf( m_File, "%d", Value);
}

void CIndexFile::WriteFloat( float Value )
{
	int nWrittenBytes;
	nWrittenBytes = fprintf( m_File, "%f", Value);
}

//not in use since appearance very ugly (6.19543e-002, for example)
void CIndexFile::WriteDouble( double Value )
{
	int nWrittenBytes;
	nWrittenBytes = fprintf( m_File, "%e", Value);
}

void CIndexFile::WriteString( const char* Value )
{
	int nWrittenBytes;
	nWrittenBytes = fprintf( m_File, "%s", Value);
}

void CIndexFile::WriteSpace()
{
	int nWrittenBytes;
	nWrittenBytes = fprintf( m_File, "\t");
}

void CIndexFile::WriteLine()
{
	int nWrittenBytes;
	nWrittenBytes = fprintf( m_File, "\n");
}


bool CIndexFile::EndOfFile()
{
    return m_File == NULL || feof(m_File);
}


bool CIndexFile::SkipLine()
{
	if (EndOfFile())
		return false;

	fgets(m_Line, MAX_LINE_SIZE, m_File);
	m_LineIsNew = true;

    return true;
}

// private methods

int CIndexFile::GetInt( bool bSkipLine/* = true*/)
{
    int Value;
    const char* Token = GetNextToken();
    if (Token == NULL || sscanf(Token, "%d", &Value) != 1)
        Value = -1;			//indicating an error

    if (bSkipLine)
		SkipLine();

    return Value;
}

float CIndexFile::GetFloat(bool bSkipLine)
{
    float Value;
    const char* Token = GetNextToken();
    if (Token == NULL || sscanf(Token, "%f", &Value) != 1)
        Value = (float)0;

    if (bSkipLine)
		SkipLine();

    return Value;
}

void CIndexFile::GetString(char * Value, int Size, bool bSkipLine)
{
	//char Value[100];			//not char*, preventing memory problems!
	const char* Token = GetNextToken();
    if ( Token == NULL )
	{
		Value = NULL;		//indicating an ERROR
		return;
	}

	strcpy(Value, Token);

    if (bSkipLine)
		SkipLine();
}


void CIndexFile::Close()
{
    if ( m_File != NULL )
    {
        fclose( m_File );
        m_File = NULL;
    }
}


static const char* Delimiters = " \t\n";


const char* CIndexFile::GetNextToken()
{
    // read token from current line:
    const char* Token = strtok(m_LineIsNew ? m_Line : NULL, Delimiters);

    // If it's End Of Line - return NULL:.
    if (Token == NULL)
    {
		return NULL;
    }
    m_LineIsNew = false;
    return Token;
}