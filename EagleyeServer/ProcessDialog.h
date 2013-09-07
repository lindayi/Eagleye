#pragma once


// CProcessDialog 对话框
#include "resource.h"
#include "EntityClass.h"
#include "afxcmn.h"

class CProcessDialog : public CDialog
{
	DECLARE_DYNAMIC(CProcessDialog)

public:
	CProcessDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProcessDialog();
	CListCtrl *m_pProcess;

// 对话框数据
	enum { IDD = IDD_PROCESS_FORMVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CMonitoredPC *m_pMonitoredPC;
	afx_msg void OnBnClickedButtonKill();
	afx_msg void OnBnClickedButtonAddbl();
};
