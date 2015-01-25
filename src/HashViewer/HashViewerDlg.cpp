// HashViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HashViewer.h"
#include "HashViewerDlg.h"
#include <stdlib.h>			//div_t

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************/
/*     constants to determine the paths and files names         */
/****************************************************************/

const char* OUTPUT_FILES_PATH		= "D:\\MY DOCUMENTS\\IR_PROJECT\\FILES\\";
const char* DICTIONARY_FILE_NAME	= "\\DICTIONARY.TXT";
const int	SIZE_OF_FILENAME		= 150;
const int	SIZE_OF_WORD			= 25;


/////////////////////////////////////////////////////////////////////////////
// CHashViewerDlg dialog

CHashViewerDlg::CHashViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHashViewerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHashViewerDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHashViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHashViewerDlg)
	DDX_Control(pDX, IDC_VIEWER_SPREAD, m_Spread);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHashViewerDlg, CDialog)
	//{{AFX_MSG_MAP(CHashViewerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILL_VIEWER_BUTTON, OnFillViewer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHashViewerDlg message handlers

BOOL CHashViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	InitSpread();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


HCURSOR CHashViewerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CHashViewerDlg::OnFillViewer() 
{
	char pcTemp[ SIZE_OF_FILENAME ];
	strcpy( pcTemp, OUTPUT_FILES_PATH );
	strcat( pcTemp, DICTIONARY_FILE_NAME );
	m_Dictionary = new CIndexFile( pcTemp );
	div_t divResult;

	char pcWord[ SIZE_OF_WORD ];
	int nWordIndex;
	m_Dictionary->SkipLine();
	m_Dictionary->SkipLine();
	while ( !m_Dictionary->EndOfFile() )
	{
		m_Dictionary->GetStringAndWaitInSameLine( pcWord, SIZE_OF_WORD );
		m_Dictionary->GetIntAndWaitInSameLine();	//read word's index
		nWordIndex = m_Dictionary->GetInt();	//read int and go to next line

		divResult = div( nWordIndex, 40 );
		m_Spread.SetRow( divResult.quot + 1);
		m_Spread.SetCol( divResult.rem /*+ 1*/ );
		m_Spread.SetBackColor( 0x800000 /*=dark blue*/);
	}
}

void CHashViewerDlg::InitSpread()
{
	//const int MAX_ROWS = 50000;	// 50 000 * 40 = 2 000 000
	//after modifications, i reduced the hash table size to 100 000, so:
	const int MAX_ROWS = 2500;		// 2500 * 40 = 100 000
	m_Spread.SetMaxCols( 40 );
	for( int i = 0; i <= 40; i++ )
		m_Spread.SetColWidth( i, 1 );
	m_Spread.SetMaxRows( MAX_ROWS );
	for( i = 0; i <= MAX_ROWS; i++ )
		m_Spread.SetRowHeight( i, 1 );
}
