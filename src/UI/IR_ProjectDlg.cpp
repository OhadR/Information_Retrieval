// IR_ProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IR_Project.h"
#include "IR_ProjectDlg.h"
#include "DiagnosticsDialog.h"
#include "../IR_Project/Parser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIR_ProjectDlg dialog

CIR_ProjectDlg::CIR_ProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIR_ProjectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIR_ProjectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIR_ProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIR_ProjectDlg)
	DDX_Control(pDX, IDC_GRP_NAME_EDIT, m_GrpNameEdit);
	DDX_Control(pDX, IDC_GRP_MMBRS_EDIT, m_GrpMembersEdit);
	DDX_Control(pDX, IDC_SEARCH_RESULTS_LIST, m_ResultsList);
	DDX_Control(pDX, IDC_QUERY_EDIT, m_QueryEdit);
	DDX_Control(pDX, IDC_PATH_EDIT, m_PathEdit);
	DDX_Control(pDX, IDC_FILE_VIEWER_EDIT, m_FileViewer);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIR_ProjectDlg, CDialog)
	//{{AFX_MSG_MAP(CIR_ProjectDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUILD_BUTTON, OnBuildButton)
	ON_BN_CLICKED(IDC_SEARCH_BUTTON, OnSearchButton)
	ON_BN_CLICKED(IDC_SHOW_BUTTON, OnShowButton)
	ON_BN_CLICKED(IDC_SET_GRP_BUTTON, OnSetGrpButton)
	ON_BN_CLICKED(IDC_DIAGNOSTICS_BUTTON, OnDiagnosticsButton)
	ON_BN_CLICKED(IDC_BUTTON2, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIR_ProjectDlg message handlers

BOOL CIR_ProjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_ResultsList.InsertColumn( 1, "#", LVCFMT_CENTER, 25 );
	m_ResultsList.InsertColumn( 2, " Document ID ", LVCFMT_LEFT, 200 );
	m_ResultsList.SetExtendedStyle(LVS_EX_FULLROWSELECT);


	m_FileViewer.Initialize();


	CAlgorithmManager::Instance()->SetListener( this );
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIR_ProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIR_ProjectDlg::OnPaint() 
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
HCURSOR CIR_ProjectDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*****************************************************/

/*****************************************************/

void CIR_ProjectDlg::OnBuildButton() 
{
	CWaitCursor Cursor;		//shows "busy" mouse

	//get the path:
	CString Path;
	m_PathEdit.GetWindowText( Path );
	CAlgorithmManager::Instance()->SetSearchedFilesPath( Path.GetBuffer(100) );
	CAlgorithmManager::Instance()->BuildDataBase();
}

void CIR_ProjectDlg::OnSearchButton() 
{
	CWaitCursor Cursor;		//shows "busy" mouse

	CString Query;
	CString Answer;
	Answer=" ";

	m_QueryEdit.GetWindowText( Query );
	TDocIdVector ResultsSortedVector = CAlgorithmManager::Instance()->Search(
		Query.GetBuffer(100) ,Answer);
	
	int n = ResultsSortedVector.size();


	//preparing the keywords
	m_strSearchKeywords=Answer;
	m_FileViewer.ClearKeywords();
	m_FileViewer.AddKeywords(m_strSearchKeywords);

	PrintResultsToList( ResultsSortedVector );
}

void CIR_ProjectDlg::PrintResultsToList( const TDocIdVector& ResultsSortedVector )
{
	CString strIndex, strDocId;
	int i = 0;
	//clear the list from previous search:
	m_ResultsList.DeleteAllItems();
	for( TDocIdVector::const_iterator cit = ResultsSortedVector.begin();
	cit != ResultsSortedVector.end(); ++cit )
	{
		strIndex.Format( "%d", i );
		strDocId.Format( "%d", *cit );
		m_ResultsList.InsertItem(i, strIndex );
		m_ResultsList.SetItemText(i, 1, strDocId );
		
		++i;
	}
}


//called by the algorithm, after this class was registrated
void CIR_ProjectDlg::Write(const std::string& Line)
{
	/*CString WindowText;
	m_FileViewer.GetWindowText( WindowText );
	WindowText += Line.c_str();
	WindowText += "\r\n";
	m_FileViewer.SetWindowText( WindowText );
	*/
	m_FileViewer.SetWindowText( Line.c_str() );

    return ;
}

void CIR_ProjectDlg::OnShowButton() 
{
	CWaitCursor Cursor;		//shows "busy" mouse

	CString strConverter;
	POSITION pos = m_ResultsList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}

	while (pos)
	{
		int nItem = m_ResultsList.GetNextSelectedItem(pos);
		strConverter = m_ResultsList.GetItemText( nItem, 1 );
		int nDocId = atoi( strConverter.GetBuffer(10) );

		CAlgorithmManager::Instance()->SearchForDocument( nDocId );
	}
}

void CIR_ProjectDlg::OnSetGrpButton() 
{
	CString GrpName;
	m_GrpNameEdit.GetWindowText( GrpName );
	CString GrpMembers;
	m_GrpMembersEdit.GetWindowText( GrpMembers );
	CAlgorithmManager::Instance()->AddGroup( GrpName.GetBuffer(40), GrpMembers.GetBuffer(100) );
	
}

void CIR_ProjectDlg::OnDiagnosticsButton() 
{
	CDiagnosticsDialog DiagnosticsDialog;
	DiagnosticsDialog.m_NumOfWordsFilteredSinceTooShort = CAlgorithmManager::Instance()->GetNumOfWordsFilteredSinceTooShort();
	DiagnosticsDialog.m_NumOfWordsFilteredSinceTooLong = CAlgorithmManager::Instance()->GetNumOfWordsFilteredSinceTooLong();
	DiagnosticsDialog.m_NumOfTotalWords = CAlgorithmManager::Instance()->GetNumOfTotalWords();
	DiagnosticsDialog.m_NumOfUniqueWords = CAlgorithmManager::Instance()->GetNumOfUniqueWords();
	DiagnosticsDialog.m_groups = CParser::GetInstance()->GetGroups();
	DiagnosticsDialog.m_StopList = CAlgorithmManager::Instance()->GetStopList();
	DiagnosticsDialog.m_nStopListSize = CAlgorithmManager::Instance()->GetStopList().size();
	DiagnosticsDialog.DoModal();

	
}

void CIR_ProjectDlg::OnOK() 
{
	return;	
}


void CIR_ProjectDlg::OnExit() 
{
	CDialog::OnOK();
	
}
