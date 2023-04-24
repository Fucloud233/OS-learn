#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

int thread_num = 0;
int max_thread_num = 0;

// 原始斐波那契递归函数
int fib(int n) {
	if(n<=1)
		return 1;
	else
		return fib(n-1) + fib(n-2);
}

void *fib_thread(void *);

// 用于创建线程 当达到最大线程数时 则返回false
// 注意: 这里要传入指针 否则就是临时变量 会被回收内存
int create_thread(pthread_t *thread, int *argv) {
	if(thread_num == max_thread_num)
		return 0;
	pthread_create(thread, NULL, fib_thread, (void *)argv);
	thread_num++;
	return 1;
}

// 不能单独调用函数来等待线程
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
		int n1 = n-1, n2 = n-2;

		// 创建线程
		int flag1, flag2;
		flag1 = create_thread(&thread1, &n1);
		flag2 = create_thread(&thread2, &n2);
		
		// 等待线程 如果没有创建线程 则调用fib函数
		int ret1, ret2;
		if (flag1)
			pthread_join(thread1, (void *)&ret1);
		else
			ret1 = fib(n1);
		if (flag2) 
			pthread_join(thread2, (void *)&ret2);
		else
			ret2 = fib(n2);
		
		// 退出进程
		int result = ret1 + ret2;
		pthread_exit((void *)result);
	}
}

int main(int argc, char* argv[]) {
	// 1. 读取外部参数
	if (argc!=3) {
		printf("usage:%s <n> <pthread number>\n", argv[0]);
		exit(1);
	}

	int n = atoi(argv[1]);
	int n1 = n-1, n2 = n-2;
	max_thread_num = atoi(argv[2]);
	
	// 2. 记录结果
	int ret1, ret2, res;
	struct timeval start_time, end_time;
	double exec_time;

	// 3. 创建线程
	pthread_t thread1, thread2;

	gettimeofday(&start_time, NULL);
	
	int flag1, flag2;
	flag1 = create_thread(&thread1, &n1);
	flag2 = create_thread(&thread2, &n2);
	
	if(flag1)
		pthread_join(thread1, (void *)&ret1);
	else
		ret1 = fib(n1);

	if(flag2)
		pthread_join(thread2, (void *)&ret2);
	else
		ret2 = fib(n2);
	res = ret1 + ret2;
	
	gettimeofday(&end_time, NULL);

	// 4. 计算执行时间
	exec_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
	exec_time += (end_time.tv_usec - start_time.tv_usec) / 1000.0;
	
	// 5. 输出结果
	printf("Result: %3d, (%.3fms)\n", res, exec_time); 
//	printf("%.3f", exec_time);
}
