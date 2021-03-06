#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>

using namespace std;
using namespace std::chrono;

double score = 0.0;
mutex score_mutex;

void myThreadFunc() {
	for (int i = 0; i < 1000000; i++) {
		score_mutex.lock();
		score = score + 1.0;
		score_mutex.unlock();
	}
}

int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	
	thread myThreads[10];

	for (int i = 0; i < 10; i++) {
		myThreads[i] = thread(myThreadFunc);
	}

	for (int n = 0; n < 10; n++) {
		myThreads[n].join();
	}

	cout << score << endl;
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "It took me " << time_span.count() << " seconds.";
	std::cout << std::endl;

}


//When sharing a common resource in a thread, you must stop other threads from accessing said resource during computation 
//In order to do this, we create a global mutex that we lock before accessing the common resource
//This prevents all otehr threads from accessing it whilst they are running 
//After we have altered the common resource, we unlock it allowing it to be used again by another thread
