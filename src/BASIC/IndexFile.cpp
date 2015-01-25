/****************************************************************/
/*						IndexFile.CPP					        */
/*				      by: Ohad Redlich							*/
/*						10.5.2001								*/
/****************************************************************/

#include "IndexFile.h"
#include <cassert>
#include <windows.h>

using namespace std;

void printf_pause()
{
	printf("press ENTER to continus... ");
	getchar();
}

/****************************************************************/
/*                class CIndexFile implementation               */
/****************************************************************/


CIndexFile::CIndexFile( const string& FileName, bool ReadOnly ) : m_File(NULL)
{
	if ( !Open( FileName, ReadOnly ) )
	{
		string Msg = "Error opening " + FileName;
		MessageBox( NULL, Msg.c_str(), "WB Server Error", MB_OK | MB_ICONERROR );		
		//printf("Error opening %s\n", FileName.c_str());	//ERROR!
		//printf_pause();
		exit( 1 );
	}
	
	m_Line[0] = '\0';
    m_LineIsNew = true;
}

CIndexFile::~CIndexFile()
{
	Close();
}

bool CIndexFile::Open(const string& FileName, bool ReadOnly )
{
    assert(!FileName.empty());
	m_File = fopen(FileName.c_str(), ReadOnly ? "r" : "w");
    if (m_File == NULL)
        return false;
    return true;
}

float CIndexFile::GetFloat()
{
    return GetFloat(true);		//true for moving on to next line
}

int CIndexFile::GetInt()
{
    return GetInt( true );		//true for moving on to next line
}

int CIndexFile::GetHexa()
{
    return GetHexa( true );		//true for moving on to next line
}

string CIndexFile::GetString()
{
    return GetString( true );	//true for moving on to next line
}

int CIndexFile::GetIntAndWaitInSameLine()
{
    return GetInt( false /* SkipLine */);
}

int CIndexFile::GetHexaAndWaitInSameLine()
{
    return GetHexa( false /* SkipLine */);
}

float CIndexFile::GetFloatAndWaitInSameLine()
{
    return GetFloat(false);
}

string CIndexFile::GetStringAndWaitInSameLine()
{
    return GetString( false );
}

void CIndexFile::WriteInt( const int Value )
{
	int nWrittenBytes;
	nWrittenBytes = fprintf( m_File, "%d", Value);
}

void CIndexFile::WriteHexa( const int Value )
{
	int nWrittenBytes;
	nWrittenBytes = fprintf( m_File, "%X", Value);
}

void CIndexFile::WriteFloat( const float Value )
{
	int nWrittenBytes;
	nWrittenBytes = fprintf( m_File, "%f", Value);
}

//not in use since appearance very ugly (6.19543e-002, for example)
void CIndexFile::WriteDouble( const double Value )
{
	int nWrittenBytes;
	nWrittenBytes = fprintf( m_File, "%e", Value);
}

void CIndexFile::WriteString( const string& Value )
{
	int nWrittenBytes;
	nWrittenBytes = fprintf( m_File, "%s", Value.c_str() );
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

void CIndexFile::FindString(const std::string& Value, bool FromStart)
{
	if( FromStart )
		fseek(m_File, 0L, SEEK_SET );	//move file pointer to the start of file
	string Str;
	do {
		Str = GetStringAndWaitInSameLine();
		if( Str.empty() )
			SkipLine();
	} while(Str != Value)
		;
}

bool CIndexFile::EndOfFile() const
{
    return m_File == NULL || feof(m_File);
}


//go to the next non-commented not-empty line:
bool CIndexFile::SkipLine()
{
	do
	{
		if (EndOfFile())
			return false;
		
		fgets(m_Line, MAX_LINE_SIZE, m_File);
		m_LineIsNew = true;
	}	while( IsCommentLine() || IsEmptyLine() );

    return true;
}

// private methods

bool CIndexFile::IsCommentLine() const
{
    const char RemarkChar1 = '/';
    const char RemarkChar2 = ';';
    const char RemarkChar3 = '#';
	
    // A line which starts with remark char, or contains no tokens is not valid
    return	m_Line[0] == '\0' || 
			m_Line[0] == RemarkChar1 ||
			m_Line[0] == RemarkChar2 ||
			m_Line[0] == RemarkChar3 ;
}

int CIndexFile::GetInt( bool bSkipLine/* = true*/)
{
    int Value;
    string Token = GetNextToken();
    if ( Token.empty() || sscanf(Token.c_str(), "%d", &Value) != 1)
        Value = c_nIndexFileError;			//indicating an error

    if (bSkipLine)
		SkipLine();

    return Value;
}

int CIndexFile::GetHexa( bool bSkipLine)
{
    int Value;
    string Token = GetNextToken();
    if ( Token.empty() || sscanf(Token.c_str(), "%X", &Value) != 1)
        Value = c_nIndexFileError;			//indicating an error
	
    if (bSkipLine)
		SkipLine();
	
    return Value;
}

float CIndexFile::GetFloat(bool bSkipLine)
{
    float Value;
    string Token = GetNextToken();
    if (Token.empty() || sscanf(Token.c_str(), "%f", &Value) != 1)
        Value = c_fIndexFileError;			//indicating an error

    if (bSkipLine)
		SkipLine();

    return Value;
}

string CIndexFile::GetString( bool bSkipLine)
{
	string Value;
	string Token = GetNextToken();
    if ( Token.empty() )
	{
		return c_strIndexFileError;		//indicating an ERROR
	}

	Value = Token;

    if (bSkipLine)
		SkipLine();

	return Value;
}


void CIndexFile::Close()
{
    if ( m_File != NULL )
    {
        fclose( m_File );
        m_File = NULL;
    }
}


static const string Delimiters = " \t\n";


string CIndexFile::GetNextToken()
{
    // read token from current line:
    const char* Token = strtok(m_LineIsNew ? m_Line : NULL, Delimiters.c_str());
	
    // If it's End Of Line - return NULL:.
    if (Token == NULL)
    {
		return "";
    }
    m_LineIsNew = false;
    return Token;
}

//returns true if the line consists nothing but delimiters
bool CIndexFile::IsEmptyLine() const
{
	string Line = m_Line;
	return Line.find_first_not_of(Delimiters) == string.npos;
}

