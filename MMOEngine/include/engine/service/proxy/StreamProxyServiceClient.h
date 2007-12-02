/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef STREAMPROXYSERVICECLIENT_H_
#define STREAMPROXYSERVICECLIENT_H_

#include "engine/engine.h"

class StreamProxyServiceClient : public StreamServiceClient, public Logger 
{
	class StreamProxyService* service;

	class StreamProxyClient* proxyClient;

public:
	StreamProxyServiceClient(StreamProxyService* serv, string& host, int port);

	void run();

	void stop();

	void handleMessage(Packet* message);

	void forwardMessage(Packet* message);

	// setters
	inline void setProxyClient(StreamProxyClient* pclient)
	{
		proxyClient = pclient;
	}

};

#endif /*STREAMPROXYSERVICECLIENT_H_*/
