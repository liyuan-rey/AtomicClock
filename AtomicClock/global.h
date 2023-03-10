// global.h

#pragma once

//////////////////////////////////////////////////////////////////////////

#include "skin\skinmanager.h"
#include "skin\skindialog.h"
#include "skin\skindlgbghelper.h"
#include "skin\skinbutton.h"
#include "skin\skinpicture.h"

#include "htmllite\htmllite.h"

#include "include\w3mfc\sntp.h"

//////////////////////////////////////////////////////////////////////////

#define APP_MSG_BASE				100
#define WM_ATOMICCLOCK_NTPRESPONSED		(WM_APP + APP_MSG_BASE + 1)

#define ATOMICCLOCK_THREAD_TIMEOUT			15000

#define ATOMICCLOCK_TIMERID_BASE			500
#define ATOMICCLOCK_TIMERID_ACEVERY		(ATOMICCLOCK_TIMERID_BASE + 1)
