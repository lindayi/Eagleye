#pragma once

#include "ClientSocket.h"
#include <string>
using namespace std;
class CConnection
{
private:
	CClientSocket m_TCPSocket;
	CClientSocket m_UDPSocket;
	CClientSocket m_SessionSocket;
	
	int m_nUDPTimerID;
	int m_nTCPTimerID;
	static CConnection * m_pThis;	//供回调函数获得

public:
	CConnection(void);
	~CConnection(void);
	CClientSocket *GetTCPSocket();
	CClientSocket *GetUDPSocket();
	CClientSocket *GetSessionSocket();

	int GetUDPTimerID();
	int GetTCPTimerID();
	int SetUDPTimerID(int nID);
	int SetTCPTimerID(int nID);
	//设置静态指针，供静态回调函数使用，实现静态回调函数对非静态类成员的访问

	void SetStaticPThis();
	int InitCConnection();	//初始化信息

	//局域网发送广播信息，通知服务端上线
	static int Broadcast(string &rszInfo);
	//客户端监听服务端
	static int ReceiveMessage(CClientSocket &rTCPSocket);
	//客户端监听到服务端的连接请求
	static int EstablishConnection();
	//客户端发送监控信息
	static int SendMonitoredInfo(string &rInfo);
	//定时器回调函数 触发发送受监控信息
	static  VOID CALLBACK ProcTCPTimer(HWND hWnd,UINT uMsg,UINT idEvent,unsigned long dwTime);
	//定时器回调函数 触发发送广播信息
	static  VOID CALLBACK ProcUDPTimer(HWND hWnd,UINT uMsg,UINT idEvent,unsigned long dwTime);

	friend class CCreateBag;
};