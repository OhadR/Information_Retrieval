#ifndef _UTILS_H__
#define _UTILS_H__

#include <string>	
#include <vector>

#pragma warning ( disable : 4786 )

#define IN
#define OUT

static const int s_nMinSizeOfWord = 3;
static const int s_nMaxSizeOfWord = 13;

typedef unsigned short WORD;
typedef std::vector<int>			TDocIdVector;

///////////////////////////////////////////////////////////
//
class SOperator
{
public:
	//constructor:
	SOperator( std::string oper,
						unsigned int prior,
						bool binary = false)
	{
		_operator = oper;
		_priority = prior;
		_bBinary  = binary;
		//_parameter = "";
	}

	std::string		_operator;
	unsigned int	_priority;
	bool			_bBinary;
	//std::string		_parameter;		//in case of ">", the (X, Y) are operator's parameter
};

typedef std::vector<SOperator>	TOperators;

///////////////////////////////////////////////////////////

typedef std::vector<std::string> TWordsCollection;

struct SGroup
{
	SGroup(
		const std::string& name,
		const TWordsCollection& Words)
	{
		_name = name;
		_Words = Words;
	}
	
	std::string					_name;
	//group is a collection of words:
	TWordsCollection			_Words;
};


typedef std::vector<SGroup>		TGroups;

///////////////////////////////////////////////////////////

static void ConvertExpressionToLowerCase(std::string& expression)
{
	for(std::string::iterator strIt = expression.begin();
	strIt != expression.end();
	++strIt	)
	{
		if(strIt[0] >= 'A' && strIt[0] <= 'Z')
			strIt[0] += 32;
	}
}

//filter a word. returns true if word is OK, false means "drop it!"
static bool WordFilter(IN std::string& Word)
{
	//filter the size of the word:
	if( Word.size() < s_nMinSizeOfWord )
	{
		return false;
	}

	if( Word.size() > s_nMaxSizeOfWord )
	{
		return false;
	}

	//now, convert all letters to lower-case, and check for numbers in the word.
	//if there is a number in the word - drop it:
	ConvertExpressionToLowerCase(Word);
	
	//check for numbers in the word. if there is a number in the word - drop it:
	for(std::string::iterator it = Word.begin(); it != Word.end(); ++it)
	{
		if( *it >= '0' && *it <= '9' )
		{
			return false;
		}
	}

	return true;
}

/**
	1. the input containers MUST BE SORTED FIRST!!!
	2. the ouptput container must be with enough space and not empty!!!
	**/
template <class TIterator>
void GetComplementary(
				IN TIterator FullBegin,
				IN TIterator FullEnd,
				IN TIterator CollBegin,
				IN TIterator CollEnd,
				OUT TIterator OutputBegin,
				OUT TIterator OutputEnd)
{
	TIterator full_it = FullBegin;
	TIterator it2 = CollBegin;
	TIterator output_it = OutputBegin;
	while( full_it != FullEnd && it2 != CollEnd )
	{
		if(*full_it == *it2)
		{
			++it2;
			++full_it;
			continue;
		}
		if( *full_it < *it2 )
		{
			*output_it = *full_it;
			++output_it;
			++full_it;
			continue;
		}
		/*if( *it2 < *full_it )
		{
			assert(false);		//cannot happen that item is in vec2 but not in fullvec
			++it2;
			continue;
		}*/
	}
}


/**
	this function ,akes "and" operation between two containers.
	1. the input containers MUST BE SORTED FIRST!!!
	2. the ouptput container must be with enough space and not empty!!!
	**/
template <class TIterator>
TIterator GetCommonInstances(
				IN TIterator LeftBegin,
				IN TIterator LeftEnd,
				IN TIterator RightBegin,
				IN TIterator RightEnd,
				OUT TIterator OutputBegin,
				OUT TIterator OutputEnd)
{
	TIterator right_it = RightBegin;
	TIterator left_it = LeftBegin;
	TIterator output_it = OutputBegin;
	while( right_it != RightEnd && left_it != LeftEnd )
	{
		if(*right_it == *left_it)
		{
			//instance in both containers - put item in "and" container:
			*output_it = *right_it;
			++output_it;
			++right_it;
			++left_it;
			continue;
		}
		if( *right_it < *left_it )
		{
			++right_it;
			continue;
		}
		if( *left_it < *right_it )
		{
			++left_it;
			continue;
		}
	}
	return output_it;
}

/**
	this function ,akes "and" operation between two containers.
	the second container is used as an output container, for the results
	1. the input containers MUST BE SORTED FIRST!!!
	**/
template <class TIterator>
TIterator GetCommonInstances(
				IN TIterator LeftBegin,
				IN TIterator LeftEnd,
				IN OUT TIterator RightBegin,
				IN OUT TIterator RightEnd)
{
	TIterator right_it = RightBegin;
	TIterator left_it = LeftBegin;
	TIterator output_it = RightBegin;
	while( right_it != RightEnd && left_it != LeftEnd )
	{
		if(*right_it == *left_it)
		{
			//instance in both containers - put item in "and" container:
			*output_it = *right_it;
			++output_it;
			++right_it;
			++left_it;
			continue;
		}
		if( *right_it < *left_it )
		{
			++right_it;
			continue;
		}
		if( *left_it < *right_it )
		{
			++left_it;
			continue;
		}
	}
	return output_it;
}

#endif	//_UTILS_H__
