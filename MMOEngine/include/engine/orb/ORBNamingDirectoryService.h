/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ORBNAMINGDIRECTORYSERVICE_H_
#define ORBNAMINGDIRECTORYSERVICE_H_

#include "ORBClient.h"

#include "object/ORBObject.h"
#include "object/ORBObjectNameMap.h"

#include "object/ORBClassHelperMap.h"

namespace engine {
  namespace ORB {

	class ObjectRequestBroker;
	
	class ORBNamingDirectoryService {
		ORBClient* rootNamingDirectory;
		
		ORBObjectNameMap objectNameMap;
		ORBClassHelperMap* classMap;
	
		uint64 nextObjectID;
		
	public:
		ORBNamingDirectoryService(ObjectRequestBroker* broker);
		ORBNamingDirectoryService(ObjectRequestBroker* broker, const string& address);
	
		void deploy(ORBObjectStub* stub);
		void deploy(const string& name, ORBObjectStub* stub);
	
		ORBObject* lookUp(const string& name);
		
		ORBObject* undeploy(const string& name);
		
		inline bool isRootDirectory() {
			return rootNamingDirectory == NULL;
		}
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*ORBNAMINGDIRECTORYSERVICE_H_*/
