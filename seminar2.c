#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Calculator {
	char* serie;
	float pret;
	int nrPorturi;

};
struct Calculator initializare(const char* serie, float pret, int nrPorturi) {
	struct Calculator c;
	c.serie = (char*)malloc(sizeof(char) * (strlen(serie) + 1));
	strcpy(c.serie, serie);
	c.nrPorturi = nrPorturi;
	c.pret = pret;
	return c;
}

void afisareCalculator(struct Calculator c) {
	printf(" Calculator are seria %s, costa %5.2f, si are %d porturi\n", c.serie, c.pret, c.nrPorturi);
}
//Functie care copiaza primele n elemente 
struct Calculator* copiazaNCalculatoare(struct Calculator* calculatoare, int nrCalculatoare, int nrCalculatoareCopiate) {
	struct Calculator* copiate = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoareCopiate);
	for (int i = 0; i < nrCalculatoareCopiate; i++) {
		copiate[i] = calculatoare[i];//shallow coopy probleme dezalocare
		copiate[i].serie = (char*)malloc(sizeof(char) * (1 + strlen(calculatoare[i].serie)));//am alocat un nou spatiu
		strcpy(copiate[i].serie, calculatoare[i].serie);
		//deep copy 

	}
	return copiate;
}
struct Calculator* copiazaCalculatoareCuMultePorturi(struct Calculator* calculatoare, int nrCalculatoare, int pragNrPorturi, int* nrCalculatoarePorturi) {
	*nrCalculatoarePorturi = 0;
	for (int i = 0; i < nrCalculatoare; i++)
	{
		if (calculatoare[i].nrPorturi > pragNrPorturi)
		{
			(*nrCalculatoarePorturi)++;

		}

	}

	struct Calculator* v = (struct Calculator*)malloc(sizeof(struct Calculator) * (*nrCalculatoarePorturi));
	int k = 0;
	for (int i = 0; i < nrCalculatoare; i++)
	{
		if (calculatoare[i].nrPorturi > pragNrPorturi) {
			v[k++] = initializare(calculatoare[i].serie, calculatoare[i].pret, calculatoare[i].nrPorturi);

		}

	}
	return v;
}



void afisareVectorCalculatoare(struct Calculator* vector, int nrCalculatoare) {
	if (nrCalculatoare > 0 && vector != NULL)
		for (int i = 0; i < nrCalculatoare; i++)
			afisareCalculator(vector[i]);
}
void Dezalocare(struct Calculator** vector, int* dim) {
	for (int i = 0; i < (*dim); i++)
	{
		free((*vector)[i].serie);
	}
	free(*vector);
	*vector = NULL;
	*dim = 0;
}

void main() {
	//int v[10];//alocat static pe stack ocupa 40 de octeti
	//int* v1;//adesa catre primul element care ocupa 4 sau 8 
	int nrCalculatoare = 5;
	struct Calculator* calculatoare = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoare);
	for (int i = 0; i < nrCalculatoare; i++) {
		calculatoare[i] = initializare("1234567890", i * 20 + 10, i + 1);

	}
	int nrCalculatoareCopiate = 3;
	afisareVectorCalculatoare(calculatoare, nrCalculatoare);
	struct Calculator* calculatoareCopiate = copiazaNCalculatoare(calculatoare, nrCalculatoare, nrCalculatoareCopiate);
	afisareVectorCalculatoare(calculatoare, nrCalculatoare);
	int nrCalculatoarePorturi = 0;
	struct Calculator* calculatoarePorturi = copiazaCalculatoareCuMultePorturi(calculatoare, nrCalculatoare, 3, &nrCalculatoarePorturi);
	printf("\n\n\n");
	afisareVectorCalculatoare(calculatoarePorturi, nrCalculatoarePorturi);

}