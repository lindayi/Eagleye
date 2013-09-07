// EagleyeServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MainFrmDlg.h"
#include "EagleyeServer.h"
#include "afxsock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CEagleyeServerApp

BEGIN_MESSAGE_MAP(CEagleyeServerApp, CWinApp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEagleyeServerApp construction

CEagleyeServerApp::CEagleyeServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_pFrame = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEagleyeServerApp object

CEagleyeServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEagleyeServerApp initialization

BOOL CEagleyeServerApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	// Change the path under which your skin files are stored.
	if (CUIMgr::SetUIPath(_T("Skins\\EagleyeServer\\the.xui")) != 0)
	{
		AfxMessageBox(_T("Failed to set the ui path or the ui path isn't exist!"));
		return FALSE;
	}

	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	m_pFrame = new CMainFrmDlg;
	m_pMainWnd = m_pFrame;

	// create and load the frame with its resources

	BOOL bRet = m_pFrame->LoadFrame(IDR_MAINFRAME, 
		WS_POPUP|WS_CLIPCHILDREN|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX, NULL);

	if (!bRet)
	{
		DWORD dwLastError = m_pFrame->GetLastCreateError();
		switch (dwLastError)
		{
		case E_LOADBMPB: // 1 failed to load the base image
		case E_LOADBMPN: // 2 failed to load the background image of normal status(end by _N.bmp)
		case E_LOADBMPH: // 3 failed to laod the background image of highlight status(end by _H.bmp)
		case E_LOADBMPD: // 4 failed to load the background image of disable status(end by _D.bmp)
		case E_LOADBMPS: // 5 failed to load the background image of selected status(end by _S.bmp)
		case E_LOADBMPC: // 6 failed to load the background image of checked status(end by _C.bmp)
			TRACE(_T("Failed to load background image"));
			break;
		case E_ATTACHBMPB: // 50 failed to attach the HBITMAP of base image to CBitmap object
		case E_ATTACHBMPN: // 51 failed to attach the HBITMAP of normal image to CBitmap object
		case E_ATTACHBMPH: // 52 failed to attach the HBITMAP of highlight image to CBitmap object
		case E_ATTACHBMPD: // 53 failed to attach the HBITMAP of disable image to CBitmap object
		case E_ATTACHBMPS: // 54 failed to attach the HBITMAP of selected image to CBitmap object
		case E_ATTACHBMPC: // 55 failed to attach the HBITMAP of checked image to CBitmap object
		case E_ADJUSTCHILD:// 56 failed to adjust the child controls while change the skin
			TRACE(_T("Failed to attach bitmap to CBitmao object"));
			break;
		case E_CREATECHILD:// 110 failed to create the child window
			TRACE(_T("Failed to create child windows"));
			break;
		default:
			break;
		}
		return FALSE;
	}

	// The one and only window has been initialized, so show and update it.
	m_pFrame->ShowWindow(SW_SHOW);
	m_pFrame->UpdateWindow();

	return TRUE;
}

int CEagleyeServerApp::ExitInstance() 
{
	if (m_pFrame != NULL)
	{
		delete m_pFrame;
		m_pFrame = NULL;
	}

	CUIMgr::ReleaseSkin();

	// TODO: Add your specialized code here and/or call the base class

	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CEagleyeServerApp message handlers

