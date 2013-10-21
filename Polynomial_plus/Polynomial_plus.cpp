#include<stdio.h>
#include<stdlib.h>

typedef struct Node *Polynomial;

struct Node{
	int Coefficient;
	int Exponent;
	Polynomial Next;
};

void AddPolynomial(const Polynomial Poly1, const Polynomial Poly2, Polynomial PolySum);
void showPolynomial(const Polynomial Poly);

int main(void){
	struct Node P0, P1, P2, P3;
	P0.Next = &P1;
	P1.Coefficient = 10;
	P1.Exponent = 1000;
	P1.Next = &P2;
	P2.Coefficient = 5;
	P2.Exponent = 14;
	P2.Next = &P3;
	P3.Coefficient = 1;
	P3.Exponent = 1;
	P3.Next = NULL;
	struct Node P9, P4, P5, P6, P7;
	P9.Next = &P4;
	P4.Coefficient = 3;
	P4.Exponent = 1900;
	P4.Next = &P5;
	P5.Coefficient = -2;
	P5.Exponent = 1492;
	P5.Next = &P6;
	P6.Coefficient = 11;
	P6.Exponent = 1;
	P6.Next = &P7;
	P7.Coefficient = 5;
	P7.Exponent = 0;
	P7.Next = NULL;
	struct Node P8;
	Polynomial Poly1 = &P0;
	Polynomial Poly2 = &P9;
	showPolynomial(Poly1);
	showPolynomial(Poly2);
	Polynomial PolySum = &P8;	
	AddPolynomial(Poly1, Poly2, PolySum);
	showPolynomial(PolySum);
	getchar();
	return 0;
}

void showPolynomial(Polynomial Poly){
	Polynomial tempPoly = Poly->Next;
	while (tempPoly != NULL){
		printf("%d %d\n", tempPoly->Coefficient, tempPoly->Exponent);
		tempPoly = tempPoly->Next;
	}
}

void AddPolynomial(const Polynomial Poly1, const Polynomial Poly2, Polynomial PolySum){
	int temp1 = -1;
	int temp2 = -1;
	Polynomial tempPoly1 = Poly1->Next;
	Polynomial tempPoly2 = Poly2->Next;
	Polynomial tempPoly = (Polynomial) malloc(sizeof(struct Node));
	if (tempPoly == NULL)
		exit(-1);
	PolySum->Next = tempPoly;
	while (!(tempPoly1 == NULL && tempPoly2 == NULL)){
		if (tempPoly1 == NULL){
			tempPoly->Coefficient = tempPoly2->Coefficient;
			tempPoly->Exponent = tempPoly2->Exponent;
			tempPoly2 = tempPoly2->Next;
		}
		else if (tempPoly2 == NULL){
			tempPoly->Coefficient = tempPoly1->Coefficient;
			tempPoly->Exponent = tempPoly1->Exponent;
			tempPoly1 = tempPoly1->Next;
		}
		else{
			temp1 = tempPoly1->Exponent;
			temp2 = tempPoly2->Exponent;
			if (temp1 > temp2){
				tempPoly->Coefficient = tempPoly1->Coefficient;
				tempPoly->Exponent = tempPoly1->Exponent;
				tempPoly1 = tempPoly1->Next;
			}
			else if (temp1 < temp2){
				tempPoly->Coefficient = tempPoly2->Coefficient;
				tempPoly->Exponent = tempPoly2->Exponent;
				tempPoly2 = tempPoly2->Next;
			}
			else{
				tempPoly->Coefficient = tempPoly1->Coefficient + tempPoly2->Coefficient;
				tempPoly->Exponent = tempPoly1->Exponent;
				tempPoly1 = tempPoly1->Next;
				tempPoly2 = tempPoly2->Next;
			}
		}
		if (tempPoly1 == NULL && tempPoly2 == NULL)
			break;
		tempPoly->Next = (Polynomial) malloc(sizeof(struct Node));
		if (tempPoly == NULL)
			exit(-1);
		tempPoly = tempPoly->Next;
		tempPoly->Next = NULL;
	}
}