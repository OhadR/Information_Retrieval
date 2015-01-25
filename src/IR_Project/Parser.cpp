#include "Parser.h"
#include "AlgorithmManager.h"
#include <afxwin.h>			//AfxMessageBox
#include <algorithm>
//#include <cassert>

using namespace std;

void ErrorMessageBox(const string& message)
{
	AfxMessageBox( message.c_str(), MB_ICONERROR );
}


CParser::CParser()
{
	SOperator NotOperator( "!", 5, false /*unary*/);
	m_operators.push_back(NotOperator);
	SOperator AndOperator( "&", 4, true /*binary*/);
	m_operators.push_back(AndOperator);
	SOperator OrOperator( "|", 3, true /*binary*/);
	m_operators.push_back(OrOperator);
	//"then" operator:
	SOperator ThenOperator( ">", 1, true /*binary*/);
	m_operators.push_back(ThenOperator);
}

CParser::~CParser()
{
	Clear();
}

void CParser::Clear()
{
	m_TypedStrColl.clear();		//most important, for local parsers
}

CParser* CParser::GetInstance()
{
	static CParser theParser;
	return &theParser;
}

TDocIdVector CParser::Parse(const string& expression)
{
	Clear();	//for the locals, when i use the same parser for some parsings
	ConvertExpressionToLowerCase( const_cast<string&>(expression) );
	if( ! BuildTypedStringColl(expression) )
		return 0;
	BuildExpTree();
	return EvaluateTree();
}

void CParser::PrintTree() const
{
	m_DocsTree.PreOrder();
}

bool CParser::BuildTypedStringColl(string expression)
{
	string::iterator it = expression.begin();
	bool	bExpectingWord(true);	//am i expecting a number?
	while( it != expression.end() )
	{
		//2 operators can come one after the other (2 + ++3), but 2 numbers
		//can never come sequently. so i will have a flag that will tell me
		//if i m NOT expecting a number. this will solve the problem of operator -:
		//(1-2) was 2 number: 1, -2. i need to know the - is operator. or (A-4)
		
		if( IsOperator(it) )
		{
			//only after an operator i will expect a number
			bExpectingWord = true;
			STypedString TypedString;
			TypedString.Type = eOperator;
			TypedString.Value = GetOperator(it)._operator;
			m_TypedStrColl.push_back(TypedString);
			//increase the iterator (size) steps:
			it += TypedString.Value.size();
		}
		else if(IsGroup(it))
		{
			bExpectingWord = false;	//not expecting word after group
			//if it is group, i put into the tree the NAME, not the value.
			//so later on the evaluator will look for the value. this is good
			//because then the exp. V will be computed for different values of V,
			//meaning: user will parse the "V", and only then will put a value into V
			STypedString TypedString;
			TypedString.Type = eGroup;
			int n;
			TypedString.Value = GetGroup(it, n)._name;
			if( TypedString.Value == "Error" )
			{
				string message1( it );
				string message("Syntax Error: group name is illegal '" + message1 + "'" );
				ErrorMessageBox( message );
				return false;
			}
			//put the brackets back, so in the evaluation i'll know its a group:
			TypedString.Value += "]";
			TypedString.Value.insert(0, "[");
			m_TypedStrColl.push_back(TypedString);
			//increase the iterator (size) steps:
			it += n;
		}
		else if(IsDelimiter(it))	//case of space or tab.
		{
			++it;
		}
		//check if the next thing is a word, only if i m expecting one:
		else if( IsWord(it) )
		{
			if( ! bExpectingWord )
			{
				string message("Syntax Error: not expecting a word '" + GetWord(it) + "'");
				ErrorMessageBox( message );
				return false;
			}
			bExpectingWord = false;
			STypedString TypedString;
			TypedString.Type = eWord;
			TypedString.Value = GetWord(it);
			m_TypedStrColl.push_back(TypedString);
			it += TypedString.Value.size();
		}
		else
		{
			HandleUnrecognizedToken(it);
			return false;
		}
	}
	return true;
}

