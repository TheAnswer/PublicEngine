/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef OBJECT_H_
#define OBJECT_H_

#include "ref/ReferenceCounter.h"

namespace sys {
  namespace lang {

	class Object : public ReferenceCounter {
	public:
		Object() : ReferenceCounter() {
			initializeCount();
		}
		
		virtual ~Object() {
		}

		virtual void finalize() {
			release();
		}
		
		inline void acquire() {
			increaseCount();
		}
		
		inline void release() {
			if (decreaseCount())
				delete this;
		}
		
	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;

#endif /*OBJECT_H_*/
