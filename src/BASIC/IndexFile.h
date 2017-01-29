/****************************************************************/
/*						IndexFile.H						        */
/*				      by: Ohad Redlich							*/
/*						16.5.2001								* /
/*		1. added "print_pause", and improvements: changes in		
/*					GetNextToken() to STL						
/*		2. Open is public, so users can close and open files
/*		3. delimiter for marking was added: '#'
/*		4. namespace std is not called in the h file
/*		5. moving to next line actually moves to next valid line:
/*			not-commented and not-empty(only delimiters) line
/*		6. GetInt() returns min_limit when not valid, not -1
/*		7. GexHexa() and WriteHexa()
/*		8. FindString()
/*
/*						24.10.2002
/*		1. working with STL, removing includes like <string.h>
/*		2. when constructor fails, show message box to screen
/*		3. improving STL-string parameters to methods to const
/*			-reference.
/****************************************************************/

#ifndef _INDEXFILE_H
#define _INDEXFILE_H

#include <stdio.h>		//FILE
#include <string>
#include <limits>		//numeric_limits

//to be able to use the "min" of limits (STL)
#ifdef min
#undef min
#endif

const int c_nIndexFileError = std::numeric_limits<int>::min();
const float c_fIndexFileError = std::numeric_limits<float>::min();
const std::string c_strIndexFileError = "";

const int MAX_LINE_SIZE = 1000;

/****************************************************************/
/*                 class CIndexFile definition                  */
/****************************************************************/

class CIndexFile
{
public:
    CIndexFile( const std::string& FileName, bool ReadOnly = true );
    virtual ~CIndexFile();

    bool	Open(const std::string& FileName, bool ReadOnly = true);
    void	Close();
	
    // The general routines skip to next line after getting data
    int			GetInt();
	int			GetHexa();
    float		GetFloat();
	std::string	GetString();

    // Get value and NOT skip to next line
    int			GetIntAndWaitInSameLine();
    int			GetHexaAndWaitInSameLine();
    float		GetFloatAndWaitInSameLine();
	std::string	GetStringAndWaitInSameLine();
    bool		SkipLine();				//go to the next non-commented line

    void	WriteInt( const int Value );
    void	WriteHexa( const int Value );
    void	WriteFloat( const float Value );
    void	WriteDouble( const double Value );
    void	WriteString( const std::string& Value );
    void	WriteSpace();
	void	WriteLine();	//for writing - jumps to next line.

	void	FindString(const std::string& Value, bool FromStart = true);
	
    bool	EndOfFile() const;

private:
    float		GetFloat(bool SkipLine);
    int			GetInt( bool SkipLine /*= true*/ );
	int			GetHexa(bool SkipLine);
	std::string	GetString( bool SkipLine /*= true*/ );
	bool		IsCommentLine() const;
	bool		IsEmptyLine() const;
	std::string	GetNextToken();
	
    FILE*	m_File;
    char	m_Line[MAX_LINE_SIZE];
    bool	m_LineIsNew;
};


#endif	//_INDEXFILE_H