void CParser::ClearDB()
{
	m_groups.clear();
	m_operators.clear();
/*	if(&m_DocsTree)
		m_DocsTree.Clear();*/
}

bool CParser::IsWord(const string& str) const
{
	if( str[0] >= 'a' && str[0] <= 'z' )
		return true;
	else
		return false;
}

string CParser::GetWord(const string& str) const
{
	string theWord;
	string::const_iterator strIt = str.begin();

	while( (strIt != str.end()) && *strIt >= 'a' && *strIt <= 'z' )
	{
		theWord += strIt[0];
		++strIt;
	}
	return theWord;
}

bool CParser::IsGroup(const string& str) const
{
	if( str[0] == '[' )
		return true;
	else
		return false;
}

SGroup CParser::GetGroup(IN const string& str,
						 OUT int& rnNumOfCharsRead) const
{
	//get the "]":
	rnNumOfCharsRead = str.find_first_of("]");
	if( rnNumOfCharsRead == -1 )
	{
		ErrorMessageBox("Syntax Error: cannot find ']' after group name");
		TWordsCollection StrVec;
		return SGroup("Error", StrVec);
	}
	++rnNumOfCharsRead;		//pass over the "]"

	string theGroup( str );
	theGroup.erase( theGroup.begin() );		//move over the "["

	TGroups::const_iterator GroupIt;
	for( GroupIt = m_groups.begin();
	GroupIt != m_groups.end();
	++GroupIt )
	{
		if( !theGroup.compare(0, GroupIt->_name.size(), GroupIt->_name) )
		{
			return *GroupIt;
		}
	}
	//group name was not founf:
	TWordsCollection StrVec;
	return SGroup("Error", StrVec);
}

bool CParser::IsOperator(string It) const
{
	return ( GetOperator(It)._operator != "NotOperator!" );
}

SOperator CParser::GetOperator(string It) const
{
	SOperator ReturnOperator("NotOperator!", 0);
	TOperators::const_iterator prior_oper_it;
	for( prior_oper_it = m_operators.begin();
	prior_oper_it != m_operators.end();
	++prior_oper_it )
	{
		if( !It.compare(0, prior_oper_it->_operator.size(), prior_oper_it->_operator) )
		{
			ReturnOperator = *prior_oper_it;
			//special treatment to "near" operator:
			if( ReturnOperator._operator == ">" )
			{
				ParseThenOperator(It, ReturnOperator);
			}
			break;
		}
	}
	return ReturnOperator;
}


/**
  * this method checks if the character it a delimiter -  a space or a tab.
  **/
bool CParser::IsDelimiter(const string& str) const
{
	return (str[0] == ' '	||
			str[0] == '\t');
}

void CParser::ParseThenOperator(const string& InputString,
							 SOperator& rReturnOperator) const
{
	//get the operators' parameter, until the ")"
	string::const_iterator cit = InputString.begin();

	//make sure the "(" comes right after:
	++cit;
	if( cit[0] != '(' )
	{
		//error: "(" doesn't come right after ">":
		ErrorMessageBox( "Error parsing > operator: expaecting '(' right after the '>'" );
		rReturnOperator._operator = "NotOperator!";
		return;
	}
	rReturnOperator._operator += *cit;

	++cit;
	string temp;
	while( cit[0] != ',' )
	{
		//validate that the token is a digit:
		if( ! isdigit( cit[0] ) )
		{
			//error: it is not a digit:
			ErrorMessageBox( "Error parsing > operator: expaecting numbers between brackets" );
			rReturnOperator._operator = "NotOperator!";
			return;
		}
		temp += *cit;
		if( cit == InputString.end() )
		{
			//error: "," wasn't found:
			ErrorMessageBox( "Error parsing > operator: expaecting ',' and cannot find it" );
			rReturnOperator._operator = "NotOperator!";
			return;
		}
		++cit;
	}
	
	rReturnOperator._operator += temp;
	rReturnOperator._operator += ",";

	temp = "";
	//cit now is on the ",", so advance it to the next token:
	++cit;
	while( cit[0] != ')' )
	{
		//validate that the token is a digit:
		if( ! isdigit( cit[0] ) )
		{
			//error: it is not a digit:
			ErrorMessageBox( "Error parsing > operator: expaecting numbers between brackets" );
			rReturnOperator._operator = "NotOperator!";
			return;
		}
		temp += *cit;
		if( cit == InputString.end() )
		{
			//error: ")" wasn't found:
			ErrorMessageBox( "Error parsing > operator: expaecting ')' and cannot find it" );
			rReturnOperator._operator = "NotOperator!";
			return;
		}
		++cit;
	}
	rReturnOperator._operator += temp;
	rReturnOperator._operator += ")";
	
	//the query:
	//ohad >(10,10) mohse
}

