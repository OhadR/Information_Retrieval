// IR_Project.h : main header file for the IR_PROJECT application
//

#if !defined(AFX_IR_PROJECT_H__68387805_CEDE_458C_AE66_614AA028D3CD__INCLUDED_)
#define AFX_IR_PROJECT_H__68387805_CEDE_458C_AE66_614AA028D3CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIR_ProjectApp:
// See IR_Project.cpp for the implementation of this class
//

class CIR_ProjectApp : public CWinApp
{
public:
	CIR_ProjectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIR_ProjectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIR_ProjectApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IR_PROJECT_H__68387805_CEDE_458C_AE66_614AA028D3CD__INCLUDED_)
