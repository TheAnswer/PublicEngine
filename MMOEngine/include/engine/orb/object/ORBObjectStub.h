/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ORBOBJECTSTUB_H_
#define ORBOBJECTSTUB_H_

#include "ORBObjectServant.h"

namespace engine {
  namespace ORB {

	class ORBObjectStub : public ORBObject {
	protected:
		ORBObjectServant* _impl;
		
		bool deployed;
		
		ORBClassHelper* _classHelper;
		
	#ifdef TRACE_REFERENCING
		Vector<StackTrace*> traces;
		
		StackTrace* finalizedTrace;
	#endif
				
	public:
		ORBObjectStub(ORBObjectServant* obj);
		
		ORBObjectStub(ORBObjectStub& ref);

		virtual ~ORBObjectStub();

		virtual ORBObjectStub* clone();

		// deployment methods
		bool undeploy();

		// reference counting methods
		virtual void finalize();

		virtual void acquire();
	
		virtual void release();
			
		void printReferenceTrace();
		
		// setters
		inline void _setClassHelper(ORBClassHelper* helper) {
			_classHelper = helper;
		}
	
		// getters
		inline bool isDeplyoed() {
			return deployed;
		}
		
		inline ORBObjectServant* _getImplementation() {
			return _impl;
		}
		
		inline ORBClassHelper* _getClassHelper() {
			return _classHelper;
		}	
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*ORBOBJECTSTUB_H_*/
