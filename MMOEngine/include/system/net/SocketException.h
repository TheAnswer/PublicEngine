/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef SOCKETEXCEPTION_H_
#define SOCKETEXCEPTION_H_

#include "../lang/Exception.h"

namespace sys {
  namespace net {

	class SocketException : public sys::lang::Exception {
	public:
		SocketException() : Exception() {
		}

		SocketException(string msg) : Exception(msg) {
		}
		
	};

  } // namespace net
} // namespace sys

using namespace sys::net;

#endif /*SOCKETEXCEPTION_H_*/
