// SystemSettingDlg.h : interface of the CSystemSettingDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMSETTINGDLG_H__62F29AFB_F8A7_486A_BF98_9E6EFFA122F2__INCLUDED_)
#define AFX_SYSTEMSETTINGDLG_H__62F29AFB_F8A7_486A_BF98_9E6EFFA122F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSystemSettingDlg : public CUIWnd
{
public:
	CSystemSettingDlg();
	virtual ~CSystemSettingDlg();
	void WindowID() { IDD = IDW_SYSTEMSETTING; }

protected:
	int InitControls();

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CSystemSettingDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtnSavesystem();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CSkinStatic *m_pStaOfflinetime;
	CSkinEdit *m_pEdtOfflinetime;
	CSkinStatic *m_pStaRefresh;
	CSkinEdit *m_pEdtRefresh;
	CSkinButton *m_pBtnSavesystem;

public:
	CString m_strOfflinetime;
	CString m_strRefresh;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// 

#endif // !defined(AFX_SYSTEMSETTINGDLG_H__62F29AFB_F8A7_486A_BF98_9E6EFFA122F2__INCLUDED_)
