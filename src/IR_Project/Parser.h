// Parser.h: interface for the CParser class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _PARSER_H__
#define _PARSER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DoxTree.h"
#include "Utils.h"

#pragma warning( disable : 4786 )

enum E_TYPE { eWord, eOperator, eGroup, eDoxTree };

struct STypedString
{
	E_TYPE				Type;
	std::string			Value;
	CDocsTree			Tree;
};

typedef std::vector<STypedString>	TTypedStringVector;

void ErrorMessageBox(const std::string& message);

/**
  * this version of parser works with CExExpressionTree, which allows handling
  * functions, by allowing more that 2 childs per node
  **/
class CParser
{
private:
	void		ClearDB();
	bool		IsWord(const std::string& str) const;
	std::string	GetWord(const std::string& str) const;
	bool		IsGroup(const std::string& str) const;
	SGroup		GetGroup(
		IN const std::string& str,
		OUT int& rnNumOfCharsRead) const;
	bool		IsOperator(std::string It) const;
	SOperator	GetOperator(std::string It) const;
	void		ParseThenOperator(const std::string& ThenOperator,
									SOperator& rReturnOperator) const;

	void		HandleUnrecognizedToken(const std::string& str) const;
	bool		IsParamsNumberOK(const std::string& FuncName, int ParamsNum) const;
	bool		IsBracketedExpression(std::string::const_iterator& str) const;
	bool		IsDelimiter(const std::string& str) const;
	bool		BuildTypedStringColl(std::string expression);
	void		BuildExpTree();
	//second version, gives out an iterator
	std::string	GetHighestOperator( OUT TTypedStringVector::iterator& HighestIt,
									OUT bool &Binary);

	CParser();
	void		Clear();

	//evaluation of the tree:
	TDocIdVector	EvaluateTree()	{ return m_DocsTree.EvaluateTree(); 	}
	TDocIdVector	HandleOperator(const CExNode<std::string>* Node) const;
	TDocIdVector	HandleThenOperator(const CExNode<std::string>* Node) const;
	TDocIdVector	HandleGroup(const SGroup& GrpName) const;
	
	TGroups							m_groups;
	TOperators						m_operators;
	TTypedStringVector				m_TypedStrColl;
	CDocsTree						m_DocsTree;
	
public:
	virtual ~CParser();
	static CParser* GetInstance();

	TDocIdVector Parse(const std::string& expression);
	CDocsTree GetDoxTree() const			{	return m_DocsTree;	}
	void PrintTree() const;

	//evaluation of the tree:
	TDocIdVector	EvaluateNode(const CExNode<std::string>* Node) const;
	TWordsCollection	GetWordsFromNode(const CExNode<std::string>* Node) const;

	bool AddGroup(const std::string& GrpName, const std::string& GrpMembers);
	
	TGroups GetGroups() const
	{	return m_groups;	}
};

/**************************************************************************/
/**************************************************************************/



#endif // !defined(_PARSER_H__)
