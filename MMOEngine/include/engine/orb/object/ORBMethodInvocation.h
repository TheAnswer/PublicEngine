/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ORBMETHODINVOCATION_H_
#define ORBMETHODINVOCATION_H_

#include "../../../system/lang.h"

namespace engine {
  namespace ORB {

	class ObjectRequestBroker;
	class ORBObject;
	
	class ORBMethodInvocation {
		ORBObject* object;
		
		sys::uint32 methodID;
		sys::uint32 invocationID;
		
		ObjectRequestBroker* orb;
		Packet* invmsg;
		
	public:
		ORBMethodInvocation(ORBObject* obj, sys::uint32 methid);
		ORBMethodInvocation(ObjectRequestBroker* broker, Packet* pack);
		
		// exeuctor methods
		void executeWithVoidReturn();

		bool executeWithBooleanReturn();
		
		char executeWithSignedCharReturn();
		unsigned char executeWithUnsignedCharReturn();

		int executeWithSignedIntReturn();
		unsigned int executeWithUnsignedIntReturn();
		
		long long executeWithSignedLongReturn();
		unsigned long long executeWithUnsignedLongReturn();

		float executeWithFloatReturn();

		void executeWithAsciiReturn(string& value);
		void executeWithUnicodeReturn(unicode& value);
		
		ORBObject* executeWithObjectReturn();
		
		// parameter insertion methods
		void addBooleanParameter(bool val);

		void addSignedCharParameter(char val);
		void addUnsignedCharParameter(unsigned char val);

		void addSignedIntParameter(int val);
		void addUnsignedIntParameter(unsigned int val);
		
		void addSignedLongParameter(long long val);
		void addUnsignedLongParameter(unsigned long long val);

		void addFloatParameter(float val);

		void addAsciiParameter(const string& ascii);
		void addUnicodeParameter(unicode& str);

		void addObjectParameter(ORBObject* obj);
	
		// parameter reader methods
		bool getBooleanParameter();

		int getSignedIntParameter();
		unsigned int getUnsignedIntParameter();

		char getSignedCharParameter();
		unsigned char getUnsignedCharParameter();
		
		long long getSignedLongParameter();
		unsigned long long getUnsignedLongParameter();

		float getFloatParameter();

		string& getAsciiParameter(string& ascii);
		unicode& getUnicodeParameter(unicode& str);
		
		ORBObject* getObjectParameter();
	
	private:
		void execute();
		
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*ORBMETHODINVOCATION_H_*/
