/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef STREAMPROXYCLIENT_H_
#define STREAMPROXYCLIENT_H_

#include "engine/engine.h"

class StreamProxyClient : public StreamServiceClientProxy, public Logger 
{
	class StreamProxyService* service;

	class StreamProxyServiceClient* proxyClient;

public:
	StreamProxyClient(StreamProxyService* serv, Socket* sock, SocketAddress& addr);

	void run();

	void stop();

	void handleMessage(Packet* message);

	void forwardMessage(Packet* message);

	// setters
	inline void setProxyServiceClient(StreamProxyServiceClient* pclient)
	{
		proxyClient = pclient;
	}

};

#endif /*STREAMPROXYCLIENT_H_*/
