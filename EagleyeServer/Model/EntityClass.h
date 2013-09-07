#pragma once

#include <string>
//#include "LogicClass.h"
#include "SessionSocket.h"

using namespace std;

/************************************************
Class name: CClientInfo
Create by：林达意 
CreateDate：2013-08-19
Explain：描述客户端基本软硬件信息 
************************************************/ 

class CClientInfo
{
	public:
		string 	m_csClientIP;		//IP地址 
		string 	m_csMAC;			//网卡MAC地址 
	
		string	m_csOS;				//操作系统 
		string 	m_csCPU;			//CPU
		int 	m_nMemory;			//内存容量（M） 
		
	public:
		string TransFromXML(char *); 		//转换为标准XML初始化包 
		CClientInfo();				//构造函数，从系统获取信息 

};

/************************************************
Class name: CProcess
Create by：林达意 
CreateDate：2013-08-19
Explain：描述进程 
************************************************/ 

class CProcess
{
	public:
		string	m_csName;			//进程名 
		int		m_nPID;				//进程PID 
	
	public:
		CProcess(string, int);		//构造函数 
};




/************************************************
Class name: CPolicy
Create by：林达意
CreateDate：2013-08-19
Explain：描述某一具体策略 
************************************************/ 

class CPolicy
{
	private:
		string	m_csName;				//策略名
	public: 
		vector<string>	m_BlackList;	//该策略黑名单 
		
	CPolicy();					//构造函数，创建策略 
	int SetName(string);			//设置策略名 
	string GetName();			//获取策略名 
};

/************************************************
Class name: CMonitoredPC
Create by：林达意
CreateDate：2013-08-19
Explain：描述服务端监控的单台PC 
************************************************/ 

class CMonitoredPC
{
	public:
		int			m_nStatus;				//客户端状态，在线1，离线0 
		CClientInfo	m_Info;					//客户端软硬件信息 
		int			m_Group;				//客户端所在组
		int			m_Uprate[20];
		int			m_Downrate[20];
	public:
		vector<CProcess>	m_ProcessList;	//客户端进程列表
		CSessionSocket		m_SessionSocket;
		CTime				m_LastTime;
	
	CMonitoredPC();	//构造函数
	CClientInfo GetClientInfo();		//获得客户端软硬件信息
	CPolicy GetPolicy();				//获得采用的策略 
	int GetStatus();					//获取客户端状态 
	int SetPolicy(CPolicy &);		//设置采用的策略
	int SetStatus(int); 				//设置客户端状态 
	void Visualization();			//可视化数据 
	void TransFromXML(CString &);
};


/************************************************
Class name: CGroup
Create by：林达意
CreateDate：2013-08-19
Explain：描述某一具体分组
************************************************/ 

class CGroup
{
	public:
		string		m_csName;					//组名 
		CPolicy		*m_Policy;					//组策略 
	public: 
		vector<string>	m_MemberList;	//组计算机 
		
	CGroup();					//构造函数
	int SetPolicy(CPolicy &);			//设置组策略 
	int SetName(string &);				//设置组名
	string GetName();					//获取组名
	CPolicy GetPolicy();					//获取组策略 
};

/************************************************
Class name: CServerConfig
Create by：林达意 
CreateDate：2013-08-19
Explain：描述服务端配置信息 
************************************************/ 

class CServerConfig
{
	private:
		int		m_nTimeout;				//客户端异常断线超时时间（毫秒） 
		int		m_nFrequency;			//刷新频率（毫秒） 
	public:
		CGroup	m_GroupList[7];	//分组列表 
		vector<CPolicy>	m_PolicyList;	//策略列表 
	
	CServerConfig();			//构造函数 
	string ClientConfigXML();	//构造客户端配置XML信息
	int ReadConfigFile();		//从文件读取设置 
	int WriteConfigFile();		//将设置存入文件 
	int GetTimeout();			//获取超时时间
	int GetFrequency();			//获取刷新频率
	int SetTimeout(int);			//设置超时时间 
	int SetFrequency(int);			//设置刷新频率 		
};

