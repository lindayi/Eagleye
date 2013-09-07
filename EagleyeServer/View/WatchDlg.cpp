// WatchDlg.cpp : implementation of the CWatchDlg class
//

#include "stdafx.h"
#include "WatchDlg.h"
#include "EntityClass.h"
#include "DetailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDB_BITMAP1 131

/////////////////////////////////////////////////////////////////////////////
// CWatchDlg

BEGIN_MESSAGE_MAP(CWatchDlg, CUIWnd)
	//{{AFX_MSG_MAP(CWatchDlg)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_LSTCTRL_PC, CWatchDlg::OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWatchDlg construction/destruction

extern CServerConfig m_ServerConfig;
extern CMonitoredPC m_pPCArray[256];

CWatchDlg::CWatchDlg()
{
	m_pStaGroup = NULL;
	m_pRadUngroup = NULL;
	m_pRadGroup1 = NULL;
	m_pLstPc = NULL;
	m_pRadGroup2 = NULL;
	m_pRadGroup3 = NULL;
	m_pRadGroup4 = NULL;
	m_pRadGroup5 = NULL;
	m_pRadGroup6 = NULL;

}

CWatchDlg::~CWatchDlg()
{
}

void CWatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CUIWnd::DoDataExchange(pDX);

}


//////////////////////////////////////////////////////////////////////////
// protected

int CWatchDlg::InitControls()
{
	m_pStaGroup = (CSkinStatic *)GetDlgItem(IDC_STA_GROUP);
	m_pRadUngroup = (CSkinButton *)GetDlgItem(IDC_RAD_UNGROUP);
	m_pRadGroup1 = (CSkinButton *)GetDlgItem(IDC_RAD_GROUP1);
	m_pLstPc = (CSkinListCtrl *)GetDlgItem(IDC_LSTCTRL_PC);
	m_pRadGroup2 = (CSkinButton *)GetDlgItem(IDC_RAD_GROUP2);
	m_pRadGroup3 = (CSkinButton *)GetDlgItem(IDC_RAD_GROUP3);
	m_pRadGroup4 = (CSkinButton *)GetDlgItem(IDC_RAD_GROUP4);
	m_pRadGroup5 = (CSkinButton *)GetDlgItem(IDC_RAD_GROUP5);
	m_pRadGroup6 = (CSkinButton *)GetDlgItem(IDC_RAD_GROUP6);

	m_pRadUngroup->SetCheck(TRUE);

	CString sTem;
	
	if(m_ServerConfig.m_GroupList[1].m_csName == "")
		m_pRadGroup1->ShowWindow(SW_HIDE);
	else{
		sTem = m_ServerConfig.m_GroupList[1].m_csName.c_str();
		m_pRadGroup1->SetWindowTextW(sTem);
	}

	if(m_ServerConfig.m_GroupList[2].m_csName == "")
		m_pRadGroup2->ShowWindow(SW_HIDE);
	else{
		sTem = m_ServerConfig.m_GroupList[2].m_csName.c_str();
		m_pRadGroup2->SetWindowTextW(sTem);
	}
	if(m_ServerConfig.m_GroupList[3].m_csName == "")
		m_pRadGroup3->ShowWindow(SW_HIDE);
	else{
		sTem = m_ServerConfig.m_GroupList[3].m_csName.c_str();
		m_pRadGroup3->SetWindowTextW(sTem);
	}
	if(m_ServerConfig.m_GroupList[4].m_csName == "")
		m_pRadGroup4->ShowWindow(SW_HIDE);
	else{
		sTem = m_ServerConfig.m_GroupList[4].m_csName.c_str();
		m_pRadGroup4->SetWindowTextW(sTem);
	}
	if(m_ServerConfig.m_GroupList[5].m_csName == "")
		m_pRadGroup5->ShowWindow(SW_HIDE);
	else{
		sTem = m_ServerConfig.m_GroupList[5].m_csName.c_str();
		m_pRadGroup5->SetWindowTextW(sTem);
	}
	if(m_ServerConfig.m_GroupList[6].m_csName == "")
		m_pRadGroup6->ShowWindow(SW_HIDE);
	else{
		sTem = m_ServerConfig.m_GroupList[6].m_csName.c_str();
		m_pRadGroup6->SetWindowTextW(sTem);
	}

	return 0;
}

