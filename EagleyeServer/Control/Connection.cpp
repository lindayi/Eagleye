#include "StdAfx.h"
#include "Connection.h"
#include "LogicClass.h"

#include <windows.h>
#include <winsock.h>
#include <string>

using namespace std;

#pragma comment(lib,"wsock32.lib")

//extern CGroup Group[7];
extern CMonitoredPC m_pPCArray[256];

CConnection * CConnection::m_pThis=NULL;

CConnection::CConnection()
{

}

CConnection::~CConnection(void)
{
}

int CConnection::InitConnection(CMonitoredPC *pPCArray, CServerConfig *pServerConfig, CUIWnd *pWnd)
{
	m_pThis=this;
	//m_pPCArray = pPCArray;
	m_pServerConfig = pServerConfig;
	if( !m_UDPSokcet.Create(PORT,SOCK_DGRAM))
		return -1;
	//::SetTimer(NULL,0,pServerConfig->GetTimeout(),CConnection::CheckOnLine);	//定时检查是否掉线
	::SetTimer(NULL,0,20000,CConnection::CheckOnLine);
	return 0;
}

int CConnection::ReceiveUDPMessage(CUDPSocket &rUDPSocket)
{
	BYTE* buffer = new BYTE[5000];
	CString csIP,xml;
	UINT nPort;
	int i,j;
	int nRecvNum = rUDPSocket.ReceiveFrom((char*)buffer,5000, csIP, nPort);
	xml = buffer;
	int nTem = xml.Find(TEXT("</bag>")) + 6;
	xml = xml.Left(nTem);

	if (nRecvNum != -1)
	{
		i=csIP.ReverseFind('.');
		CString csPCNO=csIP.Mid(i+1);
		int nPCNO=_ttoi(csPCNO);

		//CTime ctCurrentTime=CTime::GetCurrentTime();
		//m_pThis->m_pPCArray[nPCNO].m_Info.TransFromXML((char*)buffer);
		m_pPCArray[nPCNO].m_nStatus = 1;
		m_pPCArray[nPCNO].TransFromXML(xml);
		for(i = 0; i < 7; i++)
		{
			for(j = 0; j < m_pThis->m_pServerConfig->m_GroupList[i].m_MemberList.size(); j++)
			{
				if (m_pPCArray[nPCNO].m_Info.m_csMAC == m_pThis->m_pServerConfig->m_GroupList[i].m_MemberList.at(j))
				{
					m_pPCArray[nPCNO].m_Group = i;
					break;
				}
			}
		}

		CSessionSocket *pSessionSocket = &( ((m_pPCArray)[nPCNO]).m_SessionSocket );
		pSessionSocket->Create();
		pSessionSocket->m_PC = nPCNO;

		if(pSessionSocket->Connect(csIP,PORT))
		{
			CConnection::SendConfiguration(*pSessionSocket);
		}
		else return -1;
	}
	return 0;
}

int CConnection::ReceiveMonitoredInfo(CSessionSocket &rSessionSocket)
{
	char * pBuf=new char[20480];
	int nBuflen=20480;
	int nRecvNum =0;
	int nTempNum = 0;
	pBuf[nRecvNum]=0;
	CString csTem;
	do {
		nTempNum = rSessionSocket.Receive(pBuf + nRecvNum, 40959 - nTempNum);
		nRecvNum += nTempNum;	
		pBuf[nRecvNum] = '\0';
		csTem = pBuf;
	} while ((csTem.Find(TEXT("</bag>")) == -1));

	m_pPCArray[rSessionSocket.m_PC].m_LastTime = CTime::GetCurrentTime();
	//测试
	//AfxMessageBox(csTem);
	//调用解析函数把时间和数据

	CFilter::Filter(csTem, rSessionSocket, *m_pThis->m_pServerConfig, *m_pThis);

	delete pBuf;
	return nRecvNum;

}

int CConnection::SendConfiguration(CSessionSocket &rSessionSocket)
{
	char cScore[256];
	struct hostent *p = 0;
	WSADATA w;
	WSAStartup(0x0101, &w);
	gethostname(cScore, 256);
	p = gethostbyname(cScore);
	const char *pIP = inet_ntoa(*((struct in_addr *)p->h_addr_list[0]));
	//获取系统信息	
	string str("<?xml version=\"1.0\" encoding=\"UTF-8\"?><bag type=\"clientConfig\"><serverIP>");
	str += pIP;
	str += "</serverIP><frequency>";
	char cTem[10];
	_itoa_s(m_pThis->m_pServerConfig->GetFrequency(),cTem,10);
	str += cTem;
	str += "</frequency></bag>";
	int nSendNum=rSessionSocket.Send(str.c_str() ,str.length());
	WSACleanup();
	return nSendNum;
}

//int CConnection::SendCommand(string szIP,string &szConmmand)
//{
//}

VOID CALLBACK CConnection::  CheckOnLine(HWND hWnd,UINT uMsg,UINT idEvent,unsigned long dwTime)
{
	CTime ctCurrentTime=CTime::GetCurrentTime();
	CTime ctLastTime;
	CTimeSpan ctSpan;
	CMonitoredPC *pPCArray=m_pPCArray;
	for(int i=0;i<255;i++)
	{
		if(1==pPCArray[i].GetStatus())
		{
			ctLastTime=pPCArray[i].m_LastTime;
			ctSpan=ctCurrentTime-ctLastTime;
			if(ctSpan.GetTotalSeconds() > m_pThis->m_pServerConfig->GetTimeout() / 1000) //大于某个时间
			{			
				pPCArray[i].m_SessionSocket.Close();
				//此处设置离线
				pPCArray[i].m_nStatus = 0;
				string msg;
				msg = "客户端" + pPCArray[i].m_Info.m_csClientIP;
				msg += "异常离线！";
				AfxMessageBox((CString)msg.c_str());
			}
		}
	}
}