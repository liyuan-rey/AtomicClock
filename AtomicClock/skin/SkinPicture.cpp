// SkinPicture.cpp : 实现文件
//

#include "stdafx.h"
#include "..\Resource.h"

#include "SkinManager.h"
#include "SkinPicture.h"
#include "SkinSettings.h"

#include "..\include\memdc\memdc.h"

// CSkinPicture

CSkinPicture::CSkinPicture() : m_pSettings(NULL)
{
}

CSkinPicture::~CSkinPicture()
{
}


IMPLEMENT_DYNAMIC(CSkinPicture, CStatic)


BEGIN_MESSAGE_MAP(CSkinPicture, CStatic)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


UINT CSkinPicture::GetID()
{
	return GetDlgCtrlID();
}

ESkinControl CSkinPicture::GetType()
{
	return ESkinControl::Picture;
}

BOOL CSkinPicture::SetSkinInfo(CSettings* pInfo)
{
	ATLASSERT(pInfo);
	m_pSettings = dynamic_cast<CPictureSettings*>(pInfo);
	ATLASSERT(m_pSettings);

	return (NULL != m_pSettings);
}

ISkinComponent* CSkinPicture::GetSkinParent()
{
	return dynamic_cast<ISkinComponent*>(GetParent());
}

void CSkinPicture::ApplySkin()
{
	// Binding skin info
	BOOL bSuccess = SkinManager::Instance().GetCurrentSkin()->BindSkinInfo(this);
	if (!bSuccess || !m_pSettings)
	{
		AfxMessageBox(IDS_BINDINGSKINERROR);
		return;
	}

	// Apply position and size
	CRect rcArea(m_pSettings->Area);
	if (0 == rcArea.top && 0 == rcArea.left)
	{
		CRect rcWnd;
		GetWindowRect(rcWnd);
		rcArea.OffsetRect(rcWnd.TopLeft());
	}

	MoveWindow(rcArea, TRUE);
}

void CSkinPicture::PreSubclassWindow()
{
	CStatic::PreSubclassWindow();

	ModifyStyle(0, SS_OWNERDRAW);
	ModifyStyleEx(WS_EX_STATICEDGE, 0);
}


// CSkinPicture 消息处理程序

BOOL CSkinPicture::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

void CSkinPicture::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ATLASSERT( ODT_STATIC == lpDrawItemStruct->CtlType );

	CSkinPtr spSkin = SkinManager::Instance().GetCurrentSkin();
	if (!m_pSettings || !spSkin)
		return;

	// Get Background color from parent wnd
	CWnd* pParentWnd = GetParent();
	HBRUSH hbrBg = (HBRUSH)pParentWnd->SendMessage(WM_CTLCOLORSTATIC,
					(WPARAM)lpDrawItemStruct->hDC, (LPARAM)GetSafeHwnd());
	ATLASSERT( GetLastError() == 0 );

	CMemDC memDC(CDC::FromHandle(lpDrawItemStruct->hDC));

	// Draw background
	CRect rcTmp = m_pSettings->Background;
	CRect rcClient;
	GetClientRect(rcClient);

 	memDC.FillRect(rcClient, CBrush::FromHandle(hbrBg));
	spSkin->DrawRect(rcTmp, &memDC, rcClient.left, rcClient.top,
		rcClient.Width(), rcClient.Height());
}
