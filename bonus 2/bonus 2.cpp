#pragma warning(disable:4996)
#include<stdio.h>

int N;
int total = 0;
int number[1000];
int adjacent[1000][1000];
int status[1000];

int trans(int N, int num);

int main(void){
	int i, j;
	scanf("%d", &N);
	do{
		for (i = 0; i < N; i++){
			for (j = 0; j < N; j++){
				adjacent[i][j] = 0;
			}
		}
		for (i = 0; i < N; i++){
			scanf("%d", &number[i]);
		}

		for (i = 0; i < N; i++){
			if (number[i] >= 0){
				status[i] = i - number[i] % N + 1;
				if (status[i] <= 0)
					status[i] += N;
			}
			else{
				status[i] = 0;
				total++;
			}
		}

		for (i = 0; i < N; i++){
			if (status[i] > 1){
				for (j = 1; status[i] - j >= 1; j++){
					adjacent[trans(N, i - j)][i] = 1;
				}
			}
		}

		int pos = 0;
		int flag = 0;
		while (total < N)
		{
			int min = 10000000;
			for (i = 0; i < N; i++){
				if (status[i] == 1 && number[i] < min){
					min = number[i];
					pos = i;
				}
			}
			if (flag == 0){
				printf("%d", min);
				flag++;
				total++;
				status[pos] = 0;
			}
			else{
				printf(" %d", min);
				total++;
				status[pos] = 0;
			}
			for (i = 0; i < N; i++){
				if (adjacent[pos][i] == 1){
					adjacent[pos][i] = 0;
					status[i]--;
				}
			}
		}

		printf("\n");
		total = 0;
		scanf("%d", &N);
	} while (N != 0);
	return 0;
}

int trans(int N, int num){
	if (num < 0)
		num = num + N;
	return num;
}