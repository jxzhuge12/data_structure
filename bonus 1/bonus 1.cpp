#pragma warning(disable:4996)
#include<stdio.h>

int main(void){
	int N, L;
	int i,j,k;
	do{
		scanf("%d", &N);
		if (N == 0)
			break;
		else if (N == 1){
			scanf(" %d\n", &L);
			int sample;
			scanf("%d", &sample);
			getchar();
			for (j = 0; j < L; j++){
				int test;
				scanf("%d", &test);
				getchar();
				printf("Yes\n");
			}
		}
		else{
			scanf(" %d\n", &L);
			int samplematrix[11][11];
			for (i = 0; i < 11; i++){
				for (j = 0; j < 11; j++){
					samplematrix[i][j] = 0;
				}
			}
			int sample[11];
			for (i = 1; i < 11; i++){
				sample[i] = 0;
			}
			scanf("%d", &sample[1]);
			for (j = 2; j <= N; j++){
				scanf(" %d", &sample[j]);
			}
			getchar(); //读入样本数据
			//对样本数据进行树的构建
			samplematrix[sample[1]][sample[2]] = 1;
			for (i = 3; i <= N; i++){
				int temp = sample[1];
				while (temp != 0){
					int flag = 0;
					if (sample[i] < temp){
						for (k = temp; k > 0; k--){
							if (samplematrix[temp][k] == 1){
								temp = k;
								flag = 1;
								break;
							}
						}
					}
					else{
						for (k = temp; k <= N; k++){
							if (samplematrix[temp][k] == 1){
								temp = k;
								flag = 1;
								break;
							}
						}
					}
					if (flag == 0){
						samplematrix[temp][sample[i]] = 1;
						temp = 0;
					}
				}
			}
			//开始读取后L行，与样本数据进行比较
			for (j = 0; j < L; j++){
				int allflag = 0;
				int matrix[11][11];
				for (i = 0; i < 11; i++){
					for (k = 0; k < 11; k++){
						matrix[i][k] = 0;
					}
				}
				int test[11];
				for (i = 1; i < 11; i++){
					test[i] = 0;
				}
				scanf("%d", &test[1]);
				for (i = 2; i <= N; i++){
					scanf(" %d", &test[i]);
				}
				getchar();
				matrix[test[1]][test[2]] = 1;
				for (i = 3; i <= N; i++){
					int temp = test[1];
					while (temp != 0){
						int flag = 0;
						if (test[i] < temp){
							for (k = temp; k > 0; k--){
								if (matrix[temp][k] == 1){
									temp = k;
									flag = 1;
									break;
								}
							}
						}
						else{
							for (k = temp; k <= N; k++){
								if (matrix[temp][k] == 1){
									temp = k;
									flag = 1;
									break;
								}
							}
						}
						if (flag == 0){
							matrix[temp][test[i]] = 1;
							temp = 0;
						}
					}
				}
				for (i = 1; i < 11; i++){
					for (k = 1; k < 11; k++){
						if (samplematrix[i][k] != matrix[i][k]){
							allflag = 1;
						}
					}
				}
				if (allflag == 0){
					printf("Yes\n");
				}
				else{
					printf("No\n");
				}
			}
		}
	} while (1);

	return 0;
}