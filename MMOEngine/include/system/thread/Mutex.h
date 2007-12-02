/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef MUTEX_H_
#define MUTEX_H_

#include "../platform.h"

#include <pthread.h>

#include "../lang/StackTrace.h"

namespace sys {
  namespace thread {

	class ReadWriteLock;
	
	class Mutex {
		pthread_mutex_t mutex;
	
		bool doLog;
		string lockName;
			
		int lockCount;
		int currentCount;
	
		StackTrace* trace;
		Time lockTime;
	
	public:
		Mutex() {
			//mutex = PTHREAD_MUTEX_INITIALIZER;
			pthread_mutex_init(&mutex, NULL);
				
			doLog = true;
			lockName = "Mutex";
	
			lockCount = 0;
			
			trace = NULL;
		}
	
		Mutex(const string& s) {
			//mutex = PTHREAD_MUTEX_INITIALIZER;
			pthread_mutex_init(&mutex, NULL);
				
			doLog = true;
			lockName = s;
	
			lockCount = 0;
			
			trace = NULL;
		}

		void setMutexLogging(bool dolog) {
			doLog = dolog;
		}
	
		void setLockName(const string& s) {
			lockName = s;
		}
	
		inline void lock(bool doLock = true) {
			if (!doLock)
				return;
	
			#ifdef LOG_LOCKS
				int cnt = ++lockCount;
	
				if (doLog)
					cout << "(" << Time::currentNanoTime() << " nsec) [" << lockName << "] acquiring lock #" << cnt << "\n";
			#endif
			
			#if !defined(TRACE_LOCKS) || defined(__CYGWIN__)	
				int res = pthread_mutex_lock(&mutex); 
				
				if (res != 0)
					cout << "(" << Time::currentNanoTime() << " nsec) lock() failed on Mutex \'" << lockName << "\' (" << res << ")\n";
			#else
				#ifndef LOG_LOCKS
					int cnt = ++lockCount;
				#endif
			
				Time start;
				start.addMiliTime(2000);
				
		    	while (pthread_mutex_timedlock(&mutex, start.getTimeSpec())) {
	 	  			cout << "(" << Time::currentNanoTime() << " nsec) WARNING" << "[" << lockName << "] unable to access lock #" << cnt << " at\n";
					StackTrace::printStackTrace();
	
					cout << "locked at " << lockTime.getMiliTime() << " by\n";
					trace->print();
	
					while (true);
	
					start.addMiliTime(1000);				
		    	}
	
				lockTime.update();
			
				if (trace != NULL)
					delete trace;
			
				trace = new StackTrace();
			#endif
	
			#ifdef LOG_LOCKS
				currentCount = cnt;
	
				if (doLog)
					cout << "(" << Time::currentNanoTime() << " nsec) [" << lockName << "] acquired lock #" << cnt << "\n";
			#endif
		}
	
		inline void lock(Mutex* m) {
			if (this == m) {
				cout << "(" << Time::currentNanoTime() << " nsec) ERROR: cross locking itself [" << lockName << "]\n";
				
				StackTrace::printStackTrace();
				return;
			}
	
			#ifdef LOG_LOCKS
				int cnt = ++lockCount;
	
				if (doLog)
					cout << "(" << Time::currentNanoTime() << " nsec) [" << lockName << " (" << m->lockName << ")] acquiring cross lock #" << cnt << "\n";
			#endif
	
		    while (pthread_mutex_trylock(&mutex)) {
		    	#ifndef TRACE_LOCKS
		   			pthread_mutex_unlock(&(m->mutex));
			       	pthread_mutex_lock(&(m->mutex));
			  	#else
			  		m->unlock();
			  		m->lock();
			  	#endif
	   		}
	
			#ifdef LOG_LOCKS
				currentCount = cnt;
	
				if (doLog)
					cout << "(" << Time::currentNanoTime() << " nsec) [" << lockName << " (" << m->lockName << ")] acquired cross lock #" << cnt << "\n";
			#endif
		}
	
		inline bool tryLock() {
			return pthread_mutex_trylock(&mutex) == 0;
		}
		
		inline void unlock(bool doLock = true) {
			if (!doLock)
				return;
				
			#ifdef LOG_LOCKS
				if (doLog)
					cout << "(" << Time::currentNanoTime() << " nsec) [" << lockName << "] releasing lock #" << currentCount << "\n";
			#endif
	
			#ifdef TRACE_LOCKS
				delete trace;
				trace = NULL;
			#endif
	
			int res = pthread_mutex_unlock(&mutex);
			if (res != 0) {
				cout << "(" << Time::currentNanoTime() << " nsec) unlock() failed on Mutex \'" << lockName << "\' (" << res << ")\n";
				
				StackTrace::printStackTrace();
			}
			
			#ifdef LOG_LOCKS
				if (doLog)
					cout << "(" << Time::currentNanoTime() << " nsec) [" << lockName << "] released lock #" << currentCount << "\n";
			#endif
		}
	
		friend class Condition;
		friend class ReadWriteLock;
	};

  } // namespace thread
} //namespace sys

using namespace sys::thread;

#endif /*MUTEX_H_*/
