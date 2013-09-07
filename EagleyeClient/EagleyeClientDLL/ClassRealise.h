#pragma once
#include "EntityClass.h"
#include "LogicClass.h"
#include "Markup.h"

#include <tlhelp32.h> 
#include <WinSock2.h>
#include <Iphlpapi.h>
#include <conio.h>
#include <Windows.h>
#include <winsock.h>

#include <iostream>

#pragma comment(lib,"Iphlpapi.lib")
#pragma comment(lib,"wsock32.lib")

/*********************************************************
函数名称：NetSpeed
功能描述：获取网卡接受和发送的总数据
作者：	  马聪
创建时间：2013-08-28
参数说明：up-发送流量,down-接受流量
返 回 值：无
所需头文件：#pragma comment(lib, "IPHLPAPI.lib")
            #include <iphlpapi.h>
*********************************************************/
void NetSpeed(long &up, long &down)
{
	MIB_IFTABLE * pIfTable;   //网络信息表
	ULONG  dwSize  = 0;      //接口个数 
	DWORD  dwRet = 0;     //返回值

	pIfTable = (MIB_IFTABLE *) malloc(sizeof (MIB_IFTABLE)); 
	if  ( GetIfTable( pIfTable, &dwSize, TRUE  )  ==  ERROR_INSUFFICIENT_BUFFER   )   
	{   
		pIfTable  =  (  MIB_IFTABLE  *  )  new  char[dwSize];   		
		if  (  pIfTable  !=  NULL  )   
		{   
			dwRet   =   GetIfTable(   pIfTable,   &dwSize,   TRUE   );   //获得真实接口信息			
			if   (   dwRet   ==   NO_ERROR   )   
			{     				
				for   (   int   i=0;   i<pIfTable->dwNumEntries;   i++   )   
				{   
					if((pIfTable->table[i]).dwType ==6 	&& (pIfTable->table[i]).dwInOctets>0 && (pIfTable->table[i]).dwOutOctets>0 )
					{    
						down = (pIfTable->table[i]).dwInOctets;	          //接口接受总数据
						up = (pIfTable->table[i]).dwOutOctets;		  //接口发送总数据
					}
					if((pIfTable->table[i]).dwType ==71 	&& (pIfTable->table[i]).dwInOctets>0 && (pIfTable->table[i]).dwOutOctets>0 )      
					{
						down = (pIfTable->table[i]).dwInOctets;	          //接口接受总数据
						up = (pIfTable->table[i]).dwOutOctets;		  //接口发送总数据
					}
				}
			}
		}
	}
	delete pIfTable;
}

char *WSTRToAnsi(wchar_t* Msg)//把wchar*转换称char*  
{
	int len = wcstombs(NULL, Msg, 0);  
	char *buf = new char[len+1];  
	wcstombs(buf, Msg, len);  
	buf[len] = 0;  
	return buf;
}

int CCreateBag::MonitoredInfo(string &xml, long &lastup, long &lastdown, CClientConfig &config)
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	int count = 0;
	long nowup,nowdown;

	xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><bag type=\"monitoredInfo\"><uprate>";
	NetSpeed(nowup, nowdown);
	char *pTem = new char[10];
	sprintf(pTem, "%ld", (nowup - lastup)/1024/(config.GetFrequency()/1000));
	//sprintf(pTem, "%ld", (nowup - lastup)/1024/1000*1000);
	xml += pTem;
	delete pTem;
	xml += "</uprate><downrate>";
	pTem = new char[10];
	sprintf(pTem, "%ld", (nowdown - lastdown)/1024/(config.GetFrequency()/1000));
	//sprintf(pTem, "%ld", (nowdown - lastdown)/1024/1000*1000);
	xml += pTem;
	delete pTem;
	xml += "</downrate>";
	lastup = nowup;
	lastdown = nowdown;

	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if(hProcessSnap == INVALID_HANDLE_VALUE)
	{
		//printf("CreateToolhelp32Snapshot调用失败!");
		return -1;
	}

	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while(bMore)
	{
		count++;
		xml += "<process pid=\"";
		pTem = new char[10];
		sprintf(pTem, "%d", pe32.th32ProcessID);
		xml += pTem;
		delete(pTem);
		xml += "\">";
		//string sTem = pe32.szExeFile;
		pTem=WSTRToAnsi(pe32.szExeFile);
		xml += pTem;
		delete[](pTem);
		xml += "</process>";
		//printf("%25s\t%10d\n",pe32.szExeFile,pe32.th32ProcessID);
		bMore=::Process32Next(hProcessSnap,&pe32);
	}
	::CloseHandle(hProcessSnap);
	xml += "</bag>";
	return 0;
}

