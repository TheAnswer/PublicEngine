/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef PACKET_H_
#define PACKET_H_

#include "../platform.h"

#ifndef PLATFORM_WIN
#include <arpa/inet.h>
#else
#include <winsock2.h>
#endif

#include "../util/Vector.h"

#include "PacketIndexOutOfBoundsException.h"

namespace sys {
  namespace net {

	class Packet : public Vector<char> {
	public:
		static const int RAW_MAX_SIZE = 496;
	
	private:
		char *end, *offset;
		
	public:
		Packet() : Vector<char>(RAW_MAX_SIZE, RAW_MAX_SIZE) {
			end = offset = elementData;
		}
	
		Packet(int size) : Vector<char>(size, RAW_MAX_SIZE) {
			end = offset = elementData;
		}
	
		void create(char *buf[], int len);
	
		Packet* clone(int startoffs = 0);
	
		void copy(Packet* pack, int startoffs = 0);
	
		void setSize(int len, bool copyContent = true);
	
		void extendSize(int len, bool copyContent = true);
	
		void clear();
	
		void reset();
	
		// inserting methods
		inline void insertBoolean(bool val) {
			extendSize(1);
			*(uint8*)(offset-1) = val;
		}

		inline void insertByte(uint8 val) {
			extendSize(1);
			*(uint8*)(offset-1) = val;
		}
	
		inline void insertByte(int offs, uint8 val) {
			char* elementOffset = elementData + offs;
			if (elementOffset + 1 > end)
				throw PacketIndexOutOfBoundsException(this, offs); 
			
			*(uint8*)elementOffset = val;
		}

		inline void insertSignedByte(int8 val) {
			extendSize(1);
	
			*(int8*)(offset-1) = val;
		}
	
		inline void insertShort(uint16 val) {
			extendSize(2);
	
			*(uint16*)(offset-2) = val;
		}
	
		inline void insertSignedShort(int16 val) {
			extendSize(2);
	
			*(int16*)(offset-2) = val;
		}
	
		inline void insertShortNet(uint16 val) {
			extendSize(2);
	
			*(uint16*)(offset-2) = htons(val);
		}
	
		inline void insertShort(int offs, uint16 val) {
			char* elementOffset = elementData + offs;
			if (elementOffset + 2 > end)
				throw PacketIndexOutOfBoundsException(this, offs); 
	
			*(uint16*)elementOffset = val;
		}
	
		inline void insertInt(uint32 val) {
			extendSize(4);
	
			*(uint32*)(offset-4) = val;
		}
	
		inline void insertInt(int offs, uint32 val) {
			char* elementOffset = elementData + offs;
			if (elementOffset + 4 > end)
				throw PacketIndexOutOfBoundsException(this, offs); 
	
			*(uint32*)elementOffset = val;
		}
	
		inline void insertSignedInt(int32 val) {
			extendSize(4);
	
			*(int32*)(offset-4) = val;
		}
	
		inline void insertIntNet(uint32 val) {
			extendSize(4);
	
			*(uint32*)(offset-4) = htonl(val);
		}
	
		inline void insertLong(uint64 val) {
			extendSize(8);
	
			*(uint64*)(offset-8) = val;
		}
	
		inline void insertLong(int offs, uint64 val) {
			char* elementOffset = elementData + offs;
			if (elementOffset + 8 > end)
				throw PacketIndexOutOfBoundsException(this, offs); 
	
			*(uint64*)(elementOffset + offs) = val;
		}

		inline void insertSignedLong(int64 val) {
			extendSize(8);
	
			*(int64*)(offset-8) = val;
		}
	
		inline void insertFloat(float val) {
			extendSize(4);
	
			*(float*)(offset-4) = val;
		}
	
		void insertAscii(const char *ascii) {
			int len = strlen(ascii);
			
			insertShort(len);
			insertStream(ascii, len);
		}
	
		void insertAscii(char *ascii, int len) {
			insertShort(len);
			insertStream(ascii, len);
		}
	
		void insertAscii(const string& ascii) {
			int len = ascii.size();
			insertShort(len);
			
			insertStream(ascii.c_str(), len);
		}
	
		void insertUnicode(unicode& str) {
			int len = str.size();
			insertInt(len);
			
			insertStream(str.u_str(), len * 2);
		}
	
		void insertStream(const char *buf, int len) {
			extendSize(len);
			
			memcpy(offset - len, buf, len);
		}
	
		// parsing methods
		inline bool parseBoolean() {
			shiftOffset(1);
	
			return *(uint8*)(offset-1);
		}

		inline uint8 parseByte() {
			shiftOffset(1);
	
			return *(uint8*)(offset-1);
		}
	
		inline uint8 parseByte(int offs) {
			char* elementOffset = elementData + offs;
			if (elementOffset + 1 > end)
				throw PacketIndexOutOfBoundsException(this, offs + 1); 
	
			return *(uint8*)(elementOffset);
		}

		inline int8 parseSignedByte() {
			shiftOffset(1);
	
			return *(int8*)(offset-1);
		}
	
