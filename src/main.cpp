///////////////////////////////////////////Using global variables///////////////////////////////////////////

#include<iostream>
#include<pthread.h>
#include<cstring>
using namespace std;

pthread_t tid1, tid2, tid3;
	
void* reverse(void* arg) {
	char* str = (char*)arg;
	int count = strlen(str), size = count;

	for (int i = 0; i < size/2 ; i++) {
		char temp = str[i];
		str[i] = str[count-1];
		str[count-1] = temp;
		count--;
	}
}

void* upperCase(void* arg) {
	pthread_join(tid1, NULL);

	char* str = (char*) arg;

	for (int i = 0 ; str[i] != '\0'; i++) {
		str[i] -= 32;
	}
}


void* display(void* arg) {
	pthread_join(tid2, NULL);

	cout << (char*)arg << endl;
}

int  main() {
	char* str = new char;
	
	cout << "Enter input: ";
	cin >> str;

	pthread_create(&tid1, NULL, reverse, (void*)str);
	pthread_create(&tid2, NULL, upperCase, (void*)str);
	pthread_create(&tid3, NULL, display, (void*)str);

	pthread_join(tid3, NULL);
	delete str;

	pthread_exit(NULL);
	
	return 0;
}