void CParser::HandleUnrecognizedToken( const string& str ) const
{
	string message("Syntax Error: Unrecognized token '" + str + "'");
	ErrorMessageBox( message );
}

void CParser::BuildExpTree()
{
	bool binary(false);
	TTypedStringVector::iterator TSIt = NULL;
	int Size = m_TypedStrColl.size();
	CDocsTree DocsTree;

	if(m_TypedStrColl.size() == 1)		//case of single number or variable
	{
		TSIt = m_TypedStrColl.begin();
		if( (*TSIt).Type == eOperator )
		{
			ErrorMessageBox("Syntax Error: not expecting an operator");
			return;
			//assert( (*TSIt).Type != eOperator );
		}
		if( (*TSIt).Type == eDoxTree )
			m_DocsTree = (*TSIt).Tree;	//call op==
		else	//type is eNumber or var
			m_DocsTree = (*TSIt).Value;	//call copy cons.
		return;
	}
	
	while(m_TypedStrColl.size() > 1 )
	{
		string Operator = GetHighestOperator(TSIt, binary);
		//no operator found - error!!
		if( TSIt == NULL )
		{
			ErrorMessageBox("Syntax Error: no operator was found");
			//assert(TSIt != NULL);
			return;
		}

		if(binary)
		{
			TTypedStringVector::iterator TSItLeft, TSItRight;
			TSItRight = TSIt;
			TSItRight++;
			//if binary, something must be in the right side
			if( TSItRight == m_TypedStrColl.end() )
			{
				ErrorMessageBox("Syntax Error: no operand was found on the operators' right side");
				//assert(TSItRight != m_TypedStrColl.end());
				return;
			}
			CDocsTree RightTree((*TSItRight).Value);
			if( (*TSItRight).Type == eDoxTree )
			{	//if operand is tree, use its pointer:
				RightTree = (*TSItRight).Tree;
			}
			TSItLeft = TSIt;
			if( TSItLeft == m_TypedStrColl.begin() )
			{
				ErrorMessageBox("Syntax Error: no operand was found on the operators' left side");
				//assert(TSItLeft != m_TypedStrColl.begin());
				return;
			}
			TSItLeft--;
			CDocsTree LeftTree((*TSItLeft).Value);
			if( (*TSItLeft).Type == eDoxTree )
			{	//if operand is tree, use its pointer:
				LeftTree = (*TSItLeft).Tree;
			}
			
			STypedString	TypedStr;
			TypedStr.Type = eDoxTree;
			DocsTree.BuildExp(&LeftTree, (*TSIt).Value , &RightTree);
			TypedStr.Tree = DocsTree;
			//after the insert, the iterators are no longer valid. so erase first:
			TSItLeft = m_TypedStrColl.erase(TSItLeft, ++TSItRight);	//erase: [first, last)
			m_TypedStrColl.insert(TSItLeft, TypedStr);
		}
		else	//unary operator - works on something from its *RIGHT* side 
		{
			TTypedStringVector::iterator TSItRight;
			TSItRight = TSIt;
			TSItRight++;
			CDocsTree RightTree((*TSItRight).Value);
			
			STypedString	TypedStr;
			TypedStr.Type = eDoxTree;
			DocsTree.BuildExp(&RightTree, (*TSIt).Value );
			TypedStr.Tree = DocsTree;
			//like before, erase first:
			TSIt = m_TypedStrColl.erase(TSIt, ++TSItRight);
			m_TypedStrColl.insert(TSIt, TypedStr);	
		}
	}
	m_DocsTree = DocsTree;
}

