// SystemSettingDlg.cpp : implementation of the CSystemSettingDlg class
//

#include "stdafx.h"
#include "SystemSettingDlg.h"
#include "EntityClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSystemSettingDlg

BEGIN_MESSAGE_MAP(CSystemSettingDlg, CUIWnd)
	//{{AFX_MSG_MAP(CSystemSettingDlg)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_SAVESYSTEM, OnBtnSavesystem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemSettingDlg construction/destruction


extern CServerConfig m_ServerConfig;

char *WSTRtoAnsi(wchar_t* Msg)//把wchar*转换称char*  
{
	int len = wcstombs(NULL, Msg, 0);  
	char *buf = new char[len+1];  
	wcstombs(buf, Msg, len);  
	buf[len] = 0;  
	return buf;
}

CSystemSettingDlg::CSystemSettingDlg()
{
	m_pStaOfflinetime = NULL;
	m_pEdtOfflinetime = NULL;
	m_pStaRefresh = NULL;
	m_pEdtRefresh = NULL;
	m_pBtnSavesystem = NULL;

	m_strOfflinetime = _T("");
	m_strRefresh = _T("");
}

CSystemSettingDlg::~CSystemSettingDlg()
{
}

void CSystemSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CUIWnd::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDT_OFFLINETIME, m_strOfflinetime);
	DDX_Text(pDX, IDC_EDT_REFRESH, m_strRefresh);
}


//////////////////////////////////////////////////////////////////////////
// protected

int CSystemSettingDlg::InitControls()
{
	m_pStaOfflinetime = (CSkinStatic *)GetDlgItem(IDC_STA_OFFLINETIME);
	m_pEdtOfflinetime = (CSkinEdit *)GetDlgItem(IDC_EDT_OFFLINETIME);
	m_pStaRefresh = (CSkinStatic *)GetDlgItem(IDC_STA_REFRESH);
	m_pEdtRefresh = (CSkinEdit *)GetDlgItem(IDC_EDT_REFRESH);
	m_pBtnSavesystem = (CSkinButton *)GetDlgItem(IDC_BTN_SAVESYSTEM);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CSystemSettingDlg message handlers

int CSystemSettingDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CUIWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (InitControls() != 0)
		return -1;

	char cTem[10];
	_itoa_s(m_ServerConfig.GetTimeout(), cTem, 10);
	m_strOfflinetime = cTem;
	_itoa_s(m_ServerConfig.GetFrequency(), cTem, 10);
	m_strRefresh = cTem;
	UpdateData(FALSE);

	return 0;
}

void CSystemSettingDlg::OnBtnSavesystem()
{
	UpdateData(TRUE);
	m_ServerConfig.SetTimeout(atoi(WSTRtoAnsi(m_strOfflinetime.GetBuffer(0))));
	m_ServerConfig.SetFrequency(atoi(WSTRtoAnsi(m_strRefresh.GetBuffer(0))));

	m_ServerConfig.WriteConfigFile();

	AfxMessageBox(TEXT("保存成功！"));
}
