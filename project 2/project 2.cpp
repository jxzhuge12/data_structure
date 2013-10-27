#include<stdio.h>
#include<malloc.h>

typedef struct TreeNode *PtrToNode;

struct TreeNode{
	char name[2];
	PtrToNode FirstChild;
	PtrToNode NextSibling;
};

int redundance(PtrToNode *place, char *test, int temp);
PtrToNode testrootid(PtrToNode *place, int N);
int findplace(PtrToNode *place, char *test, int temp);
void freeall(PtrToNode *place, int N);
void reverse(PtrToNode RootID, int * time, int height);

int main(void){
	int N, M;
	scanf("%d %d", &N, &M);
	getchar();

	while (N != 0){
		if (M == 0){
			printf("1\n");
		}
		else{
			PtrToNode *place = (PtrToNode *) malloc(N * sizeof(PtrToNode)); //生成一维数组。总共有N个元素，用来存放节点的地址
			int temp = 0;
			int temp2;
			int num;
			int placenum, placenum2;
			int i, j;
			int height;
			int *time = (int *) malloc(sizeof(int) * N);
			for (i = 0; i < N; i++){
				time[i] = 0;
			}
			PtrToNode RootID = (PtrToNode) malloc(sizeof(struct TreeNode)); //存储01节点的地址
			RootID->FirstChild = NULL;
			RootID->NextSibling = NULL;
			char test[2]; //读取节点名字
			for (i = 0; i < M; i++){
				scanf("%c%c ", &test[0], &test[1]);
				if (redundance(place, test, temp) == 0){
					place[temp] = (PtrToNode) malloc(sizeof(struct TreeNode));
					place[temp]->FirstChild = NULL;
					place[temp]->NextSibling = NULL;
					placenum = temp;
					place[temp]->name[0] = test[0];
					place[temp]->name[1] = test[1];
					temp++;
				} //没有重复节点出现过
				else{
					placenum = findplace(place, test, temp);
				} //有重复节点出现过
				scanf("%d", &num);
				for (j = 0; j < num; j++){
					scanf(" %c%c", &test[0], &test[1]);
					if (j == 0){
						if (redundance(place, test, temp) == 0){
							place[temp] = (PtrToNode) malloc(sizeof(struct TreeNode));
							place[temp]->FirstChild = NULL;
							place[temp]->NextSibling = NULL;
							place[temp]->name[0] = test[0];
							place[temp]->name[1] = test[1];
							place[placenum]->FirstChild = place[temp];
							temp2 = temp;
							temp++;
						}
						else{
							placenum2 = findplace(place, test, temp);
							place[placenum]->FirstChild = place[placenum2];
							temp2 = placenum2;
						}
					}
					else if (j == num - 1){
						if (redundance(place, test, temp) == 0){
							place[temp] = (PtrToNode) malloc(sizeof(struct TreeNode));
							place[temp]->FirstChild = NULL;
							place[temp]->name[0] = test[0];
							place[temp]->name[1] = test[1];
							place[temp]->NextSibling = NULL;
							place[temp2]->NextSibling = place[temp];
							temp++;
						}
						else{
							placenum2 = findplace(place, test, N);
							place[placenum2]->NextSibling = NULL;
							place[temp2]->NextSibling = place[placenum2];
						}
					}
					else{
						if (redundance(place, test, temp) == 0){
							place[temp] = (PtrToNode) malloc(sizeof(struct TreeNode));
							place[temp]->FirstChild = NULL;
							place[temp]->NextSibling = NULL;
							place[temp]->name[0] = test[0];
							place[temp]->name[1] = test[1];
							place[temp2]->NextSibling = place[temp];
							temp2 = temp;
							temp++;
						}
						else{
							placenum2 = findplace(place, test, N);
							place[temp2]->NextSibling = place[placenum2];
							temp2 = placenum2;
						}
					}
				}
				getchar();
			}
			RootID = testrootid(place, N);

			reverse(RootID, time, 0);
			for (j = N - 1; j >= 0; j--){
				if (time[j] != 0){
					height = j;
					break;
				}
			}
			printf("0");
			for (j = 1; j <= height; j++){
				printf(" %d", time[j]);
			}
			printf("\n");
			freeall(place, N);
		}
		scanf("%d %d", &N, &M);
		getchar();
	}
}

int redundance(PtrToNode *place, char *test, int temp){
	int i = 0;
	int flag = 0;
	for (i = 0; i < temp; i++){
		if (place[i]->name[0] == test[0] && place[i]->name[1] == test[1]){
			flag = 1;
		}
	}
	if (flag == 0){
		return 0; //没有重复节点
	}
	else if (flag == 1){
		return 1; //有重复节点
	}
}

PtrToNode testrootid(PtrToNode *place, int N){
	int i = 0;
	for (i = 0; i < N; i++){
		if (place[i]->name[0] == '0' && place[i]->name[1] == '1'){
			return place[i];
		}
	}
}

int findplace(PtrToNode *place, char *test, int temp){
	int i = 0;
	for (i = 0; i < temp; i++){
		if (place[i]->name[0] == test[0] && place[i]->name[1] == test[1]){
			return i;
		}
	}
}

void freeall(PtrToNode *place, int N){
	int i;
	for (i = 0; i < N; i++){
		free(place[i]);
	}
	free(place);
}

void reverse(PtrToNode RootID, int * time, int height){
	if (RootID->FirstChild == NULL){
		time[height]++;
	}
	else{
		reverse(RootID->FirstChild, time, height + 1);
	}

	if (RootID->NextSibling != NULL){
		reverse(RootID->NextSibling, time, height);
	}
}