/**
  * this function take PriorOperColl list with operators and priorities, and TS - a vector 
  * with strings that part of them are operators. it searches for the highest-priority 
  * operator, returns it, and as an output parameters it gives the index of this operator
  * as well as if it is unary or binary
  **/
//second version, gives out an iterator
std::string	CParser::GetHighestOperator(OUT TTypedStringVector::iterator& HighestIt,
										OUT bool &Binary)
{
	TTypedStringVector::const_iterator	TSIt;
	TOperators::const_iterator It;
	int Priority = 0;
	std::string HighestOperator;
	
	for( TSIt = m_TypedStrColl.begin();
	TSIt != m_TypedStrColl.end();
	++TSIt )
	{
		if((*TSIt).Type == eOperator)
		{
			for( It = m_operators.begin();
			It != m_operators.end();
			++It )
			{
				//if( It->_operator == (*TSIt).Value )
				if( !(*TSIt).Value.compare(0, It->_operator.size(), It->_operator) )
				{
					if(It->_priority > Priority)
					{
						HighestOperator = It->_operator;
						Priority	= It->_priority;
						Binary		= It->_bBinary;
						HighestIt	= const_cast<TTypedStringVector::iterator>(TSIt);
					}
				}
			}
		}
	}
	return HighestOperator;
}


//evaluation of the tree:

/**
  * called by the CDocsTree, to evaluate a node
  **/
TDocIdVector CParser::EvaluateNode(const CExNode<string>* Node) const
{
	TDocIdVector ReturnColl;
	string NodeString = Node->m_Val;
	if(IsOperator(NodeString))
	{
		//run function/operator with all the childs (parameters): (recursion)
		return HandleOperator(Node);
	}
	else if(IsGroup(NodeString))
	{
		//end-condition I of the recursion:
		//return group value, which is "or" between the words
		int nNumOfCharsRead;
		SGroup Grp = GetGroup(NodeString, nNumOfCharsRead);
		if( Grp._name == "Error" )
		{
			return 0;
		}
		TGroups::const_iterator GrpIt;
		for( GrpIt = m_groups.begin();
		GrpIt != m_groups.end();
		++GrpIt )
		{
			if( !Grp._name.compare(0, GrpIt->_name.size(), GrpIt->_name) )
			{
				//calculate the group and return it:
				return HandleGroup( Grp );
			}
		}
		//var was not found	
		string message("Error: group name is illegal '" + Grp._name + "'");
		ErrorMessageBox( message );
		return 0;
		//assert(false);	//var was not found		
	}
	else if(IsWord(NodeString))
	{
		//end-condition II of the recursion:
		//return word value:
		string theWord = GetWord(NodeString);
		//calculate the word and return it:
		//call the algorithm manager to do it:
		return CAlgorithmManager::Instance()->SearchWord( theWord );
		
		return ReturnColl;
	}
	ErrorMessageBox("Error while evaluating a node");
	//assert(false);
	return 0;
}

