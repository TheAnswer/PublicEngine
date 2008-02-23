/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ORBOBJECTSERVANT_H_
#define ORBOBJECTSERVANT_H_

#include "../../../system/lang.h"

#include "ORBClassHelper.h"

namespace engine {
  namespace ORB {
  	
  	class ORBObjectStub;
  	
	class ORBObjectServant {
	protected:
		ORBClassHelper* _classHelper;
		
		ORBObjectStub* _stub;
		
	public:
		ORBObjectServant();
		
		virtual ~ORBObjectServant();

		ORBObject* deploy();
		ORBObject* deploy(const char* name);
		ORBObject* deploy(const string& name);
		ORBObject* deploy(const string& name, sys::uint64 nid);

		// setters
		virtual void _setStub(ORBObjectStub* stub) = 0;
		
		inline void _setClassHelper(ORBClassHelper* helper) {
			_classHelper = helper;
		}

		// getters
		virtual ORBObjectStub* _getStub() = 0;

		inline ORBClassHelper* _getClassHelper() {
			return _classHelper;
		}	
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*ORBOBJECTSERVANT_H_*/
