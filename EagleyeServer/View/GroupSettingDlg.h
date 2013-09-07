// GroupSettingDlg.h : interface of the CGroupSettingDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GROUPSETTINGDLG_H__312110D1_C30A_44A9_94D6_57B1866A761A__INCLUDED_)
#define AFX_GROUPSETTINGDLG_H__312110D1_C30A_44A9_94D6_57B1866A761A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGroupSettingDlg : public CUIWnd
{
public:
	CGroupSettingDlg();
	virtual ~CGroupSettingDlg();
	void WindowID() { IDD = IDW_GROUPSETTING; }

protected:
	int InitControls();
	int InitCmbGroupname();
	int InitCmbGrouppolicy();

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CGroupSettingDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtn6();
	afx_msg void OnBtnSavegroup();
	afx_msg void OnSelChange(); 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CSkinStatic *m_pStaGroupname;
	CSkinComboBox *m_pCmbGroupname;
	CSkinButton *m_pBtn6;
	CSkinStatic *m_pStaGrouppolicy;
	CSkinComboBox *m_pCmbGrouppolicy;
	CSkinButton *m_pBtnSavegroup;

public:
	CString m_strGroupname;
	CString m_strGrouppolicy;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// 

#endif // !defined(AFX_GROUPSETTINGDLG_H__312110D1_C30A_44A9_94D6_57B1866A761A__INCLUDED_)
