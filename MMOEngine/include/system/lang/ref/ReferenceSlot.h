/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef REFERENCESLOT_H_
#define REFERENCESLOT_H_

#include "../Object.h"

namespace sys {
  namespace lang {

	template<class O> class ReferenceSlot {
	protected:
		O* object;

	public:
		ReferenceSlot() {
			object = NULL;
		}

		ReferenceSlot(const ReferenceSlot& refslot) {
			setObject(refslot.object);
		}

		ReferenceSlot(O* obj) {
			setObject(obj);
		}

		virtual ~ReferenceSlot() {
			releaseObject();
		}

		void operator=(const ReferenceSlot& refslot) {
			setObject(refslot.object);
		}

		void operator=(O* obj) {
			releaseObject();

			setObject(obj);
		}

		O* operator->() {
			return object;
		}

		operator O*() {
			return object;
		}

		inline O* get() {
			return object;
		}
		
	protected:
		inline void setObject(O* obj) {
			if (obj != object)
				object = obj;
			else
				return;

			acquireObject();
		}

		inline void acquireObject() {
			if (object != NULL)
				object->acquire();
		}

		inline void releaseObject() {
			if (object != NULL) {
				object->release();
				object = NULL;
			}
		}

	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;

#endif /*REFERENCESLOT_H_*/
