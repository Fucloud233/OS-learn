#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int thread_num = 0;
int max_thread_num = 0;

int fib(int n) {
	if(n<=1)
		return 1;
	else
		return fib(n-1) + fib(n-2);
}

void *fib_thread(void *);

int create_thread(pthread_t *thread, int *argv) {
	if(thread_num == max_thread_num)
		return 0;
	pthread_create(thread, NULL, fib_thread, (void *)argv);
	thread_num++;
	return 1;
}

int wait_thread(pthread_t *thread) {
	int ret_value;
	pthread_join(*thread, (void *)&ret_value);
	thread_num--;
	return ret_value;
}

void *fib_thread(void* n_pointer) {
	int n = *(int *)n_pointer;

	if(n<=1) 
		pthread_exit((void *)1);
	else {
		pthread_t thread1, thread2;
		// 创建线程
		int flag1, flag2;
		int n1 = n-1, n2 = n-2;
		flag1 = create_thread(&thread1, &n1);
		flag2 = create_thread(&thread2, &n2);
		
		// 等待线程结束
		// 如果没有创建线程 则调用递归的fib解决
		int ret1, ret2;
		if (flag1)
			pthread_join(thread1, (void *)&ret1);
		else
			ret1 = fib(n1);
		if (flag2) 
			pthread_join(thread2, (void *)&ret2);
		else
			ret2 = fib(n2);
		// 返回 最终结果
		int res = ret1 + ret2;
		pthread_exit((void *)res);
	}
	thread_num--;
}

int main(int argc, char* argv[]) {
	if (argc!=3) {
		printf("usage:%s <n> <pthread number>\n", argv[0]);
		exit(1);
	}
	
	int n = atoi(argv[1]);
	max_thread_num = atoi(argv[2]) + 1;
	int res;
	pthread_t thread;
	
	pthread_create(&thread, NULL, fib_thread, (void *)&n);
	pthread_join(thread, (void *)&res);
	printf("Result: %d\n", res); 
}
