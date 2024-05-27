/*
muMultithreading.h - Muukid
Public domain simple single-file C library for cross-platform multithreading.
No warranty implied; use at your own risk.

Licensed under MIT License or public domain, whichever you prefer.
More explicit license information at the end of file.
*/

#ifndef MUM_H
	#define MUM_H

	/* muUtility commit 2b34ba6 header */
	
		#if !defined(MU_CHECK_VERSION_MISMATCHING) && defined(MUU_H) && \
			(MUU_VERSION_MAJOR != 1 || MUU_VERSION_MINOR != 0 || MUU_VERSION_PATCH != 0)

			#pragma message("[MUMA] muUtility's header has already been defined, but version doesn't match the version that this library is built for. This may lead to errors, warnings, or unexpected behavior. Define MU_CHECK_VERSION_MISMATCHING before this to turn off this message.")

		#endif

		#ifndef MUU_H
			#define MUU_H
			
			#if !defined(MU_SECURE_WARNINGS) && !defined(_CRT_SECURE_NO_WARNINGS)
				#define _CRT_SECURE_NO_WARNINGS
			#endif

			#ifdef __cplusplus
			extern "C" { // }
			#endif

			#define MUU_VERSION_MAJOR 1
			#define MUU_VERSION_MINOR 0
			#define MUU_VERSION_PATCH 0

			/* C standard library dependencies */

				#if !defined(int8_m)      || \
					!defined(uint8_m)     || \
					!defined(int16_m)     || \
					!defined(uint16_m)    || \
					!defined(int32_m)     || \
					!defined(uint32_m)    || \
					!defined(int64_m)     || \
					!defined(uint64_m)    || \
					!defined(MU_SIZE_MAX)

					#define __STDC_LIMIT_MACROS
					#define __STDC_CONSTANT_MACROS
					#include <stdint.h>

					#ifndef int8_m
						#ifdef INT8_MAX
							#define int8_m int8_t
						#else
							#define int8_m char
						#endif
					#endif

					#ifndef uint8_m
						#ifdef UINT8_MAX
							#define uint8_m uint8_t
						#else
							#define uint8_m unsigned char
						#endif
					#endif

					#ifndef int16_m
						#ifdef INT16_MAX
							#define int16_m int16_t
						#else
							#define int16_m short
						#endif
					#endif

					#ifndef uint16_m
						#ifdef UINT16_MAX
							#define uint16_m uint16_t
						#else
							#define uint16_m unsigned short
						#endif
					#endif

					#ifndef int32_m
						#ifdef INT32_MAX
							#define int32_m int32_t
						#else
							#define int32_m long
						#endif
					#endif

					#ifndef uint32_m
						#ifdef UINT32_MAX
							#define uint32_m uint32_t
						#else
							#define uint32_m unsigned long
						#endif
					#endif

					#ifndef int64_m
						#ifdef INT64_MAX
							#define int64_m int64_t
						#else
							#define int64_m long long
						#endif
					#endif

					#ifndef uint64_m
						#ifdef UINT64_MAX
							#define uint64_m uint64_t
						#else
							#define uint64_m unsigned long long
						#endif
					#endif

					#ifndef MU_SIZE_MAX
						#define MU_SIZE_MAX SIZE_MAX
					#endif

				#endif

				#if !defined(size_m)

					#include <stddef.h>

					#ifndef size_m
						#define size_m size_t
					#endif

				#endif

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

			/* Useful macros */

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

				#ifndef muByte
					#define muByte uint8_m
				#endif

				#ifndef mu_rle_uint8
					#define mu_rle_uint8(b) ((uint8_m)b[0] << 0)
				#endif
				#ifndef mu_rbe_uint8
					#define mu_rbe_uint8(b) ((uint8_m)b[0] << 0)
				#endif

				#ifndef mu_rle_uint16
					#define mu_rle_uint16(b) ((uint16_m)b[0] << 0 | (uint16_m)b[1] << 8)
				#endif
				#ifndef mu_rbe_uint16
					#define mu_rbe_uint16(b) ((uint16_m)b[1] << 0 | (uint16_m)b[0] << 8)
				#endif

				#ifndef mu_rle_uint32
					#define mu_rle_uint32(b) ((uint32_m)b[0] << 0 | (uint32_m)b[1] << 8 | (uint32_m)b[2] << 16 | (uint32_m)b[3] << 24)
				#endif
				#ifndef mu_rbe_uint32
					#define mu_rbe_uint32(b) ((uint32_m)b[3] << 0 | (uint32_m)b[2] << 8 | (uint32_m)b[1] << 16 | (uint32_m)b[0] << 24)
				#endif

				#ifndef mu_rle_uint64
					#define mu_rle_uint64(b) ((uint64_m)b[0] << 0 | (uint64_m)b[1] << 8 | (uint64_m)b[2] << 16 | (uint64_m)b[3] << 24 | (uint64_m)b[4] << 32 | (uint64_m)b[5] << 40 | (uint64_m)b[6] << 48 | (uint64_m)b[7] << 56)
				#endif
				#ifndef mu_rbe_uint64
					#define mu_rbe_uint64(b) ((uint64_m)b[7] << 0 | (uint64_m)b[6] << 8 | (uint64_m)b[5] << 16 | (uint64_m)b[4] << 24 | (uint64_m)b[3] << 32 | (uint64_m)b[2] << 40 | (uint64_m)b[1] << 48 | (uint64_m)b[0] << 56)
				#endif

				#ifndef mu_wle_uint8
					#define mu_wle_uint8(b, i) b[0] = (uint8_m)(i >> 0);
				#endif
				#ifndef mu_wbe_uint8
					#define mu_wbe_uint8(b, i) b[0] = (uint8_m)(i >> 0);
				#endif

				#ifndef mu_wle_uint16
					#define mu_wle_uint16(b, i) b[0] = (uint8_m)(i >> 0); b[1] = (uint8_m)(i >> 8);
				#endif
				#ifndef mu_wbe_uint16
					#define mu_wbe_uint16(b, i) b[1] = (uint8_m)(i >> 0); b[0] = (uint8_m)(i >> 8);
				#endif

				#ifndef mu_wle_uint32
					#define mu_wle_uint32(b, i) b[0] = (uint8_m)(i >> 0); b[1] = (uint8_m)(i >> 8); b[2] = (uint8_m)(i >> 16); b[3] = (uint8_m)(i >> 24);
				#endif
				#ifndef mu_wbe_uint32
					#define mu_wbe_uint32(b, i) b[3] = (uint8_m)(i >> 0); b[2] = (uint8_m)(i >> 8); b[1] = (uint8_m)(i >> 16); b[0] = (uint8_m)(i >> 24);
				#endif

				#ifndef mu_wle_uint64
					#define mu_wle_uint64(b, i) b[0] = (uint8_m)(i >> 0); b[1] = (uint8_m)(i >> 8); b[2] = (uint8_m)(i >> 16); b[3] = (uint8_m)(i >> 24); b[4] = (uint8_m)(i >> 32); b[5] = (uint8_m)(i >> 40); b[6] = (uint8_m)(i >> 48); b[7] = (uint8_m)(i >> 56);
				#endif
				#ifndef mu_wbe_uint64
					#define mu_wbe_uint64(b, i) b[7] = (uint8_m)(i >> 0); b[6] = (uint8_m)(i >> 8); b[5] = (uint8_m)(i >> 16); b[4] = (uint8_m)(i >> 24); b[3] = (uint8_m)(i >> 32); b[2] = (uint8_m)(i >> 40); b[1] = (uint8_m)(i >> 48); b[0] = (uint8_m)(i >> 56);
				#endif

				#ifndef MU_NULL_PTR
					#define MU_NULL_PTR 0
				#endif

				#ifndef MU_NULL
					#define MU_NULL 0
				#endif

				#ifndef MU_NONE
					#define MU_NONE MU_SIZE_MAX
				#endif

				#ifndef MU_SET_RESULT
					#define MU_SET_RESULT(res, val) if(res!=MU_NULL_PTR){*res=val;}
				#endif

				#ifndef MU_ASSERT
					#define MU_ASSERT(cond, res, val, after) if(!(cond)){MU_SET_RESULT(res, val) after}
				#endif

				#define MU_ENUM(name, ...) enum _##name{__VA_ARGS__};typedef enum _##name _##name; typedef size_m name;

				#if !defined(MU_WIN32) && !defined(MU_UNIX)
					#if defined(WIN32) || defined(_WIN32)
						#define MU_WIN32
					#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
						#define MU_UNIX
					#endif
				#endif

			#ifdef __cplusplus
			}
			#endif

		#endif /* MUU_H */
	
	#ifdef __cplusplus
	extern "C" { // }
	#endif

	#define MUM_VERSION_MAJOR 1
	#define MUM_VERSION_MINOR 0
	#define MUM_VERSION_PATCH 0

	/* C standard library dependencies */

		#if !defined(mu_malloc) || \
			!defined(mu_free)

			#include <stdlib.h>

			#ifndef mu_malloc
				#define mu_malloc malloc
			#endif

			#ifndef mu_free
				#define mu_free free
			#endif

		#endif

		#if !defined(mu_memcpy)

			#include <string.h>

			#ifndef mu_memcpy
				#define mu_memcpy memcpy
			#endif

		#endif

	/* Enums */

		MU_ENUM(mumResult,
			MUM_SUCCESS,

			MUM_FAILED_ALLOCATE,

			// Win32
			MUM_FAILED_CREATE_THREAD,
			MUM_FAILED_CLOSE_HANDLE,
			MUM_FAILED_GET_EXIT_CODE_THREAD,
			MUM_THREAD_WAIT_TIMEOUT,
			MUM_THREAD_WAIT_FAILED,
			MUM_FAILED_CREATE_MUTEX,
			MUM_MUTEX_WAIT_FAILED,
			MUM_MUTEX_WAIT_ABANDONED,
			MUM_FAILED_RELEASE_MUTEX,
		)

	/* Macros */

		#define muThread void*
		#define muMutex void*
		#define muSpinlock void*

	/* Functions */

		MUDEF void mum_global_result(mumResult* result);

		/* Names */

			#ifdef MUM_NAMES
				MUDEF const char* mum_result_get_name(mumResult result);
			#endif

		/* Thread */

			MUDEF muThread mu_thread_create_(mumResult* result, void (*start)(void* args), void* args);
			MUDEF muThread mu_thread_create(void (*start)(void* args), void* args);

			MUDEF muThread mu_thread_destroy_(mumResult* result, muThread thread);
			MUDEF muThread mu_thread_destroy(muThread thread);

			MUDEF void mu_thread_exit(void* ret);

			MUDEF void mu_thread_wait_(mumResult* result, muThread thread);
			MUDEF void mu_thread_wait(muThread thread);

			MUDEF void* mu_thread_get_return_value_(mumResult* result, muThread thread);
			MUDEF void* mu_thread_get_return_value(muThread thread);

		/* Mutex */

			MUDEF muMutex mu_mutex_create_(mumResult* result);
			MUDEF muMutex mu_mutex_create(void);

			MUDEF muMutex mu_mutex_destroy_(mumResult* result, muMutex mutex);
			MUDEF muMutex mu_mutex_destroy(muMutex mutex);

			MUDEF void mu_mutex_lock_(mumResult* result, muMutex mutex);
			MUDEF void mu_mutex_lock(muMutex mutex);

			MUDEF void mu_mutex_unlock_(mumResult* result, muMutex mutex);
			MUDEF void mu_mutex_unlock(muMutex mutex);

		/* Spinlock */

			MUDEF muSpinlock mu_spinlock_create_(mumResult* result);
			MUDEF muSpinlock mu_spinlock_create(void);

			MUDEF muSpinlock mu_spinlock_destroy_(mumResult* result, muSpinlock spinlock);
			MUDEF muSpinlock mu_spinlock_destroy(muSpinlock spinlock);

			MUDEF void mu_spinlock_lock_(mumResult* result, muSpinlock spinlock);
			MUDEF void mu_spinlock_lock(muSpinlock spinlock);

			MUDEF void mu_spinlock_unlock_(mumResult* result, muSpinlock spinlock);
			MUDEF void mu_spinlock_unlock(muSpinlock spinlock);

	#ifdef __cplusplus
	}
	#endif

