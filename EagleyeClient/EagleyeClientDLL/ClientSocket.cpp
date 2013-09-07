// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientSocket.h"
#include "LogicClass.h"


// CClientSocket
CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}
//CClientSocket 成员函数

void CClientSocket::OnReceive(int nErrorCode) 
{
	CConnection::ReceiveMessage(*this);
	CSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnAccept(int nErrorCode) 
{
	CConnection::EstablishConnection();	
	CSocket::OnAccept(nErrorCode);
}