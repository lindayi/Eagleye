// SessionSocket.cpp : 实现文件
//

#include "stdafx.h"
//#include "EagleServer.h"
#include "SessionSocket.h"
#include "Connection.h"


// CSessionSocket

CSessionSocket::CSessionSocket()
{
}

CSessionSocket::~CSessionSocket()
{
}


// CSessionSocket 成员函数
void CSessionSocket::OnReceive(int nErrorCode) 
{
	CConnection::ReceiveMonitoredInfo(*this);
	CSocket::OnReceive(nErrorCode);
}