#endif /* MUM_H */

#ifdef MUM_IMPLEMENTATION

	#ifdef __cplusplus
	extern "C" { // }
	#endif

	/* Global functions */

		mumResult* mum_global_res = 0;
		MUDEF void mum_global_result(mumResult* result) {
			mum_global_res = result;
		}

		/* Names */

			#ifdef MUM_NAMES
				MUDEF const char* mum_result_get_name(mumResult result) {
					switch (result) {
						default: return "MUM_UNKNOWN"; break;
						case MUM_SUCCESS: return "MUM_SUCCESS"; break;
						case MUM_FAILED_ALLOCATE: return "MUM_FAILED_ALLOCATE"; break;
						case MUM_FAILED_CREATE_THREAD: return "MUM_FAILED_CREATE_THREAD"; break;
						case MUM_FAILED_CLOSE_HANDLE: return "MUM_FAILED_CLOSE_HANDLE"; break;
						case MUM_FAILED_GET_EXIT_CODE_THREAD: return "MUM_FAILED_GET_EXIT_CODE_THREAD"; break;
						case MUM_THREAD_WAIT_TIMEOUT: return "MUM_THREAD_WAIT_TIMEOUT"; break;
						case MUM_THREAD_WAIT_FAILED: return "MUM_THREAD_WAIT_FAILED"; break;
						case MUM_FAILED_CREATE_MUTEX: return "MUM_FAILED_CREATE_MUTEX"; break;
						case MUM_MUTEX_WAIT_FAILED: return "MUM_MUTEX_WAIT_FAILED"; break;
						case MUM_MUTEX_WAIT_ABANDONED: return "MUM_MUTEX_WAIT_ABANDONED"; break;
						case MUM_FAILED_RELEASE_MUTEX: return "MUM_FAILED_RELEASE_MUTEX"; break;
					}
				}
			#endif

	/* Win32 */

	#ifdef MU_WIN32

		#include <windows.h>

		/* Thread */

			struct mum_win32_thread {
				HANDLE handle;
			};
			typedef struct mum_win32_thread mum_win32_thread;

			MUDEF muThread mu_thread_create_(mumResult* result, void (*start)(void* args), void* args) {
				mum_win32_thread* p = (mum_win32_thread*)mu_malloc(sizeof(mum_win32_thread));
				if (!p) {
					MU_SET_RESULT(result, MUM_FAILED_ALLOCATE)
					return 0;
				}

				// Memcpy into valid pointer because compiler be dumb sometimes
				LPTHREAD_START_ROUTINE lp_start;
				mu_memcpy(&lp_start, &start, sizeof(void*));

				DWORD id;
				p->handle = CreateThread(0, 0, lp_start, args, 0, &id);
				if (p->handle == 0) {
					MU_SET_RESULT(result, MUM_FAILED_CREATE_THREAD)
					mu_free(p);
					return 0;
				}

				return p;
			}
			MUDEF muThread mu_thread_create(void (*start)(void* args), void* args) {
				return mu_thread_create_(mum_global_res, start, args);
			}

			MUDEF muThread mu_thread_destroy_(mumResult* result, muThread thread) {
				mum_win32_thread* p = (mum_win32_thread*)thread;

				if (CloseHandle(p->handle) == 0) {
					MU_SET_RESULT(result, MUM_FAILED_CLOSE_HANDLE)
					return thread;
				}

				mu_free(thread);
				return 0;
			}
			MUDEF muThread mu_thread_destroy(muThread thread) {
				return mu_thread_destroy_(mum_global_res, thread);
			}

			MUDEF void mu_thread_exit(void* ret) {
				DWORD d;
				mu_memcpy(&d, &ret, sizeof(DWORD));
				ExitThread(d);
			}

			MUDEF void mu_thread_wait_(mumResult* result, muThread thread) {
				mum_win32_thread* p = (mum_win32_thread*)thread;

				DWORD wait_result = WaitForSingleObject(p->handle, INFINITE);

				switch (wait_result) {
					case WAIT_TIMEOUT: {
						MU_SET_RESULT(result, MUM_THREAD_WAIT_TIMEOUT)
					} break;
					case WAIT_FAILED: {
						MU_SET_RESULT(result, MUM_THREAD_WAIT_FAILED)
					} break;
				}
			}
			MUDEF void mu_thread_wait(muThread thread) {
				mu_thread_wait_(mum_global_res, thread);
			}

			MUDEF void* mu_thread_get_return_value_(mumResult* result, muThread thread) {
				mum_win32_thread* p = (mum_win32_thread*)thread;

				DWORD exit_code = 0;
				if (GetExitCodeThread(p->handle, &exit_code) == 0) {
					MU_SET_RESULT(result, MUM_FAILED_GET_EXIT_CODE_THREAD)
					return 0;
				}

				void* tp;
				mu_memcpy(&tp, &exit_code, sizeof(DWORD));
				return tp;
			}
			MUDEF void* mu_thread_get_return_value(muThread thread) {
				return mu_thread_get_return_value_(mum_global_res, thread);
			}

		/* Mutex */

			struct mum_win32_mutex {
				HANDLE handle;
			};
			typedef struct mum_win32_mutex mum_win32_mutex;

			MUDEF muMutex mu_mutex_create_(mumResult* result) {
				mum_win32_mutex* p = (mum_win32_mutex*)mu_malloc(sizeof(mum_win32_mutex));
				if (!p) {
					MU_SET_RESULT(result, MUM_FAILED_ALLOCATE)
					return 0;
				}

				p->handle = CreateMutex(0, MU_FALSE, 0);
				if (p->handle == 0) {
					MU_SET_RESULT(result, MUM_FAILED_CREATE_MUTEX)
					mu_free(p);
					return 0;
				}

				return (muMutex)p;
			}
			MUDEF muMutex mu_mutex_create(void) {
				return mu_mutex_create_(mum_global_res);
			}

			MUDEF muMutex mu_mutex_destroy_(mumResult* result, muMutex mutex) {
				mum_win32_mutex* p = (mum_win32_mutex*)mutex;

				if (CloseHandle(p->handle) == 0) {
					MU_SET_RESULT(result, MUM_FAILED_CLOSE_HANDLE)
					return p;
				}

				mu_free(p);
				return 0;
			}
			MUDEF muMutex mu_mutex_destroy(muMutex mutex) {
				return mu_mutex_destroy_(mum_global_res, mutex);
			}

			MUDEF void mu_mutex_lock_(mumResult* result, muMutex mutex) {
				mum_win32_mutex* p = (mum_win32_mutex*)mutex;

				DWORD wait_result = WaitForSingleObject(p->handle, INFINITE);

				switch (wait_result) {
					// The mutex has most likely been closed. This should pretty much never happen with
					// the way mum is set up, but if it has, that's really bad. Most likely, rather mum
					// is not working as intended at all, or the user has modified things that they
					// shouldn't.
					case WAIT_FAILED: {
						MU_SET_RESULT(result, MUM_MUTEX_WAIT_FAILED)
					} break;

					// The thread holding the mutex has died. This can be due to a few things:
					// * The thread crashed or otherwise imploded in on itself.
					// * The user has fiddled around with values they shouldn't.
					// Either way, this is REALLY, REALLY bad, and will lead to sporadic random bugs &
					// crashes.
					// Note: we still have ownership due to this, but ehhhhh.
					// https://devblogs.microsoft.com/oldnewthing/20050912-14/?p=34253
					// (Raymond Chen is awesome btw)
					case WAIT_ABANDONED: {
						MU_SET_RESULT(result, MUM_MUTEX_WAIT_ABANDONED)
					} break;
				}
			}
			MUDEF void mu_mutex_lock(muMutex mutex) {
				mu_mutex_lock_(mum_global_res, mutex);
			}

			MUDEF void mu_mutex_unlock_(mumResult* result, muMutex mutex) {
				mum_win32_mutex* p = (mum_win32_mutex*)mutex;

				if (ReleaseMutex(p->handle) == 0) {
					MU_SET_RESULT(result, MUM_FAILED_RELEASE_MUTEX)
				}
			}
			MUDEF void mu_mutex_unlock(muMutex mutex) {
				mu_mutex_unlock_(mum_global_res, mutex);
			}

		/* Spinlock */

			struct mum_win32_spinlock {
				LONG volatile locked;
			};
			typedef struct mum_win32_spinlock mum_win32_spinlock;

			MUDEF muSpinlock mu_spinlock_create_(mumResult* result) {
				mum_win32_spinlock* p = (mum_win32_spinlock*)mu_malloc(sizeof(mum_win32_spinlock));
				if (!p) {
					MU_SET_RESULT(result, MUM_FAILED_ALLOCATE)
					return 0;
				}

				p->locked = 0;
				return p;
			}
			MUDEF muSpinlock mu_spinlock_create(void) {
				return mu_spinlock_create_(mum_global_res);
			}

			MUDEF muSpinlock mu_spinlock_destroy_(mumResult* result, muSpinlock spinlock) {
				mu_free(spinlock);
				return 0; if (result) {}
			}
			MUDEF muSpinlock mu_spinlock_destroy(muSpinlock spinlock) {
				return mu_spinlock_destroy_(mum_global_res, spinlock);
			}

			MUDEF void mu_spinlock_lock_(mumResult* result, muSpinlock spinlock) {
				mum_win32_spinlock* p = (mum_win32_spinlock*)spinlock;

				while (InterlockedCompareExchange(&p->locked, 1, 0) == 1) {}

				return; if (result) {}
			}
			MUDEF void mu_spinlock_lock(muSpinlock spinlock) {
				mu_spinlock_lock_(mum_global_res, spinlock);
			}

			MUDEF void mu_spinlock_unlock_(mumResult* result, muSpinlock spinlock) {
				mum_win32_spinlock* p = (mum_win32_spinlock*)spinlock;

				_interlockedbittestandreset(&p->locked, 0);

				return; if (result) {}
			}
			MUDEF void mu_spinlock_unlock(muSpinlock spinlock) {
				mu_spinlock_unlock_(mum_global_res, spinlock);
			}

	#endif

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

