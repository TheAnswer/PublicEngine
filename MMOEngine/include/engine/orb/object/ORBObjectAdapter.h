/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ORBOBJECTADAPTER_H_
#define ORBOBJECTADAPTER_H_

#include "ORBObjectStub.h"

#include "ORBMethodInvocation.h"

namespace engine {
  namespace ORB {
  	
	class ORBObjectServant;
	
	class ORBObjectAdapter {
	protected:
		ORBObjectServant* impl;
		
		ORBObjectStub* stub;
		
	public:
		ORBObjectAdapter(ORBObjectServant* obj) {
			impl = obj;
			stub = NULL;
		}
		
		virtual ~ORBObjectAdapter() {
		}
		
		virtual Packet* invokeMethod(sys::uint32 methid, ORBMethodInvocation* inv) = 0;
		
		inline void setStub(ORBObjectStub* stb) {
			stub = stb;
		}
		
		inline ORBObjectServant* getImplementation() {
			return impl;
		}
	
		inline ORBObjectStub* getStub() {
			return stub;
		}
	
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*ORBOBJECTADAPTER_H_*/
