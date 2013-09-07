// EagleyeServer.h : main header file for the EAGLEYESERVER application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

class CMainFrmDlg;

/////////////////////////////////////////////////////////////////////////////
// CEagleyeServerApp:
// See EagleyeServer.cpp for the implementation of this class
//

class CEagleyeServerApp : public CWinApp
{
public:
	CEagleyeServerApp();

// Overrides
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	DECLARE_MESSAGE_MAP()

private:
	CMainFrmDlg *m_pFrame;
};

