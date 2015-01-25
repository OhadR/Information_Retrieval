#if !defined(_EXTENDED_EXPRESSION_TREE_H_)
#define _EXTENDED_EXPRESSION_TREE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Basic/ExtendedTree.h"
#include "Utils.h"
#include <string>
#include <vector>

typedef std::string TYPE;

/**
  * since it is a special tree for parsing and evaluating, i dont care to include
  * special files (like evaluator.h). generic methods, like AddChild(), copy cons.
  * and other were defined in the parent
  **/
class CDocsTree : public CExTree<TYPE>
{
public:
	CDocsTree() {}
	CDocsTree(TYPE Val);
	~CDocsTree() {}

	void			BuildExp(CDocsTree* Operand1, std::string Operator,
							 CDocsTree* Operand2 = NULL);

	virtual void		PreOrder() const		{ PreOrder(m_Root, 0); }
	TDocIdVector		EvaluateTree() const	{ return EvaluateTree(m_Root);	}
	
protected:
	virtual void	Visit(CExNode<TYPE>* current) const;
	virtual void	Visit(CExNode<TYPE>* current, int level) const;
	
private:
	void				PreOrder(CExNode<TYPE> * current, int level) const;
	TDocIdVector		EvaluateTree(CExNode<TYPE> * current) const;
	
};


#endif // !defined(_EXTENDED_EXPRESSION_TREE_H_)
