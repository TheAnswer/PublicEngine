/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ORBPACKETHANDLER_H_
#define ORBPACKETHANDLER_H_

#include "../../system/lang.h"

#include "../log/Logger.h"

namespace engine {
  namespace ORB {

	class ObjectRequestBroker;
	class ORBClient;
	
	class ORBPacketHandler : public Logger {
		ObjectRequestBroker* orb;
	
	public:
		ORBPacketHandler();
		ORBPacketHandler(const string& s, ObjectRequestBroker* broker);
	
		~ORBPacketHandler();
	
		void handlePacket(ORBClient* client, Packet* pack);
		
		void handleObjectLookUpMessage(ORBClient* client, Packet* pack);
		void handleObjectDeployMessage(ORBClient* client, Packet* pack);
		void handleMethodInvocationMessage(ORBClient* client, Packet* pack);
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*ORBPACKETHANDLER_H_*/
