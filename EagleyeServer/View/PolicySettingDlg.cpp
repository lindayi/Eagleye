// PolicySettingDlg.cpp : implementation of the CPolicySettingDlg class
//

#include "stdafx.h"
#include "PolicySettingDlg.h"
#include "EntityClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolicySettingDlg

BEGIN_MESSAGE_MAP(CPolicySettingDlg, CUIWnd)
	//{{AFX_MSG_MAP(CPolicySettingDlg)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_SAVEPOLICY, OnBtnSavepolicy)
	ON_BN_CLICKED(IDC_BTN_NEWPOLICY, OnBtnNewpolicy)
	ON_CBN_SELCHANGE(IDC_CMB_POLICYNAME,OnSelChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPolicySettingDlg construction/destruction

extern CServerConfig m_ServerConfig;

CPolicySettingDlg::CPolicySettingDlg()
{
	m_pStaPolicyname = NULL;
	m_pCmbPolicyname = NULL;
	m_pLstBlacklist = NULL;
	m_pBtnSavepolicy = NULL;
	m_pStaBlacklist = NULL;
	m_pBtnNewpolicy = NULL;

	m_strPolicyname = _T("");
}

CPolicySettingDlg::~CPolicySettingDlg()
{
}

void CPolicySettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CUIWnd::DoDataExchange(pDX);

	DDX_CBString(pDX, IDC_CMB_POLICYNAME, m_strPolicyname);
}


//////////////////////////////////////////////////////////////////////////
// protected

int CPolicySettingDlg::InitControls()
{
	m_pStaPolicyname = (CSkinStatic *)GetDlgItem(IDC_STA_POLICYNAME);
	m_pCmbPolicyname = (CSkinComboBox *)GetDlgItem(IDC_CMB_POLICYNAME);
	m_pLstBlacklist = (CSkinListCtrl *)GetDlgItem(IDC_LSTCTRL_BLACKLIST);
	m_pBtnSavepolicy = (CSkinButton *)GetDlgItem(IDC_BTN_SAVEPOLICY);
	m_pStaBlacklist = (CSkinStatic *)GetDlgItem(IDC_STA_BLACKLIST);
	m_pBtnNewpolicy = (CSkinButton *)GetDlgItem(IDC_BTN_NEWPOLICY);

	return 0;
}

int CPolicySettingDlg::InitCmbPolicyname()
{
	CString strTemp;
	for(int i=0; i<m_ServerConfig.m_PolicyList.size(); i++)
	{
		strTemp = (m_ServerConfig.m_PolicyList.at(i).GetName().c_str());
		m_pCmbPolicyname->AddString(strTemp);
	}
	m_pCmbPolicyname->SetCurSel(0);
	return 0;
}

int CPolicySettingDlg::InitLstBlacklist()
{
	m_pLstBlacklist->InsertColumn(0, _T("序号"), LVCFMT_LEFT, 50);
	m_pLstBlacklist->InsertColumn(1, _T("进程名"), LVCFMT_LEFT, 150);
	int nIndex;
	char cTem[10];
	CString strTemp;
	for(int i=0; i<m_ServerConfig.m_PolicyList.at(0).m_BlackList.size(); i++)
	{
		itoa(m_ServerConfig.m_PolicyList.at(0).m_BlackList.size()-i, cTem, 10);
		strTemp = cTem;
		nIndex = m_pLstBlacklist->InsertItem(0, strTemp);
		strTemp =  m_ServerConfig.m_PolicyList.at(0).m_BlackList.at(i).c_str();
		m_pLstBlacklist->SetItemText(nIndex, 1, strTemp);
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CPolicySettingDlg message handlers

int CPolicySettingDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CUIWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (InitControls() != 0)
		return -1;

	InitCmbPolicyname();
	InitLstBlacklist();

	return 0;
}

void CPolicySettingDlg::OnSelChange()
{
	int iPos = m_pCmbPolicyname->GetCurSel();
	m_pLstBlacklist->DeleteAllItems();
	int nIndex;
	char cTem[10];
	CString strTemp;
	for(int i=0; i<m_ServerConfig.m_PolicyList.at(iPos).m_BlackList.size(); i++)
	{
		itoa(m_ServerConfig.m_PolicyList.at(iPos).m_BlackList.size()-i, cTem, 10);
		strTemp = cTem;
		nIndex = m_pLstBlacklist->InsertItem(0, strTemp);
		strTemp =  m_ServerConfig.m_PolicyList.at(iPos).m_BlackList.at(i).c_str();
		m_pLstBlacklist->SetItemText(nIndex, 1, strTemp);
	}
}

void CPolicySettingDlg::OnBtnSavepolicy()
{
	AfxMessageBox(_T("保存成功！"));
}

char *WSTRtoAnsi2(wchar_t* Msg)//把wchar*转换称char*  
{
	int len = wcstombs(NULL, Msg, 0);  
	char *buf = new char[len+1];  
	wcstombs(buf, Msg, len);  
	buf[len] = 0;  
	return buf;
}

void CPolicySettingDlg::OnBtnNewpolicy()
{
	CPolicy *pPo;
	CString strTemp;
	m_pCmbPolicyname->GetWindowTextW(strTemp);
	pPo = new CPolicy();
	m_pCmbPolicyname->AddString(strTemp);
	pPo->SetName(WSTRtoAnsi2(strTemp.GetBuffer(0)));
	
	m_ServerConfig.m_PolicyList.push_back(*pPo);
	m_pLstBlacklist->DeleteAllItems();


	AfxMessageBox(_T("新建成功！"));
}
