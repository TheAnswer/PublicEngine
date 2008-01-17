/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef DATAGRAMSERVICECLIENTPROXY_H_
#define DATAGRAMSERVICECLIENTPROXY_H_

#include "../../system/lang.h"

#include "ServiceClient.h"

namespace engine {
  namespace service {

	class DatagramServiceClientProxy : public ServiceClient {
	public:
		DatagramServiceClientProxy(Socket* sock, SocketAddress& addr) : ServiceClient(sock, addr) {
		}

		void run() {
		}

		bool send(Packet* pack) {
			if (packetLossChance != 0 && System::random(100) < (uint32) packetLossChance)
				return false;
			
			socket->sendTo(pack, &addr);
			
			return true;
		}

		bool read(Packet* pack) {
			if (packetLossChance != 0 && System::random(100) < (uint32) packetLossChance)
				return false;

			SocketAddress addr;
			socket->recieveFrom(pack, &addr);

			return true;
		}

	};

  } // namespace service
} // namespace engine

using namespace engine::service;

#endif /*DATAGRAMSERVICECLIENTPROXY_H_*/
