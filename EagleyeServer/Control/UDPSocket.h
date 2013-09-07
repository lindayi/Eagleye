#pragma once
#include "afxsock.h"

// CUDPSocket ÃüÁîÄ¿±ê

class CUDPSocket : public CSocket
{
public:
	CUDPSocket();
	virtual ~CUDPSocket();
	virtual void OnReceive(int nErrorCode);
};