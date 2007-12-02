/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef THREAD_H_
#define THREAD_H_

#include "../platform.h"

#include <pthread.h>

namespace sys {
  namespace thread {

	/*! 
	 * thread wrapper class. the inheriting classes must implement a run() method that have to contain the code to be executed
	 */
	class Thread {
		pthread_t thread;
	
		static void* execute_thread(void* th) {
			Thread* impl = (Thread*) th;
			impl->run();
	
			return NULL;
		}
	
	public:
		//! allocates a new Thread
		Thread() { }
	
		//! causes this thread to begin execution
		void start() {
			pthread_create(&thread, NULL, execute_thread, this);
		}
	
		//! causes this thread to be cancelled
		void cancel() {
			pthread_cancel(thread);
		}
	
		//! causes the calling thread to be waiting until this thread finishes
		void join() {
			pthread_join(thread, NULL);
		}
	
	#ifndef PLATFORM_WIN
		static void sleepMili(uint64 time) {
			struct timespec tm, trem;
	
			tm.tv_sec  = time / 1000;
			tm.tv_nsec = (time % 1000) * 1000000;
	
		  	nanosleep(&tm, &trem);
		}
	
		static void sleepMikro(uint64 time) {
			struct timespec tm, trem;
	
			//tm.tv_sec  = time / 1000000;
			//tm.tv_nsec = (time % 1000000) * 1000;
	
			tm.tv_sec  = 0;
			tm.tv_nsec = 10;
	
		  	nanosleep(&tm, &trem);
		}
	#endif

		//! this method is called when the thread starts
		virtual void run() = 0;
	};

  } // namespace thread
} //namespace sys

using namespace sys::thread;

#endif /*THREAD_H_*/
