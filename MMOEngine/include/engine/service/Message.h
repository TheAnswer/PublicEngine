/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "../../system/lang.h"

#include "proto/BasePacket.h"
#include "ServiceClient.h"

#include "../orb/object/ORBObject.h"

namespace engine {
  namespace service {

	class Message : public BasePacket, public ORBObject {
		ServiceClient* client;
	
		uint64 timestamp;
		
	public:
		Message() : BasePacket(), ORBObject() {
			insertShort(0x0900);
			insertShort(0x0000);
		}
	
		Message(int size) : BasePacket(size), ORBObject() {
			insertShort(0x0900);
			insertShort(0x0000);
		}
	
		Message(Packet* pack, int start) : BasePacket(pack->size() - start), ORBObject() {
			if (start < 0)
				throw new PacketIndexOutOfBoundsException(pack, start);
	
			insertStream(pack->getBuffer() + start, pack->size() - start);
			reset();
		}
	
		Message(Packet* pack, int startoffs, int endoffs) : BasePacket(endoffs - startoffs), ORBObject() {
			if (startoffs < 0)
				throw new PacketIndexOutOfBoundsException(pack, startoffs);
	
			if (endoffs > pack->size())
				throw new PacketIndexOutOfBoundsException(pack, endoffs);
			
			insertStream(pack->getBuffer() + startoffs, endoffs - startoffs);
			reset();
		}
	
		int compareTo(Message* m) {
			uint64 t1 = timestamp;
			uint64 t2 = m->getTimeStamp();
			
			if (t1 < t2)
				return 1;
			else if (t1 > t2)
				return -1;
			else
				return 0; 
		}
	
		Message* clone(int startoffs = 0) {
			Message* pack = new Message();
			copy(pack, startoffs);
			
			pack->doSeq = doSeq;
			pack->doEncr = doEncr;
			pack->doComp = doComp;
			pack->doCRCTest = doCRCTest;
			return pack;
		}
	
		// setters and getters
		inline void setClient(ServiceClient* c) {
			client = c;
		}
	
		inline void setTimeStamp(uint64 ts) {
			timestamp = ts;
		}
	
		inline uint64 getTimeStamp() {
			return timestamp;
		}
	
		inline ServiceClient* getClient() {
			return client;
		}
	};

  } // namespace service
} // namespace engine

using namespace engine::service;

#endif /*MESSAGE_H_*/