int CWatchDlg::InitLstPc()
{
	/*
	HBITMAP hBitmap;
	CBitmap *pBitmap;
	CImageList *pOnOffLine;
	pOnOffLine = new CImageList;
	pOnOffLine->Create(65, 41, ILC_COLOR24, 2, 2);
	pBitmap = new CBitmap;
	hBitmap = (HBITMAP)LoadImage(NULL, "../res/online.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	*/
	CImageList* pImageList;
	pImageList = new CImageList();
	pImageList->Create(83,61,ILC_COLOR24,0,4);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	pImageList->Add(&bmp, RGB(255,0,0));
	bmp.DeleteObject();
	
	
	m_pLstPc->SetImageList(pImageList,LVSIL_NORMAL);

	m_pLstPc->SetExtendedStyle(LVS_EX_SUBITEMIMAGES);

	m_pLstPc->InsertColumn(0,TEXT("PC"), LVCFMT_RIGHT, 100);
	
	//m_pLstPc->InsertItem(0, _T("192.168.0.1"));
	
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CWatchDlg message handlers

int CWatchDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CUIWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (InitControls() != 0)
		return -1;

	InitLstPc();
	SetTimer(1,1000,NULL) ;

	return 0;
}

void CWatchDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CDetailDlg dlg;
	int nIdx = m_pLstPc->GetSelectionMark();
	if (nIdx == -1) nIdx = 0;
	CString ppc = m_pLstPc->GetItemText(nIdx, 0);
	int i=ppc.ReverseFind('.');
	CString csPCNO=ppc.Mid(i+1);
	int DetailNum=_ttoi(csPCNO);

	dlg.m_pMonitoredPC =&m_pPCArray [DetailNum];
	dlg.m_BaseInfoDlg .m_pMonitoredPC =&m_pPCArray [DetailNum];
	dlg.m_ProcessDlg .m_pMonitoredPC =&m_pPCArray [DetailNum];
	dlg.DoModal ();
	*pResult = 0;
}

void CWatchDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString sTem;
	m_pLstPc->DeleteAllItems();
	m_pRadGroup1->ShowWindow(SW_SHOW);
	m_pRadGroup2->ShowWindow(SW_SHOW);
	m_pRadGroup3->ShowWindow(SW_SHOW);
	m_pRadGroup4->ShowWindow(SW_SHOW);
	m_pRadGroup5->ShowWindow(SW_SHOW);
	m_pRadGroup6->ShowWindow(SW_SHOW);

	if(m_ServerConfig.m_GroupList[1].m_csName == "")
		m_pRadGroup1->ShowWindow(SW_HIDE);
	else{
		sTem = m_ServerConfig.m_GroupList[1].m_csName.c_str();
		m_pRadGroup1->SetWindowTextW(sTem);
	}

	if(m_ServerConfig.m_GroupList[2].m_csName == "")
		m_pRadGroup2->ShowWindow(SW_HIDE);
	else{
		sTem = m_ServerConfig.m_GroupList[2].m_csName.c_str();
		m_pRadGroup2->SetWindowTextW(sTem);
	}
	if(m_ServerConfig.m_GroupList[3].m_csName == "")
		m_pRadGroup3->ShowWindow(SW_HIDE);
	else{
		sTem = m_ServerConfig.m_GroupList[3].m_csName.c_str();
		m_pRadGroup3->SetWindowTextW(sTem);
	}
	if(m_ServerConfig.m_GroupList[4].m_csName == "")
		m_pRadGroup4->ShowWindow(SW_HIDE);
	else{
		sTem = m_ServerConfig.m_GroupList[4].m_csName.c_str();
		m_pRadGroup4->SetWindowTextW(sTem);
	}
	if(m_ServerConfig.m_GroupList[5].m_csName == "")
		m_pRadGroup5->ShowWindow(SW_HIDE);
	else{
		sTem = m_ServerConfig.m_GroupList[5].m_csName.c_str();
		m_pRadGroup5->SetWindowTextW(sTem);
	}
	if(m_ServerConfig.m_GroupList[6].m_csName == "")
		m_pRadGroup6->ShowWindow(SW_HIDE);
	else{
		sTem = m_ServerConfig.m_GroupList[6].m_csName.c_str();
		m_pRadGroup6->SetWindowTextW(sTem);
	}

	if(this->IsDlgButtonChecked(IDC_RAD_UNGROUP) == BST_CHECKED)
	{
		for(int i=0; i<256; i++)
			if((m_pPCArray[i].m_Group == 0)&&(m_pPCArray[i].m_nStatus == 1))
			{
				sTem = m_pPCArray[i].m_Info.m_csClientIP.c_str();
				m_pLstPc->InsertItem(0, sTem);
			}
	}

	if(this->IsDlgButtonChecked(IDC_RAD_GROUP1) == BST_CHECKED)
	{
		for(int i=0; i<256; i++)
			if((m_pPCArray[i].m_Group == 1)&&(m_pPCArray[i].m_nStatus == 1))
			{
				sTem = m_pPCArray[i].m_Info.m_csClientIP.c_str();
				m_pLstPc->InsertItem(0, sTem);
			}
	}

	if(this->IsDlgButtonChecked(IDC_RAD_GROUP2) == BST_CHECKED)
	{
		for(int i=0; i<256; i++)
			if((m_pPCArray[i].m_Group == 2)&&(m_pPCArray[i].m_nStatus == 1))
			{
				sTem = m_pPCArray[i].m_Info.m_csClientIP.c_str();
				m_pLstPc->InsertItem(0, sTem);
			}
	}

	if(this->IsDlgButtonChecked(IDC_RAD_GROUP3) == BST_CHECKED)
	{
		for(int i=0; i<256; i++)
			if((m_pPCArray[i].m_Group == 3)&&(m_pPCArray[i].m_nStatus == 1))
			{
				sTem = m_pPCArray[i].m_Info.m_csClientIP.c_str();
				m_pLstPc->InsertItem(0, sTem);
			}
	}

	if(this->IsDlgButtonChecked(IDC_RAD_GROUP4) == BST_CHECKED)
	{
		for(int i=0; i<256; i++)
			if((m_pPCArray[i].m_Group == 4)&&(m_pPCArray[i].m_nStatus == 1))
			{
				sTem = m_pPCArray[i].m_Info.m_csClientIP.c_str();
				m_pLstPc->InsertItem(0, sTem);
			}
	}

	if(this->IsDlgButtonChecked(IDC_RAD_GROUP5) == BST_CHECKED)
	{
		for(int i=0; i<256; i++)
			if((m_pPCArray[i].m_Group == 5)&&(m_pPCArray[i].m_nStatus == 1))
			{
				sTem = m_pPCArray[i].m_Info.m_csClientIP.c_str();
				m_pLstPc->InsertItem(0, sTem);
			}
	}

	if(this->IsDlgButtonChecked(IDC_RAD_GROUP6) == BST_CHECKED)
	{
		for(int i=0; i<256; i++)
			if((m_pPCArray[i].m_Group == 6)&&(m_pPCArray[i].m_nStatus == 1))
			{
				sTem = m_pPCArray[i].m_Info.m_csClientIP.c_str();
				m_pLstPc->InsertItem(0, sTem);
			}
	}

	CUIWnd::OnTimer(nIDEvent);
}