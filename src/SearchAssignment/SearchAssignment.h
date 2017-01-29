// SearchAssignment.h : main header file for the SEARCHASSIGNMENT application
//

#if !defined(AFX_SEARCHASSIGNMENT_H__)
#define AFX_SEARCHASSIGNMENT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols



/////////////////////////////////////////////////////////////////////////////
// CSearchAssignmentApp:
// See SearchAssignment.cpp for the implementation of this class
//

class CSearchAssignmentApp : public CWinApp
{
public:
	CSearchAssignmentApp();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchAssignmentApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHASSIGNMENT_H__)
