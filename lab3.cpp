#include "lab3.h"

#include <stdio.h>
#include <windows.h>
#include <iostream>

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else

#include <unistd.h> // for usleep

#endif

const int SLEEP_TIME = 10;

HANDLE lock;
HANDLE semaphore_a,
semaphore_b,
semaphore_c,
semaphore_d,
semaphore_e,
semaphore_f,
semaphore_h,
semaphore_g,
semaphore_i,
semaphore_k,
semaphore_m,
semaphore_r,
semaphore_sync,
semaphore_g1,
semaphore_k1,
semaphore_m1,
semaphore_n1;

unsigned int lab3_thread_graph_id()
{
	return 20;
}

const char* lab3_unsynchronized_threads()
{
	return "bcf";
}

const char* lab3_sequential_threads()
{
	return "gkmn";
}

DWORD WINAPI thread_a(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'a' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	ReleaseSemaphore(semaphore_a, 3, NULL);
	return TRUE;
}
DWORD WINAPI thread_b(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	WaitForSingleObject(semaphore_a, INFINITE);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'b' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	ReleaseSemaphore(semaphore_b, 3, NULL);
	return TRUE;
}
DWORD WINAPI thread_c(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	WaitForSingleObject(semaphore_a, INFINITE);
	for (int i = 0; i < 6; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'c' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	ReleaseSemaphore(semaphore_c, 2, NULL);
	return TRUE;
}
DWORD WINAPI thread_d(LPVOID lpParam) {

	WaitForSingleObject(semaphore_b, INFINITE);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'd' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	ReleaseSemaphore(semaphore_d, 2, NULL);
	return TRUE;
}
DWORD WINAPI thread_e(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	WaitForSingleObject(semaphore_b, INFINITE);
	for (int i = 0; i < 9; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'e' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	ReleaseSemaphore(semaphore_e, 1, NULL);
	return TRUE;
}
DWORD WINAPI thread_f(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	WaitForSingleObject(semaphore_a, INFINITE);
	for (int i = 0; i < 9; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'f' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	ReleaseSemaphore(semaphore_f, 3, NULL);
	return TRUE;
}
DWORD WINAPI thread_g(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	WaitForSingleObject(semaphore_b, INFINITE);
	for (int i = 0; i < 9; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'g' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	//TODO WAIT ANOTHER SEMAPHORE


	HANDLE semaphores[] = {
		semaphore_i,
		semaphore_e,
		semaphore_r
	};
	WaitForMultipleObjects(3, semaphores, TRUE, INFINITE);
	ReleaseSemaphore(semaphore_n1, 1, NULL);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(semaphore_n1, INFINITE);
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'g' << std::flush;
		ReleaseMutex(lock);
		computation();
		ReleaseSemaphore(semaphore_g1, 1, NULL);
	}

	ReleaseSemaphore(semaphore_g, 2, NULL);
	WaitForSingleObject(semaphore_n1, INFINITE);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'g' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	return TRUE;
}
DWORD WINAPI thread_h(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	HANDLE semaphores[2] = {
		semaphore_c,
		semaphore_d
	};
	WaitForMultipleObjects(2, semaphores, TRUE, INFINITE);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'h' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	ReleaseSemaphore(semaphore_h, 3, NULL);
	return TRUE;
}
DWORD WINAPI thread_i(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	HANDLE semaphores[2] = {
		semaphore_f,
		semaphore_h
	};
	WaitForMultipleObjects(2, semaphores, TRUE, INFINITE);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'i' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	ReleaseSemaphore(semaphore_i, 1, NULL);
	return TRUE;
}
DWORD WINAPI thread_k(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(semaphore_g1, INFINITE);
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'k' << std::flush;
		ReleaseMutex(lock);
		computation();
		ReleaseSemaphore(semaphore_k1, 1, NULL);
	}
	ReleaseSemaphore(semaphore_k, 1, NULL);
	return TRUE;
}
DWORD WINAPI thread_m(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	HANDLE semaphores[2] = {
		semaphore_f,
		semaphore_h
	};
	WaitForMultipleObjects(2, semaphores, TRUE, INFINITE);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'm' << std::flush;
		ReleaseMutex(lock);
		computation();
	}

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(semaphore_k1, INFINITE);
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'm' << std::flush;
		ReleaseMutex(lock);
		computation();
		ReleaseSemaphore(semaphore_m1, 1, NULL);
	}
	ReleaseSemaphore(semaphore_m, 1, NULL);
	return TRUE;
}
DWORD WINAPI thread_n(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	HANDLE semaphores[2] = {
		semaphore_f,
		semaphore_h
	};
	WaitForMultipleObjects(2, semaphores, TRUE, INFINITE);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'n' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(semaphore_m1, INFINITE);
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'n' << std::flush;
		ReleaseMutex(lock);
		computation();
		ReleaseSemaphore(semaphore_n1, 1, NULL);
	}
	WaitForSingleObject(semaphore_g, INFINITE);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'n' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	return TRUE;
}
DWORD WINAPI thread_p(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	HANDLE semaphores[] = {
		semaphore_k,
		semaphore_g,
		semaphore_m
	};
	WaitForMultipleObjects(2, semaphores, TRUE, INFINITE);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'p' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	return TRUE;
}
DWORD WINAPI thread_r(LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	HANDLE semaphores[2] = {
		semaphore_c,
		semaphore_d
	};
	WaitForMultipleObjects(2, semaphores, TRUE, INFINITE);
	for (int i = 0; i < 6; i++) {
		WaitForSingleObject(lock, INFINITE);
		std::cout << 'r' << std::flush;
		ReleaseMutex(lock);
		computation();
	}
	ReleaseSemaphore(semaphore_r, 1, NULL);
	return TRUE;
}
int lab3_init() {
	DWORD ThreadID;
	HANDLE aThread[14];
	lock = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex
	if (lock == NULL) {
		std::cerr << "CreateMutex error: " << GetLastError() << '\n';
		return 1;
	}

	semaphore_a = CreateSemaphore(NULL, 0, 3, NULL);
	if (semaphore_a == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

	semaphore_b = CreateSemaphore(NULL, 0, 10, NULL);          // unnamed semaphore
	if (semaphore_b == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

	semaphore_c = CreateSemaphore(NULL, 0, 7, NULL);          // unnamed semaphore
	if (semaphore_c == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

	semaphore_d = CreateSemaphore(NULL, 0, 7, NULL);          // unnamed semaphore
	if (semaphore_d == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

	semaphore_e = CreateSemaphore(NULL, 0, 2, NULL);          // unnamed semaphore
	if (semaphore_e == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

	semaphore_f = CreateSemaphore(NULL, 0, 5, NULL);          // unnamed semaphore
	if (semaphore_f == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

	semaphore_h = CreateSemaphore(NULL, 0, 5, NULL);          // unnamed semaphore
	if (semaphore_h == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}
	semaphore_g = CreateSemaphore(NULL, 0, 5, NULL);          // unnamed semaphore
	if (semaphore_g == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

	semaphore_i = CreateSemaphore(NULL, 0, 2, NULL);          // unnamed semaphore
	if (semaphore_i == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

	semaphore_k = CreateSemaphore(NULL, 0, 1, NULL);          // unnamed semaphore
	if (semaphore_k == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

	semaphore_m = CreateSemaphore(NULL, 0, 1, NULL);          // unnamed semaphore
	if (semaphore_m == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

	semaphore_r = CreateSemaphore(NULL, 0, 2, NULL);          // unnamed semaphore
	if (semaphore_r == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

	semaphore_sync = CreateSemaphore(NULL, 0, 2, NULL);          // unnamed semaphore
	

	semaphore_g1 = CreateSemaphore(NULL, 0, 2, NULL);          // unnamed semaphore
	

	semaphore_k1 = CreateSemaphore(NULL, 0, 2, NULL);          // unnamed semaphore
	
	semaphore_m1 = CreateSemaphore(NULL, 0, 2, NULL);          // unnamed semaphore
	

	semaphore_n1 = CreateSemaphore(NULL, 0, 2, NULL);          // unnamed semaphore
	
	aThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_a, NULL, 0, &ThreadID);
	if (aThread[0] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	aThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_b, NULL, 0, &ThreadID);
	if (aThread[1] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	aThread[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_c, NULL, 0, &ThreadID);
	if (aThread[2] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	aThread[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_d, NULL, 0, &ThreadID);
	if (aThread[3] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	aThread[4] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_e, NULL, 0, &ThreadID);
	if (aThread[4] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	aThread[5] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_f, NULL, 0, &ThreadID);
	if (aThread[5] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	aThread[6] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_g, NULL, 0, &ThreadID);
	if (aThread[6] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	aThread[7] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_h, NULL, 0, &ThreadID);
	if (aThread[7] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	aThread[8] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_i, NULL, 0, &ThreadID);
	if (aThread[8] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	aThread[9] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_k, NULL, 0, &ThreadID);
	if (aThread[9] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	aThread[10] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_m, NULL, 0, &ThreadID);
	if (aThread[10] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	aThread[11] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_n, NULL, 0, &ThreadID);
	if (aThread[11] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	aThread[12] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_p, NULL, 0, &ThreadID);
	if (aThread[12] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	aThread[13] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_r, NULL, 0, &ThreadID);
	if (aThread[13] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}


	WaitForMultipleObjects(14, aThread, TRUE, INFINITE);
	CloseHandle(lock);
	for (int i = 0; i < 14; i++)
		CloseHandle(aThread[i]);
	CloseHandle(semaphore_a);
	CloseHandle(semaphore_b);
	CloseHandle(semaphore_c);
	CloseHandle(semaphore_d);
	CloseHandle(semaphore_e);
	CloseHandle(semaphore_f);
	CloseHandle(semaphore_h);
	CloseHandle(semaphore_i);
	CloseHandle(semaphore_k);
	CloseHandle(semaphore_m);
	CloseHandle(semaphore_r);
	return 0;
}
