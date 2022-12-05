#include<pthread.h>
#include <iostream>
#include <ctime>
#include<string>
#include <math.h>
#include<fstream>
using namespace std;
const int N = 6;
const long x = pow(10.0, N);

#define threadsNo 10

long  len = x / threadsNo;
// c = total sum 
int c;
pthread_mutex_t  mymutex;

ofstream out("PthreadOut.txt", ios::app);

bool isPrime(long n) {
	if (n == 1 || n == 0)
		return false;
	else {

		for (int i = 2; i <= sqrt((double)n); ++i) {
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
			/*pthread_mutex_lock(&mymutex);
			out<<i<<endl;
			pthread_mutex_unlock(&mymutex);*/
		}
	}
	pthread_mutex_lock(&mymutex);
	c += mySum;
	pthread_mutex_unlock(&mymutex);
	pthread_exit(NULL);
	return NULL;
}

void main() {

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
	out.close();
	system("pause");
}