/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef OBJECT_H_
#define OBJECT_H_

namespace sys {
  namespace lang {

	class Object {
		int references;
		
	public:
		Object() {
			references = 1;
		}
		
		inline void acquireObject() {
			++references;
		}
		
		inline void releaseObject() {
			if (--references == 0)
				delete this;
		}
		
		inline int getReferences() {
			return references;
		}
		
	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;

#endif /*OBJECT_H_*/
