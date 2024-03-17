/*
muMultithreading.h - Muukid
Public domain simple single-file C library for cross-platform multithreading.
No warranty implied; use at your own risk.

Licensed under MIT License or public domain, whichever you prefer.
More explicit license information at the end of file.

@MENTION All C standard library dependencies are noted BESIDES OS-specific ones
@MENTION Prob have to link against pthread
*/

#ifndef MUM_H
	#define MUM_H
	
	#if !defined(MU_SECURE_WARNINGS) && !defined(_CRT_SECURE_NO_WARNINGS)
		#define _CRT_SECURE_NO_WARNINGS
	#endif
	
	#ifdef __cplusplus
		extern "C" {
	#endif

	#define MUM_VERSION_MAJOR 1
	#define MUM_VERSION_MINOR 0
	#define MUM_VERSION_PATCH 0

	#ifndef MUDEF
		#ifdef MU_STATIC
			#define MUDEF static
		#else
			#define MUDEF extern
		#endif
	#endif

	#ifndef MU_ZERO_STRUCT
		#ifdef __cplusplus
			#define MU_ZERO_STRUCT(s) {}
		#else
			#define MU_ZERO_STRUCT(s) (s){0}
		#endif
	#endif

	#ifndef MU_ZERO_STRUCT_CONST
		#ifdef __cplusplus
			#define MU_ZERO_STRUCT_CONST(s) {}
		#else
			#define MU_ZERO_STRUCT_CONST(s) {0}
		#endif
	#endif

	#ifndef MU_SET_RESULT
		#define MU_SET_RESULT(res, val) if(res!=MU_NULL_PTR){*res=val;}
	#endif

	/* C standard library dependencies */

		#if !defined(muBool)   || \
			!defined(MU_TRUE)  || \
			!defined(MU_FALSE)

			#include <stdbool.h>

			#ifndef muBool
				#define muBool bool
			#endif

			#ifndef MU_TRUE
				#define MU_TRUE true
			#endif

			#ifndef MU_FALSE
				#define MU_FALSE false
			#endif

		#endif

		#if !defined(mu_memcpy)

			#include <string.h>

			#ifndef mu_memcpy
				#define mu_memcpy memcpy
			#endif

		#endif

	/* Enums */

		enum _mumResult {
			MUM_SUCCESS,
			MUM_FAILURE,
			MUM_CREATE_CALL_FAILED,
			MUM_DESTROY_CALL_FAILED,
			MUM_LOCK_CALL_FAILED,
			MUM_UNLOCK_CALL_FAILED,
			MUM_WAIT_CALL_FAILED,
			MUM_INVALID_THREAD,
			MUM_INVALID_MUTEX,
			MUM_PREVIOUS_THREAD_CLOSED_BEFORE_LOCK,
			MUM_THREAD_TIMED_OUT
		};
		typedef enum _mumResult _mumResult;
		#define mumResult size_m

	/* Macros */

		#ifndef MU_NULL_PTR
			#define MU_NULL_PTR 0
		#endif

	/* Operating system */

		#if !defined(MU_WIN32) && !defined(MU_UNIX)
			#if defined(WIN32) || defined(_WIN32)
				#define MU_WIN32
			#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
				#define MU_UNIX
			#endif
		#endif

	/* Structs */

		#if defined(MU_WIN32)

			struct muThread {

			};
			typedef struct muThread muThread;

		#elif defined(MU_UNIX)

			#include <pthread.h>

			/* Thread */

				struct muThread {
					muBool active;
					pthread_t thread;
					void* ret;
				};
				typedef struct muThread muThread;

				muThread mu_inner_thread_destroy(mumResult* result, muThread thread) {
					if (pthread_cancel(thread.thread) != 0) {
						MU_SET_RESULT(result, MUM_DESTROY_CALL_FAILED)
						return thread;
					}
					return MU_ZERO_STRUCT(muThread);
				}

			/* Mutex */

				struct muMutex {
					muBool active;
					pthread_mutex_t mutex;
				};
				typedef struct muMutex muMutex;

				muMutex mu_inner_mutex_destroy(mumResult* result, muMutex mutex) {
					if (pthread_mutex_destroy(&mutex.mutex) != 0) {
						MU_SET_RESULT(result, MUM_DESTROY_CALL_FAILED)
						return mutex;
					}
					return MU_ZERO_STRUCT(muMutex);
				}

			/* Spinlock */

				struct muSpinlock {
					muBool active;
					int locked;
				};
				typedef struct muSpinlock muSpinlock;

				muSpinlock mu_inner_spinlock_destroy(mumResult* result, muSpinlock spinlock) {
					MU_SET_RESULT(result, MUM_SUCCESS)
					if (spinlock.active) {

					}
					return MU_ZERO_STRUCT(muSpinlock);
				}

		#endif

	/* Functions */

		#ifdef MUM_NAMES
			MUDEF const char* mum_result_get_name(mumResult result);
		#endif

		/* Thread */

			MUDEF muThread mu_thread_create(mumResult* result, void (*start)(void* args), void* args);
			MUDEF muThread mu_thread_destroy(mumResult* result, muThread thread);

			MUDEF void mu_thread_exit(void* ret);
			MUDEF void mu_thread_wait(mumResult* result, muThread* p_thread);
			MUDEF void* mu_thread_get_return_value(mumResult* result, muThread thread);

		/* Mutex */

			MUDEF muMutex mu_mutex_create(mumResult* result);
			MUDEF muMutex mu_mutex_destroy(mumResult* result, muMutex mutex);

			MUDEF void mu_mutex_lock(mumResult* result, muMutex* p_mutex);
			MUDEF void mu_mutex_unlock(mumResult* result, muMutex* p_mutex);

		/* Spinlock */

			MUDEF muSpinlock mu_spinlock_create(mumResult* result);
			MUDEF muSpinlock mu_spinlock_destroy(mumResult* result, muSpinlock spinlock);

			MUDEF void mu_spinlock_lock(mumResult* result, muSpinlock* p_spinlock);
			MUDEF void mu_spinlock_unlock(mumResult* result, muSpinlock* p_spinlock);

	#ifdef __cplusplus
		}
	#endif

