// HashViewer.h : main header file for the HASHVIEWER application
//

#if !defined(AFX_HASHVIEWER_H__2F3E0DE2_775E_11D4_8D1D_005004355210__INCLUDED_)
#define AFX_HASHVIEWER_H__2F3E0DE2_775E_11D4_8D1D_005004355210__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHashViewerApp:
// See HashViewer.cpp for the implementation of this class
//

class CHashViewerApp : public CWinApp
{
public:
	CHashViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHashViewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHashViewerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HASHVIEWER_H__2F3E0DE2_775E_11D4_8D1D_005004355210__INCLUDED_)
