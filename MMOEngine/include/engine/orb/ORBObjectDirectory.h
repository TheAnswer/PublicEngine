/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ORBOBJECTDIRECTORY_H_
#define ORBOBJECTDIRECTORY_H_

#include "object/ORBObject.h"
#include "object/ORBObjectAdapter.h"

#include "object/ORBObjectMap.h"

namespace engine {
  namespace ORB {

	class ORBObjectDirectory {
		ORBObjectMap objectMap;
	
	public:
		ORBObjectDirectory();
		
		void add(sys::uint64 objid, ORBObjectAdapter* adapter);
	
		ORBObject* get(sys::uint64 objid);
		
		void remove(sys::uint64 objid);
	
		ORBObjectAdapter* getAdapter(uint64 objid);
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*ORBOBJECTDIRECTORY_H_*/
