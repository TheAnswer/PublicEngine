/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef STREAM_H_
#define STREAM_H_

#include "../platform.h"

#include "../util/Vector.h"

#include "StreamIndexOutOfBoundsException.h"

namespace sys {
  namespace io {

	class Stream : public Vector<char> {
	protected:
		char *end, *offset;
		
	public:
		Stream() : Vector<char>() {
			end = offset = elementData;
		}
	
		Stream(int initsize) : Vector<char>(initsize) {
			end = offset = elementData;
		}

		Stream(int initsize, int capincr) : Vector<char>(initsize, capincr) {
			end = offset = elementData;
		}

		Stream(char *buf[], int len) : Vector<char>(len) {
			offset = elementData;
			end = elementData + len;

			memcpy(elementData, buf, len);
		}
	
		virtual ~Stream() {
			end = offset = NULL;
		}

		Stream* clone(int startoffs = 0) {
			int newSize = size() - startoffs;
			Stream* stream = new Stream(newSize);

			stream->writeStream(elementData + startoffs, newSize);
	
			return stream;		
		}
	
		void copy(Stream* stream, int startoffs = 0) {
			int newSize = size() - startoffs;
	
			stream->reset();
			stream->writeStream(elementData + startoffs, newSize);
		}
	
		void setSize(int len, bool copyContent = true) {
			char* oldElementData = elementData;
			Vector<char>::setSize(len, copyContent);
			
			if (oldElementData != elementData)
				offset = (offset - oldElementData) + elementData;
			
			end = elementData + len;
		}
	
		void extendSize(int len, bool copyContent = true) {
			if ((offset += len) > end) {
				char* oldElementData = elementData;
				Vector<char>::setSize(offset - elementData);
		
				if (oldElementData != elementData)
					offset = (offset - oldElementData) + elementData;
		
				end = offset;
			}
		}
	
		inline void setOffset(int offs) {
			if ((offset = elementData + offs) > end)
				throw StreamIndexOutOfBoundsException(this, offs);
		}
	
		inline void shiftOffset(int offs) {
			if ((offset += offs) > end)
				throw StreamIndexOutOfBoundsException(this, offset - elementData);
		}
	
		void clear() {
			Vector<char>::setSize(0);
			 
			end = offset = elementData;
		}
	
		void reset() {
			offset = elementData;
		}
	
		void removeLastBytes(int len) {
			int newSize = size() - len;
			if (newSize < 0)
				throw StreamIndexOutOfBoundsException(this, newSize);

			setSize(newSize);
		}

		// stream manipulation methods
		void writeStream(const char *buf, int len) {
			extendSize(len);

			memcpy(offset - len, buf, len);
		}

		void writeStream(Stream* stream) {
			writeStream(stream->getBuffer(), stream->size());
		}

		void writeStream(Stream* stream, int len) {
			if (len > stream->size())
				throw StreamIndexOutOfBoundsException(stream, len);

			writeStream(stream->getBuffer(), len);
		}

		inline void readStream(char *buf, int len) {
			shiftOffset(len);

			memcpy(buf, offset - len, len);
		}

		inline void readStream(Stream* stream, int len) {
			stream->setSize(len);

			readStream(stream->getBuffer(), stream->size());
		}

		// getters
		inline int getOffset() {
			return offset - elementData;
		}
	
		inline bool hasData() {
			return offset < end;
		}
	
		inline char* getBuffer() {
			return elementData;
		}
		
		inline int size() {
			return end - elementData;
		}
		
	};

  } // namespace io
} // namespace sys

using namespace sys::io;

#endif /*STREAM_H_*/
