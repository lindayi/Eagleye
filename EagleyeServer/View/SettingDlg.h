// SettingDlg.h : interface of the CSettingDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGDLG_H__7C7DCF66_7619_4358_A6AE_9FABA026DCF8__INCLUDED_)
#define AFX_SETTINGDLG_H__7C7DCF66_7619_4358_A6AE_9FABA026DCF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "GroupSettingDlg.h"
#include "PolicySettingDlg.h"
#include "SystemSettingDlg.h"

class CSettingDlg : public CUIWnd
{
public:
	CSettingDlg();
	virtual ~CSettingDlg();
	void WindowID() { IDD = IDW_SETTING; }

protected:
	int InitControls();

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CSettingDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CSkinStatic *m_pStaSetting;
	CSkinButton *m_pRadSystemsetting;
	CSkinButton *m_pRadPolicysetting;
	CSkinButton *m_pRadGroupsetting;
	//CRectCtrl *m_pRcSettask;

public:

protected:
	CTaskWndMgr m_SettingTaskWndMgr;
	CPolicySettingDlg m_wndPolicySetting;
	CSystemSettingDlg m_wndSystemSetting;
	CGroupSettingDlg m_wndGroupSetting;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// 

#endif // !defined(AFX_SETTINGDLG_H__7C7DCF66_7619_4358_A6AE_9FABA026DCF8__INCLUDED_)
