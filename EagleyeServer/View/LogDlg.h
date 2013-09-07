// LogDlg.h : interface of the CLogDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGDLG_H__AF0BD319_B4D7_4E03_99F4_39C06F19BADE__INCLUDED_)
#define AFX_LOGDLG_H__AF0BD319_B4D7_4E03_99F4_39C06F19BADE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLogDlg : public CUIWnd
{
public:
	CLogDlg();
	virtual ~CLogDlg();
	void WindowID() { IDD = IDW_LOG; }

protected:
	int InitControls();
	int InitLstLog();

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CLogDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtn2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CSkinListCtrl *m_pLstLog;
	CSkinButton *m_pBtn2;

public:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// 

#endif // !defined(AFX_LOGDLG_H__AF0BD319_B4D7_4E03_99F4_39C06F19BADE__INCLUDED_)
