#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

void MergeSort(int * list);

int N;

int main(void){
	int i;
	scanf("%d", &N);
	while (N != 0){
		int * list = (int *) malloc(sizeof(int) * N);
		if (list == NULL)
			exit(-1);
		for (i = 0; i < N; i++)
			scanf("%d", &list[i]);
		MergeSort(list);
		printf("%d", list[0]);
		for (i = 1; i < N; i++)
			printf(" %d", list[i]);
		printf("\n");
		scanf("%d", &N);
	}
	return 0;
}

void MergeSort(int * list){
	int gap = 1;
	int* tmp = (int *) malloc(sizeof(int) * N);
	if (tmp == NULL)
		exit(-1);
	do{
		int i = 0;
		int posit = 0;
		while (posit < N){
			int left = posit;
			int right = posit + gap;
			int upbound;
			if (posit + 2 * gap < N)
				upbound = posit + 2 * gap;
			else
				upbound = N;
			while (left < posit + gap && right < upbound){
				if (list[left] < list[right])
					tmp[i++] = list[left++];
				else
					tmp[i++] = list[right++];
			}
			if (left == posit + gap){
				while (right < upbound){
					tmp[i++] = list[right++];
				}
			}
			else if (right == upbound){
				while (left < posit + gap){
					tmp[i++] = list[left++];
				}
			}
			posit = upbound;
		}
		for (i = 0; i < N; i++){
			list[i] = tmp[i];
		}
		gap *= 2;
	} while (gap < N);
}