# muMultithreading v1.0.0

muMultithreading (acrynomized to mum) is a public domain header-only single-file C library for cross-platform multithreading. To use it, download the `muMultithreading.h` file, add it to your include path, and include it like so:

```c
#define MUM_IMPLEMENTATION
#include <muMultithreading.h>
```

More information about the general structure of a mu library is provided at [the mu library information GitHub repository.](https://github.com/Muukid/mu-library-information)

# Demos

Demos that quickly show the gist of the library and how it works are available in the `demos` folder.

# Licensing

mum is licensed under public domain or MIT, whichever you prefer. More information is provided in the accompanying file `license.md` and at the bottom of `muMultithreading.h`.

# Other library dependencies

mum has a dependency on:

[muMemoryAllocator v1.0.0](https://github.com/Muukid/muMemoryAllocator/tree/v1.0.0)

Note that mu libraries store their dependencies within their files, so you don't need to import these dependencies yourself.

Note that the libraries listed may also have other dependencies that they also include that aren't listed here.

# System dependencies

muMultithreading is built for POSIX and Win32.

For POSIX, in particular, pthreads is needed. This means that pthread needs to be linked to, usually with `-pthread`.

# Thread safety

mum, on default, has no thread safety, but can be made automatically thread safe by defining `MU_THREADSAFE`. Once on, this protects threads, mutexes, spinlocks, and locks from being accessed by multiple threads at once.

# Functions

## Initiation / Termination

The functions `mum_init` and `mum_term` initiate and terminate mum respectively, defined below:

```c
MUDEF void mum_init(mumResult* result);
MUDEF void mum_term(mumResult* result);
```

## Threads

### Creation / Destruction

The functions `mu_thread_create` and `mu_thread_destroy` create and destroy a thread respectively, defined below:

```c
MUDEF muThread mu_thread_create(mumResult* result, void (*start)(void* args), void* args);
MUDEF muThread mu_thread_destroy(mumResult* result, muThread thread);
```

Note that there is a delay between `mu_thread_create` being called and the thread's execution beginning. This means that, for example, if multiple threads are created in sequence, the order of thread execution cannot be guaranteed.

### Exit

The function `mu_thread_exit` exits from the current thread, defined below:

```c
MUDEF void mu_thread_exit(void* ret);
```

This function is meant to be called from within a thread, and is expected to be called at *some* point during the thread's lifetime.

`ret` is the value that will be returned if `mu_thread_get_return_value` is called for this thread.

### Wait

The function `mu_thread_wait` waits for a given thread to finish executing, defined below:

```c
MUDEF void mu_thread_wait(mumResult* result, muThread thread);
```

### Get return value

The function `mu_thread_get_return_value` returns the value passed into `mu_thread_exit` by the thread during its execution, defined below:

```c
MUDEF void* mu_thread_get_return_value(mumResult* result, muThread thread);
```

Note that this function may not perform correctly unless `mu_thread_wait` has been called for the given thread beforehand, even if it can be guaranteed that the thread will have already been finished by now.

## Lock

A lock (represented as `muLock`) is, on default, a [mutex](https://en.wikipedia.org/wiki/Lock_(computer_science) (`muMutex`), unless `MU_SPINLOCK` is defined, in which case it is a [spinlock](https://en.wikipedia.org/wiki/Spinlock) (`muSpinlock`).

### Creation / Destruction

The functions `mu_lock_create` and `mu_lock_destroy` create and destroy a lock, defined below:

```c
MUDEF muLock mu_lock_create(mumResult* result);
MUDEF muLock mu_lock_destroy(mumResult* result, muLock lock);
```

### Lock/Unlock

The functions `mu_lock_lock` and `mu_lock_unlock` lock and unlock a lock, defined below:

```c
MUDEF void mu_lock_lock(mumResult* result, muLock lock);
MUDEF void mu_lock_unlock(mumResult* result, muLock lock);
```

Note that `mu_lock_lock` can wait theroetically indefinitely on a lock, so be careful when calling it.

## Mutex

### Creation / Destruction

The functions `mu_mutex_create` and `mu_mutex_destroy` create and destroy a mutex, defined below:

```c
MUDEF muMutex mu_mutex_create(mumResult* result);
MUDEF muMutex mu_mutex_destroy(mumResult* result, muMutex mutex);
```

### Lock/Unlock

The functions `mu_mutex_lock` and `mu_mutex_unlock` lock and unlock a mutex, defined below:

```c
MUDEF void mu_mutex_lock(mumResult* result, muMutex mutex);
MUDEF void mu_mutex_unlock(mumResult* result, muMutex mutex);
```

Note that `mu_mutex_lock` can wait theroetically indefinitely on a lock, so be careful when calling it.

## Spinlock

### Creation / Destruction

The functions `mu_spinlock_create` and `mu_spinlock_destroy` create and destroy a spinlock, defined below:

```c
MUDEF muSpinlock mu_spinlock_create(mumResult* result);
MUDEF muSpinlock mu_spinlock_destroy(mumResult* result, muSpinlock spinlock);
```

### Lock/Unlock

The functions `mu_mutex_lock` and `mu_mutex_unlock` lock and unlock a spinlock, defined below:

```c
MUDEF void mu_spinlock_lock(mumResult* result, muSpinlock spinlock);
MUDEF void mu_spinlock_unlock(mumResult* result, muSpinlock spinlock);
```

Note that `mu_spinlock_lock` can wait theroetically indefinitely on a lock, so be careful when calling it.

## Names

The function `mum_result_get_name` takes a `mumResult` value and returns a `const char*` representation of it, defined below:

```c
MUDEF const char* mum_result_get_name(mumResult result);
```

Note that this function is only defined if `MUM_NAMES` is defined before the header of mum.

# Macros

## Thread

The object `muThread` is an ID reference represented by the type `size_m`. It represents a [thread](https://en.wikipedia.org/wiki/Thread_(computing)).

## muLock

The object `muLock` is an ID reference represented by the type `size_m`. It represents a [lock](https://en.wikipedia.org/wiki/Lock_(computer_science)).

### `MU_SPINLOCK`

On default, the object `muLock` is a mutex. However, if `MU_SPINLOCK` is defined before the header of mum is defined, `muLock` will be a spinlock, and the functions `mu_lock_create`, `mu_lock_destroy`, `mu_lock_lock`, and `mu_lock_unlock` will internally change accordingly.

## Mutex

The object `muMutex` is an ID reference represented by the type `size_m`. It represents a [mutex](https://en.wikipedia.org/wiki/Lock_(computer_science)).

## Spinlock

The object `muSpinlock` is an ID reference represented by the type `size_m`. It represents a [spinlock](https://en.wikipedia.org/wiki/Spinlock).

## `MUM_NAMES`

If `MUM_NAMES` is defined before the header of mum is defined, the function `mum_result_get_name` is defined.

## Version macro

mum defines three macros to define the version of mum: `MUM_VERSION_MAJOR`, `MUM_VERSION_MINOR`, and `MUM_VERSION_PATCH`, following the format of:

```
vMAJOR.MINOR.PATCH
```

# Enumerators

## Result enumerator

mum uses the `mumResult` enumerator to represent how a function went. It has these possible values:

`MUM_SUCCESS`: the task succeeded.

`MUM_MUMA_SUCCESS`: a call to a muma function was made, which gave the result `MUMA_SUCCESS`.

`MUM_MUMA_FAILED_TO_ALLOCATE`: a call to a muma function was made, which gave the result `MUMA_FAILED_TO_ALLOCATE`.

`MUM_MUMA_INVALID_INDEX`: a call to a muma function was made, which gave the result `MUMA_INVALID_INDEX`.

`MUM_MUMA_INVALID_SHIFT_AMOUNT`: a call to a muma function was made, which gave the result `MUMA_INVALID_SHIFT_AMOUNT`.

`MUM_MUMA_NOT_FOUND`: a call to a muma function was made, which gave the result `MUMA_NOT_FOUND`.

`MUM_ALLOCATION_FAILED`: an allocation call failed.

`MUM_ALREADY_INITIALIZED`: a call to a function assuming that mum hadn't been initialized (most likely `mum_init`) was made when mum was initialized.

`MUM_ALREADY_TERMINATED`: a call to a function assuming that mum had already been terminated (most likely `mum_term`) was made when mum was terminated.

`MUM_NOT_YET_INITIALIZED`: a call to a function that needs mum to be initialized to perform correctly was made when mum wasn't initialized.

`MUM_CREATE_CALL_FAILED`: a system call to create a given object failed.

`MUM_DESTROY_CALL_FAILED`: a system call to destroy a given object failed.

`MUM_WAIT_CALL_FAILED`: a system call to wait on a given object failed.

`MUM_LOCK_CALL_FAILED`: a system call to lock a given object failed.

`MUM_UNLOCK_CALL_FAILED`: a system call to unlock a given object failed.

`MUM_GET_RETURN_VALUE_CALL_FAILED`: a system call to get the return value of a given object (most likely a thread) failed. Note that this can happen if you didn't call `mu_thread_wait` on a thread.

`MUM_INVALID_ID`: a given object was invalid.

`MUM_THREAD_TIMED_OUT`: a thread timed out.

`MUM_PREVIOUS_THREAD_CLOSED_BEFORE_LOCK`: the thread controlling the lock previously was closed. The lock has still been successfully locked.

Unless specified otherwise, if the result of a function does not equal `MUM_SUCCESS`, whatever the function was supposed to do failed, and it will be as if the function was never called (meaning the function call had no permanent effect).

# Global variables

## Context

The variable `mum_global_context` is used to refer to the context of mum globally, defined below:

```c
MUDEF mumContext* mum_global_context;
```

This context is 0, or `MU_NULL_PTR`, if mum is not currently initiated. This variable can be checked by the user, but should not be written to.

# Incomplete types

## Context type

mum has an incomplete type defined in its header called `mumContext` that represents the context of mum. This context is not meant to be used by the user, and is later defined in the implementation.