int CCreateBag::ClientInfo(string &xml, CClientInfo &ClientInfo)
{
	xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><bag type=\"init\"><clientIP>";
	xml += ClientInfo.m_csClientIP;
	xml += "</clientIP><mac>";
	xml += ClientInfo.m_csMAC;
	xml += "</mac><os>";
	xml += ClientInfo.m_csOS;
	xml += "</os><cpu>";
	xml += ClientInfo.m_csCPU;
	xml += "</cpu><mem>";
	char *pTem = new char[10];
	sprintf(pTem, "%I64d", ClientInfo.m_nMemory);
	xml += pTem;
	delete(pTem);
	xml += "</mem></bag>";
	return 0;
}

CClientInfo::CClientInfo()
{

	/*******************************************************
	功能描述:获取Ip地址
	作者：	  马聪
	创建时间：2013-8-26
	*********************************************************/

	char cScore[256];
	struct hostent *p = 0;
	WSADATA w;
	WSAStartup(0x0101, &w);
	gethostname(cScore, 256);
	p = gethostbyname(cScore);
	const char *pIP = inet_ntoa(*((struct in_addr *)p->h_addr_list[0]));//此处获得本机IP
	m_csClientIP = pIP;
	string st = pIP;
	WSACleanup();


	/*******************************************************
	功能描述:获取Mac地址
	作者：	  马聪
	创建时间：2013-8-26
	********************************************************/

    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();          //PIP_ADAPTER_INFO结构体指针存储本机网卡信息
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);               	//得到结构体大小,用于GetAdaptersInfo参数
	int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);				 //填充pIpAdapterInfo指针变量
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		delete pIpAdapterInfo;
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);    
	} 
	if (ERROR_SUCCESS == nRel)
	{
		while (pIpAdapterInfo)										  //可能有多网卡,循环判定
		{		
			IP_ADDR_STRING *pIpAddrString = &(pIpAdapterInfo->IpAddressList);	  //可能网卡有多IP,循环判定
			do 
			{
				
				if(st == pIpAddrString->IpAddress.String)
				{	
					char ch[6][6];
					int j = 0;
					for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
					{
						if (i < pIpAdapterInfo->AddressLength-1)
						{
							sprintf(ch[j],"%02X-",pIpAdapterInfo->Address[i]);
							m_csMAC += ch[j];
						}
						else
						{
							sprintf(ch[j],"%02X\n",pIpAdapterInfo->Address[i]);
							m_csMAC += ch[j];
						}
						j++;
					}					
				}
				pIpAddrString=pIpAddrString->Next;
			} while (pIpAddrString);
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
	}
	if (pIpAdapterInfo)										//释放内存空间
	{
		delete pIpAdapterInfo;
	}

	/*******************************************************
	功能描述:获取物理内存大小
	作者：	  马聪
	创建时间：2013-8-26
	*********************************************************/	
	MEMORYSTATUSEX m_MemorySize;	 
	m_MemorySize.dwLength = sizeof (m_MemorySize);
	GlobalMemoryStatusEx (&m_MemorySize);
	m_nMemory = m_MemorySize.ullTotalPhys/1024;				//物理内存大小


	/*******************************************************
	功能描述:获取操作系统版本
	作者：	  马聪
	创建时间：2013-8-27
	*********************************************************/

	OSVERSIONINFO os;
	SYSTEM_INFO info;
	BOOL bIsWindowsXPorLater;

	ZeroMemory(&os, sizeof(OSVERSIONINFO));
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	if(GetVersionEx((OSVERSIONINFO *)&os))  
	{   
		//下面根据版本信息判断操作系统名称   
		switch(os.dwMajorVersion)//判断主版本号  
		{  
		case 4:  
			switch(os.dwMinorVersion)//判断次版本号   
			{   
			case 0:  
				if(os.dwPlatformId==VER_PLATFORM_WIN32_NT)  
					m_csOS = "Microsoft Windows NT 4.0";   
				else if(os.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)  
					m_csOS = "Microsoft Windows 95";  
				break;  
			case 10:  
				m_csOS = "Microsoft Windows 98";  
				break;  
			case 90:  
				m_csOS = "Microsoft Windows Me";  
				break;  
			}  
			break;  

		case 5:  
			switch(os.dwMinorVersion)     
			{   
			case 0:  
				m_csOS = "Microsoft Windows 2000";  
				break;  

			case 1:  
				m_csOS = "Microsoft Windows XP";  
				break;  

			case 2:  
				if(2 == VER_NT_WORKSTATION   
					&& info.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)  
				{  
					m_csOS = "Microsoft Windows XP Professional x64 Edition";  
				}  
				else if(GetSystemMetrics(SM_SERVERR2)==0)  
					m_csOS = "Microsoft Windows Server 2003";  
				else if(GetSystemMetrics(SM_SERVERR2)!=0)  
					m_csOS = "Microsoft Windows Server 2003 R2";  
				break;  
			}  
			break;  

		case 6:  
			switch(os.dwMinorVersion)  
			{  
			case 0:  
				if(0 == VER_NT_WORKSTATION)  
					m_csOS = "Microsoft Windows Vista";  
				else  
					m_csOS = "Microsoft Windows Server 2008";  
				break;  
			case 1:  
				if(1 == VER_NT_WORKSTATION)  
					m_csOS = "Microsoft Windows 7";  
				else  
					m_csOS = "Microsoft Windows Server 2008 R2";  
				break;  
			case 2:
				m_csOS = "Microsoft Windows 8";
				break;
			}  
			break;  
		}  
	}

	/*******************************************************
	功能描述:获取CPU信息
	作者：	  马聪
	创建时间：2013-8-27
	*********************************************************/

	const DWORD id = 0x80000002; //从0x80000002开始,到0x80000004结束
	char CPUType[49];//用来存储CPU型号信息
	DWORD deax;
	DWORD debx;
	DWORD decx;
	DWORD dedx;
	memset(CPUType,0,sizeof(CPUType));//初始化数组
	for(DWORD t = 0 ; t < 3 ; t++ )
	{
		DWORD veax = id+t;
		__asm
		{
			mov eax,veax
				cpuid
				mov deax,eax
				mov debx,ebx
				mov decx,ecx
				mov dedx,edx
		}
		//每次循环结束,保存信息到数组
		memcpy(CPUType+16*t+ 0,&deax,4);
		memcpy(CPUType+16*t+ 4,&debx,4);
		memcpy(CPUType+16*t+ 8,&decx,4);
		memcpy(CPUType+16*t+12,&dedx,4);
	}
	m_csCPU = string(CPUType);
}


