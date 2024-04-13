/*
============================================================
                        DEMO INFO

DEMO NAME:          threads.c
DEMO WRITTEN BY:    Muukid
CREATION DATE:      2024-04-13
LAST UPDATED:       2024-04-13

============================================================
                        DEMO PURPOSE

This demo shows the basics behind using threads.

============================================================

============================================================
                        LICENSE INFO

All code is licensed under MIT License or public domain, 
whichever you prefer.
More explicit license information at the end of file.

============================================================

============================================================
                        ADDITIONAL NOTES

This demo is largely inspired by this GeeksForGeeks page:
https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
============================================================
*/

// Include mum
#define MUM_NAMES // (for mum_result_get_name)
#define MUM_IMPLEMENTATION
#include <muMultithreading.h>

// Include stdio for printing
#include <stdio.h>

/* Create a function that our threads will run on */

// Note: any thread function has to have this return type and parameters
void test(void* args) {
	// Read from the args pointer to get our thread ID
	size_m id = *(size_m*)args;

	// Print the thread start message
	printf("Thread #%i has started\n", (int)id);

	// Wait a little bit doing busy work
	for (size_m i = 0; i < 60000; i++) {  }

	// Print the thread end message
	printf("Thread #%i has finished\n", (int)id);
	
	// Exit the thread
	mu_thread_exit(MU_NULL_PTR);
}

int main(void) {
	mumResult result = MUM_SUCCESS;

	// Initiate mum

	mum_init(&result);
	if (result != MUM_SUCCESS)
		printf("WARNING: mum_init returned %s\n", mum_result_get_name(result));

	// Setup an array to hold our threads and an array to hold the id for our threads that will be
	// passed to the threads

	muThread threads[2];
	size_m thread_ids[2] = { 0, 1 };

	// Create our threads with a loop

	for (size_m i = 0; i < 2; i++) {
		threads[i] = mu_thread_create(&result, test, &thread_ids[i]);
		if (result != MUM_SUCCESS)
			printf("WARNING: mu_thread_create returned %s\n", mum_result_get_name(result));
	}

	// Wait on all of our threads and destroy them

	for (size_m i = 0; i < 2; i++) {
		mu_thread_wait(&result, threads[i]);
		if (result != MUM_SUCCESS)
			printf("WARNING: mu_thread_wait returned %s\n", mum_result_get_name(result));

		mu_thread_destroy(&result, threads[i]);
		if (result != MUM_SUCCESS)
			printf("WARNING: mu_thread_destroy returned %s\n", mum_result_get_name(result));
	}

	// Terminate

	mum_term(&result);
	if (result != MUM_SUCCESS)
		printf("WARNING: mum_term returned %s\n", mum_result_get_name(result));

	// The results of this demo's printing can vary, but they should contain these lines in no
	// particular order:
	/*
	Thread #0 has started
	Thread #0 has finished
	Thread #1 has started
	Thread #1 has finished
	*/

	return 0;
}

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

