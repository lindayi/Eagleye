// MainFrmDlg.h : interface of the CMainFrmDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRMDLG_H__469CB8C7_B440_454F_B414_F7FD248AB189__INCLUDED_)
#define AFX_MAINFRMDLG_H__469CB8C7_B440_454F_B414_F7FD248AB189__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WatchDlg.h"
#include "LogDlg.h"
#include "SettingDlg.h"

class CMainFrmDlg : public CUIWnd
{
public:
	CMainFrmDlg();
	virtual ~CMainFrmDlg();
	void WindowID() { IDD = IDW_MAIN; }

protected:
	int InitControls();

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrmDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CSkinButton *m_pBtnMin;
	CSkinButton *m_pBtnClose;
	CSkinButton *m_pRadWatch;
	CSkinButton *m_pRadLog;
	CSkinButton *m_pRadSetting;
	//CRect m_pRcTask;

public:
	

protected:
	CTaskWndMgr m_MainTaskWndMgr;
	CLogDlg m_wndLog;
	CSettingDlg m_wndSetting;
	CWatchDlg m_wndWatch;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// 

#endif // !defined(AFX_MAINFRMDLG_H__469CB8C7_B440_454F_B414_F7FD248AB189__INCLUDED_)

