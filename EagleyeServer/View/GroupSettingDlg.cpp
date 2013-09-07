// GroupSettingDlg.cpp : implementation of the CGroupSettingDlg class
//

#include "stdafx.h"
#include "GroupSettingDlg.h"
#include "EntityClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupSettingDlg

BEGIN_MESSAGE_MAP(CGroupSettingDlg, CUIWnd)
	//{{AFX_MSG_MAP(CGroupSettingDlg)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_6, OnBtn6)
	ON_BN_CLICKED(IDC_BTN_SAVEGROUP, OnBtnSavegroup)
	
	ON_CBN_SELCHANGE(IDC_CMB_GROUPNAME,OnSelChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroupSettingDlg construction/destruction

extern CServerConfig m_ServerConfig;

CGroupSettingDlg::CGroupSettingDlg()
{
	m_pStaGroupname = NULL;
	m_pCmbGroupname = NULL;
	m_pBtn6 = NULL;
	m_pStaGrouppolicy = NULL;
	m_pCmbGrouppolicy = NULL;
	m_pBtnSavegroup = NULL;

	m_strGroupname = _T("");
	m_strGrouppolicy = _T("");
}

CGroupSettingDlg::~CGroupSettingDlg()
{
}

void CGroupSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CUIWnd::DoDataExchange(pDX);

	DDX_CBString(pDX, IDC_CMB_GROUPNAME, m_strGroupname);
	DDX_CBString(pDX, IDC_CMB_GROUPPOLICY, m_strGrouppolicy);
}


//////////////////////////////////////////////////////////////////////////
// protected

int CGroupSettingDlg::InitControls()
{
	m_pStaGroupname = (CSkinStatic *)GetDlgItem(IDC_STA_GROUPNAME);
	m_pCmbGroupname = (CSkinComboBox *)GetDlgItem(IDC_CMB_GROUPNAME);
	m_pBtn6 = (CSkinButton *)GetDlgItem(IDC_BTN_6);
	m_pStaGrouppolicy = (CSkinStatic *)GetDlgItem(IDC_STA_GROUPPOLICY);
	m_pCmbGrouppolicy = (CSkinComboBox *)GetDlgItem(IDC_CMB_GROUPPOLICY);
	m_pBtnSavegroup = (CSkinButton *)GetDlgItem(IDC_BTN_SAVEGROUP);

	return 0;
}

int CGroupSettingDlg::InitCmbGroupname()
{
	int Groupno,i;
	for(i = 0; i < 7; i++)
		if (m_ServerConfig.m_GroupList[i].m_csName == "") break;
	Groupno = i;
	CString strTemp;
	for(i = 0; i < Groupno; i++)
	{
		strTemp = m_ServerConfig.m_GroupList[i].m_csName.c_str();
		m_pCmbGroupname->AddString(strTemp);
	}

	m_pCmbGroupname->SetCurSel(0);
	return 0;
}

int CGroupSettingDlg::InitCmbGrouppolicy()
{
	CString strTemp;
	for(int i=0; i<m_ServerConfig.m_PolicyList.size(); i++)
	{
		strTemp = (m_ServerConfig.m_PolicyList.at(i).GetName().c_str());
		m_pCmbGrouppolicy->AddString(strTemp);
	}
	
	int ng = m_pCmbGroupname->GetCurSel();

	for(int i=0; i<m_ServerConfig.m_PolicyList.size(); i++)
		if(m_ServerConfig.m_GroupList[ng].m_Policy->GetName() == m_ServerConfig.m_PolicyList.at(i).GetName())
			m_pCmbGrouppolicy->SetCurSel(i);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CGroupSettingDlg message handlers

int CGroupSettingDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CUIWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (InitControls() != 0)
		return -1;

	InitCmbGroupname();
	InitCmbGrouppolicy();

	return 0;
}

char *WSTRtoAnsi3(wchar_t* Msg)//把wchar*转换称char*  
{
	int len = wcstombs(NULL, Msg, 0);  
	char *buf = new char[len+1];  
	wcstombs(buf, Msg, len);  
	buf[len] = 0;  
	return buf;
}

void CGroupSettingDlg::OnBtn6()
{
	int Groupno,i;
	CString strTemp;
	m_pCmbGroupname->GetWindowTextW(strTemp);
	for(i = 0; i < 7; i++)
		if (m_ServerConfig.m_GroupList[i].m_csName == "") break;
	Groupno = i;
	m_ServerConfig.m_GroupList[Groupno].m_csName = (WSTRtoAnsi3(strTemp.GetBuffer(0)));
	int po = m_pCmbGrouppolicy->GetCurSel();
	m_ServerConfig.m_GroupList[Groupno].m_Policy = &m_ServerConfig.m_PolicyList.at(po);
	m_pCmbGroupname->AddString(strTemp);

	AfxMessageBox(_T("新建成功！"));
}

void CGroupSettingDlg::OnBtnSavegroup()
{
	int ng = m_pCmbGroupname->GetCurSel();
	int po = m_pCmbGrouppolicy->GetCurSel();
	m_ServerConfig.m_GroupList[ng].m_Policy = &m_ServerConfig.m_PolicyList.at(po);
	AfxMessageBox(_T("保存成功！"));
}

void CGroupSettingDlg::OnSelChange()
{
	int iPos = m_pCmbGroupname->GetCurSel();
	for(int i=0; i<m_ServerConfig.m_PolicyList.size(); i++)
		if(m_ServerConfig.m_GroupList[iPos].m_Policy->GetName() == m_ServerConfig.m_PolicyList.at(i).GetName())
			m_pCmbGrouppolicy->SetCurSel(i);
}