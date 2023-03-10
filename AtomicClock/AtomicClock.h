// AtomicClock.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include <loki/Singleton.h>

#include "skin\skinmanager.h"
#include "AtomicClockSettings.h"

// CAtomicClockApp:
// See AtomicClock.cpp for the implementation of this class
//
class CAtomicClockApp : public CWinApp
{
public:
	CAtomicClockApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	protected:
	//{{AFX_MSG(CAtomicClockApp)

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	static const TCHAR defaultSettingsFolder[];
	static const TCHAR defaultSettingsFile[];

	AFX_INLINE CMainSettings& GetSettings() {
		return m_settings;
	}

	CPath GetSettingsPath(LPCTSTR szSettingsFile = defaultSettingsFile);

protected:
	int LoadSettings();
	BOOL SaveSettings();

	CPath m_pthAppRoot;
	CMainSettings m_settings;
};

extern CAtomicClockApp theApp;
