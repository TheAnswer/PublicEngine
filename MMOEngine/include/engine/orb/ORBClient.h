/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ORBCLIENT_H_
#define ORBCLIENT_H_

#include "../log/Logger.h"

#include "../service/StreamServiceClient.h"

namespace engine {
  namespace ORB {

	class ObjectRequestBroker;
	
	class ORBClient : public StreamServiceClient, public Logger {
		ObjectRequestBroker* orb;
		
	public:
		ORBClient(ObjectRequestBroker* broker, Socket* sock);
		ORBClient(ObjectRequestBroker* broker, const string& host);
		
		void run();
		
		void send(Packet* pack);
		
		inline ObjectRequestBroker* getBroker() {
			return orb;
		}
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*ORBCLIENT_H_*/
