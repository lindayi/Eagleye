#pragma once


// CBaseInfoDialog 对话框
#include "resource.h"
#include "LogicClass.h"
#include "afxwin.h"

class CBaseInfoDialog : public CDialog
{
	DECLARE_DYNAMIC(CBaseInfoDialog)

public:
	CBaseInfoDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBaseInfoDialog();

// 对话框数据
	enum { IDD = IDD_BASEINFO_FORMVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CMonitoredPC *m_pMonitoredPC;
	afx_msg void OnBnClickedSendcomm();
	afx_msg void OnCbnSelchangeGroup();
	CComboBox m_cbGroup;
};
