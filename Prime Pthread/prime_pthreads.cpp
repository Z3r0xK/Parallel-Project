#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <io.h>
#include <Windows.h>
# include <ctime >
//#include <mpi.h>
# include <iomanip>
#include<string>
#include<omp.h>

using namespace std;
const int N = 6;
const long x = pow(10, N);

#define threadsNo 10
long  len = x / threadsNo;
int c;
pthread_mutex_t  mymutex;

bool isPrime(long n) {
	if (n == 1 || n == 0)
		return true;
	else {

		for (int i = 2; i <= n / 2; ++i) {
			if (n % i == 0) {
				return false;
			}
		}
		return true;
	}
}

void* f(void* arg) {
	long offset, start, end, mySum = 0;
	offset = (long)arg;
	start = offset * len;
	end = start + len;

	for (int i = start; i < end; i++) {
		if (isPrime(i)) {
			mySum += 1;
		}
	}
	pthread_mutex_lock(&mymutex);
	c += mySum;
	pthread_mutex_unlock(&mymutex);
	pthread_exit(NULL);
	return NULL;
}
int main() {

	long pi = 0;
	clock_t t1 = clock();

	pthread_t myThreads[threadsNo];
	pthread_mutex_init(&mymutex, NULL);

	for (int i = 0; i < threadsNo; i++) {
		pthread_create(&myThreads[i], NULL, *f, (void*)i);

	}
	for (int i = 0; i < threadsNo; i++) {
		pthread_join(myThreads[i], NULL);
	}

	clock_t t2 = clock();
	cout << "number of primes less than 10 power N is : " << c << endl;
	cout << "time in sec is " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	pthread_mutex_destroy(&mymutex);
	pthread_exit(NULL);
	return 0;
}