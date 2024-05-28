
# muMultithreading v2.0.0

muMultithreading (acrynomized to mum) is a public domain header-only single-file C library for cross-platform multithreading. To use it, download the `muMultithreading.h` file, add it to your include path, and include it like so:

```c
#define MUM_IMPLEMENTATION
#include "muMultithreading.h"
```

More information about the general structure of a mu library is provided at [the mu library information GitHub repository.](https://github.com/Muukid/mu-library-information)

# Demos

Demos that quickly show the gist of the library and how it works are available in the `demos` folder.

# Licensing

mum is licensed under public domain or MIT, whichever you prefer. More information is provided in the accompanying file `license.md` and at the bottom of `muMultithreading.h`.

# Other library dependencies

mum has a dependency on:

[muUtility v1.1.0](https://github.com/Muukid/muUtility/releases/tag/v1.1.0)

Note that mu libraries store their dependencies within their files, so you don't need to import these dependencies yourself.

Note that the libraries listed may also have other dependencies that they also include that aren't listed here.

# System dependencies

muMultithreading is built for POSIX and Win32.

For POSIX, in particular, pthreads is needed. This means that pthread needs to be linked to, usually with `-pthread`.


# C standard library dependencies

mum has several C standard library dependencies not provided by its other library dependencies, all of which are overridable by defining them before MUM_H is defined. The following is a list of those dependencies. Note that defining all of the dependencies of a C standard library file prevents it from being included.

## `stdlib.h` dependencies

`mu_malloc`: equivalent to malloc.

`mu_free`: equivalent to free.

## `string.h` dependencies

`mu_memcpy`: equivalent to memcpy.

# Enumerators

## Result enumerator

mum uses the `mumResult` enumerator to represent how a function went. It has the following possible values.


### General result enumerators

`MUM_SUCCESS`: the task succeeded.

`MUM_FAILED_ALLOCATE`: memory necessary to complete the task failed to allocate.

### Win32-specific result enumerators

`MUM_FAILED_CREATE_THREAD`: a call to `CreateThread` failed, and the thread has not been created.

`MUM_FAILED_CLOSE_HANDLE`: a call to `CloseHandle` failed, and the object has not been destroyed.

`MUM_FAILED_GET_EXIT_CODE_THREAD`: a call to `GetExitCodeThread` failed, and the return value could not be retrieved.

`MUM_THREAD_WAIT_TIMEOUT`: a call to `WaitForSingleObject` returned `WAIT_TIMEOUT`, and the thread has been reset.

`MUM_THREAD_WAIT_FAILED`: a call to `WaitForSingleObject` returned `WAIT_FAILED`, and the thread's state is unknown.

`MUM_FAILED_CREATE_MUTEX`: a call to `CreateMutex` failed, and the mutex has not been created.

`MUM_MUTEX_WAIT_FAILED`: a call to `WaitForSingleObject` returned `WAIT_FAILED`, most likley implying that the mutex has been closed whilst waiting.

`MUM_MUTEX_WAIT_ABANDONED`: a call to `WaitForSingleObject` returned `WAIT_ABANDONED`, meaning that the thread holding the mutex has closed before unlocking it; the mutex is unlocked; see [this](https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject).

`MUM_FAILED_RELEASE_MUTEX`: a call to `ReleaseMutex` failed; the thread that called this function does not have it locked.

### Unix-specific result enumerators

`MUM_FAILED_PTHREAD_CREATE`: a call to `pthread_create` failed, and the thread has not been created.

`MUM_FAILED_PTHREAD_CANCEL`: a call to `pthread_cancel` failed, and the thread has not been destroyed.

`MUM_FAILED_PTHREAD_JOIN`: a call to `pthread_join` failed.

`MUM_FAILED_PTHREAD_MUTEX_INIT`: a call to `pthread_mutex_init` failed, and the mutex has not been created.

`MUM_FAILED_PTHREAD_MUTEX_DESTROY`: a call to `pthread_mutex_destroy` failed, and the mutex has not been destroyed.

`MUM_FAILED_PTHREAD_MUTEX_LOCK`: a call to `pthread_mutex_lock` failed, and the mutex has not been locked.

`MUM_FAILED_PTHREAD_MUTEX_UNLOCK`: a call to `pthread_mutex_unlock` failed, and the mutex has not been unlocked.

# Macros

## Object macros

There are several macros used to represent an object, which are all macros for the type `void*`. These are:

`muThread`: a [thread](https://en.wikipedia.org/wiki/Thread_(computing)).

`muMutex`: a [mutex](https://en.wikipedia.org/wiki/Lock_(computer_science)).

`muSpinlock`: a [spinlock](https://en.wikipedia.org/wiki/Spinlock).

## Version macros

There are three major, minor, and patch macros respectively defined to represent the version of mum, defined as `MUM_VERSION_MAJOR`, `MUM_VERSION_MINOR`, and `MUM_VERSION_PATCH`, following the formatting of `vMAJOR.MINOR.PATCH`.

# Functions

## Global result

### Global result

The function `mum_global_result` sets the global result pointer assumed by all non-result-checking functions to the given value, defined below: 

```c
MUDEF void mum_global_result(mumResult* result);
```


Note that the assumed global result pointer is 0, and can be safely left as this or later set to this via this function to not check the result of functions.

## Names

All the functions within this section are not defined unless `MUM_NAMES` was defined before mum was included.

### Get name of result

The function `mum_result_get_name` returns a `const char*` representation of the given result enum value, defined below: 

```c
MUDEF const char* mum_result_get_name(mumResult result);
```


## Thread functions

### Thread creation and destruction

The function `mu_thread_create` creates a thread, defined below: 

```c
MUDEF muThread mu_thread_create(void (*start)(void* args), void* args);
```


Its explicit result checking equivalent is defined below: 

```c
MUDEF muThread mu_thread_create_(mumResult* result, void (*start)(void* args), void* args);
```


Note that there is a delay between thread creation being called and the thread's execution beginning. This means that, for example, if multiple threads are created in sequence, the order of the given threads beginning execution cannot be guaranteed.

The function `mu_thread_destroy` destroys a thread, defined below: 

```c
MUDEF muThread mu_thread_destroy(muThread thread);
```


Its explicit result checking equivalent is defined below: 

```c
MUDEF muThread mu_thread_destroy_(mumResult* result, muThread thread);
```


### Thread exiting

The function `mu_thread_exit` exits from the current thread with a return value, defined below: 

```c
MUDEF void mu_thread_exit(void* ret);
```


This function is meant to be called from within a thread, and is expected to be called at *some* point during the thread's lifetime; if this function is not called during a created thread's lifetime, resulting behaviour is undefined.

### Thread waiting

The function `mu_thread_wait` waits on a thread to finish executing, defined below: 

```c
MUDEF void mu_thread_wait(muThread thread);
```


Its explicit result checking equivalent is defined below: 

```c
MUDEF void mu_thread_wait_(mumResult* result, muThread thread);
```


### Retrieving thread return value

The function `mu_thread_get_return_value` retrieves the value passed to `mu_thread_exit` by a thread, defined below: 

```c
MUDEF void* mu_thread_get_return_value(muThread thread);
```


Its explicit result checking equivalent is defined below: 

```c
MUDEF void* mu_thread_get_return_value_(mumResult* result, muThread thread);
```


This function may not perform correctly unless `mu_thread_wait` has been called for the given thread beforehand, even if it can be guaranteed that the thread will have already been finished by now.

## Mutex functions

### Mutex creation and destruction

The function `mu_mutex_create` creates a mutex, defined below: 

```c
MUDEF muMutex mu_mutex_create(void);
```


Its explicit result checking equivalent is defined below: 

```c
MUDEF muMutex mu_mutex_create_(mumResult* result);
```


The function `mu_mutex_destroy` destroys a mutex, defined below: 

```c
MUDEF muMutex mu_mutex_destroy(muMutex mutex);
```


Its explicit result checking equivalent is defined below: 

```c
MUDEF muMutex mu_mutex_destroy_(mumResult* result, muMutex mutex);
```


### Mutex locking and unlocking

The function `mu_mutex_lock` locks a mutex, defined below: 

```c
MUDEF void mu_mutex_lock(muMutex mutex);
```


Its explicit result checking equivalent is defined below: 

```c
MUDEF void mu_mutex_lock_(mumResult* result, muMutex mutex);
```


The function `mu_mutex_unlock` unlocks a mutex, defined below: 

```c
MUDEF void mu_mutex_unlock(muMutex mutex);
```


Its explicit result checking equivalent is defined below: 

```c
MUDEF void mu_mutex_unlock_(mumResult* result, muMutex mutex);
```


## Spinlock functions

### Spinlock creation and destruction

The function `mu_spinlock_create` creates a spinlock, defined below: 

```c
MUDEF muSpinlock mu_spinlock_create(void);
```


Its explicit result checking equivalent is defined below: 

```c
MUDEF muSpinlock mu_spinlock_create_(mumResult* result);
```


The function `mu_spinlock_destroy` destroys a spinlock, defined below: 

```c
MUDEF muSpinlock mu_spinlock_destroy(muSpinlock spinlock);
```


Its explicit result checking equivalent is defined below: 

```c
MUDEF muSpinlock mu_spinlock_destroy_(mumResult* result, muSpinlock spinlock);
```


### Spinlock locking and unlocking

The function `mu_spinlock_lock` locks a spinlock, defined below: 

```c
MUDEF void mu_spinlock_lock(muSpinlock spinlock);
```


Its explicit result checking equivalent is defined below: 

```c
MUDEF void mu_spinlock_lock_(mumResult* result, muSpinlock spinlock);
```


The function `mu_spinlock_unlock` unlocks a spinlock, defined below: 

```c
MUDEF void mu_spinlock_unlock(muSpinlock spinlock);
```


Its explicit result checking equivalent is defined below: 

```c
MUDEF void mu_spinlock_unlock_(mumResult* result, muSpinlock spinlock);
```

