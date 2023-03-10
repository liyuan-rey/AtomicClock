// FrameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AtomicClock.h"
#include "FrameDlg.h"

#include "skin\SkinManager.h"
#include "skin\Skin.h"

#include "DlgMain.h"
#include "DlgTrayClock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFrameDlg dialog
CFrameDlg::CFrameDlg(CWnd* pParent /*=NULL*/)
	: CSkinDialog(CFrameDlg::IDD, pParent)
	, m_nActivedPanel(0), m_pWndActivedPanel(NULL), m_pDlgMain(NULL)
	, m_pDlgTrayClock(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFrameDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICT_1, m_pic1);
	DDX_Control(pDX, IDC_PICT_2, m_pic2);
	DDX_Control(pDX, IDC_PICT_3, m_pic3);
	DDX_Control(pDX, IDC_RBN_ATOMICCLOCK, m_rbnAtomicClock);
	DDX_Control(pDX, IDC_RBN_TRAYCLOCK, m_rbnTrayClock);
	DDX_Control(pDX, IDC_RBN_WEATHER, m_rbnWeather);
	DDX_Control(pDX, IDC_RBN_REMINDER, m_rbnReminder);
	DDX_Control(pDX, IDC_RBN_CALENDER, m_rbnCalender);
	DDX_Control(pDX, IDC_RBN_STOPWATCH, m_rbnStopWatch);
	DDX_Control(pDX, IDC_RBN_SETTINGS, m_rbnSettings);
	DDX_Control(pDX, IDC_RBN_ABOUT, m_rbnAbout);
	DDX_Radio(pDX, IDC_RBN_ATOMICCLOCK, m_nActivedPanel);
}

BEGIN_MESSAGE_MAP(CFrameDlg, CSkinDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RBN_ATOMICCLOCK, IDC_RBN_ABOUT, OnChangePanel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CFrameDlg message handlers
BOOL CFrameDlg::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	ApplySkin();

	// create sub dlg
	InitPanel();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFrameDlg::ApplySkin()
{
	m_pic1.ApplySkin();
	m_pic2.ApplySkin();
	m_pic3.ApplySkin();

	m_rbnAtomicClock.ApplySkin();
	m_rbnTrayClock.ApplySkin();
	m_rbnWeather.ApplySkin();
	m_rbnReminder.ApplySkin();
	m_rbnCalender.ApplySkin();
	m_rbnStopWatch.ApplySkin();
	m_rbnSettings.ApplySkin();
	m_rbnAbout.ApplySkin();
}

void CFrameDlg::InitPanel()
{
	CSkinPtr spSkin = SkinManager::Instance().GetCurrentSkin();
	ATLASSERT(spSkin);

	RECT rcArea = {0};
	spSkin->GetCustomSetting(CSkin::GCSRect, 1, &rcArea);
	ATLASSERT( FALSE == CRect(rcArea).IsRectEmpty() );

	ATLASSERT( m_pDlgMain == NULL );
	m_pDlgMain = new CDlgMain(this);
	m_pDlgMain->Create(CDlgMain::IDD, this);
	ATLASSERT(m_pDlgMain->GetSafeHwnd());
	m_pDlgMain->MoveWindow(&rcArea, FALSE);

	ATLASSERT( m_pDlgTrayClock == NULL );
	m_pDlgTrayClock = new CDlgTrayClock(this);
	m_pDlgTrayClock->Create(CDlgTrayClock::IDD, this);
	ATLASSERT(m_pDlgTrayClock->GetSafeHwnd());
	m_pDlgTrayClock->MoveWindow(&rcArea, FALSE);

	OnChangePanel(IDC_RBN_ATOMICCLOCK);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CFrameDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CSkinDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFrameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFrameDlg::OnChangePanel(UINT id)
{
	if (m_pWndActivedPanel->GetSafeHwnd() && m_nActivedPanel == id)
		return;

	UpdateData(TRUE);

	CWnd* pWndOld = m_pWndActivedPanel;

	switch(id)
	{
	case IDC_RBN_ATOMICCLOCK:
		m_pWndActivedPanel = m_pDlgMain;
		m_nActivedPanel = id;
		break;
	case IDC_RBN_TRAYCLOCK:
		m_pWndActivedPanel = m_pDlgTrayClock;
		m_nActivedPanel = id;
		break;
	case IDC_RBN_WEATHER:
	case IDC_RBN_REMINDER:
	case IDC_RBN_CALENDER:
	case IDC_RBN_STOPWATCH:
	case IDC_RBN_SETTINGS:
	case IDC_RBN_ABOUT:
		return;
	default:
		ATLASSERT( FALSE && _T("Unknown panel id.") );
		return;
	}

	pWndOld->GetSafeHwnd() ? pWndOld->ShowWindow(SW_HIDE) : __noop;
	m_pWndActivedPanel->ShowWindow(SW_NORMAL);
}

void CFrameDlg::OnDestroy()
{
	if (m_pDlgMain->GetSafeHwnd())
	{
		m_pDlgMain->DestroyWindow();
		delete m_pDlgMain;
		m_pDlgMain = NULL;
	}

	if (m_pDlgTrayClock->GetSafeHwnd())
	{
		m_pDlgTrayClock->DestroyWindow();
		delete m_pDlgTrayClock;
		m_pDlgTrayClock = NULL;
	}

	CSkinDialog::OnDestroy();
}
