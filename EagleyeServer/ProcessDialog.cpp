// ProcessDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "EagleyeServer.h"
#include "ProcessDialog.h"


// CProcessDialog 对话框

extern CServerConfig m_ServerConfig;

IMPLEMENT_DYNAMIC(CProcessDialog, CDialog)

CProcessDialog::CProcessDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessDialog::IDD, pParent)
{

}

CProcessDialog::~CProcessDialog()
{
}

void CProcessDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CProcessDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_KILL, &CProcessDialog::OnBnClickedButtonKill)
	ON_BN_CLICKED(IDC_BUTTON_ADDBL, &CProcessDialog::OnBnClickedButtonAddbl)
END_MESSAGE_MAP()


// CProcessDialog 消息处理程序
BOOL CProcessDialog::OnInitDialog()
{
	int nIndex, j;
	CString sTem;
	char csTem[10];
	CDialog ::OnInitDialog ();
	m_pProcess = (CListCtrl *)GetDlgItem(IDC_LIST_PROCESS);
	m_pProcess->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	m_pProcess->InsertColumn (0,TEXT("PID"), LVCFMT_LEFT, 80);
	m_pProcess->InsertColumn (1,TEXT("进程名"), LVCFMT_LEFT, 500);

	for (j = 0; j < m_pMonitoredPC->m_ProcessList.size(); j++)
	{
		itoa( m_pMonitoredPC->m_ProcessList.at(j).m_nPID, csTem, 10);
		sTem = csTem;
		nIndex = m_pProcess->InsertItem(0, sTem);
		sTem = m_pMonitoredPC->m_ProcessList.at(j).m_csName.c_str();
		m_pProcess->SetItemText(nIndex, 1, sTem);
	}

	return true;
}

char *WSTRToAnsi4(wchar_t* Msg)//把wchar*转换称char*  
{
	int len = wcstombs(NULL, Msg, 0);  
	char *buf = new char[len+1];  
	wcstombs(buf, Msg, len);  
	buf[len] = 0;  
	return buf;
}

void CProcessDialog::OnBnClickedButtonKill()
{
	// TODO: 在此添加控件通知处理程序代码
	
	int nIdx = m_pProcess->GetSelectionMark();
	string pid = WSTRToAnsi4(m_pProcess->GetItemText(nIdx, 0).GetBuffer(0));
	string command = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><bag type=\"command\"><command>taskkill /F /PID ";
	command += pid;
	command += "</command></bag>";
	m_pMonitoredPC->m_SessionSocket.Send(command.c_str(), command.length());
	AfxMessageBox(TEXT("查杀成功！"));
}

void CProcessDialog::OnBnClickedButtonAddbl()
{
	// TODO: 在此添加控件通知处理程序代码

	int nIdx = m_pProcess->GetSelectionMark();
	string name = WSTRToAnsi4(m_pProcess->GetItemText(nIdx, 1).GetBuffer(0));
	m_ServerConfig.m_GroupList[m_pMonitoredPC->m_Group].m_Policy->m_BlackList.push_back(name);
	AfxMessageBox(TEXT("添加成功！"));
}
