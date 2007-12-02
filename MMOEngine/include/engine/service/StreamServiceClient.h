/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef STREAMSERVICECLIENT_H_
#define STREAMSERVICECLIENT_H_

#include "../../system/lang.h"

#include "ServiceClient.h"

namespace engine {
  namespace service {

	class StreamServiceClient : public ServiceClient, public Thread {
	protected:
		bool doRun;
		
	public:
		StreamServiceClient(Socket* sock);
		StreamServiceClient(Socket* sock, SocketAddress& addr);
		StreamServiceClient(const string& host, int port);

		void connect();
		
		virtual void run() {
		}

		// message methods
		void receiveMessages();

		virtual void handleMessage(Packet* message) {
		}

		virtual bool handleError(Exception& e);

		// socket methods
		bool send(Packet* pack);
	
		bool read(Packet* pack);
		
		void disconnect();

	};

  } // namespace service
} // namespace engine

using namespace engine::service;

#endif /*STREAMSERVICECLIENT_H_*/
