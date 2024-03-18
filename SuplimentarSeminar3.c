#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
struct Laptop {
	int id;
	char* nume;
	float pret;


};
struct Laptop* adauga(struct Laptop* vector, struct Laptop laptop, int* nrlap) {
	struct Laptop* copie = (struct Laptop*)malloc(sizeof(struct Laptop) * ((*nrlap) + 1));
	copie[(*nrlap)] = laptop;
	for (int i = 0; i < (*nrlap); i++) {
		copie[i] = vector[i];
	}

	if (vector)
		free(vector);
	(*nrlap)++;
	return copie;
}

struct Laptop* citireFisier(const char* numefisier, int* nrlap) {
	struct Laptop* vector = NULL;
	FILE* f = fopen(numefisier, "r");
	if (f == NULL) printf("fisierul nu se deschide");
	else {
		*nrlap = 0;
		char buffer[100];
		while (fgets(buffer, 99, f)) {
			struct Laptop laptop;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			laptop.id = atoi(token);
			token = strtok(NULL, delimitator);
			laptop.nume = (char*)malloc(sizeof(char) * (1 + strlen(token)));
			strcpy(laptop.nume, token);
			token = strtok(NULL, delimitator);
			laptop.pret = atof(token);

			vector = adauga(vector, laptop, nrlap);

		}
		fclose(f);
	}

	return vector;
}
void afisarelaptop(struct Laptop* laptop) {
	printf("Laptopul % s cu id-ul %i are pretul de %.2f\n", laptop->nume, laptop->id, laptop->pret);

}
void afisareVectorLaptopuri(struct Laptop* vector, int nrlap) {
	for (int i = 0; i < nrlap; i++)
		afisarelaptop(&vector[i]);

}
void idCautat(struct Laptop* laptopuri, int nrlap, int idCautat) {

	int ok = 0;
	for (int i = 0; i < nrlap; i++)
		if (laptopuri[i].id == idCautat)
		{
			ok = 1;
			afisarelaptop(&laptopuri[i]);
			break;
		}
	if (!ok)
	{
		struct Laptop laptop;
		laptop.id = -1;
		laptop.nume = (char*)malloc(sizeof(char) * (1 + strlen("N/A")));
		strcpy(laptop.nume, "N/A");
		laptop.pret = 0;
		afisarelaptop(&laptop);
		free(laptop.nume);
	}
}
void dezalocare(struct Laptop** laptop, int* nrlap) {
	for (int i = 0; i < (*nrlap); i++)
		free((*laptop)[i].nume);
	free(*laptop);
	(*laptop) = NULL;
	*nrlap = 0;
}
void main() {
	int nrlap = 0;
	struct Laptop* laptopuri = NULL;
	laptopuri = citireFisier("laptopuri.txt", &nrlap);
	afisareVectorLaptopuri(laptopuri, nrlap);
	idCautat(laptopuri, nrlap, 2);
	dezalocare(&laptopuri, &nrlap);
}