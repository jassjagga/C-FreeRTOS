#include<stdlib.h>
#include<string.h>
#include <stdio.h>

struct person_struct {
	char first_name[30];
	char last_name[30];
	char city_name[30];
};

//database of 100 people
typedef struct person_struct person_t;
person_t dbasepeople[100];

//comparetor for qsort function.
int compare(const void *pa, const void *pb) {
	char *Ina = ((person_t*) pa)->last_name;
	char *Inb = ((person_t*) pb)->last_name;
	return strcmp(Ina, Inb);
}

int main(void) {

	size_t ctr = 0;
	FILE *fp;
	fp = fopen("file.txt", "r");
	if (fp == NULL) {
		printf("\n Cannot open the file \n");
		exit(0);
	}

	char str1[30], str2[30], str3[30];

	while (fgetc(fp) != EOF) {
		fscanf(fp, "%s %s %s", str1, str2, str3);
		strcpy(dbasepeople[ctr].first_name, str1);
		strcpy(dbasepeople[ctr].last_name, str2);
		strcpy(dbasepeople[ctr].city_name, str3);

		ctr++;

	}

	printf("Before sorting \n \n");

	for (int j = 0; j < ctr; j++) {
		printf("%d %s %s %s \n", j, dbasepeople[j].last_name,
				dbasepeople[j].first_name, dbasepeople[j].city_name);
	}

	//Q-sort function
	qsort(dbasepeople, ctr, sizeof(person_t), compare);

	printf("After sorting\n \n");

	for (int j = 0; j < ctr; j++) {
		printf("%d %s %s %s \n", j, dbasepeople[j].last_name,
				dbasepeople[j].first_name, dbasepeople[j].city_name);
	}

	return 0;
}
