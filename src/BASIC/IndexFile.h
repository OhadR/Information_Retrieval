/****************************************************************/
/*						IndexFile.H						        */
/*				      by: Ohad Redlich							*/
/*						10.8.2000								*/
/****************************************************************/


#ifndef _INDEXFILE_H
#define _INDEXFILE_H



#include <stdio.h>		//FILE
#include <string.h>
#include <stdlib.h>		// exit

const int MAX_LINE_SIZE = 1000;


/****************************************************************/
/*                 class CIndexFile definition                  */
/****************************************************************/


class CIndexFile
{
public:
    CIndexFile( const char* FileName, bool ReadOnly = true );
    virtual ~CIndexFile();

    void	Close();

    // The general routines skip to next line after getting data
    int		GetInt();
    float	GetFloat();
    void	GetString(char* Value, int Size);

    // Get value and NOT skip to next line
    int		GetIntAndWaitInSameLine();
    float	GetFloatAndWaitInSameLine();
	void	GetStringAndWaitInSameLine(char* Value, int Size);
    bool	SkipLine();

    void	WriteInt( int Value );
    void	WriteFloat( float Value );
    void	WriteDouble( double Value );
    void	WriteString( const char* Value );
    void	WriteSpace();
	void	WriteLine();	//for writing - jumps to next line.

    bool	EndOfFile();

private:
    bool	Open(const char* FileName, bool ReadOnly = true);

    float	GetFloat(bool SkipLine);
    int		GetInt( bool SkipLine /*= true*/ );
	void	GetString(char * Value, int Size, bool SkipLine /*= true*/ );
    const char* GetNextToken();

    FILE*	m_File;
    char	m_Line[MAX_LINE_SIZE];
    bool	m_LineIsNew;
};


#endif	//_INDEXFILE_H