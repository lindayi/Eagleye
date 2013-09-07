// LogDlg.cpp : implementation of the CLogDlg class
//

#include "stdafx.h"
#include "LogDlg.h"
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogDlg

BEGIN_MESSAGE_MAP(CLogDlg, CUIWnd)
	//{{AFX_MSG_MAP(CLogDlg)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_2, OnBtn2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogDlg construction/destruction

extern vector<string> log;

CLogDlg::CLogDlg()
{
	m_pLstLog = NULL;
	m_pBtn2 = NULL;

}

CLogDlg::~CLogDlg()
{
}

void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CUIWnd::DoDataExchange(pDX);

}


//////////////////////////////////////////////////////////////////////////
// protected

int CLogDlg::InitControls()
{
	m_pLstLog = (CSkinListCtrl *)GetDlgItem(IDC_LSTCTRL_LOG);
	m_pBtn2 = (CSkinButton *)GetDlgItem(IDC_BTN_2);

	return 0;
}

int CLogDlg::InitLstLog()
{
	m_pLstLog->InsertColumn(0, _T("日志"), LVCFMT_LEFT, 600);
	CString sTem;
	/*int nIndex = m_pLstLog->InsertItem(0, _T("2013-08-22 15:30:02"));
	nIndex = m_pLstLog->InsertItem(0, _T("2013-08-22 16:40:51"));
	m_pLstLog->SetItemText(nIndex, 1, _T("192.168.0.41"));
	m_pLstLog->SetItemText(nIndex, 2, _T("F5-23-6D-1E-7A-5P"));
	m_pLstLog->SetItemText(nIndex, 3, _T("手动查杀"));
	m_pLstLog->SetItemText(nIndex, 4, _T("Thunder.exe"));
	*/
	for(int i=0; i<log.size(); i++)
	{
		sTem = log.at(i).c_str();
		m_pLstLog->InsertItem(0,sTem);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CLogDlg message handlers

int CLogDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CUIWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (InitControls() != 0)
		return -1;

	InitLstLog();

	return 0;
}

void CLogDlg::OnBtn2()
{
	m_pLstLog->DeleteAllItems();
}
