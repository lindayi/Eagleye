#pragma once

// CClientSocket 命令目标


class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	//接收信息
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
};

