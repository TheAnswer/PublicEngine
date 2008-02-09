/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef THREAD_H_
#define THREAD_H_

#include "../platform.h"

#include <pthread.h>
#include <signal.h>

namespace sys {
  namespace thread {

	/*! 
	 * thread wrapper class. the inheriting classes must implement a run() method that have to contain the code to be executed
	 */
	class Thread {
		pthread_t thread;
		pthread_attr_t attributes;
		
		static void* execute_thread(void* th) {
			Thread* impl = (Thread*) th;
			impl->run();
	
			if (impl->isDetached())
				delete impl;
			
			return NULL;
		}
	
	public:
		//! allocates a new Thread
		Thread() { 
			pthread_attr_init(&attributes);
		}
	
		virtual ~Thread() {
		}

		//! this method is called when the thread starts
		virtual void run() = 0;

		//! causes this thread to begin execution
		void start() {
			pthread_create(&thread, &attributes, execute_thread, this);
		}
	
		void kill(int signal = SIGINT) {
			pthread_kill(thread, signal);
		}
		
		//! causes this thread to be cancelled
		void cancel() {
			pthread_cancel(thread);
		}
	
		//! causes the calling thread to be waiting until this thread finishes
		void join() {
			if (isDetached())
				setJoinable();
			
			pthread_join(thread, NULL);
		}

		void detach() {
			pthread_detach(thread);
		}

		static void sleepMili(uint64 time) {
			#ifndef PLATFORM_WIN
				struct timespec tm, trem;
	
				tm.tv_sec  = time / 1000;
				tm.tv_nsec = (time % 1000) * 1000000;
	
				nanosleep(&tm, &trem);
			#endif
		}
	
		static void sleepMikro(uint64 time) {
			#ifndef PLATFORM_WIN
				struct timespec tm, trem;
	
				//tm.tv_sec  = time / 1000000;
				//tm.tv_nsec = (time % 1000000) * 1000;
	
				tm.tv_sec  = 0;
				tm.tv_nsec = 10;
	
				nanosleep(&tm, &trem);
			#endif
		}

		// setters
		inline void setDetached() {
			pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_DETACHED);
		}

		inline void setJoinable() {
			pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_JOINABLE);
		}

		// getters
		inline bool isDetached() {
			int state;
			pthread_attr_getdetachstate(&attributes, &state);

			return state == PTHREAD_CREATE_DETACHED;
		}

		inline uint32 getCurrentThreadID() {
			#ifndef PLATFORM_WIN
				return 0;
			#else
				return GetCurrentThreadId();
			#endif
		}
	
	};

  } // namespace thread
} //namespace sys

using namespace sys::thread;

#endif /*THREAD_H_*/
