#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	FILE * fp;
	fopen_s(&fp, "spawn.txt", "wt");

	srand(time(NULL));

	printf("이 프로그램은 학교 내에 아이템/퀴즈를 랜덤 생성 합니다.\n\n");

	int i;
	int k;
	int m;
	printf("how many items do you want to spawn? :");
	scanf_s("%d", &i, sizeof(i));
	char name[100];

	printf("how many types in there? : ");
	scanf_s("%d", &m, sizeof(m));

	printf("what is table name? : ");
	scanf_s("%s", name, 100);


	double x;
	double y;


	for (int j = 0; j < i; j++) {
		x = rand() % 12564 + 9310;
		x = x / 1000000;
		y = rand() % 10922 + 318451;
		y = y / 1000000;
		k = rand() % m + 1;
		fprintf(fp, "insert into %s values('%d','%d','%lf','%lf');", name,j + 1, k, 36 + x, 129 + y);

	}


}