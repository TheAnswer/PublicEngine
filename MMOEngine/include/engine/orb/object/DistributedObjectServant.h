/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef DISTRIBUTEDOBJECTSERVANT_H_
#define DISTRIBUTEDOBJECTSERVANT_H_

#include "system/lang.h"

namespace engine {
  namespace ORB {
  	
  	class DistributedObjectStub;

  	class DistributedObjectClassHelper;

	class DistributedObjectServant {
	protected:
		DistributedObjectClassHelper* _classHelper;
		
		DistributedObjectStub* _stub;
		
	public:
		DistributedObjectServant();
		
		virtual ~DistributedObjectServant();

		DistributedObject* deploy();
		DistributedObject* deploy(const char* name);
		DistributedObject* deploy(const string& name);
		DistributedObject* deploy(const string& name, sys::uint64 nid);

		// setters
		virtual void _setStub(DistributedObjectStub* stub) = 0;
		
		inline void _setClassHelper(DistributedObjectClassHelper* helper) {
			_classHelper = helper;
		}

		// getters
		virtual DistributedObjectStub* _getStub() = 0;

		inline DistributedObjectClassHelper* _getClassHelper() {
			return _classHelper;
		}	
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*DISTRIBUTEDOBJECTSERVANT_H_*/
