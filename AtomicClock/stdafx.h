// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER
#define WINVER 0x0410 // Allow use of features specific to Windows 98 or later.
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500 // Allow use of features specific to Windows 2000 or later.
#endif						

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410 // Allow use of features specific to Windows 98 or later.
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0400 // Allow use of features specific to IE 4.0 or later.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxpriv.h>
#include <afxsock.h>		// MFC socket extensions
#include <afxtempl.h>
#include <afxmt.h>

#include <Shlwapi.h>
#include <atlpath.h>
#include <ATLComTime.h>
#include <atlsimpcoll.h>

#include <math.h>

#include <loki/SmartPtr.h>

#include "global.h"