TDocIdVector CParser::HandleOperator(const CExNode<string>* Node) const
{
	TDocIdVector ReturnColl;
	SOperator Operator = GetOperator(Node->m_Val);
	//get operands:
	CExNode<string>* current = Node->m_LeftChild;
	TDocIdVector LeftOperand = EvaluateNode(current);
	TDocIdVector RightOperand;
	if (Operator._bBinary)
	{
		current = current->m_NodeInRight;
		RightOperand = EvaluateNode(current);
	}

	if(Operator._operator == "&")
	{
		//handle "and" between the lists:
		/*
		//concatanate the two vectors:
		LeftOperand.insert( LeftOperand.end(), RightOperand.begin(), RightOperand.end() ); 
		//sort them
		sort(LeftOperand.begin(), LeftOperand.end());
		//take only docs that appear in both of the vectors
		TDocIdVector::iterator itNewEnd = unique(LeftOperand.begin(), LeftOperand.end());
		LeftOperand.erase(LeftOperand.begin(), itNewEnd);
		TDocIdVector ComplementaryColl( CompleteColl.size() - LeftOperand.size() );
		*/
		//sort them
		sort(LeftOperand.begin(), LeftOperand.end());
		sort(RightOperand.begin(), RightOperand.end());
		//TDocIdVector AndColl( min(RightOperand.size(), LeftOperand.size()) );
		TDocIdVector::iterator itNewEnd = GetCommonInstances(
			LeftOperand.begin(),
			LeftOperand.end(),
			RightOperand.begin(),
			RightOperand.end()		);
		RightOperand.erase(itNewEnd, RightOperand.end());

		int g = RightOperand.size();
		return RightOperand;
	}
	else if(Operator._operator == "|")
	{
		//handle "or" between the lists:
		//concatanate the two vectors:
		LeftOperand.insert( LeftOperand.end(), RightOperand.begin(), RightOperand.end() ); 
		//sort them
		sort(LeftOperand.begin(), LeftOperand.end());
		//remove docs that apear more than twice
		TDocIdVector::iterator itNewEnd = unique(LeftOperand.begin(), LeftOperand.end());
		LeftOperand.erase(itNewEnd, LeftOperand.end());
		return LeftOperand;
	}
	else if(Operator._operator == "!")
	{
		//handle "not": give the completion list to the operands'
		//it is jult like "and" between the *completion* list and the full list:
		TDocIdVector CompleteColl = CAlgorithmManager::Instance()->GetDocuments();
		int debug = CompleteColl.size();
		TDocIdVector ComplementaryColl( CompleteColl.size() - LeftOperand.size() );
		GetComplementary(
			CompleteColl.begin(),
			CompleteColl.end(),
			LeftOperand.begin(),
			LeftOperand.end(),
			ComplementaryColl.begin(),
			ComplementaryColl.end()		);

		return ComplementaryColl;
	}
	else if(Operator._operator[0] == '>')
	{
		ReturnColl = HandleThenOperator(Node);
	}
	return ReturnColl;
}

TDocIdVector	CParser::HandleThenOperator(const CExNode<string>* Node) const
{
	//get parameters (before, after):
	string str = Node->m_Val;
	int index = str.find("(");
	if( index == -1 )
	{
		//error: "(" wasn't found:
		ErrorMessageBox( "Error parsing > operator: expaecting '(' and cannot find it" );
		return 0;
	}
	char	line [MAXLINE];
	strcpy(line, Node->m_Val.c_str());
	//line+1, without the ">":
	char* word = strtok(line+1, " ,()\\\"\n\t");
	int nBefore = atoi(word);
	word = strtok(NULL, " ,()\\\"\n\t");
	int nAfter = atoi(word);
	
	//get operands:
	CExNode<string>* current = Node->m_LeftChild;
	TWordsCollection LeftGroup = GetWordsFromNode(current);
	//TWordsCollection StrVec;
	current = current->m_NodeInRight;
	TWordsCollection RightGroup = GetWordsFromNode(current);

	return CAlgorithmManager::Instance()->SearchNearWords(
		LeftGroup,
		RightGroup,
		nBefore,
		nAfter);
}

