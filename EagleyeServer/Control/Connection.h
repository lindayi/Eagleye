#pragma once
#include "UDPSocket.h"
#include "SessionSocket.h"
#include "EntityClass.h"

#include <string>
using namespace std;

#define PORT 32767

class CConnection
{
private:
	CUDPSocket m_UDPSokcet;
	//CMonitoredPC *m_pPCArray;
	CServerConfig *m_pServerConfig;
public:
	static CConnection * m_pThis;
	CUIWnd *m_pUI;
	CConnection();
	~CConnection(void);
	
	int InitConnection(CMonitoredPC *pPCArray,CServerConfig *, CUIWnd *);
	static int ReceiveUDPMessage(CUDPSocket &rUDPSocket);//接收UDP广播
	static int ReceiveMonitoredInfo(CSessionSocket &rSessionSocket);//接收监控信息
	static int SendConfiguration(CSessionSocket &rSessionSocket);//发送配置信息
	//static int SendCommand();//发送指令
	static 	VOID CALLBACK CheckOnLine(HWND hWnd,UINT uMsg,UINT idEvent,unsigned long dwTime);//检查是否掉线
};
