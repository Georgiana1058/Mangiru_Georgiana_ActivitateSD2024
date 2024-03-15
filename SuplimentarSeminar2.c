#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct Politist {
	char* nume;
	int varsta;
	int grade;

};
struct Politist initializare(const char* nume, int varsta, int grade) {
	struct Politist politist;
	politist.varsta = varsta;
	politist.grade = grade;
	politist.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(politist.nume, nume);
	return politist;

}
void afisarePolitist(struct Politist politist) {
	if (politist.nume != NULL) {
		printf("Nume: %s\n", politist.nume);
	}
	printf("Varsta:%i\n", politist.varsta);
	printf("Grade:%i\n", politist.grade);
}
void afisareSectiePolitie(struct Politist* politisti, int nrpolitisti) {
	if (nrpolitisti > 0 && politisti != NULL)
	{
		for (int i = 0; i < nrpolitisti; i++)
		{
			afisarePolitist(politisti[i]);
		}
	}
}
void dezalocare(struct Politist** politisti, int* nrpolitisti) {

	if (politisti != NULL) {
		for (int i = 0; i < (*nrpolitisti); i++)
			free((*politisti)[i].nume);
		free(*politisti);
		*politisti = NULL;
		*nrpolitisti = 0;
	}
}
struct Politist* copiazaNpolitisti(struct Politist* politisti, int nrPolitistiCopiati) {
	struct Politist* politist = (struct Politist*)malloc(sizeof(struct Politist) * nrPolitistiCopiati);

	for (int i = 0; i < nrPolitistiCopiati; i++) {
		//politist[i].varsta = politisti[i].varsta;
		//politist[i].grade = politisti[i].grade;
		politist[i] = politisti[i];
		politist[i].nume = (char*)malloc(sizeof(char) * (1 + strlen(politisti[i].nume)));
		strcpy(politist[i].nume, politisti[i].nume);
	}
	return politist;
}
struct Politist* politistiCuNrMinDeGrade(struct Politist* politisti, int nrpolitisti, int nrgrademin, int* nrpolcunrmindegrade) {
	*nrpolcunrmindegrade = 0;
	for (int i = 0; i < nrpolitisti; i++) {
		if (politisti[i].grade > nrgrademin)
			(*nrpolcunrmindegrade)++;
	}
	struct Politist* pol = (struct Politist*)malloc(sizeof(struct Politist) * (*nrpolcunrmindegrade));
	int k = 0;
	for (int i = 0; i < nrpolitisti; i++) {
		if (politisti[i].grade > nrgrademin)
			pol[k++] = initializare(politisti[i].nume, politisti[i].varsta, politisti[i].grade);
	}
	return pol;
}
//Cotenarea a doi vectori
struct Politist* concatenare(struct Politist* pol1, struct Politist* pol2, int lung1, int lung2, int* lung) {
	*lung = 0;
	*lung = lung1 + lung2;
	struct Politist* pol = (struct Politist*)malloc(sizeof(struct Politist) * (*lung));
	for (int i = 0; i < lung1; i++) {
		pol[i] = pol1[i];
	}
	for (int i = 0; i < lung2; i++) {
		pol[i + lung1] = pol2[i];
	}
	return pol;
}
void main() {
	int nrPolitisti = 5;
	struct Politist* politisti = (struct Politist*)malloc(sizeof(struct Politist) * nrPolitisti);
	for (int i = 0; i < nrPolitisti; i++)
		politisti[i] = initializare("Georgel", i + 18, i + 1);
	afisareSectiePolitie(politisti, nrPolitisti);
	int nrPolCop = 2;
	struct Politist* politist = copiazaNpolitisti(politisti, nrPolCop);
	printf("\n");
	afisareSectiePolitie(politist, nrPolCop);
	printf("\n");
	int nrpolcunrmindegrade = 0;
	struct Politist* pol = politistiCuNrMinDeGrade(politisti, nrPolitisti, 2, &nrpolcunrmindegrade);
	afisareSectiePolitie(pol, nrpolcunrmindegrade);
	printf("\n");
	int lung = 0;
	struct Politist* con = concatenare(politist, pol, nrPolCop, nrpolcunrmindegrade, &lung);
	afisareSectiePolitie(con, lung);
	dezalocare(&politisti, &nrPolitisti);
	dezalocare(&politist, &nrPolCop);
	dezalocare(&pol, &nrpolcunrmindegrade);

}