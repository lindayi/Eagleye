#pragma once

#include "stdafx.h"
#include "LogicClass.h"
#include "EntityClass.h"
#include "Markup.h"

using namespace std;

extern CMonitoredPC m_pPCArray[256];
vector<string> log;

char *WSTRToAnsi(wchar_t* Msg)//把wchar*转换称char*  
{
	int len = wcstombs(NULL, Msg, 0);  
	char *buf = new char[len+1];  
	wcstombs(buf, Msg, len);  
	buf[len] = 0;  
	return buf;
}

int CMonitoredPC::GetStatus()
{
	return m_nStatus;
}

CMonitoredPC::CMonitoredPC()
{}

void CMonitoredPC::TransFromXML(CString &x)
{
	CMarkup xml;
	xml.SetDoc(x);
	xml.ResetPos();
	xml.ResetChildPos();
	xml.FindChildElem();
	m_Info.m_csClientIP = WSTRToAnsi(xml.GetChildData().GetBuffer(0));
	xml.FindChildElem();
	m_Info.m_csMAC = WSTRToAnsi(xml.GetChildData().GetBuffer(0));
	xml.FindChildElem();
	m_Info.m_csOS = WSTRToAnsi(xml.GetChildData().GetBuffer(0));
	xml.FindChildElem();
	m_Info.m_csCPU = WSTRToAnsi(xml.GetChildData().GetBuffer(0));
	xml.FindChildElem();
	m_Info.m_nMemory = atoi(WSTRToAnsi((xml.GetChildData()).GetBuffer(0)));
}

CGroup::CGroup()
{ 
}

CPolicy::CPolicy()
{}

string CPolicy::GetName()
{
	return m_csName;
}

int CPolicy::SetName(string name)
{
	m_csName = name;
	return 0;
}

CClientInfo::CClientInfo()
{}

CServerConfig::CServerConfig()
{}

int CServerConfig::GetFrequency()
{
	return m_nFrequency;
}

int CServerConfig::SetFrequency(int Frequency)
{
	m_nFrequency = Frequency;
	return 0;
}

int CServerConfig::GetTimeout()
{
	return m_nTimeout;
}

int CServerConfig::SetTimeout(int Timeout)
{
	m_nTimeout = Timeout;
	return 0;
}

int CServerConfig::ReadConfigFile()
{
	FILE *fp;
	int i,n,j,k;
	char cName[1000],cR[1000],cB[1000];
	CPolicy *cPo;
	fp = fopen ("config.ini","r");		      //文件路径
	if ( fp == NULL)
	{
		return -1;
	}
	fscanf(fp,"%d",&m_nTimeout);
	fscanf(fp,"%d",&m_nFrequency);
	fscanf(fp,"%d",&n);
	for(i = 0;i<n;i++)
	{
		fscanf(fp,"%s",&cName);
		cPo=new CPolicy;
		cPo->SetName(cName);
		do
		{
			fscanf(fp,"%s",&cR);
			if(cR[0] != '0')
			{
				cPo->m_BlackList.push_back(cR);
			}
		}while (cR[0] != '0');
		m_PolicyList.push_back(*cPo);
	}
	fscanf(fp,"%d",&n);
	for(i = 0;i < n;i++)
	{
		fscanf(fp,"%s",&cName);
		fscanf(fp,"%s",&cR);
		m_GroupList[i].m_csName = cName;
		for(j = 0; j < m_PolicyList.size(); j++)
		{
			if(m_PolicyList.at(j).GetName() == cR) m_GroupList[i].m_Policy = &m_PolicyList.at(j);
		}
		fscanf(fp,"%d",&k);
		for(j = 0; j < k; j++)
		{
			fscanf(fp,"%s",&cB);
			m_GroupList[i].m_MemberList.push_back(cB);
		}
	}
	fclose(fp);
	return 0;
}

int CServerConfig::WriteConfigFile()
{
	return 0;
}

void CFilter::Filter(CString &x, CSessionSocket &rSessionSocket, CServerConfig &ServerConfig, CConnection &m_pThis)
{
	int i;
	CMarkup xml;
	xml.SetDoc(x);
	CString sTem, pidTem;
	string *sLog;
	CProcess *Process;
	xml.ResetPos();
	xml.ResetChildPos();
	xml.FindChildElem();

	for(i=0;i<19;i++)
	{
		m_pPCArray[rSessionSocket.m_PC].m_Uprate[i]=m_pPCArray[rSessionSocket.m_PC].m_Uprate[i+1];
	}
	m_pPCArray[rSessionSocket.m_PC].m_Uprate[19] = atoi(WSTRToAnsi(xml.GetChildData().GetBuffer(0)));
	xml.FindChildElem();

	for(i=0;i<19;i++)
	{
		m_pPCArray[rSessionSocket.m_PC].m_Downrate[i]=m_pPCArray[rSessionSocket.m_PC].m_Downrate[i+1];
	}
	m_pPCArray[rSessionSocket.m_PC].m_Downrate[19]  = atoi(WSTRToAnsi(xml.GetChildData().GetBuffer(0)));
	m_pPCArray[rSessionSocket.m_PC].m_ProcessList.clear();
	vector <CProcess>().swap(m_pPCArray[rSessionSocket.m_PC].m_ProcessList);
	while(xml.FindChildElem(TEXT("process")))
	{
		pidTem = xml.GetChildAttrib(TEXT("pid"));
		sTem = xml.GetChildData();
		Process = new CProcess(WSTRToAnsi(sTem.GetBuffer(0)), atoi(WSTRToAnsi(pidTem.GetBuffer(0))));
		m_pPCArray[rSessionSocket.m_PC].m_ProcessList.push_back(*Process);
		for(i = 0; i < ServerConfig.m_GroupList[m_pPCArray[rSessionSocket.m_PC].m_Group].m_Policy->m_BlackList.size(); i++)
			if (WSTRToAnsi(sTem.GetBuffer(0)) == ServerConfig.m_GroupList[m_pPCArray[rSessionSocket.m_PC].m_Group].m_Policy->m_BlackList.at(i))
			{
				CFilter::KillProcess(pidTem,rSessionSocket);
				sLog = new string;
				*sLog = "自动查杀 IP：" + m_pPCArray[rSessionSocket.m_PC].m_Info.m_csClientIP;
				*sLog += " MAC：";
				*sLog += m_pPCArray[rSessionSocket.m_PC].m_Info.m_csMAC;
				*sLog += " 进程：";
				*sLog += WSTRToAnsi(sTem.GetBuffer(0));
				log.push_back(*sLog);
			}
	}
	
}

void CFilter::KillProcess(CString &nPid,CSessionSocket &rSessionSocket)
{
	string csCmd("<?xml version=\"1.0\" encoding=\"UTF-8\"?><bag type=\"command\"><command>taskkill /F /PID ");
	csCmd += WSTRToAnsi(nPid.GetBuffer(0));
	csCmd += "</command></bag>";
	int i=rSessionSocket.Send(csCmd.c_str(),csCmd.length());
}

CProcess::CProcess(string name, int pid)
{
	m_csName = name;
	m_nPID = pid;
}