TDocIdVector	CParser::HandleGroup(const SGroup& Grp) const
{
	TDocIdVector ReturnColl;

	for(TWordsCollection::const_iterator cit = Grp._Words.begin();
	cit != Grp._Words.end(); ++cit )
	{
		string theWord = *cit;
		//calculate the word and return it:
		//call the algorithm manager to do it:
		TDocIdVector tempColl = CAlgorithmManager::Instance()->SearchWord( theWord );
		ReturnColl.insert( ReturnColl.end(), tempColl.begin(), tempColl.end() ); 
	}
	sort(ReturnColl.begin(), ReturnColl.end());
	TDocIdVector::iterator itNewEnd = unique(ReturnColl.begin(), ReturnColl.end());
	ReturnColl.erase(itNewEnd, ReturnColl.end());
	return ReturnColl;
}

TWordsCollection	CParser::GetWordsFromNode(const CExNode<std::string>* Node) const
{
	TWordsCollection StrVec;
	string NodeString = Node->m_Val;
	if(IsGroup(NodeString))
	{
		//end-condition I of the recursion:
		//return group value, which is "or" between the words
		int nNumOfCharsRead;
		SGroup Grp = GetGroup(NodeString, nNumOfCharsRead);
		if( Grp._name == "Error" )
		{
			return 0;
		}
		TGroups::const_iterator GrpIt;
		for( GrpIt = m_groups.begin();
		GrpIt != m_groups.end();
		++GrpIt )
		{
			if( !Grp._name.compare(0, GrpIt->_name.size(), GrpIt->_name) )
			{
				//calculate the group and return it:
				return Grp._Words;
			}
		}
		//var was not found	
		string message("Error: group name is illegal '" + Grp._name + "'");
		ErrorMessageBox( message );
		return 0;
		//assert(false);	//var was not found		
	}
	else if(IsWord(NodeString))
	{
		//end-condition II of the recursion:
		//return word value:
		string theWord = GetWord(NodeString);
		
		StrVec.push_back(theWord);
	}
	else		//chiild node is not a word and not a group!!!
		assert(false);

	return StrVec;
}

bool CParser::AddGroup(const std::string& crGrpName, const std::string& GrpMembers)
{
	//parse the group members and make sure the list of words is OK:
	ConvertExpressionToLowerCase( const_cast<string&>(GrpMembers) );
	TWordsCollection Members;
	string GrpName = crGrpName;
	
	string::const_iterator it = GrpMembers.begin();
	while( it != GrpMembers.end() )
	{
		if(IsDelimiter(it))	//case of space or tab.
		{
			++it;
		}
		//check if the next thing is a word, only if i m expecting one:
		else if( IsWord(it) )
		{
			string temp = GetWord(it);
			if( WordFilter( temp ) )
			{
				Members.push_back( temp );
			}
			else
			{
				ErrorMessageBox("Error: Group member is illegal: '" + temp + "'");
			}
			it += temp.size();
		}
		else
		{
			string message1( it );
			ErrorMessageBox( "Syntax Error: Illegal group member '" + message1 + "'" );
			return false;
		}
	}

	//handle the group name:
	ConvertExpressionToLowerCase( GrpName );
	if( IsWord(GrpName) )
	{
		/*GrpName.insert(0, "[");
		GrpName += "]";*/
	}
	else
	{
		//error:
		ErrorMessageBox( "Syntax Error: Illegal group name '" + GrpName + "'" );
		return false;
	}

	SGroup Grp(GrpName, Members);
	//make sure there is no group with the same name:
	TGroups::const_iterator GroupIt;
	for( GroupIt = m_groups.begin();
	GroupIt != m_groups.end();
	++GroupIt )
	{
		if( GroupIt->_name == GrpName )
		{
			//error:
			ErrorMessageBox( "Error: group already exist '" + GrpName + "'" );
			return false;
		}
	}

	m_groups.push_back(Grp);
	return true;

}

