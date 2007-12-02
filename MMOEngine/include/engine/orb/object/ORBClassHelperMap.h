/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ORBCLASSHELPERMAP_H_
#define ORBCLASSHELPERMAP_H_

#include "../../../system/lang.h"

namespace engine {
  namespace ORB {

	class ORBClassHelper;
	
	class ORBClassHelperMap : public HashTable<string, ORBClassHelper*> {
		int hash(const string& key) {
	        return sys::lang::String::hashCode(key);
		}
	
	public:
		ORBClassHelperMap() : HashTable<string, ORBClassHelper*>(100) {
			setNullValue(NULL);
		}
		
	};
	
  } // namespace ORB
} // namespace engine

using namespace engine::ORB;	

#endif /*ORBCLASSHELPERMAP_H_*/
