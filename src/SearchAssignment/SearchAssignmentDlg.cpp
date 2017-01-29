// SearchAssignmentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SearchAssignment.h"
#include "SearchAssignmentDlg.h"
#include "FileViewer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const int MAX_WORDS_IN_QUERY = 20;

/////////////////////////////////////////////////////////////////////////////
// CSearchAssignmentDlg dialog

CSearchAssignmentDlg::CSearchAssignmentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchAssignmentDlg::IDD, pParent)
{
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CSearchAssignmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchAssignmentDlg)
	DDX_Control(pDX, IDC_TITLE_STATIC, m_Title);
	DDX_Control(pDX, IDC_BUILDPATHEDIT, m_FilesToBuildPath);
	DDX_Control(pDX, IDC_QUERYEDIT, m_Query);
	DDX_Control(pDX, IDC_OUTPUTFILESPATHEDIT, m_OutputFilesPath);
	DDX_Control(pDX, IDC_SEARCH_RESULTS_LIST, m_SearchResultsList);
	DDX_Control(pDX, IDC_STATUS_STATIC, m_StatusStatic);
	DDX_Control(pDX, IDC_SHOWBUTTON, m_ShowButton);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSearchAssignmentDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchAssignmentDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEARCHBUTTON, OnSearch)
	ON_BN_CLICKED(IDC_BUILDBUTTON, OnBuild)
	ON_NOTIFY(NM_DBLCLK, IDC_SEARCH_RESULTS_LIST, OnListDblclk)
	ON_BN_CLICKED(IDC_SHOWBUTTON, OnShow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchAssignmentDlg message handlers

BOOL CSearchAssignmentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_SearchResultsList.InsertColumn( 1, "#", LVCFMT_CENTER, 25 );
	m_SearchResultsList.InsertColumn( 2, " Document File Name ", LVCFMT_LEFT, 200 );

	CFont font;
	font.CreateFont (-20,0,0,0, FW_BOLD, 0, 1, 0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_CHARACTER_PRECIS , DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"MS Sans Serif");
	m_StatusStatic.SetFont(&font);

	m_ShowButton.SetFocus();

	
	return TRUE;
}



// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CSearchAssignmentDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSearchAssignmentDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CSearchAssignmentDlg::OnBuild() 
{
	CWaitCursor Cursor;		//shows "busy" mouse

	Status nBuildResultStatus;
	CString StemmedFilesPath, OutputFilesPath;
	m_FilesToBuildPath.GetWindowText( StemmedFilesPath );
	m_OutputFilesPath.GetWindowText( OutputFilesPath );
	m_VectorianModel.Build( StemmedFilesPath, OutputFilesPath, nBuildResultStatus );
	if ( nBuildResultStatus == OK )
	{
		m_StatusStatic.SetTextColor(RGB(0, 255, 0)/*green*/);
		m_StatusStatic.SetWindowText( "BUILDING FILES COMPLETED - OK" );
	}
	else
	{
		CString strErrorMsg = "ERROR: BUILDING FILES FAILED:\n";
		m_StatusStatic.SetTextColor(RGB(255, 0, 0)/*red*/);
		if ( nBuildResultStatus == COULD_NOT_CREATE_DB_FILES )
		{
			strErrorMsg += "COULD_NOT_CREATE_DB_FILES";
		}
		//can add if's with messages
		m_StatusStatic.SetWindowText( strErrorMsg );
	}
}


void CSearchAssignmentDlg::OnSearch() 
{
	CWaitCursor Cursor;		//shows "busy" mouse

	Status nSearchResultStatus;
	char ppcResultsSortedVector[ MAX_NUM_OF_FILES ][ SIZE_OF_FILENAME ];
	CString Query, OutputFilesPath;
	
	m_Query.GetWindowText( Query );
	m_OutputFilesPath.GetWindowText( OutputFilesPath );
	
	m_VectorianModel.Search( OutputFilesPath, Query, ppcResultsSortedVector, nSearchResultStatus );
	if ( nSearchResultStatus == OK )
	{
		m_StatusStatic.SetTextColor(RGB(0, 255, 0)/*green*/);
		m_StatusStatic.SetWindowText( "SEARCH WAS COMPLETED - OK" );
	}
	else
	{
		CString strErrorMsg = "ERROR: SEARCHING FAILED:\n";
		m_StatusStatic.SetTextColor(RGB(255, 0, 0)/*red*/);
		if ( nSearchResultStatus == DB_FILES_NOT_FOUND )
		{
			strErrorMsg += "DB_FILES_NOT_FOUND";
		}
		//can add if's with messages
		m_StatusStatic.SetWindowText( strErrorMsg );
		return;
	}
	PrintResultsToList( ppcResultsSortedVector );
}

void CSearchAssignmentDlg::PrintResultsToList( char ppcResultsSortedVector[][SIZE_OF_FILENAME])
{
	CString strField;
	int i = 0;
	//clear the list from previous search:
	m_SearchResultsList.DeleteAllItems();
	while( strcmp( ppcResultsSortedVector[ i ], "END_OF_VECTOR") != 0 )
	{
		strField.Format( "%d", i );
		m_SearchResultsList.InsertItem(i, strField );
		m_SearchResultsList.SetItemText(i, 1, ppcResultsSortedVector[ i ] );
		
		i++;
	}
}

void CSearchAssignmentDlg::OnListDblclk( NMHDR* pNMHDR, LRESULT* pResult ) 
{
	OnShow();
}

void CSearchAssignmentDlg::OnShow() 
{
	CString FilePath;
	m_FilesToBuildPath.GetWindowText( FilePath );
	char pcFilePath[ SIZE_OF_FILENAME ] = "";
	sscanf( FilePath, "%s", pcFilePath );
	
	m_VectorianModel.Show( pcFilePath  );

	CString strFileName, strConverter;
	POSITION pos = m_SearchResultsList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		while (pos)
		{
			int nItem = m_SearchResultsList.GetNextSelectedItem(pos);
			strConverter = m_SearchResultsList.GetItemText( nItem, 1 );	//*.stem
			strConverter.Replace( "STEM", "TXT" );
			strConverter.Replace( "stem", "txt" );

			strFileName = pcFilePath;
			strFileName += strConverter;
			
			CFileViewer FileViewer( strFileName, IDD_FILE_VIEWER );
			FileViewer.DoModal();
		}
	}
}
