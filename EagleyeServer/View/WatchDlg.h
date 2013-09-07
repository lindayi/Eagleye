// WatchDlg.h : interface of the CWatchDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WATCHDLG_H__B1A091FA_3BE4_4673_A951_7E5A902AD685__INCLUDED_)
#define AFX_WATCHDLG_H__B1A091FA_3BE4_4673_A951_7E5A902AD685__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWatchDlg : public CUIWnd
{
public:
	CWatchDlg();
	virtual ~CWatchDlg();
	void WindowID() { IDD = IDW_WATCH; }

protected:
	int InitControls();
	int InitLstPc();

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWatchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Generated message map functions
public:
	//{{AFX_MSG(CWatchDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CSkinStatic *m_pStaGroup;
	CSkinButton *m_pRadUngroup;
	CSkinButton *m_pRadGroup1;
	CSkinListCtrl *m_pLstPc;
	CSkinButton *m_pRadGroup2;
	CSkinButton *m_pRadGroup3;
	CSkinButton *m_pRadGroup4;
	CSkinButton *m_pRadGroup5;
	CSkinButton *m_pRadGroup6;

public:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// 

#endif // !defined(AFX_WATCHDLG_H__B1A091FA_3BE4_4673_A951_7E5A902AD685__INCLUDED_)
