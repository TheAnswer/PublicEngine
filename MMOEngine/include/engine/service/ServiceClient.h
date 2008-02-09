/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef SERVICECLIENT_H_
#define SERVICECLIENT_H_

#include "../../system/lang.h"

namespace engine {
  namespace service {

	class ServiceClient {
	protected:
		SocketAddress addr;
		Socket* socket;

		bool hasError, disconnected;

		int packetLossChance;
		
	public:
		ServiceClient(Socket* sock) {
			socket = sock;
	
			packetLossChance = 0;
		}
	
		ServiceClient(Socket* sock, SocketAddress& addr) {
			socket = sock;
			ServiceClient::addr = addr;
	
			packetLossChance = 0;
		}
	
		ServiceClient(const string& host, int port) {
			setAddress(host, port);
			
			packetLossChance = 0;
		}

		virtual ~ServiceClient() {
		}

		void close() {
			if (socket != NULL) 	{
				socket->close();
				
				delete socket;
				socket = NULL;
			}			
		}
		
		bool isAvailable() {
			if (socket == NULL)
				return false;
			
			return !(hasError || disconnected);			
		}

		inline bool isDisconnected() {
			return disconnected;
		}

		// setters
		inline void setAddress(const string& host, int port) {
			addr = SocketAddress(host, port);
		}

		inline void setError() {
			hasError = true;
		}

		inline void setPacketLoss(int ratio) {
			packetLossChance = ratio;
		}

		// getters
		inline uint64 getNetworkID() {
			return addr.getNetworkID();
		}
		
		inline SocketAddress& getAddress()
		{
			return addr;
		}
	};

  } // namespace service
} // namespace engine

using namespace engine::service;

#endif /*SERVICECLIENT_H_*/
