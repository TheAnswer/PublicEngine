/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef DATAGRAMPROXYCLIENT_H_
#define DATAGRAMPROXYCLIENT_H_

#include "engine/engine.h"

class DatagramProxyClient : public DatagramServiceClientProxy, public Logger 
{
	class DatagramProxyService* service;

	class DatagramProxyServiceClient* proxyServiceClient;

public:
	DatagramProxyClient(DatagramProxyService* serv, Socket* sock, SocketAddress& addr);

	void forwardMessage(Packet* message);

	// setters
	inline void setProxyServiceClient(DatagramProxyServiceClient* pclient)
	{
		proxyServiceClient = pclient;
	}

};

#endif /*DATAGRAMPROXYCLIENT_H_*/
