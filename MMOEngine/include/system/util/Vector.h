/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef VECTOR_H_
#define VECTOR_H_

#include "../platform.h"

#include "../lang/types.h"

#include "../lang/ArrayIndexOutOfBoundsException.h"

namespace sys {
  namespace util {

	template<class E> class Vector {
	protected:
		E* elementData;
		
		int elementCapacity, capacityIncrement;
		int elementCount;
	
	public:
		Vector() {
			init(10, 5);
		}
		
		Vector(int incr) {
			init(10, incr);
		}
		
		Vector(int initsize, int incr) {
			init(initsize, incr);
		}
	
		virtual ~Vector() {
			delete [] elementData;
		}
	
	    bool add(const E& o);
	    void add(int index, const E& element);
	
	    E& set(int index, const E& element);
	
	    E& get(int index);
	
	    E remove(int index);

	    bool removeElement(const E& o);

		void removeAll();

		void clone(Vector<E>& vector);

		Vector<E>& operator=(Vector<E>& vector);
	
		void setSize(int newSize, bool doCopyContent = true);
	
	protected:
		void init(int initsize, int incr);
		
		void ensureCapacity(int minCapacity, bool doCopyContent = true);

	    void insertElementAt(const E& obj, int index);
	
	public:
		inline int size() {
			return elementCount;
		}
	
	    inline int capacity() {
			return elementCapacity;
	    }
	    
	    inline bool isEmpty() {
			return elementCount == 0;
	    }
	
	};
	
	template<class E> void Vector<E>::init(int initsize, int incr) {
		elementCapacity = initsize;
		elementData = new E[elementCapacity];
	
		elementCount = 0;
		capacityIncrement = incr;
	}
		
	template<class E> void Vector<E>::ensureCapacity(int minCapacity, bool doCopyContent) {
		int oldCapacity = elementCapacity;
			
		if (minCapacity > oldCapacity) {
	    	E* oldData = elementData;
	
	    	int newCapacity = (capacityIncrement > 0) ?
				(oldCapacity + capacityIncrement) : (oldCapacity * 2);
	
	   	    if (newCapacity < minCapacity) {
				newCapacity = minCapacity;
	    	}
		    	
	    	elementData = new E[elementCapacity = newCapacity];
		    	
	    	if (doCopyContent) {
	    		if (TypeInfo<E>::needConstructor) {
	    			for (int i = 0; i < elementCount; ++i)
	    				elementData[i] = oldData[i];
	    		} else
	    			memcpy(elementData, oldData, elementCount * sizeof(E));
	    	}
				
			delete [] oldData;
		}
	}
		
	template<class E> void Vector<E>::setSize(int newSize, bool doCopyContent) {
		if (newSize > elementCount)
	    	ensureCapacity(newSize, doCopyContent);
				
		elementCount = newSize;
	}
	
	template<class E> void Vector<E>::insertElementAt(const E& obj, int index) {
		if (index > elementCount || index < 0) {
	    	throw ArrayIndexOutOfBoundsException(index);
		}
		
		ensureCapacity(elementCount + 1);
		
		if (TypeInfo<E>::needConstructor) {
			for (int i = elementCount - 1; i >= index ; --i)
				elementData[i + 1] = elementData[i];
		} else {
			E* indexOffset = elementData + index;
			memmove(indexOffset + 1, indexOffset, (elementCount - index) * sizeof(E));
		}
		
		elementData[index] = obj;
		elementCount++;
	}
	
	template<class E> bool Vector<E>::add(const E& o) {
		ensureCapacity(elementCount + 1);
		elementData[elementCount++] = o;
			
		return true;
	}
	
	template<class E> void Vector<E>::add(int index, const E& element) {
		insertElementAt(element, index);
	}
	
	template<class E> E& Vector<E>::set(int index, const E& element) {
		if (index >= elementCount || index < 0)
		    throw ArrayIndexOutOfBoundsException(index);
	
		E& oldValue = elementData[index];
		elementData[index] = element;
			
		return oldValue;
	}
	
	template<class E> E& Vector<E>::get(int index) {
		if (index >= elementCount || index < 0)
		    throw ArrayIndexOutOfBoundsException(index);
	
		return elementData[index];
	}
	
	template<class E> E Vector<E>::remove(int index) {
		if (index >= elementCount || index < 0)
	    	throw ArrayIndexOutOfBoundsException(index);
	
		E oldValue = elementData[index];
	
		int numMoved = elementCount - index - 1;
		if (numMoved > 0) {
			if (TypeInfo<E>::needConstructor) {
				for (int i = 0; i < numMoved; ++i)
					elementData[i] = elementData[i + 1];
			} else {
				E* indexOffset = elementData + index;
				memcpy(indexOffset, indexOffset + 1, numMoved * sizeof(E));
			}
		}
			
		--elementCount;
		return oldValue;
	}

	template<class E> bool Vector<E>::removeElement(const E& o) {
		for (int i = 0; i < elementCount; ++i) {
			if (elementData[i] == o) {
				remove(i);
				return true;
			}
		}

		return false;
	}

	template<class E> void Vector<E>::removeAll() {
		delete [] elementData;
			
		init(10, 5);
	}

	template<class E> void Vector<E>::clone(Vector<E>& vector) {
		vector.removeAll();
		vector.init(elementCapacity, capacityIncrement);

		vector.elementCount = elementCount;

		if (TypeInfo<E>::needConstructor) {
			for (int i = 0; i < elementCount; ++i)
				vector.elementData[i] = elementData[i];
		} else
			memcpy(vector.elementData, elementData, elementCount * sizeof(E));
	}

	template<class E> Vector<E>& Vector<E>::operator=(Vector<E>& vector) {
		clone(vector);

		return vector;
	}
	
  } // namespace util
} // namespace sys

using namespace sys::util;

#endif /*VECTOR_H_*/
