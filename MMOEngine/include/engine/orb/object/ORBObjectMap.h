/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ORBOBJECTMAP_H_
#define ORBOBJECTMAP_H_

#include "../../../system/lang.h"

namespace engine {
  namespace ORB {

	class ORBObjectAdapter;
	
	class ORBObjectMap : public HashTable<uint64, ORBObjectAdapter*> {
		int hash(const uint64& key) {
	        return Long::hashCode(key);
		}
	
	public:
		ORBObjectMap() : HashTable<uint64, ORBObjectAdapter*>(100) {
			setNullValue(NULL);
		}
		
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*ORBOBJECTMAP_H_*/
