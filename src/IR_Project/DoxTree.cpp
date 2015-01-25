#include "DoxTree.h"
#include "Parser.h"

using namespace std;

CDocsTree::CDocsTree(TYPE Val)	:	CExTree<TYPE>(Val)
{
}

void CDocsTree::BuildExp(CDocsTree* Operand1, string Operator, CDocsTree* Operand2)
{
   	//if root is already allocated, delete it
	if ( m_Root )
    {
		Clear(m_Root);
    }    
	m_Root = new CExNode<TYPE>(Operator);
	m_Root->m_LeftChild = Copy(Operand1->m_Root);
	if(Operand2)
		m_Root->m_LeftChild->m_NodeInRight = Copy(Operand2->m_Root);
}


//i need special preorder, with level, so i can see the levels in the printout
void CDocsTree::PreOrder(CExNode<TYPE>* current, int level) const
{
	//stopping condition:
	if(!current)
		return;
	
	//visit current:
	Visit(current, level);
	//visit childs:	(left child, and through him all other childs)
	PreOrder(current->m_LeftChild, level+1);
	//visit "brother":
	PreOrder(current->m_NodeInRight, level);
}


void CDocsTree::Visit(CExNode<TYPE>* current) const
{
	if( !current )
		return;			//no place to visit...
	
	printf("%s\n", current->m_Val.c_str());
}

void CDocsTree::Visit(CExNode<TYPE>* current, int level) const
{
	if( !current )
		return;			//no place to visit...
	
	for(int i = 0; i < level; ++i)
		printf(" ");
	printf("%s\n", current->m_Val.c_str());
}

TDocIdVector CDocsTree::EvaluateTree(CExNode<TYPE> * current) const
{
	//stopping condition:
	if(!current)
		return 0;			//no where to visit at...
	
	//evaluate current:
	int n = current->NumOfChilds();
	printf("'%s' is being handled...\n", current->m_Val.c_str());
	
	return CParser::GetInstance()->EvaluateNode(current);
}