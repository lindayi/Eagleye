#pragma once

#include "afxsock.h"
//#include "EntityClass.h"
// CSessionSocket 命令目标

class CSessionSocket : public CSocket
{
public:
	//CMonitoredPC &m_PC;
	int m_PC;//需修改
public:
	CSessionSocket();
	virtual ~CSessionSocket();
	virtual void OnReceive(int nErrorCode);
};


