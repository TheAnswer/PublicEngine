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
		ORBClassHelperMap() : HashTable<string, ORBClassHelper*>(1000) {
			setNullValue(NULL);
		}
		
		~ORBClassHelperMap() {
			HashTableIterator<string, ORBClassHelper*> iter(this);
			
			while (iter.hasNext()) {
				string& helpername = iter.getNextKey();
				ORBClassHelper* helper = remove(helpername);
				
				helper->finalizeHelper();
			}
		}
		
	};
	
  } // namespace ORB
} // namespace engine

using namespace engine::ORB;	

#endif /*ORBCLASSHELPERMAP_H_*/
