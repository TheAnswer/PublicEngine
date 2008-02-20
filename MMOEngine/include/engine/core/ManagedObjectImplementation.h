/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef MANAGEDOBJECTIMPLEMENTATION_H_
#define MANAGEDOBJECTIMPLEMENTATION_H_

#include "thread/RWLockable.h"

#include "ManagedObject.h"

class ManagedObjectImplementation : public ManagedObjectServant {
public:
	void lock(bool doLock = true) {
		wlock(doLock);
	}

	void lock(ManagedObject* obj) {
		wlock(obj);
	}
	
};

#endif /*MANAGEDOBJECTIMPLEMENTATION_H_*/
