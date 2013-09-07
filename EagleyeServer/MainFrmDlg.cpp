// MainFrmDlg.cpp : implementation of the CMainFrmDlg class
//

#include "stdafx.h"
#include "EagleyeServer.h"
#include "MainFrmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrmDlg

BEGIN_MESSAGE_MAP(CMainFrmDlg, CUIWnd)
	//{{AFX_MSG_MAP(CMainFrmDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrmDlg construction/destruction

CMainFrmDlg::CMainFrmDlg(): m_MainTaskWndMgr(FALSE)
{
	m_pBtnMin = NULL;
	m_pBtnClose = NULL;
	m_pRadWatch = NULL;
	m_pRadLog = NULL;
	m_pRadSetting = NULL;
	//m_pRcTask = NULL;

}

CMainFrmDlg::~CMainFrmDlg()
{
}

void CMainFrmDlg::DoDataExchange(CDataExchange* pDX)
{
	CUIWnd::DoDataExchange(pDX);

	//DDX_Check(pDX, IDC_CHK_MAX, m_bMax);
}


//////////////////////////////////////////////////////////////////////////
// protected

int CMainFrmDlg::InitControls()
{
	m_pBtnMin = (CSkinButton *)GetDlgItem(IDC_BTN_MIN);
	m_pBtnClose = (CSkinButton *)GetDlgItem(IDC_BTN_CLOSE);
	m_pRadWatch = (CSkinButton *)GetDlgItem(IDC_RAD_WATCH);
	m_pRadLog = (CSkinButton *)GetDlgItem(IDC_RAD_LOG);
	m_pRadSetting = (CSkinButton *)GetDlgItem(IDC_RAD_SETTING);
	
	

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrmDlg message handlers

int CMainFrmDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CUIWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (InitControls() != 0)
		return -1;

	CenterWindow();
	
	// TODO: Add your message handler code here

	m_MainTaskWndMgr.SetParent(this);
	CRect m_pRcTask(-1,155,800,600);
	m_MainTaskWndMgr.SetPosRect(m_pRcTask);
	m_MainTaskWndMgr.AddTaskWindow(IDC_RAD_WATCH, &m_wndWatch, IDW_WATCH);
	m_MainTaskWndMgr.AddTaskWindow(IDC_RAD_LOG, &m_wndLog, IDW_LOG);
	m_MainTaskWndMgr.AddTaskWindow(IDC_RAD_SETTING, &m_wndSetting, IDW_SETTING);
	m_MainTaskWndMgr.SwitchToTaskWindow(IDC_RAD_WATCH);

	return 0;
}
