#include<stdio.h>
#include<pthread.h>

int row = 25;
int col = 25;
pthread_mutex_t lock;

void* f1(void* args){
	FILE *fp1 = (FILE*) args;
	int i, j;
	int ones_array[row][col];
	pthread_mutex_lock(&lock);
	for(i = 0; i<row; i++){
		for(j = 0; j<col; j++){
			ones_array[i][j] = 1;
			fwrite(&ones_array[i][j], sizeof(int), 1, fp1);	
			fflush(fp1);
		}
	}
	pthread_mutex_unlock(&lock);
}


void* f2(void* args){
	FILE *fp2 = (FILE*) args;
	int i, j;
	int twos_array[row][col];
	pthread_mutex_lock(&lock);
	for(i = 0; i<row; i++){
		for(j = 0; j<col; j++){
			twos_array[i][j] = 2;
			fwrite(&twos_array[i][j], sizeof(int), 1, fp2 );
			fflush(fp2);
		}
	}
	pthread_mutex_unlock(&lock);
}
int main(){
	FILE *fp1, *fp2, *fp3;
	int test[row][col], i, j;
	pthread_mutex_init(&lock, NULL);
	fp1 = fopen("datafile", "wb");
	fp2 = fopen("datafile", "wb");
	setbuf(fp1, NULL);
	setbuf(fp2, NULL);
	pthread_t thread1;
	pthread_t thread2;
	pthread_create(&thread2, NULL, f2, fp2);
	pthread_create(&thread1, NULL, f1, fp1);	
	pthread_join(thread2, NULL);
	pthread_join(thread1, NULL);
	fclose(fp1);
	fclose(fp2);
	fp3 = fopen("datafile", "rb");
	fread(test, sizeof(int), row*col, fp3);
	for(i = 0; i<row; i++){
		for(j = 0; j<col; j++){
			printf("%d", test[i][j]);
		}
	printf("\n");
	}
	fclose(fp3);
	return 0;
}
