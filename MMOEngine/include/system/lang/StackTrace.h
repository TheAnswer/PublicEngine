/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef STACKTRACE_H_
#define STACKTRACE_H_

#include "../platform.h"

#ifdef PLATFORM_UNIX
	#include <execinfo.h>
#elif defined PLATFORM_CYGWIN
	extern "C" void cygwin_stackdump(void);
#endif

namespace sys {
  namespace lang {
		
	class StackTrace {
		char** symbols;
	
		int count;
	
	public:
		StackTrace();
		
		~StackTrace();
		
		void print();
	
		static void printStackTrace();	
		
	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;

#endif /*STACKTRACE_H_*/
