/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ORBOBJECTNAMEMAP_H_
#define ORBOBJECTNAMEMAP_H_

#include "../../../system/lang.h"

#include "ORBObjectStub.h"
//class ORBObjectStub;

namespace engine {
  namespace ORB {

	class ORBObjectNameMap : public HashTable<string, ORBObjectStub*> {
		int hash(const string& key) {
	        return sys::lang::String::hashCode(key);
		}
	
	public:
		ORBObjectNameMap() : HashTable<string, ORBObjectStub*>(100) {
			setNullValue(NULL);
		}
	
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*ORBOBJECTNAMEMAP_H_*/
