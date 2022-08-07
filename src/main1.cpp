///////////////////////////////////////////Without using global variables///////////////////////////////////////////

#include<iostream>
#include<pthread.h>
#include<cstring>
using namespace std;
	
void* reverse(void* arg) {
	char* str = (char*)arg;
	int count = strlen(str), size = count;

	for (int i = 0; i < size/2 ; i++) {
		char temp = str[i];
		str[i] = str[count-1];
		str[count-1] = temp;
		count--;
	}

	pthread_exit((void*)str);
}

void* upperCase(void* arg) {
	void* status;
	pthread_join(*((pthread_t*)arg), &status);

	char* str = (char*)status;

	for (int i = 0 ; str[i] != '\0'; i++) {
		str[i] -= 32;
	}

	pthread_exit((void*)str);
}


void* display(void* arg) {
	void* status;
	pthread_join(*((pthread_t*)arg), &status);

	cout << (char*)status << endl;
}

int  main() {
	pthread_t tid1, tid2, tid3;
	char* str = new char;
	
	cout << "Enter input: ";
	cin >> str;

	pthread_create(&tid1, NULL, reverse, (void*)str);
	pthread_create(&tid2, NULL, upperCase, (void*)tid1);
	pthread_create(&tid3, NULL, display, (void*)tid2);

	pthread_join(tid3, NULL);
	delete str;

	pthread_exit(NULL);
	
	return 0;
}