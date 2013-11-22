#include<stdio.h>
#include<time.h>
#include<malloc.h>

//ʱ���������
clock_t  start, stop;
double  duration;

//��������
int iterseq(int* test, int N, int num);//�������˳����Һ���
int iterbin(int* test, int N, int num);//����������ֲ��Һ���
int recurseq(int* test, int i, int N, int num);//����ݹ�˳����Һ���
int recurbin(int* test, int i, int j, int N, int num);//����ݹ���ֲ��Һ���

int main(void){

	//��������
	int N;//��������������С
	int K;//ѭ�����к����Ĵ���
	int i, j;
	char runagain;//����ʵ��ѯ���û��Ƿ���Ҫ��β�������
	char Kneeded;//����ʵ��ѯ���û��Ƿ���Ҫ���ѭ�����к������Ƿ���Ҫ����Kֵ��
	int* test;//�������飬�����1��(N-1)�����ǵ�N���ֻ��10000�����Դ������ɺ�10000��Ԫ�ص�����
	FILE *fp;
	char ch;
	int tempdata;
	int findnumber;//��ҪѰ�ҵ���

	do{
		printf("Please enter the number N:\n");
		scanf("%d", &N);
		getchar();
		//��ȡN

		test = (int *) malloc(sizeof(int) * N);//��̬�����ڴ�
		if ((fp = fopen("data.txt", "r")) == NULL){
			printf("can't open file\n");
			return -1;
		}
		//�����ļ�

		for (i = 0; i < N; i++){
			fscanf(fp, "%d", &tempdata);
			test[i] = tempdata;
		}

		printf("Please enter the number you want to search.\n");
		scanf("%d", &findnumber);
		getchar();

		for (j = 0; j < N; j++){
			test[j] = j;
		}//����N�Ĵ�С�������鸳ֵ

		printf("Do you need to enter the number K? (Y/N)\n");
		scanf("%c", &Kneeded);
		getchar();
		//���������Ƿ���Ҫ����Kֵ�������ַ�����Kneeded����û���ѡ��

		//�����Ƿ���Ҫ����K���ֱ���������������
		if (Kneeded == 'Y'){
			//�û���Ҫ����Kֵ

			printf("Please enter the number K:\n");
			scanf("%d", &K);
			getchar();
			//������Ҫ����K������������û�����Kֵ�����洢�����ͱ���K

			start = clock();
			for (i = 0; i < K; i++){
				iterseq(test, N, findnumber);
			}
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//����ѭ��K�εĵ���˳����������ʱ��
			printf("%lf seconds is needed to finish the iterative version of %d-number sequential search for %d times and every time takes %e seconds.\n", duration, N, K, duration / K);
			//������

			start = clock();
			for (i = 0; i < K; i++){
				iterbin(test, N, findnumber);
			}
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//����ѭ��K�εĵ������ֲ��������ʱ��
			printf("%lf seconds is needed to finish the iterative version of %d-number binary search for %d times and every time takes %e seconds.\n", duration, N, K, duration / K);
			//������

			start = clock();
			for (i = 0; i < K; i++){
				recurseq(test, 0, N, findnumber);
			}
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//����ѭ��K�εĵݹ�˳����������ʱ��
			printf("%lf seconds is needed to finish the recursive version of %d-number sequential search for %d times and every time takes %e seconds.\n", duration, N, K, duration / K);
			//������

			start = clock();
			for (i = 0; i < K; i++){
				recurbin(test, 0, N - 1, N, findnumber);
			}
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//����ѭ��K�εĵݹ���ֲ��������ʱ��
			printf("%lf seconds is needed to finish the recursive version of %d-number binary search for %d times and every time takes %e seconds.\n", duration, N, K, duration / K);
			//������

			printf("Need to run again? (Y/N)\n");
			scanf("%c", &runagain);
			//ѯ���û��Ƿ���Ҫ�������в������������Ҫ�����˳�whileѭ��
		}
		else{
			//�û�����Ҫ����Kֵ

			start = clock();
			iterseq(test, N, findnumber);
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//��������˳����������ʱ��
			printf("%e seconds is needed to finish the iterative version of %d-number sequential search.\n", duration, N);
			//������

			start = clock();
			iterbin(test, N, findnumber);
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//�����������ֲ��������ʱ��
			printf("%e seconds is needed to finish the iterative version of %d-number binary search.\n", duration, N);
			//������

			start = clock();
			recurseq(test, 0, N, findnumber);
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//�����ݹ�˳����������ʱ��
			printf("%e seconds is needed to finish the recursive version of %d-number sequential search.\n", duration, N);
			//������

			start = clock();
			recurbin(test, 0, N - 1, N, findnumber);
			stop = clock();
			duration = ((double) (stop - start)) / CLK_TCK;
			//�����ݹ���ֲ��������ʱ��
			printf("%e seconds is needed to finish the recursive version of %d-number binary search.\n", duration, N);
			//������

			printf("Need to run again? (Y/N)\n");
			scanf("%c", &runagain);
			getchar();
			//ѯ���û��Ƿ���Ҫ�������в������������Ҫ�����˳�whileѭ��
		}
	} while (runagain == 'Y');

	return 0;
}

//�������˳����Һ���
int iterseq(int* test, int N, int num){
	int i;
	for (i = 0; i < N; i++){
		if (test[i] == num)
			return i;
	}
	return -1;
}

//����������ֲ��Һ���
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

//����ݹ�˳����Һ���
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

//����ݹ���ֲ��Һ���
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