#endif /* MUM_H */

#ifdef MUM_IMPLEMENTATION

	#ifdef __cplusplus
		extern "C" {
	#endif

	/* Shared API functions */

		#ifdef MUM_NAMES
			MUDEF const char* mum_result_get_name(mumResult result) {
				switch (result) {
					default: return "MUM_UNKNOWN"; break;
					case MUM_SUCCESS: return "MUM_SUCCESS"; break;
					case MUM_CREATE_CALL_FAILED: return "MUM_CREATE_CALL_FAILED"; break;
					case MUM_DESTROY_CALL_FAILED: return "MUM_DESTROY_CALL_FAILED"; break;
					case MUM_LOCK_CALL_FAILED: return "MUM_LOCK_CALL_FAILED"; break;
					case MUM_UNLOCK_CALL_FAILED: return "MUM_UNLOCK_CALL_FAILED"; break;
					case MUM_WAIT_CALL_FAILED: return "MUM_WAIT_CALL_FAILED"; break;
					case MUM_INVALID_THREAD: return "MUM_INVALID_THREAD"; break;
					case MUM_INVALID_MUTEX: return "MUM_INVALID_MUTEX"; break;
					case MUM_PREVIOUS_THREAD_CLOSED_BEFORE_LOCK: return "MUM_PREVIOUS_THREAD_CLOSED_BEFORE_LOCK"; break;
					case MUM_FAILURE: return "MUM_FAILURE"; break;
					case MUM_THREAD_TIMED_OUT: return "MUM_THREAD_TIMED_OUT"; break;
				}
			}
		#endif

	/* Windows implementation */

	#ifdef MU_WIN32

		// ...

	#endif

	/* Unix implementation */

	#ifdef MU_UNIX

		/* API functions */

			/* Thread */

				#define MU_UNIX_CHECK_THREAD_ACTIVE(ret) if(thread.active!=MU_TRUE){if(result!=MU_NULL_PTR){*result=MUM_INVALID_THREAD;}return ret;}
				#define MU_UNIX_CHECK_PTHREAD_ACTIVE(ret) if(p_thread->active!=MU_TRUE){if(result!=MU_NULL_PTR){*result=MUM_INVALID_THREAD;}return ret;}

				MUDEF muThread mu_thread_create(mumResult* result, void (*start)(void* args), void* args) {
					MU_SET_RESULT(result, MUM_SUCCESS)

					muThread thread = MU_ZERO_STRUCT(muThread);
					thread.active = MU_TRUE;

					void* (*func)(void*);
					mu_memcpy(&func, &start, sizeof(void*));
					if (pthread_create(&thread.thread, 0, func, args) != 0) {
						MU_SET_RESULT(result, MUM_CREATE_CALL_FAILED)
						return MU_ZERO_STRUCT(muThread);
					}

					thread.ret = MU_NULL_PTR;
					return thread;
				}

				MUDEF muThread mu_thread_destroy(mumResult* result, muThread thread) {
					MU_UNIX_CHECK_THREAD_ACTIVE(thread)

					mumResult res = MUM_SUCCESS;
					thread = mu_inner_thread_destroy(&res, thread);
					MU_SET_RESULT(result, res)
					return thread;
				}

				MUDEF void mu_thread_exit(void* ret) {
					pthread_exit(ret);
				}

				MUDEF void mu_thread_wait(mumResult* result, muThread* p_thread) {
					MU_SET_RESULT(result, MUM_SUCCESS)

					MU_UNIX_CHECK_PTHREAD_ACTIVE()

					if (pthread_join(p_thread->thread, &p_thread->ret) != 0) {
						MU_SET_RESULT(result, MUM_WAIT_CALL_FAILED)
						return;
					}
				}

				MUDEF void* mu_thread_get_return_value(mumResult* result, muThread thread) {
					MU_SET_RESULT(result, MUM_SUCCESS)

					MU_UNIX_CHECK_THREAD_ACTIVE(MU_NULL_PTR)

					return thread.ret;
				}

			/* Mutex */

				#define MU_UNIX_CHECK_MUTEX_ACTIVE(ret) if(mutex.active!=MU_TRUE){if(result!=MU_NULL_PTR){*result=MUM_INVALID_MUTEX;}return ret;}
				#define MU_UNIX_CHECK_PMUTEX_ACTIVE(ret) if(p_mutex->active!=MU_TRUE){if(result!=MU_NULL_PTR){*result=MUM_INVALID_MUTEX;}return ret;}

				MUDEF muMutex mu_mutex_create(mumResult* result) {
					MU_SET_RESULT(result, MUM_SUCCESS)

					muMutex mutex = MU_ZERO_STRUCT(muMutex);
					mutex.active = MU_TRUE;

					if (pthread_mutex_init(&mutex.mutex, 0) != 0) {
						MU_SET_RESULT(result, MUM_CREATE_CALL_FAILED)
						return MU_ZERO_STRUCT(muMutex);
					}

					return mutex;
				}

				MUDEF muMutex mu_mutex_destroy(mumResult* result, muMutex mutex) {
					MU_UNIX_CHECK_MUTEX_ACTIVE(mutex)

					mumResult res = MUM_SUCCESS;
					mutex = mu_inner_mutex_destroy(&res, mutex);
					MU_SET_RESULT(result, res)
					return mutex;
				}

				MUDEF void mu_mutex_lock(mumResult* result, muMutex* p_mutex) {
					MU_SET_RESULT(result, MUM_SUCCESS)
					MU_UNIX_CHECK_PMUTEX_ACTIVE()

					if (pthread_mutex_lock(&p_mutex->mutex) != 0) {
						MU_SET_RESULT(result, MUM_LOCK_CALL_FAILED)
						return;
					}
				}

				MUDEF void mu_mutex_unlock(mumResult* result, muMutex* p_mutex) {
					MU_SET_RESULT(result, MUM_SUCCESS)
					MU_UNIX_CHECK_PMUTEX_ACTIVE()

					if (pthread_mutex_unlock(&p_mutex->mutex) != 0) {
						MU_SET_RESULT(result, MUM_UNLOCK_CALL_FAILED)
						return;
					}
				}

			/* Spinlock */

				// A lot of this code is stolen from:
				// https://github.com/stepancheg/no-mutex-c

				static inline muBool mum_atomic_compare_exchange(int* ptr, int compare, int exchange) {
					return __atomic_compare_exchange_n(ptr, &compare, exchange, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
				}

				static inline void mum_atomic_store(int* ptr, int value) {
					if (value) {}
					__atomic_store_n(ptr, 0, __ATOMIC_SEQ_CST);
				}

				#define MU_UNIX_CHECK_SPINLOCK_ACTIVE(ret) if(spinlock.active!=MU_TRUE){if(result!=MU_NULL_PTR){*result=MUM_INVALID_MUTEX;}return ret;}
				#define MU_UNIX_CHECK_PSPINLOCK_ACTIVE(ret) if(p_spinlock->active!=MU_TRUE){if(result!=MU_NULL_PTR){*result=MUM_INVALID_MUTEX;}return ret;}

				MUDEF muSpinlock mu_spinlock_create(mumResult* result) {
					MU_SET_RESULT(result, MUM_SUCCESS)

					muSpinlock spinlock = MU_ZERO_STRUCT(muSpinlock);
					spinlock.active = MU_TRUE;

					return spinlock;
				}

				MUDEF muSpinlock mu_spinlock_destroy(mumResult* result, muSpinlock spinlock) {
					MU_UNIX_CHECK_SPINLOCK_ACTIVE(spinlock)

					mumResult res = MUM_SUCCESS;
					spinlock = mu_inner_spinlock_destroy(&res, spinlock);
					MU_SET_RESULT(result, res)
					return spinlock;
				}

				MUDEF void mu_spinlock_lock(mumResult* result, muSpinlock* p_spinlock) {
					MU_SET_RESULT(result, MUM_SUCCESS)

					while (!mum_atomic_compare_exchange(&p_spinlock->locked, 0, 1)) {

					}
				}

				MUDEF void mu_spinlock_unlock(mumResult* result, muSpinlock* p_spinlock) {
					MU_SET_RESULT(result, MUM_SUCCESS)

					mum_atomic_store(&p_spinlock->locked, 0);
				}

	#endif /* MU_UNIX */

	#ifdef __cplusplus
		}
	#endif

#endif /* MUM_IMPLEMENTATION */

/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2024 Hum
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/

