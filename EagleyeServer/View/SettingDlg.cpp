// SettingDlg.cpp : implementation of the CSettingDlg class
//

#include "stdafx.h"
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg

BEGIN_MESSAGE_MAP(CSettingDlg, CUIWnd)
	//{{AFX_MSG_MAP(CSettingDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg construction/destruction

CSettingDlg::CSettingDlg() : m_SettingTaskWndMgr(FALSE)
{
	m_pStaSetting = NULL;
	m_pRadSystemsetting = NULL;
	m_pRadPolicysetting = NULL;
	m_pRadGroupsetting = NULL;
	//m_pRcSettask = NULL;

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CUIWnd::DoDataExchange(pDX);

}


//////////////////////////////////////////////////////////////////////////
// protected

int CSettingDlg::InitControls()
{
	m_pStaSetting = (CSkinStatic *)GetDlgItem(IDC_STA_SETTING);
	m_pRadSystemsetting = (CSkinButton *)GetDlgItem(IDC_RAD_SYSTEMSETTING);
	m_pRadPolicysetting = (CSkinButton *)GetDlgItem(IDC_RAD_POLICYSETTING);
	m_pRadGroupsetting = (CSkinButton *)GetDlgItem(IDC_RAD_GROUPSETTING);
	//m_pRcSettask = (CRectCtrl *)GetRectChild(IDC_RECT_SETTASK);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg message handlers

int CSettingDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CUIWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (InitControls() != 0)
		return -1;

	m_SettingTaskWndMgr.SetParent(this);
	CRect m_pRcSetting(256,-1,800,445);
	m_SettingTaskWndMgr.SetPosRect(m_pRcSetting);
	m_SettingTaskWndMgr.AddTaskWindow(IDC_RAD_SYSTEMSETTING, &m_wndSystemSetting, IDW_SYSTEMSETTING);
	m_SettingTaskWndMgr.AddTaskWindow(IDC_RAD_POLICYSETTING, &m_wndPolicySetting, IDW_POLICYSETTING);
	m_SettingTaskWndMgr.AddTaskWindow(IDC_RAD_GROUPSETTING, &m_wndGroupSetting, IDW_GROUPSETTING);
	m_SettingTaskWndMgr.SwitchToTaskWindow(IDC_RAD_SYSTEMSETTING);

	return 0;
}
