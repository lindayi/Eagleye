// UDPSocket.cpp : 实现文件
//

#include "stdafx.h"
//#include "EagleServer.h"
#include "UDPSocket.h"
#include "Connection.h"

// CUDPSocket

CUDPSocket::CUDPSocket()
{
}

CUDPSocket::~CUDPSocket()
{
}


// CUDPSocket 成员函数
void CUDPSocket::OnReceive(int nErrorCode) 
{
	CConnection::ReceiveUDPMessage(*this);
	CSocket::OnReceive(nErrorCode);
}