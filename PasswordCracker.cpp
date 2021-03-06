//First thread checks 000 - 323, second checks 333 - 665, third checks 666 - 999. 
//These threads do not need to interact at all.They can be run on entirely different computers.
//implement a variable guessed_the_password which will turn on if one of the threads guesses the password and tells the other threads to stop guessing.

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;


int password = 500;
int max_password_limit = 999;
int found_password;
bool password_reached = false;
condition_variable password_cv;
mutex password_m;

void myThreadFunc(int search_between, int i) {


	for (int n = (search_between * i); !password_reached && n <= (search_between * (i + 1)); n++) {
		if (n == password) {
			password_m.lock();
			found_password = n;
			password_cv.notify_all();
			password_reached = true;
			password_m.unlock();
			return;
		}
	}
}

int main() {
	int search_between = max_password_limit / 3;

	thread myThreads[3];

	for (int i = 0; i < 3; i++) {
		myThreads[i] = thread(myThreadFunc, search_between, i);
	}

	unique_lock<mutex> lk(password_m);
	password_cv.wait(lk, [] { return password_reached; });

	for (int n = 0; n < 3; n++) {
		myThreads[n].join();
	}
	cout << found_password << endl;
}
