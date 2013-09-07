#pragma once

/************************************************
Class name: CClientInfo
Create by：林达意 
CreateDate：2013-08-19
Explain：描述客户端基本软硬件信息 
************************************************/ 

#include <string>

using namespace std;

class CClientInfo
{
	private:
		string 	m_csClientIP;		//IP地址 
		string 	m_csMAC;			//网卡MAC地址 
	
		string	m_csOS;				//操作系统 
		string 	m_csCPU;			//CPU
		DWORDLONG 	m_nMemory;			//内存容量（M） 
	public:
		CClientInfo();				//构造函数，从系统获取信息 
		friend class CCreateBag;
};

/************************************************
Class name: CClientConfig
Create by：林达意 
CreateDate：2013-08-19
Explain：描述客户端配置信息 
************************************************/ 

class CClientConfig
{
	private:
		string	m_csServerIP;		//服务端IP 
		int 	m_nFrequency;		//刷新频率（毫秒） 
	
	public:
		int ReadXML(string &);  	//读取XML，初始化配置
		string GetServerIP();		//获取服务端IP 
		int GetFrequency();			//获取刷新频率 
};

/************************************************
Class name: CCommand
Create by：林达意 
CreateDate：2013-08-19
Explain：描述CMD指令 
************************************************/ 

class CCommand
{
	private:
		string	m_csCommand;		//CMD指令 
	
	public:
		int RunCommand();		//执行CMD指令 
		int SetCommand(CString);
};