#include <pthread.h>
#include <stdio.h>

void *fib(void* n_pointer) {
	int n = *(int *)n_pointer;

	if(n<=1)
		pthread_exit((void*)1);
	else {
		pthread_t thread1, thread2;
		int n1 = n-1, n2 = n-2;	

		// 创建线程
		pthread_create(&thread1, NULL, fib, (void *)&n1);
		pthread_create(&thread2, NULL, fib, (void *)&n2);
		
		int ret1, ret2;		
		// 等待线程
		pthread_join(thread1, (void *)&ret1);
		pthread_join(thread2, (void *)&ret2);		
		
		// 退出进程
		int result = ret1 + ret2;
		pthread_exit((void*)result);
	}
}

int main(){
	pthread_t thread;
	int n = 100, ret;
	// printf("Main Thread Running\n");
	pthread_create(&thread, NULL, fib, (void *) &n);
	pthread_join(thread, (void *)&ret);
	printf("fib(%d) = %d\n", n, ret);	
}
