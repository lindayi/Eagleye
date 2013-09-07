// DetailDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EagleyeServer.h"
#include "DetailDlg.h"


// CDetailDlg 对话框

IMPLEMENT_DYNAMIC(CDetailDlg, CDialog)

CDetailDlg::CDetailDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDetailDlg::IDD, pParent)
{

}

CDetailDlg::~CDetailDlg()
{
}

void CDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_Tab);
}

BEGIN_MESSAGE_MAP(CDetailDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CDetailDlg::OnTcnSelchangeTab)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDetailDlg 消息处理程序
BOOL CDetailDlg::OnInitDialog()
{
	CDialog ::OnInitDialog ();

	//初始化TAB标签控件
	TCITEM item;
	item.mask = TCIF_TEXT;
	item.pszText = _T("基本信息");
	m_Tab.InsertItem(0,&item);

	item.mask = TCIF_TEXT;
	item.pszText = _T("进程列表");
	m_Tab.InsertItem(1,&item);

	m_BaseInfoDlg .Create(IDD_BASEINFO_FORMVIEW,&m_Tab);
	m_ProcessDlg .Create(IDD_PROCESS_FORMVIEW,&m_Tab);

	CRect rect;
	m_Tab.GetClientRect(&rect);
	m_BaseInfoDlg.SetWindowPos(NULL,rect.left,rect.top+20,rect.right,rect.bottom,SWP_SHOWWINDOW);
	m_ProcessDlg.SetWindowPos(NULL,rect.left,rect.top+20,rect.right,rect.bottom,SWP_HIDEWINDOW);

	//徐获取客户端刷新频率
	SetTimer(1,5000,NULL) ;
	return TRUE;  
}
void CDetailDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
CRect rect;
	m_Tab.GetClientRect(&rect);
	
	switch(m_Tab.GetCurSel())
	{
		case 0:
			m_BaseInfoDlg.SetWindowPos(NULL,rect.left,rect.top+20,rect.right,rect.bottom,SWP_SHOWWINDOW);
			m_ProcessDlg .SetWindowPos(NULL,rect.left,rect.top+20,rect.right,rect.bottom,SWP_HIDEWINDOW);
          	break;
		case 1:
			m_BaseInfoDlg.SetWindowPos(NULL,rect.left,rect.top+20,rect.right,rect.bottom,SWP_HIDEWINDOW);
			m_ProcessDlg.SetWindowPos(NULL,rect.left,rect.top+20,rect.right,rect.bottom,SWP_SHOWWINDOW);
            break;
	}


	*pResult = 0;
}

void CDetailDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString csUprate;
	csUprate.Format (TEXT("%d"),m_pMonitoredPC ->m_Uprate[19]);
	csUprate+="kbps";
	CString csDownrate;
	csDownrate.Format (TEXT("%d"),m_pMonitoredPC ->m_Downrate[19]);
	csDownrate+="kbps"; 
	this->GetDlgItem (IDC_UPRATE_EDIT)->SetWindowTextW (csUprate);
	this->GetDlgItem (IDC_DOWNRATE_EDIT)->SetWindowTextW (csDownrate);

	int nIndex,i;
	CString sTem;
	char csTem[10];
	
	m_ProcessDlg.m_pProcess->DeleteAllItems();

	for (i=0; i<m_pMonitoredPC->m_ProcessList.size(); i++)
	{
		itoa( m_pMonitoredPC->m_ProcessList.at(i).m_nPID, csTem, 10);
		sTem = csTem;
		nIndex = m_ProcessDlg.m_pProcess->InsertItem(0, sTem);
		sTem = m_pMonitoredPC->m_ProcessList.at(i).m_csName.c_str();
		m_ProcessDlg.m_pProcess->SetItemText(nIndex, 1, sTem);
	}


	CDialog::OnTimer(nIDEvent);
}

