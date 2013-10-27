#include<stdio.h>

void genergo();
int header(int posit);
void merge(int* costall);

int N, M;
int citytemp[1001][1001];//生成citytemp
int go[1001];

int main(void){
	int i, j, k, q;
	scanf("%d", &N);//输入N
	do{
		int highway[1001][1001];
		for (i = 1; i <= N; i++){
			for (j = 1; j <= N; j++){
				highway[i][j] = -1;
			}
		}//给highway中所有数据赋初值-1
		int costall[1001];//生成costall，来存储删除第i个节点后，需要costall[i]的损失
		int statue, cost;
		int city1, city2;
		scanf("%d", &M);
		for (i = 0; i < M; i++){
			scanf("%d %d %d %d", &city1, &city2, &cost, &statue);
			if (statue == 1){
				highway[city1][city2] = 0;
				highway[city2][city1] = 0;
			}
			else{
				highway[city1][city2] = cost;
				highway[city2][city1] = cost;
			}
		}//对于有联通路的两个城市，将距离设为0，而断路的两个城市，将距离设为价格

		for (i = 1; i <= N; i++){//对于删除每个节点
			for (j = 1; j <= N; j++){
				if (j == i)
					continue;
				for (k = 1; k <= N; k++){
					if (k == i)
						continue;
					if (j > i){
						if (k > i)
							citytemp[j - 1][k - 1] = highway[j][k];
						else
							citytemp[j - 1][k] = highway[j][k];
					}
					else{
						if (k > i)
							citytemp[j][k - 1] = highway[j][k];
						else
							citytemp[j][k] = highway[j][k];
					}
				}
			}//对highway矩阵去掉第i行，第i列，存入citytemp中

			for (q = 1; q < N; q++){
				go[q] = -1;
			}
			genergo();
			merge(&costall[i]);
		}

		int max = 0;
		for (i = 1; i <= N; i++){
			if (costall[i] > max){
				max = costall[i];
			}
		}//找出costall里最大的，也就是说最多的损失
		if (max == 0)
			printf("0\n");//若最大的损失是0，就输出0
		else{
			int flag = 0;
			for (i = 1; i <= N; i++){
				if (costall[i] == max){
					if (flag == 0){
						flag++;
						printf("%d", i);
					}
					else
						printf(" %d", i);
				}
			}
			printf("\n");
		}//如果最大的损失不是0，那么输出和最大损失相同的城市编号
		scanf("%d", &N);
	} while (N != 0);
	return 0;
}

void genergo(){
	int i, j;
	for (i = 1; i < N; i++){
		for (j = 1; j < i; j++){
			if (citytemp[i][j] == 0){
				if (go[i] < 0 && go[j] < 0){
					go[i] = go[i] + go[j];
					go[j] = i;
				}
				else if (go[i] > 0 && go[j] < 0){
					go[j] = go[j] + go[header(i)];
					go[header(i)] = j;
				}
				else if (go[i] < 0 && go[j] > 0){
					go[i] = go[i] + go[header(j)];
					go[header(j)] = i;
				}
				else{
					go[header(i)] = go[header(i)] + go[header(j)];
					go[header(j)] = header(i);
				}
			}
		}
	}
}

int header(int posit){
	while (go[posit] > 0)
		posit = go[posit];
	return posit;
}

void merge(int* costall){
	int i, j, k;
	*costall = 0;
	int num = 0;
	for (i = 1; i < N; i++){
		if (go[i] < 0)
			num++;
	}
	int temp[1001][1001];
	for (i = 1; i < N; i++){
		for (j = 1; j < i; j++){
			temp[i][j] = -1;
			if (go[header(j)] != go[header(i)]){
				temp[i][j] = citytemp[i][j];
			}
		}
	}
	int min = 0;
	for (i = 1; i < num; i++){
		int temp2 = 0;
		for (j = 1; j < N; j++){
			for (k = 1; k < j; k++){
				if (temp[j][k] > 0){
					if (temp2 == 0){
						min = temp[j][k];
						temp2++;
					}
					else{
						if (temp[j][k] < min){
							min = temp[j][k];
						}
					}
				}
			}
		}
		int temp3 = 0;
		for (j = 1; j < N; j++){
			for (k = 1; k < j; k++){
				if (temp[j][k] == min){
					temp[j][k] = -1;
					temp3++;
					break;
				}
			}
			if (temp3 == 1)
				break;
		}
		*costall += min;
	}
}