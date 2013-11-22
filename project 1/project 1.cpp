#include<stdio.h>
#include<time.h>
#include<malloc.h>

//时间变量定义
clock_t  start, stop;
double  duration;

//函数定义
int iterseq(int* test, int N, int num);//定义迭代顺序查找函数
int iterbin(int* test, int N, int num);//定义迭代二分查找函数
int recurseq(int* test, int i, int N, int num);//定义递归顺序查找函数
int recurbin(int* test, int i, int j, int N, int num);//定义递归二分查找函数

int main(void){

	//变量定义
	int N;//搜索数据数量大小
	int K;//循环运行函数的次数
	int i, j;
	char runagain;//用来实现询问用户是否需要多次测量程序
	char Kneeded;//用来实现询问用户是否需要多次循环运行函数（是否需要输入K值）
	int* test;//创建数组，来存放1至(N-1)。考虑到N最多只到10000，所以创建最多可含10000个元素的数组
	FILE *fp;
	char ch;
	int tempdata;
	int findnumber;//需要寻找的数

	do{
		printf("Please enter the number N:\n");
		scanf("%d", &N);
		getchar();
		//读取N

		test = (int *) malloc(sizeof(int) * N);//动态分配内存
		if ((fp = fopen("data.txt", "r")) == NULL){
			printf("can't open file\n");
			return -1;
		}
		//读入文件

		for (i = 0; i < N; i++){
			fscanf(fp, "%d", &tempdata);
			test[i] = tempdata;
		}

		printf("Please enter the number you want to search.\n");
		scanf("%d", &findnumber);
		getchar();

		for (j = 0; j < N; j++){
			test[j] = j;
		}//根据N的大小，给数组赋值

		printf("Do you need to enter the number K? (Y/N)\n");
		scanf("%c", &Kneeded);
		getchar();
		//用来提醒是否需要输入K值，并用字符变量Kneeded存放用户的选择

		//根据是否需要输入K，分别进入以下两种情况
		if (Kneeded == 'Y'){
			//用户需要输入K值

			printf("Please enter the number K:\n");
			scanf("%d", &K);
			getchar();
			//对于需要输入K的情况，提醒用户输入K值，并存储至整型变量K

			start = clock();
			for (i = 0; i < K; i++){
				iterseq(test, N, findnumber);
			}
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//测量循环K次的迭代顺序查找所需的时间
			printf("%lf seconds is needed to finish the iterative version of %d-number sequential search for %d times and every time takes %e seconds.\n", duration, N, K, duration / K);
			//输出结果

			start = clock();
			for (i = 0; i < K; i++){
				iterbin(test, N, findnumber);
			}
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//测量循环K次的迭代二分查找所需的时间
			printf("%lf seconds is needed to finish the iterative version of %d-number binary search for %d times and every time takes %e seconds.\n", duration, N, K, duration / K);
			//输出结果

			start = clock();
			for (i = 0; i < K; i++){
				recurseq(test, 0, N, findnumber);
			}
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//测量循环K次的递归顺序查找所需的时间
			printf("%lf seconds is needed to finish the recursive version of %d-number sequential search for %d times and every time takes %e seconds.\n", duration, N, K, duration / K);
			//输出结果

			start = clock();
			for (i = 0; i < K; i++){
				recurbin(test, 0, N - 1, N, findnumber);
			}
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//测量循环K次的递归二分查找所需的时间
			printf("%lf seconds is needed to finish the recursive version of %d-number binary search for %d times and every time takes %e seconds.\n", duration, N, K, duration / K);
			//输出结果

			printf("Need to run again? (Y/N)\n");
			scanf("%c", &runagain);
			//询问用户是否需要继续进行测量，如果不需要，则退出while循环
		}
		else{
			//用户不需要输入K值

			start = clock();
			iterseq(test, N, findnumber);
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//测量迭代顺序查找所需的时间
			printf("%e seconds is needed to finish the iterative version of %d-number sequential search.\n", duration, N);
			//输出结果

			start = clock();
			iterbin(test, N, findnumber);
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//测量迭代二分查找所需的时间
			printf("%e seconds is needed to finish the iterative version of %d-number binary search.\n", duration, N);
			//输出结果

			start = clock();
			recurseq(test, 0, N, findnumber);
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//测量递归顺序查找所需的时间
			printf("%e seconds is needed to finish the recursive version of %d-number sequential search.\n", duration, N);
			//输出结果

			start = clock();
			recurbin(test, 0, N - 1, N, findnumber);
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//测量递归二分查找所需的时间
			printf("%e seconds is needed to finish the recursive version of %d-number binary search.\n", duration, N);
			//输出结果

			printf("Need to run again? (Y/N)\n");
			scanf("%c", &runagain);
			getchar();
			//询问用户是否需要继续进行测量，如果不需要，则退出while循环
		}
	} while (runagain == 'Y');

	return 0;
}

//定义迭代顺序查找函数
int iterseq(int* test, int N, int num){
	int i;
	for (i = 0; i < N; i++){
		if (test[i] == num)
			return i;
	}
	return -1;
}

//定义迭代二分查找函数
int iterbin(int* test, int N, int num){
	int i = 0;
	int j = N - 1;
	while ((j - i) > 1){
		if ((i + j) % 2 == 0){
			if (test[(i + j) / 2] < num){
				i = (i + j) / 2;
			}
			else if (test[(i + j) / 2] > num){
				j = (i + j) / 2;
			}
			else{
				return (i + j) / 2;
			}
		}
		else{
			if (test[(i + j - 1) / 2] < num){
				i = (i + j - 1) / 2;
			}
			else if (test[(i + j - 1) / 2] > num){
				j = (i + j - 1) / 2;
			}
			else{
				return (i + j - 1) / 2;
			}
		}
	}
	return -1;
}

//定义递归顺序查找函数
int recurseq(int* test, int i, int N, int num){
	if (i < N){
		if (test[i] == num){
			return i;
		}
		else{
			i = recurseq(test, i + 1, N, num);
			return i;
		}
	}
	else{
		return -1;
	}
}

//定义递归二分查找函数
int recurbin(int* test, int i, int j, int N, int num){
	if (test[i] == num){
		return i;
	}
	else if (test[j] == num){
		return j;
	}
	else{
		while ((j - i) > 1){
			if ((i + j) % 2 == 0){
				if (test[(i + j) / 2] < num){
					return recurbin(test, (i + j) / 2, j, N, num);
				}
				else if (test[(i + j) / 2] > num){
					return recurbin(test, i, (i + j) / 2, N, num);
				}
				else{
					return (i + j) / 2;
				}
			}
			else{
				if (test[(i + j - 1) / 2] < num){
					return recurbin(test, (i + j - 1) / 2, j, N, num);
				}
				else if (test[(i + j - 1) / 2] > num){
					return recurbin(test, i, (i + j - 1) / 2, N, num);
				}
				else{
					return (i + j - 1) / 2;
				}
			}
		}
		return -1;
	}
}