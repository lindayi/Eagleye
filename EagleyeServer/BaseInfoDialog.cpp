// BaseInfoDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "EagleyeServer.h"
#include "BaseInfoDialog.h"


// CBaseInfoDialog 对话框
extern CServerConfig m_ServerConfig;

IMPLEMENT_DYNAMIC(CBaseInfoDialog, CDialog)

CBaseInfoDialog::CBaseInfoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseInfoDialog::IDD, pParent)
{

}

CBaseInfoDialog::~CBaseInfoDialog()
{
}

void CBaseInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP, m_cbGroup);
}


BEGIN_MESSAGE_MAP(CBaseInfoDialog, CDialog)
	ON_BN_CLICKED(IDC_SENDCOMM, &CBaseInfoDialog::OnBnClickedSendcomm)
	ON_CBN_SELCHANGE(IDC_GROUP, &CBaseInfoDialog::OnCbnSelchangeGroup)
END_MESSAGE_MAP()


// CBaseInfoDialog 消息处理程序
BOOL CBaseInfoDialog::OnInitDialog()
{
	CDialog ::OnInitDialog ();
	CString sTem;
	sTem = m_pMonitoredPC ->m_Info.m_csClientIP.c_str();
	this->GetDlgItem (IDC_IP_EDIT)->SetWindowTextW (sTem);
	sTem = m_pMonitoredPC ->m_Info .m_csOS.c_str();
	this->GetDlgItem (IDC_OS_EDIT)->SetWindowTextW (sTem);
	sTem = m_pMonitoredPC ->m_Info .m_csMAC.c_str();
	this->GetDlgItem (IDC_MAC_EDIT)->SetWindowTextW (sTem);
	char csTem[10];
	itoa(m_pMonitoredPC ->m_Info .m_nMemory, csTem, 10);
	sTem = csTem;
	this->GetDlgItem (IDC_MEM_EDIT)->SetWindowTextW (sTem);
	sTem = m_pMonitoredPC ->m_Info .m_csCPU .c_str();
	this->GetDlgItem (IDC_CPU_EDIT)->SetWindowTextW (sTem);
	
	this->GetDlgItem (IDC_IP_EDIT)->EnableWindow (FALSE);
	this->GetDlgItem (IDC_OS_EDIT)->EnableWindow (FALSE);
	this->GetDlgItem (IDC_MAC_EDIT)->EnableWindow (FALSE);
	this->GetDlgItem (IDC_MEM_EDIT)->EnableWindow (FALSE);
	this->GetDlgItem (IDC_CPU_EDIT)->EnableWindow (FALSE);
	
	int i = 0;
	while((m_ServerConfig.m_GroupList[i].m_csName != "")&&(i < 7))
	{
		CString sTem;
		sTem = m_ServerConfig.m_GroupList[i].m_csName.c_str();
		m_cbGroup.AddString(sTem);
		i++;
	}
	m_cbGroup.SetCurSel(m_pMonitoredPC->m_Group);

	return true;
}


char *WSTRToAnsi3(wchar_t* Msg)//把wchar*转换称char*  
{
	int len = wcstombs(NULL, Msg, 0);  
	char *buf = new char[len+1];  
	wcstombs(buf, Msg, len);  
	buf[len] = 0;  
	return buf;
}


void CBaseInfoDialog::OnBnClickedSendcomm()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_str;
	string command = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><bag type=\"command\"><command>";
	GetDlgItem(IDC_COMMAND)->GetWindowTextW(m_str);
	command += WSTRToAnsi3(m_str.GetBuffer(0));
	command += "</command></bag>";
	m_pMonitoredPC->m_SessionSocket.Send(command.c_str(), command.length());
	AfxMessageBox(_T("CMD指令发送成功！"));
}

void CBaseInfoDialog::OnCbnSelchangeGroup()
{
	// TODO: 在此添加控件通知处理程序代码
	int iPos = m_cbGroup.GetCurSel();
	m_pMonitoredPC->m_Group = iPos;
	AfxMessageBox(_T("分组修改成功！"));
}
