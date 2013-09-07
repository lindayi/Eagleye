#pragma once

#include "StdAfx.h"
#include "LogicClass.h"
#include "Markup.h"
//#include "ClassRealise.h"
#define PORT 32767

CConnection::CConnection(void)
{
	m_nUDPTimerID = -1;
	m_nTCPTimerID = -1;
}

CConnection::~CConnection(void)
{
}

CClientSocket * CConnection::GetTCPSocket()
{
	return &m_TCPSocket;
}

CClientSocket * CConnection::GetUDPSocket()
{
	return &m_UDPSocket;
}

CClientSocket * CConnection::GetSessionSocket()
{
	return &m_SessionSocket;
}

int CConnection::GetUDPTimerID()
{
	return m_nUDPTimerID;
}

int CConnection::GetTCPTimerID()
{
	return m_nTCPTimerID;
}


int CConnection::SetUDPTimerID(int nID)
{
	m_nUDPTimerID=nID;
	return m_nUDPTimerID;
}

int CConnection::SetTCPTimerID(int nID)
{
	m_nTCPTimerID=nID;
	return  m_nTCPTimerID;
}

CConnection * CConnection::m_pThis=NULL;

void CConnection::SetStaticPThis()
{
	m_pThis=this;
}

int CConnection::InitCConnection()
{
	SetStaticPThis();

	//此处需获取系统信息，然后进行首次发送广播信息
	if (  m_TCPSocket.Create(PORT)==NULL )
	{
		return -1;
	};
	m_TCPSocket.Listen ();

	string BroadcastMessage;
	CCreateBag::ClientInfo(BroadcastMessage, ClientInfo);

	//AfxMessageBox(_T("广播第一个"));
	CConnection::Broadcast(BroadcastMessage);
	int nID=::SetTimer(NULL,0,1000,CConnection::ProcUDPTimer);  //设置定时发送广播
	m_pThis->SetUDPTimerID(nID);
	return 0;
}
	
int CConnection::Broadcast(string &rszInfo)
{
	CClientSocket  &rUDPSocket = *( CConnection::m_pThis->GetUDPSocket() );

	if(rUDPSocket == INVALID_SOCKET)//查看UDP是否已经建立
	{
		if(	!rUDPSocket.Create(0,SOCK_DGRAM) )
			return -1;
	}
	BOOL bCmdOpt = TRUE;//无实际意义,用来存放SO_BROADCAST代表的数值
	rUDPSocket.SetSockOpt(SO_BROADCAST, (void*)&bCmdOpt, 1);	//设置套接字为广播套接字

	/*//指定UDP广播地址
	SOCKADDR_IN addr;
	//sin_family指代协议族，在socket编程中只能是AF_INET
	addr.sin_family = AF_INET;
	//sin_addr存储IP地址,s_addr按照网络字节顺序存储IP地址
	addr.sin_addr.S_un.S_addr= INADDR_BROADCAST;
	//sin_port存储端口号
	addr.sin_port = htons(PORT);*/

	//int count=rUDPSocket.SendTo(rszInfo.c_str(),rszInfo.length() , (SOCKADDR*)&addr, sizeof(addr));
	int count = rUDPSocket.SendTo(rszInfo.c_str(),rszInfo.length(), PORT, TEXT("255.255.255.255"));

	return count;
}

int CConnection::ReceiveMessage(CClientSocket &rTCPSocket)
{
	//AfxMessageBox(_T("收到消息了"));
	char * pBuf = new char[5000];
	int nBuflen = 5000;
	int nRecvNum = rTCPSocket.Receive  (pBuf,nBuflen);

	pBuf[nRecvNum] = 0;
	CString m_str(pBuf);
	CString sTem;
	string m_sstr(pBuf);
	
	//AfxMessageBox(m_str);

	CMarkup xml;
	xml.SetDoc(m_str);
	xml.ResetPos();
	xml.FindElem();
	sTem = xml.GetAttrib(TEXT("type"));
	if (sTem == "clientConfig")
	{
		m_pThis->ClientConfig.ReadXML(m_sstr);
		int nID=::SetTimer(NULL,0,m_pThis->ClientConfig.GetFrequency(),ProcTCPTimer);
		CConnection::m_pThis->SetTCPTimerID(nID);
	}
	else if (sTem == "command")
	{
		CCommand command;
		xml.FindChildElem();
		command.SetCommand(xml.GetChildData());
		command.RunCommand();
	}
	
	delete pBuf;
	return 0;
}

int CConnection::EstablishConnection()
{

	CClientSocket &rTCPSocket=*( CConnection::m_pThis->GetTCPSocket() );
	CClientSocket &rSessionSocket=*( CConnection::m_pThis->GetSessionSocket() );
	if( 	!rTCPSocket.Accept(rSessionSocket) )
	{
		return 0;
	}
	else
	{
		//AfxMessageBox(_T("TCP连接上了"));
		::KillTimer(NULL,(CConnection::m_pThis->GetUDPTimerID()) );//关闭定时发送UDP广播
		/*int nID=::SetTimer(NULL,0,3000,ProcTCPTimer);
		CConnection::m_pThis->SetTCPTimerID(nID);*/
		return 1;
	}
}

int CConnection::SendMonitoredInfo(string &rInfo)
{
	//AfxMessageBox(_T("发进程"));
	CClientSocket &rTCPSocket=*(CConnection::m_pThis->GetSessionSocket());

	int nSendNum=rTCPSocket.Send(rInfo.c_str(),rInfo.length());
		if(nSendNum==WSAENOTCONN ||nSendNum==WSAENETDOWN  ||nSendNum==WSAESHUTDOWN ||nSendNum==WSAENETDOWN||nSendNum==WSAENETRESET||nSendNum==WSAECONNABORTED)
	{
		//AfxMessageBox(TEXT("服务端关闭！"));
		::KillTimer(NULL,(CConnection::m_pThis->GetTCPTimerID()) );
		CConnection::m_pThis->InitCConnection();
	}
	return nSendNum;
}

VOID CALLBACK CConnection:: ProcTCPTimer(HWND hWnd,UINT uMsg,UINT idEvent,unsigned long dwTime)
{
	//AfxMessageBox(_T("定时TCP"));
	string str;
	CCreateBag::MonitoredInfo(str, m_pThis->m_lastup, m_pThis->m_lastdown, m_pThis->ClientConfig);
	CConnection::SendMonitoredInfo(str);	
}

VOID CALLBACK CConnection::  ProcUDPTimer(HWND hWnd,UINT uMsg,UINT idEvent,unsigned long dwTime)
{
	//AfxMessageBox(_T("定时广播"));
	string str;
	CCreateBag::ClientInfo(str, CConnection::m_pThis->ClientInfo);
	CConnection::Broadcast(str);	
}