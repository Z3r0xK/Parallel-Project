#include<iostream>
#include<omp.h>
#include<ctime>
#include<math.h>
//#include<fstream>
using namespace std;
const int N = 6;
const long x = pow(10, N);

bool isPrime(long n) {
	if (n == 1 || n == 0)
		return false;
	else {

		for (int i = 2; i <= sqrt(n); ++i) {
			if (n % i == 0) {
				return false;
			}
		}
		return true;
	}
}

int main() {

    //ofstream out("openMP.txt");
	long pi = 0;
	clock_t t1 = clock();

#pragma omp parallel num_threads(12), reduction(+:pi) 
	{
#pragma omp for schedule(guided)
		for (int i = 0; i <= x; i++)
		{
			if (isPrime(i)){
				pi+=1;
				//out<<i<<endl;
			}
		}
	}

	clock_t t2 = clock();
	cout << "number of primes less than 10 power N is : " << pi << endl;
	cout << "time in sec is " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;

	return 0;
}