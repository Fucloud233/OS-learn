#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// 参考代码
// https://tuxthink.blogspot.com/2013/02/using-read-write-lock-in-pthreads.html

pthread_rwlock_t rwlock;

void *write_1(void* temp) {
	int ret = pthread_rwlock_wrlock(&rwlock);
	printf("\nFile locked, please enter the message \n");
	

	char *str = (char *)malloc(10 * sizeof(char));
	scanf("%s", str);
	
	FILE *file1 = fopen("temp", "w");
	fprintf(file1, "%s", str);
	fclose(file1);
	free(str);

	pthread_rwlock_unlock(&rwlock);
	printf("\nUnlocked the file you can read it now \n");

	pthread_exit((void *)ret);
}

void *write_2(void *temp) {
	sleep(3);
	int ret = pthread_rwlock_wrlock(&rwlock);
	printf("\nFile locked, please enter the message \n");
	

	char *str = (char *)malloc(10 * sizeof(char));
	scanf("%s", str);
	
	FILE *file1 = fopen("temp", "a");
	fprintf(file1, "%s", str);
	fclose(file1);
	free(str);

	pthread_rwlock_unlock(&rwlock);
	printf("\nUnlocked the file you can raed it now \n");
	
	pthread_exit((void *)ret);
}

void *read_1(void *temp) {
	int ret = pthread_rwlock_rdlock(&rwlock);
	printf("\n1 Opening file for reading\n");

	FILE *file1 = fopen("temp", "r");
	
	char *str = (char *)malloc(10 *sizeof(char));
	fscanf(file1, "%s", str);
	
	fclose(file1);
	
	printf("\nMessage from file is %s \n", str);

	sleep(3);
	
	pthread_rwlock_unlock(&rwlock);
	printf("\nUnlocking rwlock\n");
	pthread_exit((void *)ret);

}

void* read_2(void *temp) {
	sleep(6);
	
	int ret = pthread_rwlock_rdlock(&rwlock);
	
	FILE *file1 = fopen("temp", "r");
	
	printf("\n2 Opening file for reading\n");

	char* str = (char *)malloc(10 *sizeof(char));
	fscanf(file1, "%s", str);

	fclose(file1);
	
	pthread_rwlock_unlock(&rwlock);
	printf("\nMessage from file %s \n", str);

	pthread_exit((void *)ret);
}

int main() {
	pthread_t thread_id[4];
	pthread_attr_t atrr;

	int ret;
	pthread_rwlock_init(&rwlock, NULL);

	ret = pthread_create(&thread_id[0], NULL, write_1, NULL);
	ret = pthread_create(&thread_id[1], NULL, write_2, NULL);
	ret = pthread_create(&thread_id[2], NULL, read_1, NULL);
	ret = pthread_create(&thread_id[3], NULL, read_2, NULL);
	
	printf("\n Created thread");

	for(int i=0; i<4; i++) 
		pthread_join(thread_id[i], (void*)ret);
	
	pthread_rwlock_destroy(&rwlock);
}

