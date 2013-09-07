// PolicySettingDlg.h : interface of the CPolicySettingDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLICYSETTINGDLG_H__9B55BBA6_4AEA_48EB_A79D_2C618D571768__INCLUDED_)
#define AFX_POLICYSETTINGDLG_H__9B55BBA6_4AEA_48EB_A79D_2C618D571768__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPolicySettingDlg : public CUIWnd
{
public:
	CPolicySettingDlg();
	virtual ~CPolicySettingDlg();
	void WindowID() { IDD = IDW_POLICYSETTING; }

protected:
	int InitControls();
	int InitCmbPolicyname();
	int InitLstBlacklist();

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPolicySettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CPolicySettingDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtnSavepolicy();
	afx_msg void OnBtnNewpolicy();
	afx_msg void OnSelChange(); 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CSkinStatic *m_pStaPolicyname;
	CSkinComboBox *m_pCmbPolicyname;
	CSkinListCtrl *m_pLstBlacklist;
	CSkinButton *m_pBtnSavepolicy;
	CSkinStatic *m_pStaBlacklist;
	CSkinButton *m_pBtnNewpolicy;

public:
	CString m_strPolicyname;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// 

#endif // !defined(AFX_POLICYSETTINGDLG_H__9B55BBA6_4AEA_48EB_A79D_2C618D571768__INCLUDED_)
