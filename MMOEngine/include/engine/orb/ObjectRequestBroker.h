/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef OBJECTREQUESTBROKER_H_
#define OBJECTREQUESTBROKER_H_

#include "../../system/lang.h"

#include "../service/StreamServiceThread.h"

#include "ORBObjectDirectory.h"

#include "ORBNamingDirectoryService.h"

#include "ORBClient.h"

#include "ORBPacketHandler.h"

#include "object/ORBObject.h"
#include "object/ORBObjectStub.h"
#include "object/ORBObjectServant.h"
#include "object/ORBObjectAdapter.h"

#include "object/ORBClassHelper.h"
#include "object/ORBClassHelperMap.h"

#include "object/ORBMethodInvocation.h"

#include "object/ObjectNotDeployedException.h"

#include "packets/DeployObjectMessage.h"
#include "packets/MethodReturnMessage.h"

namespace engine {
  namespace ORB {

	class ObjectRequestBroker : public StreamServiceThread {
		static ObjectRequestBroker* impl;
	
		string address;
		ORBNamingDirectoryService* namingDirectoryInterface;
		
		ORBClassHelperMap classMap;
	
		ORBObjectDirectory objectDirectory;
	
		ORBPacketHandler* phandler;
		
	private:
		ObjectRequestBroker();
	
		~ObjectRequestBroker();

	public:
		static ObjectRequestBroker* initialize(const string& addr, int port = 44433);
		
		void init();
	
		void run();
	
		ORBClient* createConnection(Socket* sock, SocketAddress& addr);
		
		void registerClass(const string& name, ORBClassHelper* helper);
	
		// deployment methods
		ORBObject* deploy(const string& name, ORBObjectServant* obj);
		
		ORBObject* lookUp(const string& name);
		ORBObject* lookUp(uint64 objid);
		
		ORBObjectStub* undeploy(const string& name);
		
		// getters
		ORBObjectAdapter* getObjectAdapter(const string& name);
		ORBObjectAdapter* getObjectAdapter(uint64 oid);
		
		static ObjectRequestBroker* instance();
		
		inline bool hasRootDirectory() {
			return namingDirectoryInterface->isRootDirectory();
		}
		
		inline ORBPacketHandler* getPacketHandler() {
			return phandler;
		}
		
		friend class ORBNamingDirectoryService;
			
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*OBJECTREQUESTBROKER_H_*/
