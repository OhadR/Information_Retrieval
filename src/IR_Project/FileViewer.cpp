// MhiCommDialog.cpp: implementation of the CMhiCommDialog class.
//
//////////////////////////////////////////////////////////////////////

#include <afxwin.h>
#include <afxdlgs.h>
#include <afxcmn.h>


#include "../Basic/StaticControls.h"
#include "Resource.h"
#include "FileViewer.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CFileViewer, CDialog)
	//{{AFX_MSG_MAP(CMhiCommDialog)
	//ON_BN_CLICKED(IDOK, OnOk)
	//ON_BN_CLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CFileViewer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMhiCommDialog)
	DDX_Control(pDX, IDC_FILE_VIEWER_TITLE_STATIC, m_Title);
	DDX_Control(pDX, IDC_FILE_VIEWER_EDIT, m_Viewer);
	//}}AFX_DATA_MAP
}

CFileViewer::CFileViewer( CString FileName, UINT IDD) : CDialog(IDD)
{
	m_FileName = FileName;
    m_File = fopen( m_FileName, "r" );
    if ( m_File == NULL )
	{
        //ERROR!!! will be handled in OnInitDialog(), when m_Viewer will be created
	}
}


BOOL CFileViewer::OnInitDialog()
{
	CDialog::OnInitDialog();

	if ( m_File != NULL )
	{
		ShowFile();
	}
	else
	{
		//ERROR:
		m_Viewer.SetWindowText( "ERROR - COULDN'T OPEN TEXT FILE: " + m_FileName );
	}

	return TRUE;
}


void CFileViewer::ShowFile()
{
	CString WindowText = m_FileName;
	WindowText += ":\r\n\r\n";
	m_Viewer.SetWindowText( WindowText );
	
	char Line[ MAX_LINE_SIZE ];
	
	while ( !feof(m_File) )
	{
		fgets( Line, MAX_LINE_SIZE, m_File);
		//fread( Line, 1, MAX_LINE_SIZE, m_File);	//read MAX_LINE_SIZE bytes (ites is byte)
		m_Viewer.GetWindowText( WindowText );
		WindowText += Line;
		WindowText += "\r\n";
		m_Viewer.SetWindowText( WindowText );
	}
	fclose( m_File );

    return ;
}