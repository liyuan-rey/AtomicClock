// AtomicClock.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AtomicClock.h"
#include "FrameDlg.h"

#include "skin\SkinManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "include\SettingsStorage\MSettingsStorageIniFile.h"
using Mortimer::CSettingsStorageIniFile;

// CAtomicClockApp
const TCHAR CAtomicClockApp::defaultSettingsFolder[] = _T("");
const TCHAR CAtomicClockApp::defaultSettingsFile[] = _T("config.ini");

BEGIN_MESSAGE_MAP(CAtomicClockApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAtomicClockApp construction
CAtomicClockApp::CAtomicClockApp()
{
	EnableHtmlHelp();

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CAtomicClockApp object
CAtomicClockApp theApp;

// CAtomicClockApp initialization
BOOL CAtomicClockApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Get app root information for later use
	m_pthAppRoot = m_pszHelpFilePath;
	m_pthAppRoot.RemoveFileSpec();
	m_pthAppRoot.AddBackslash();

	// Initialize app configuration
	int nResult = LoadSettings();
	if (nResult < 0)
	{
		AfxMessageBox(IDS_LOADSETTINGSFAILED);
		return FALSE;
	}
	else if (nResult > 0)
	{
		AfxMessageBox(IDS_LOADSETTINGSWITHERROR);
	}

	// Initialize skin configuration
	nResult = SkinManager::Instance().LoadSkin();
	CString strInfo;
	if (nResult < 0)
	{
		AfxMessageBox(IDS_LOADSKINFAILED);
		return FALSE;
	}
	else if (nResult > 0)
	{
		AfxMessageBox(IDS_LOADSKINWITHERROR);
	}


	// Create and show main interface
	CFrameDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Save app settings
	SaveSettings();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CAtomicClockApp::LoadSettings()
{
	CPath pthAppSettings = GetSettingsPath();
	if (pthAppSettings.FileExists())
	{
		CSettingsStorageIniFile stg;
		stg.SetIniFileName(pthAppSettings, CMainSettings::defaultSectionName);

		return m_settings.Load(stg) ? 0 : 1;
	}

	return -1;
}

BOOL CAtomicClockApp::SaveSettings()
{
	CPath pthAppSettings = GetSettingsPath();

	CSettingsStorageIniFile stg;
	stg.SetIniFileName(pthAppSettings, CMainSettings::defaultSectionName);

	return m_settings.Save(stg);
}

CPath CAtomicClockApp::GetSettingsPath(LPCTSTR szSettingsFile/* = defaultSettingsFile*/)
{
	CPath pthAppSettings = m_pthAppRoot + defaultSettingsFolder;
	pthAppSettings.AddBackslash();
	pthAppSettings += szSettingsFile;

	return pthAppSettings;
}