		inline int8 parseSignedByte(int offs) {
			char* elementOffset = elementData + offs;
			if (elementOffset + 1 > end)
				throw PacketIndexOutOfBoundsException(this, offs + 1); 
	
			return *(int8*)(elementOffset);
		}
	
		inline uint16 parseShort() {
			shiftOffset(2);
			
			return *(uint16*)(offset-2);
		}

		inline int16 parseSignedShort() {
			shiftOffset(2);
			
			return *(int16*)(offset-2);
		}

		inline uint16 parseNetShort() {
			shiftOffset(2);
			
			return ntohs(*(uint16*)(offset-2));
		}
	
		inline uint16 parseShort(int offs) {
			char* elementOffset = elementData + offs;
			if (elementOffset + 2 > end)
				throw PacketIndexOutOfBoundsException(this, offs + 2); 
	
			return *(uint16*)(elementOffset);
		}
	
		inline uint16 parseNetShort(int offs) {
			char* elementOffset = elementData + offs;
			if (elementOffset + 2 > end)
				throw PacketIndexOutOfBoundsException(this, offs + 2); 
	
			return ntohs(*(uint16*)(elementOffset));
		}
		
		inline uint32 parseInt() {
			shiftOffset(4);
	
			return *(uint32*)(offset-4);
		}
	
		inline uint32 parseInt(int offs) {
			char* elementOffset = elementData + offs;
			if (elementOffset + 4 > end)
				throw PacketIndexOutOfBoundsException(this, offs + 4); 
	
			return *(uint32*)(elementOffset);
		}
	
		inline int32 parseSignedInt() {
			shiftOffset(4);
	
			return *(int32*)(offset-4);
		}
	
		inline int32 parseSignedInt(int offs) {
			char* elementOffset = elementData + offs;
			if (elementOffset + 4 > end)
				throw PacketIndexOutOfBoundsException(this, offs + 4); 
	
			return *(int32*)(elementOffset);
		}
	
		inline uint64 parseLong() {
			shiftOffset(8);
	
			return *(uint64*)(offset-8);
		}
	
		inline uint64 parseLong(int offs) {
			char* elementOffset = elementData + offs;
			if (elementOffset + 8 > end)
				throw PacketIndexOutOfBoundsException(this, offs + 8); 
	
			return *(uint64*)(elementOffset);
		}

		inline int64 parseSignedLong() {
			shiftOffset(8);
	
			return *(int64*)(offset-8);
		}
	
		inline int64 parseSignedLong(int offs) {
			char* elementOffset = elementData + offs;
			if (elementOffset + 8 > end)
				throw PacketIndexOutOfBoundsException(this, offs + 8); 
	
			return *(int64*)(elementOffset);
		}
	
		inline float parseFloat() {
			shiftOffset(4);
	
			return *(float*)(offset-4);
		}
	
		inline float parseFloat(int offs) {
			char* elementOffset = elementData + offs;
			if (elementOffset + 4 > end)
				throw PacketIndexOutOfBoundsException(this, offs + 4); 
	
			return *(float*)(elementOffset);
		}
	
		inline int parseAscii(char *ascii) {
			uint16 len = parseShort();
			parseStream(ascii, (int) len);
	
			ascii[len] = 0;
			return len;
		}
	
		inline void parseAscii(string& ascii) {
			uint32 len = parseShort();
			shiftOffset(len);
	
			ascii.clear();
			ascii.append(offset - len, len);
		}

		inline void parseAscii(int offs, string& ascii) {
			uint32 len = parseShort(offs);
	
			char* elementOffset = elementData + offs + 2;
			if (elementOffset > end)
				throw PacketIndexOutOfBoundsException(this, offs + 2); 
	
			ascii.clear();
			ascii.append(elementOffset - len, len);
		}
	
		inline void parseUnicode(unicode& str) {
			uint32 len = parseInt();
			shiftOffset(len * 2);
	
			str.clear();
			str.append((wchar_t*) (offset - len * 2), len);
		}

		inline void parseUnicode(int offs, unicode& str) {
			uint32 len = parseInt(offs);

			char* elementOffset = elementData + offs + 4;
			if (elementOffset > end)
				throw PacketIndexOutOfBoundsException(this, offs + 4); 
	
			str.clear();
			str.append((wchar_t*) (elementOffset - len * 2), len);
		}
	
		inline void parseStream(char *buf, int len) {
			shiftOffset(len);
	
			memcpy(buf, offset - len, len);
		}
	
		inline void setOffset(int offs) {
			if ((offset = elementData + offs) > end)
				throw PacketIndexOutOfBoundsException(this, offs);
		}
		
		inline void shiftOffset(int offs) {
			if ((offset += offs) > end)
				throw PacketIndexOutOfBoundsException(this, offset - elementData);
		}

		void removeLastBytes(int len);

		string toString();

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

  } // namespace net
} // namespace sys

using namespace sys::net;

#endif /*PACKET_H_*/
