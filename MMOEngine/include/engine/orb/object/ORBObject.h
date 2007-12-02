/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ORBOBJECT_H_
#define ORBOBJECT_H_

#include "../../../system/lang.h"

namespace engine {
  namespace ORB {

	class ORBClient;
	
	class ORBObjectAdapter;
	class ORBObjectStub;
	
	class ORBObject {
	protected:
		string _orbClassName;
		string _orbName;
		
		uint64 _orbObjectID;
		
		ORBClient* _orbClient;
			
	public:
		ORBObject();
	
		// setters
		inline void _setORBClassName(const string& n) {
			_orbClassName = n;
		}
		
		inline void _setORBName(const string& n) {
			_orbName = n;
		}
	
		inline void _setORBObjectID(uint64 id) {
			_orbObjectID = id;	
		}
	
		inline void _setORBClient(ORBClient* cl) {
			_orbClient = cl;
		}
	
		// getters
		inline const string& _getORBClassName() {
			return _orbClassName;
		}
	
		inline const string& _getORBName() {
			return _orbName;
		}	
		
		inline uint64 _getORBObjectID() {
			return _orbObjectID;
		}
		
		inline ORBClient* _getORBClient() {
			return _orbClient;
		}
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*ORBOBJECT_H_*/
