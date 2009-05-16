#ifndef DIVISIONBYZEROEXCEPTION_H_
#define DIVISIONBYZEROEXCEPTION_H_

#include "Exception.h"

namespace sys {
  namespace lang {

	class DivisionByZeroException : public Exception {
	public:
		DivisionByZeroException() : Exception("DivisionByZeroException") {
		}
	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;

#endif /*DIVISIONBYZEROEXCEPTION_H_*/
