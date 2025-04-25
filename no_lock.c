#include<stdio.h>
#include<pthread.h>

void* f1(void* args){
	File *fp1 = (File*) args;
	int i, j;
	int ones_array[25][25];
	for(i = 0; i<25; i++){
		for(j = 0; j<25; j++){
			ones_array[i][j] = 1;
			fwrite(&ones_array[i][j], sizeof(int), 1, fp1);	
		}
	}
}


void* f2(void* args){
	File *fp2 = (File*) args;
	int i, j;
	int twos_array[25][25];
	for(i = 0; i<25; i++){
		for(j = 0; j<25; j++){
			twos_array[i][j] = 2;
			fwrite(&twos_array[i][j], sizeof(int), 1, fp2 );
		}
	}
}
int main(){
	FILE *fp1, *fp2;
	int test[25][25];
	fp1 = fopen("datafile", "ab");
	fp2 = fopen("datafile", "ab");
	pthread_t thread1;
	pthread_t thread2;
	pthread_create(&thread1, NULL, f1, fp1);	
	pthread_create(&thread2, NULL, f2, fp2);
	pthread_join(thread1);
	pthread_join(thread2);
	return 0;
}
