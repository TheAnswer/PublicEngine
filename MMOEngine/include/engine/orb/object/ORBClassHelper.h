/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ORBCLASSHELPER_H_
#define ORBCLASSHELPER_H_

#include "ORBObject.h"
#include "ORBObjectAdapter.h"

namespace engine {
  namespace ORB {

	class ORBObjectServant;
	
	class ORBClassHelper {
	protected:
		string className;
		
	public:
		ORBClassHelper() {
		}
		
		virtual ~ORBClassHelper() {
		}	
	
		virtual void finalizeHelper() = 0;
		
		virtual ORBObject* instantiateObject() = 0;
	
		virtual ORBObjectAdapter* createAdapter(ORBObjectServant* obj) = 0;
		
		inline const string& getClassName() {
			return className;
		}
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*ORBCLASSHELPER_H_*/