string CClientConfig::GetServerIP()
{
	return m_csServerIP;
}

int CClientConfig::GetFrequency()
{
	return m_nFrequency;
}

int CClientConfig::ReadXML(string &sxml)
{
	size_t size = sxml.length();
	wchar_t *buffer = new wchar_t[size+1];
	MultiByteToWideChar( CP_ACP, 0, sxml.c_str(), size, buffer, size * sizeof(wchar_t) );
	buffer[size] = 0;
	CString sTem;

	CMarkup xml;
	xml.SetDoc(buffer);

	xml.FindChildElem();
	sTem = xml.GetChildData();
	m_csServerIP = WSTRToAnsi(sTem.GetBuffer());
	xml.FindChildElem();
	sTem = xml.GetChildData();
	m_nFrequency = atoi(WSTRToAnsi(sTem.GetBuffer()));

	delete buffer;
	return 0;
}

int CCommand::RunCommand()
{
	m_csCommand = "/c " + m_csCommand;
	size_t size = m_csCommand.length();
	wchar_t *buffer = new wchar_t[size+1];
	MultiByteToWideChar( CP_ACP, 0, m_csCommand.c_str(), size, buffer, size * sizeof(wchar_t) );
	buffer[size] = 0;
	ShellExecute(NULL,TEXT("open"),TEXT("cmd.exe"),buffer,NULL,SW_HIDE); 
	delete buffer;
	return 0;
}

int CCommand::SetCommand(CString command)
{
	m_csCommand = WSTRToAnsi(command.GetBuffer(0));
	return 0;
}

int CClientMessageHandle::RunCommand(CCommand &command)
{
	return command.RunCommand();
}

void CClientMessageHandle::ClientInitial(CClientConfig &ClientConfig, string &xml)
{
	ClientConfig.ReadXML(xml);
}